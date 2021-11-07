#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <float.h> // for FLT_EPSILON
#include <math.h>
#include "hashmap_c/hashmap_c.h"

#ifdef NEED_PRINT
	#define PRINT_INFO(h) print_info(h);
#else
	#define PRINT_INFO(h)
#endif

#define HM_INSERT(h, key, v, v_attr1, v_attr2, v_attr3)	\
	v.ft_val = v_attr1;	\
	v.int_val = v_attr2;	\
	v.s_val = calloc(1, sizeof(char) * (strlen(v_attr3)+1)); \
	strncpy(v.s_val, v_attr3, strlen(v_attr3));  \
	hashmapc_insert(h, key, &v);

#define HM_GETL(h, key, vst_ptr)	\
	vst_ptr = hashmapc_get(h, key);	\
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

static bool equal_valst(valst*, valst*);

static void validate_item(const hashmapc* h, const char* key, valst* chk_item)
{
	assert(h != NULL);
	void* item = hashmapc_get(h, key);

	assert((item == NULL && chk_item == NULL) || (item != NULL && chk_item != NULL));

	if (item != NULL && chk_item != NULL)
	{
		valst* casted_item = (valst*)item;
		bool chk_b = equal_valst(casted_item, chk_item);
		assert(chk_b);
	}
}

static void validate_size(const hashmapc* h, int target_size)
{
	assert(h != NULL);
	printf("h size=%d, target_size=%d\n", h->size, target_size);
	assert(h->size == target_size);
}

static bool equal_valst(valst* a, valst* b)
{
	if (a == NULL && b == NULL)
		return true;
	if ((a == NULL && b != NULL) ||
		(a != NULL && b == NULL))
		return false;
	
	if (fabs(a->ft_val - b->ft_val) >= FLT_EPSILON)	
		return false;
	if (a->int_val != b->int_val)
		return false;
	if (a->s_val == NULL && b->s_val == NULL)
		return true;
	if ((a->s_val != NULL && b->s_val == NULL) ||
		(a->s_val == NULL && b->s_val != NULL))
		return false;
	if (a->s_val != NULL && b->s_val != NULL)
		return strcmp(a->s_val, b->s_val) == 0;
	// if goes to this line, then it is all equal
	return true;
}

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
	validate_item(hm, "key1", &(valst){1.0f, 1, "val1"});
	validate_size(hm, 1);

	HM_INSERT(hm, "key2", v, 2.0f, 2, "val2")
	PRINT_INFO(hm)
	validate_item(hm, "key2", &(valst){2.0f, 2, "val2"});
	validate_size(hm, 2);

	HM_INSERT(hm, "key3", v, 3.0f, 3, "val3")
	PRINT_INFO(hm)
	validate_item(hm, "key3", &(valst){3.0f, 3, "val3"});
	validate_size(hm, 3);

	HM_INSERT(hm, "key4", v, 4.0f, 4, "val4")
	PRINT_INFO(hm)
	validate_item(hm, "key4", &(valst){4.0f, 4, "val4"});
	validate_size(hm, 4);

	HM_INSERT(hm, "key5", v, 5.0f, 5, "val5")
	PRINT_INFO(hm)
	validate_item(hm, "key5", &(valst){5.0f, 5, "val5"});
	validate_size(hm, 5);

	HM_INSERT(hm, "key6", v, 6.0f, 6, "val6")
	PRINT_INFO(hm)
	validate_item(hm, "key6", &(valst){6.0f, 6, "val6"});
	validate_size(hm, 6);

	HM_INSERT(hm, "key7", v, 7.0f, 7, "val7")
	PRINT_INFO(hm)
	validate_item(hm, "key7", &(valst){7.0f, 7, "val7"});
	validate_size(hm, 7);

	HM_INSERT(hm, "key8", v, 8.0f, 8, "val8")
	PRINT_INFO(hm)
	validate_item(hm, "key8", &(valst){8.0f, 8, "val8"});
	validate_size(hm, 8);

	HM_INSERT(hm, "key9", v, 9.0f, 9, "val9")
	PRINT_INFO(hm)
	validate_item(hm, "key9", &(valst){9.0f, 9, "val9"});
	validate_size(hm, 9);

	HM_INSERT(hm, "key10", v, 10.0f, 10, "val10")
	PRINT_INFO(hm)
	validate_item(hm, "key10", &(valst){10.0f, 10, "val10"});
	validate_size(hm, 10);

	HM_INSERT(hm, "key11", v, 11.0f, 11, "val11")
	PRINT_INFO(hm)
	validate_item(hm, "key11", &(valst){11.0f, 11, "val11"});
	validate_size(hm, 11);

	HM_INSERT(hm, "key12", v, 12.0f, 12, "val12")
	PRINT_INFO(hm)
	validate_item(hm, "key12", &(valst){12.0f, 12, "val12"});
	validate_size(hm, 12);

	HM_INSERT(hm, "key13", v, 13.0f, 13, "val13")
	PRINT_INFO(hm)
	validate_item(hm, "key13", &(valst){13.0f, 13, "val13"});
	validate_size(hm, 13);

	HM_INSERT(hm, "key14", v, 14.0f, 14, "val14")
	PRINT_INFO(hm)
	validate_item(hm, "key14", &(valst){14.0f, 14, "val14"});
	validate_size(hm, 14);

	HM_INSERT(hm, "key15", v, 15.0f, 15, "val15")
	PRINT_INFO(hm)
	validate_item(hm, "key15", &(valst){15.0f, 15, "val15"});
	validate_size(hm, 15);

	HM_INSERT(hm, "key16", v, 16.0f, 16, "val16")
	PRINT_INFO(hm)
	validate_item(hm, "key16", &(valst){16.0f, 16, "val16"});
	validate_size(hm, 16);

	const valst* vst = NULL;
	HM_GETL(hm, "key10", vst)
	validate_item(hm, "key10", vst);

	HM_GETL(hm, "key1000", vst);	// should not found
	validate_item(hm, "key1000", NULL);

	HM_GETL(hm, "key16", vst);
	validate_item(hm, "key16", vst);

	HM_GETL(hm, "key9", vst);
	validate_item(hm, "key9", vst);

	// -- deletion
	HM_DEL(hm, "key9")
	validate_size(hm, 15);
	validate_item(hm, "key9", NULL);

	HM_DEL(hm, "key4")
	validate_size(hm, 14);
	validate_item(hm, "key4", NULL);

	HM_DEL(hm, "key1000")	// non-existing key
	validate_size(hm, 14);	// size still the same
	validate_item(hm, "key1000", NULL);

	HM_DEL(hm, "key1")
	validate_size(hm, 13);
	valst* t = hashmapc_get(hm, "key1");
	validate_item(hm, "key1", NULL);	
	PRINT_INFO(hm)

	hashmapc_clear(hm);
	PRINT_INFO(hm)
	validate_size(hm, 0);

	HM_INSERT(hm, "key1", v, 1.0f, 1, "val1")
	PRINT_INFO(hm)
	validate_item(hm, "key1", &(valst){1.0f, 1, "val1"});
	validate_size(hm, 1);

	hashmapc_free(hm);
	hm = NULL;
	return 0;
}
