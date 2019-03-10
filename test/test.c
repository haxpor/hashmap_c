#include <stdio.h>
#include "hashmap_c.h"

#define PRINT_INFO(h) print_info(h);

#define HM_INSERT(h, key, v, v_attr1, v_attr2)	\
	v.ft_val = v_attr1;	\
	v.int_val = v_attr2;	\
	hashmapc_insert(h, key, &v);

#define HM_GETL(h, key, el_ptr)	\
	el_ptr = hashmapc_get(hm, key);	\
	if (el_ptr != NULL)	\
	{	\
		valst v = *(valst*)el_ptr;	\
		printf("-found %s with struct value .ft_val=%f, .int_val=%d\n", #key, v.ft_val, v.int_val);	\
	}	\
	else	\
	{	\
		printf("-not found %s\n", #key);	\
	}

typedef struct
{
	float ft_val;
	int int_val;
} valst;

void print_info(hashmapc* h)
{
	printf("size=%d, msize=%d, stride=%d\n", h->size, h->msize, h->stride);

	for (int i=0; i<h->msize; ++i)
	{
		hashmapc_element* elem_ptr = h->mem + i;
		if (elem_ptr->is_set > 0)
		{
			valst val = *((valst*)elem_ptr->val);
			printf("mem[%d], key='%s', .ft_val=%f, .int_val=%d, is_set=%d\n", i, elem_ptr->key, val.ft_val, val.int_val, elem_ptr->is_set);
		}
	}
	printf("\n");
}

int main (int argc, char** argv)
{
	// temporary struct to set value and insert into hashmap
	valst v;

	hashmapc* hm = hashmapc_new(sizeof(valst));

	// add initial 16 elements
	HM_INSERT(hm, "key1", v, 1.0f, 1)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key2", v, 2.0f, 2)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key3", v, 3.0f, 3)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key4", v, 4.0f, 4)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key5", v, 5.0f, 5)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key6", v, 6.0f, 6)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key7", v, 7.0f, 7)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key8", v, 8.0f, 8)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key9", v, 9.0f, 9)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key10", v, 10.0f, 10)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key11", v, 11.0f, 11)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key12", v, 12.0f, 12)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key13", v, 13.0f, 13)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key14", v, 14.0f, 14)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key15", v, 15.0f, 15)
	PRINT_INFO(hm)
	HM_INSERT(hm, "key16", v, 16.0f, 16)
	PRINT_INFO(hm)

	const hashmapc_element* el = NULL;
	HM_GETL(hm, "key10", el)
	HM_GETL(hm, "key1000", el);	// should not found
	HM_GETL(hm, "key16", el);
	HM_GETL(hm, "key9", el);

	hashmapc_free(hm);
	hm = NULL;
  return 0;
}
