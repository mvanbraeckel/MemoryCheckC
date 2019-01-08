/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 02/03/2018
 * memcheck.h
    Header file for memcheck.c functions that replace normal ones
    Also prototypes the replacement functions
 */

/* Included Libraries */
#include <stdio.h>
#include <stdlib.h>

#ifndef MEMCHECK_H
#define MEMCHECK_H

/* Redefine Functions */
#define malloc( size )         memcheck_malloc( size, __FILE__, __LINE__ )
#define free( ptr )            memcheck_free( ptr, __FILE__, __LINE__ )
#define calloc( nmemb, size )  memcheck_calloc( nmemb, size, __FILE__, __LINE__ )
#define realloc( ptr, size )   memcheck_realloc( ptr, size, __FILE__, __LINE__ )
#define main()                 memcheck_main()

/* Function Prototypes */
void *memcheck_malloc( size_t size, char* file, int line );
void memcheck_free( void *ptr, char* file, int line );
void *memcheck_calloc( size_t nmemb, size_t size, char* file, int line );
void *memcheck_realloc( void *ptr, size_t size, char* file, int line );
int memcheck_main(); /* doesn't need the __FILE__ and __LINE__ arguments */

#endif
