
/*
 * error.h
 *
 * Error macros
 */

#ifndef _error_h_
#define _error_h_

#include <stdio.h>
#include <stdlib.h>

#define SERROR(S) {						\
    printf ("ERROR: %s (%s:%d)\n", (S), __FILE__, __LINE__);	\
    exit (EXIT_FAILURE);					\
  }

#define LERROR(S,ERR) {						\
    printf ("ERROR: %s, error code = %d (%s:%d)\n", (S), (ERR), __FILE__, __LINE__); \
    exit (EXIT_FAILURE);					\
  }

#define ERROR(S) SERROR(S)

#endif
