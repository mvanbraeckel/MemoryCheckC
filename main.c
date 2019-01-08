/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 02/03/2018
 * main.c
    for making calls to malloc, free, realloc, calloc, etc. (testing memcheck.c)
 */

#include "memcheck.h"

/* real main for inputting test values (by making malloc and free calls) */
int main() {

  char *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;

  ptr1 = malloc( 1 );
  ptr2 = malloc( 31 );
  ptr3 = malloc( 37 );

  ptr4 = calloc(2, 15);
  ptr5 = calloc(3, 10);

  ptr1 = realloc(ptr1, 50);
  ptr2 = realloc(ptr2, 1);
  ptr3 = realloc(ptr3, 21);

  free( ptr1 );
  free( ptr2 );
  free( ptr3 );
  free( ptr4 );
  free( ptr5 );

  return 0;
}
