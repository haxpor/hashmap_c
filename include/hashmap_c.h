#ifndef HASHMAP_C_H_
#define HASHMAP_C_H_

typedef struct
{

} HASHMAPC;

///
/// Create a new hashmap.
///
/// \return new hashmap created on heap.
///
HASHMAPC* HASHMAPC_new();

///
/// Free internals of hashmap.
/// Use this for a chance to re-create or starting over for the same hashmap instance.
///
/// \param h hashmap to be freed for its internals.
///
void HASHMAPC_free_internals(HASHMAPC* h);

///
/// Free hashmap.
///
/// \param h hashmap to be freed
///
void HASHMAPC_free(HASHMAPC* h);

#endif
