#ifndef HASHMAP_C_H_
#define HASHMAP_C_H_

///
/// Hashmap with string as key
///

typedef struct
{
  /// key associated with this element
  /// use fixed size to avoid dynamically allocated memory space in run-time
  char key[32];

  /// actual data that stored in this element
  void* val;
  
  /// 1 if this element is set
  /// 0 if this element is not set yet
  int is_set;
} hashmapc_element;

typedef struct
{
  /// currently size of filled elements
  unsigned int size;

  /// read-only
  /// internally managed already allocated memory space length
  /// it will be initially set to 16 elements by default
  unsigned int msize;

  /// memory space to hold all individual values
  hashmapc_element* mem;

  /// size in bytes for individual value element
  unsigned int stride;

  /// read-only
  /// internally managed, for seed value used in hashing function
  unsigned int seed;

  /// function pointer for freeing individual element when delete, or clear
  /// from hashmap
  void (*free_elem_func)(void* val);
} hashmapc;

///
/// Create a new hashmap.
///
/// \param stride number of bytes for individual value element
/// \return new hashmap created on heap.
///
extern hashmapc* hashmapc_new(unsigned int stride);

///
/// Free hashmap.
///
/// \param h hashmap to be freed
///
extern void hashmapc_free(hashmapc* h);

///
/// Insert a new value at key.
///
/// `val` needs to have the same size as hashmap's stride.
///
/// \param h hashmap
/// \param key pointer to null-terminated string. Accept up to 32 characters. If it's longer than that, it will cut
///            only take 32 characters in length.
/// \param val value to be added at key, it need to have the same size as of hashmap's stride
///
extern void hashmapc_insert(hashmapc* h, const char* key, void* val);

///
/// Get value from specified `key` from the first found.
///
/// \param h hashmap
/// \param key key to try to search and get associated value from
/// \return opaque pointer to found value, otherwise if not found, then NULL will be returned.
///
extern const void* hashmapc_get(hashmapc* h, const char* key);

///
/// Delete item frm `key`.
///
/// \param h hashmap
/// \param key key associated with item which will be delete
///
extern void hashmapc_delete(hashmapc* h, const char* key);

///
/// Clear hashmap.
/// This will remove all items in hashmap.
///
/// \param h hashmap
///
extern void hashmapc_clear(hashmapc* h);

///
/// Set function to free element when hashmap deletes or clears it.
/// This function accepts NULL, thus set free element function to empty and hashmap won't call it when deleting or clearing.
///
/// \param h hashmap
/// \param func function pointer with signature of void (*func)(void*) in which void* is the opaque pointer
///             to the actual element's memory space.
///
extern void hashmapc_set_free_elem_func(hashmapc* h, void (*func)(void*));

#endif
