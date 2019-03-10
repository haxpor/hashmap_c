#include "hashmap_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "MurmurHash3.h"

/// when the number of values added into itself
/// exceed LOAD_FACTOR of current number of values element added
/// then it will expand its memory space in *double* each time
///
/// default initial number of and load factor taken from
/// what Java uses in its implementation of Hashmap class
/// See https://javaconceptoftheday.com/initial-capacity-and-load-factor-of-hashmap-in-java/
#define LOAD_FACTOR 0.75f

/// number of available buckets initially allocated
/// similarly as commented on top of LOAD_FACTOR
#define INITIAL_ALLOC 16

/// this should be aligned with what defined in header file
/// defined here to avoid pollute user's code with what defined in header file
/// this size included null-terminated character
#define KEY_SIZE 32

///
/// init default
///
/// \param h hashmap to initialize
/// \param stride number of bytes for individual item
///
static void init_defaults(hashmapc* h, unsigned int stride);

///
/// Expand then rehash all key-value items of hashmap after expand to `new_size`.
/// This function will extend the memory of input hashmap by doubling it from current capacity.
/// Then rehash all the items then store it in new memory space.
///
/// Note: When capacity size changed, hashing needs to be re-calculate.
///
/// \param h input hashmap to extend its backing memory space and rehash all items
///
static void erehash(hashmapc* h);

///
/// free hashmap's memory
///
/// \param h input hashmap to free it's mem space
///
static void free_mem(hashmapc* h);

void init_defaults(hashmapc* h, unsigned int stride)
{
  h->stride = stride;
  h->size = 0;
  h->msize = INITIAL_ALLOC;

  // allocate memory for its element wrapper, and actual backing memory space
  h->mem = malloc(sizeof(hashmapc_element) * INITIAL_ALLOC);
  for (int i=0; i<h->msize; ++i)
  {
    hashmapc_element* elem_ptr = h->mem + i;
    elem_ptr->val = malloc(h->stride);

    elem_ptr->is_set = 0;
    memset(elem_ptr->key, 0, KEY_SIZE);
  }
}

void erehash(hashmapc* h)
{
  // this will require around double of memory usage
  // as it needs to make a copy of current hashmap of N items then double it
  // technically it could be N/2 + N; former and new one

  // calculate new size
  unsigned int new_size = h->msize << 1;

  // double the current size or just shift 1-bit to the left
  // hold into a new pointer, we swap it when we finish rehash all items
  hashmapc_element* elems_ptr = malloc(sizeof(hashmapc_element) * new_size);
  // should we do more on error handling here?
  if (elems_ptr != NULL)
  {
    unsigned int stride = h->stride;

    // allocate space for newly expanded elements
    for (int i=0; i<new_size; ++i)
    {
      hashmapc_element* el_ptr = elems_ptr + i;

      el_ptr->val = malloc(stride);

      el_ptr->is_set = 0;
      memset(el_ptr->key, 0, KEY_SIZE);
    }

    // rehash old item then set into new mem
    for (int i=0; i<h->msize; ++i)
    {
      // get hold of old element
      hashmapc_element* oldel_ptr = h->mem + i;
      // if it's not set yet (or empty), then skip
      if (oldel_ptr->is_set == 0)
        continue;

      // calculate new hash value for index to be put into new mem pointer
      // tehnical note about murmurhash3, see hashmapc_insert() function
      uint64_t out[2];
      // cap key length to KEY_SIZE
      size_t key_len = strlen(oldel_ptr->key) > KEY_SIZE ? KEY_SIZE : strlen(oldel_ptr->key);
      // use length of null-terminated string as the size
      MurmurHash3_x64_128(oldel_ptr->key, key_len, rand() % (uint32_t)(pow(2,32) - 1), out);

      // use new size of hashmap now for new element
      unsigned int hindex = out[1] & (new_size - 1);

#ifdef HASHMAPC_DEBUG
      printf("[REHASH] hash index: %d\n", hindex);
#endif

      // get hold of new element
      hashmapc_element* newel_ptr = elems_ptr + hindex;

      // if not set yet, then proceed to directly set
      if (newel_ptr->is_set == 0)
      {
        // deep copy from old value into new one
        memcpy(newel_ptr->val, oldel_ptr->val, h->stride);
        // mark as set for this element
        newel_ptr->is_set = 1;
        // deep copy of old key into new one
        memcpy(newel_ptr->key, oldel_ptr->key, KEY_SIZE);
      }
      // otherwise, we need to iterate to find an empty slot to set via linear probing
      else
      {
#ifdef HASHMAPC_DEBUG
        printf("[REHASH] collision found\n");
#endif
        for (int i=1; i<new_size-1; ++i)
        {
          int ii = (i + hindex) % new_size;

          // get hold of new element
          hashmapc_element* newel_ptr = elems_ptr + ii;

          if (newel_ptr->is_set == 0)
          {
#ifdef HASHMAPC_DEBUG
          printf("[REHASH] found hash index %d\n", ii);
#endif
            // deep copy from old value into new one
            memcpy(newel_ptr->val, oldel_ptr->val, h->stride);
            // mark as set for this element
            newel_ptr->is_set = 1;
            // deep copy of old key into new one
            strncpy(newel_ptr->key, oldel_ptr->key, KEY_SIZE);
            break;
          }
        }
      }
    }

    // free old mem pointer
    // note: call this first before updating its new size
    free_mem(h);

    // update new msize
    h->msize = new_size;

    // swap the mem pointer
    h->mem = elems_ptr;

#ifdef HASHMAPC_DEBUG
    printf("[REHASH] Done rehashing\n");
#endif
  }
}

void free_mem(hashmapc* h)
{
  // free its memory space
  if (h->mem != NULL)
  {
    // free its backing memory space first
    for (int i=0; i<h->msize; ++i)
    {
      hashmapc_element* elem_ptr = h->mem + i;

      free(elem_ptr->val);
      elem_ptr->val = NULL;

      elem_ptr->is_set = 0;
      memset(elem_ptr->key, 0, KEY_SIZE);
    }

    // now free itself
    free(h->mem);
    h->mem = NULL;
  }
}

hashmapc* hashmapc_new(unsigned int stride)
{
  // use random when we need to do hashing
  srand(time(NULL));

  hashmapc* out = malloc(sizeof(hashmapc));

  // init defaults
  init_defaults(out, stride);
  
  return out;
}

void hashmapc_free(hashmapc* h)
{
  // free mem
  free_mem(h);

  h->size = 0;
  h->msize = 0;
  h->stride = 0;

  // free itself
  free(h);
}

void hashmapc_insert(hashmapc* h, const char* key, void* val)
{
  // check to expand memory space
  if (h->size * 1.0f >= h->msize * 1.0f * LOAD_FACTOR)
  {
#ifdef HASHMAPC_DEBUG
    printf("exceeded LOAD_FACTOR, expand memory space\n");
#endif
    // we need to rehash all elements
    // as hashing function on new hashmap's new size will result in different index
    erehash(h);
  }

  // if there's still enough mem space to add more element
  if (h->size < h->msize)
  {
    // compute hash of input key
    // note: choose x64_128 variant as the result shows it's the fastest to work with
    // for large block of data.
    // see reference at https://github.com/aappleby/smhasher/wiki/MurmurHash3
    // 
    // possibly might be better for small block of data to work with MurmurHash2_x64_64 variant?
    uint64_t out[2];
    // cap key length to KEY_SIZE
    size_t key_len = strlen(key) > KEY_SIZE ? KEY_SIZE : strlen(key);
    // use length of null-terminated string as the size
    MurmurHash3_x64_128(key, key_len, rand() % (uint32_t)(pow(2,32) - 1), out);

    // output stored by murmurhash3 as big-endian, thus we access the lower bits part at index 1
    // mask with the current managed size of memory space to hold possible elements
    // just need integer with same size of msize to hold the data
    unsigned int index = out[1] & (h->msize - 1);

#ifdef HASHMAPC_DEBUG
    printf("[INSERT] hash index: %d\n", index);
#endif

    // get hold of such element
    hashmapc_element* elem_ptr = h->mem + index;

    // if not set yet, then proceed to directly set
    if (elem_ptr->is_set == 0)
    {
      // make a deep copy from input `val` to our backing memory space
      memcpy(elem_ptr->val, val, h->stride);
      // mark as set for this element
      elem_ptr->is_set = 1;
      // copy key to element's key (remainder of destination string will be filled with '\0'
      strncpy(elem_ptr->key, key, key_len);

      // update hashmap's size
      h->size++;
    }
    // otherwise, we need to iterate to find an empty slot to set via linear probing
    else
    {
#ifdef HASHMAPC_DEBUG
      printf("[INSERT] collision found\n");
#endif
      for (int i=1; i<h->msize-1; ++i)
      {
        int ii = (i + index) % h->msize;
        hashmapc_element* elem_ptr = h->mem + ii;
        if (elem_ptr->is_set == 0)
        {
          // make a deep copy from input `val` to our backing memory space
          memcpy(elem_ptr->val, val, h->stride);
          // mark as set for this element
          elem_ptr->is_set = 1;
          // copy key to element's key (remainder of destination string will be filled with '\0'
          strncpy(elem_ptr->key, key, key_len);

          // update hashmap's size
          h->size++;
          break;
        }
      }
    }
  }
}
