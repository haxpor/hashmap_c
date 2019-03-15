#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap_c.h"

#define PRINT_INFO(h) print_info(h);

#define HM_INSERT(h, key, v, v_attr1, v_attr2, v_attr3)	\
	v.ft_val = v_attr1;	\
	v.int_val = v_attr2;	\
  v.s_val = calloc(1, sizeof(char) * (strlen(v_attr3)+1)); \
  strncpy(v.s_val, v_attr3, strlen(v_attr3));  \
	hashmapc_insert(h, key, &v);

#define HM_GETL(h, key, vst_ptr)	\
	vst_ptr = hashmapc_get(hm, key);	\
	if (vst_ptr != NULL)	\
	{	\
		valst v = *(valst*)vst_ptr;	\
		printf("-found %s with struct value .ft_val=%f, .int_val=%d, .s_val=%s\n", #key, v.ft_val, v.int_val, v.s_val);	\
	}	\
	else	\
	{	\
		printf("-not found %s\n", #key);	\
	}

#define HM_DEL(h, key)	\
	hashmapc_delete(h, key);

typedef struct
{
	float ft_val;
	int int_val;
  char* s_val;
} valst;

/// note: only free element's internals not itself
/// as memory space is mananged by hashmapc
static void free_internals_elem(void* ptr)
{
  // convert from opaque poitner to our element pointer
  valst* v = (valst*)ptr;

  printf("free element (ft_val=%f, int_val=%d, s_val=%s)\n", v->ft_val, v->int_val, v->s_val);
  
  free(v->s_val);
  v->s_val = NULL;
}

static void print_info(hashmapc* h)
{
	printf("size=%d, msize=%d, stride=%d\n", h->size, h->msize, h->stride);

	for (int i=0; i<h->msize; ++i)
	{
		hashmapc_element* elem_ptr = h->mem + i;
		if (elem_ptr->is_set > 0)
		{
			valst val = *((valst*)elem_ptr->val);
			printf("mem[%d], key='%s', .ft_val=%f, .int_val=%d, .s_val=%s, is_set=%d\n", i, elem_ptr->key, val.ft_val, val.int_val, val.s_val, elem_ptr->is_set);
		}
	}
	printf("\n");
}

int main (int argc, char** argv)
{
	// temporary struct to set value and insert into hashmap
  // note: v will act as a placeholder to hold attribute valuese to initialize
  // each item inserting into hashmap.
  // each consecutive insert, its values will be cleared and set again for new one
  // notice s_val which is dynamically allocated and will be handled by hashmap when time to free comes
	valst v;

	hashmapc* hm = hashmapc_new(sizeof(valst));
  // set our custom free-element function
  hashmapc_set_free_internals_elem_func(hm, free_internals_elem);

	// add initial 16 elements
	HM_INSERT(hm, "key1", v, 1.0f, 1, "val1")
	PRINT_INFO(hm)

	HM_INSERT(hm, "key2", v, 2.0f, 2, "val2")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key3", v, 3.0f, 3, "val3")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key4", v, 4.0f, 4, "val4")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key5", v, 5.0f, 5, "val5")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key6", v, 6.0f, 6, "val6")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key7", v, 7.0f, 7, "val7")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key8", v, 8.0f, 8, "val8")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key9", v, 9.0f, 9, "val9")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key10", v, 10.0f, 10, "val10")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key11", v, 11.0f, 11, "val11")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key12", v, 12.0f, 12, "val12")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key13", v, 13.0f, 13, "val13")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key14", v, 14.0f, 14, "val14")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key15", v, 15.0f, 15, "val15")
	PRINT_INFO(hm)
	HM_INSERT(hm, "key16", v, 16.0f, 16, "val16")
	PRINT_INFO(hm)

	const valst* vst = NULL;
	HM_GETL(hm, "key10", vst)
	HM_GETL(hm, "key1000", vst);	// should not found
	HM_GETL(hm, "key16", vst);
	HM_GETL(hm, "key9", vst);

	HM_DEL(hm, "key9")
	HM_DEL(hm, "key4")
	HM_DEL(hm, "key1000")
	HM_DEL(hm, "key1")
	PRINT_INFO(hm)

	hashmapc_clear(hm);
	PRINT_INFO(hm)

	HM_INSERT(hm, "key1", v, 1.0f, 1, "val1")
	PRINT_INFO(hm)

	hashmapc_free(hm);
	hm = NULL;
  return 0;
}
