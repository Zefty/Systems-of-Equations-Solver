
/*
 * fileio.h
 *
 * File IO macros
 */

#ifndef _fileio_h_
#define _fileio_h_

#include <stdio.h>
#include <stdlib.h>

#define FOPEN(VAR,PATH,ATTRIBUTES) \
  { \
    (VAR) = fopen ((PATH), (ATTRIBUTES)); \
    if ((VAR) == NULL) { \
      fprintf (stderr, "FILEIO: %s could not be opened (%s,%d)\n", (PATH), __FILE__, __LINE__); \
      exit (EXIT_FAILURE); \
    } \
  }

#define FCLOSE(VAR) \
  { \
    fclose (VAR); \
    (VAR) = NULL; \
  }

#define SKIPLINE(VAR) \
  fscanf ((VAR), "%*[^\n] ");

#endif
