
/*
 * allocate.h
 *
 * Dynamic memory allocation macros
 */

#ifndef _allocate_h_
#define _allocate_h_

#include <stdio.h>
#include <stdlib.h>

#define ALLOCATE(VAR,TYPE,SIZE) \
  { \
    (VAR) = (TYPE *) calloc ((SIZE), sizeof(TYPE)); \
    if ((VAR) == NULL) { \
      fprintf (stderr, "ALLOCATE: Memory allocation failed (%s:%d) [%d]\n", __FILE__, __LINE__, (SIZE)); \
      exit (EXIT_FAILURE); \
    } \
  }


#define FREE(VAR) \
  { \
    free ((VAR)); \
    (VAR) = NULL; \
  }

#endif
