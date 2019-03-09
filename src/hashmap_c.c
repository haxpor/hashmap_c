#include "hashmap_c.h"
#include <stdlib.h>

HASHMAPC* HASHMAPC_new()
{
  HASHMAPC* out = malloc(sizeof(HASHMAPC));
  return out;
}

void HASHMAPC_free_internals(HASHMAPC* h)
{
  
}

void HASHMAPC_free(HASHMAPC* h)
{
  // free internals
  HASHMAPC_free_internals(h);

  // free itself
  free(h);
}
