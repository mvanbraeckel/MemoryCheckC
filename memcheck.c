/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 02/03/2018
 * memcheck.c
    Contains all the functions required for memcheck.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================== STRUCT DECLARATIONS ========================== */
struct linked_list_struct {
  void *mem;                       /* memory pointer to hold the address that was malloc'ed */
  char* file;                      /* the name of the file from the argument "file" */
  int line_num;                    /* the line number from the argument "line" */
  struct linked_list_struct *next; /* points to the "next" item in the linked list.*/
}; typedef struct linked_list_struct List;

/* =========================== FUNCTION PROTOTYPES ========================== */
int memcheck_main();

/* ============================ GLOBAL VARIABLES ============================ */
List *g_first_item = NULL; /* Global variable to point to the first item (the start) of the list.
                             We need to use the same variable in our memcheck_free and memcheck_malloc functions,
                             but don't want to have to add it to the main function in main.c. */

/* ========================================================================== */
/* String Duplication (2): returns a pointer to a new string which is a duplicate of the string
   @param *str: Memory for the new string is obtained with malloc(3), and can be freed with free(3). */
char *strdup2( char *str ) {
  char *new;
  new = malloc( strlen(str)+1 );
  if (new) {
    strcpy( new, str );
  }
  return new;
}

/* Prints the error message for leaving an allocated memory address unfreed */
void print_list(List *list) {
  /* loops through the entire linked list */
  while(list) {
    printf("memcheck error:  memory address %p which was allocated in file \"%s\", line %d, was never freed\n", list->mem, list->file, list->line_num);
    list = list->next;  /* iterate to next item in the list */
  }
}

/* Fake main that actually runs the stuff to go through the list */
int main() {
  memcheck_main();

  /* loops through the entire linked list, printing error message if something was NOT freed */
  print_list(g_first_item);
  return 0;
}

/* ========================================================================== */

/* Allocate a new list item,
   Set its pointer to the malloc address,
   strdup (please read the Forum Thread "strdup" below now) the file value,
   and Copy the line value,
   and Set the next pointer to the value of the global variable. (sets it to "NULL" on the first call)

   Then, I'm going to make the global variable point to the new list item.
      Note: I'm also going to modify the function to actually malloc some memory (using the normal malloc command),
      store it in a temporary variable,
      and finally return it. */
void *memcheck_malloc( size_t size, char* file, int line_num ) {
  List *temp_list = malloc(sizeof(List)); /* give it memory for the structure to exist */

  temp_list->mem = malloc(size);    /* allocate enough memory (equal to the size given as a parameter) */
  temp_list->file = strdup2(file);  /* strdup(2) -- string duplicate -- the file value "__.c" */
  temp_list->line_num = line_num;   /* copy the line # value (line in "__.c") */
  temp_list->next = g_first_item;   /* now, points to the previously most recent added item to the list */

  g_first_item = temp_list;         /* now points to the new list item we just added to the list */

  return temp_list->mem;
}

/* Loop through the entire linked list (ends if = NULL)
      Check if the ptr is found in the list, if it is, then remove it by freeing the entire list item struct
      Note: Don't forget to fix the chain linking of next ptr and skip over the now removed element
            If removing the first item, must change what the global first_item List ptr points to*/
void memcheck_free( void *ptr, char* file, int line_num ) {
  List *temp, *prev;
  temp = g_first_item;
  prev = NULL;

  /* check if ptr given =NULL, then immediate outout error msg and return (can't free if doesn't exist)*/
  if(ptr == NULL) {
    printf("memcheck error:  attempting to free memory address %p in file \"%s\", line %d.\n", ptr, file, line_num);
    return;
  }

  /* loop through the linked list until it matches pointer, or reaches end
      Note: want it to hold the last item (and never further) so it won't be using NULL in the following ifs */
  while(temp->mem != ptr && temp->next != NULL) {
    prev = temp;
    temp = temp->next;
  }

  /* only free if the ptr matches an item in the linked list:
      CASE 1: first item -- so reset global
      CASE 2: otherwise, not first item (middle or last) -- jump over the current item *by setting prev next to current next */
  if(temp->mem == ptr) {

    if(prev == NULL) {  /* CASE 1: item IS first item in linked list (prev still =NULL as init orig) */
      g_first_item = temp->next;  /* reset new first item, before removing (freeing) */

    } else {            /* CASE 2: NOT the first item in linked list (thus, prev does NOT =NULL as init originally) */
      prev->next = temp->next;  /* jumps over the item, before removing (freeing) */
    }

    /* free all attributes of the item and itself */
    free(temp->mem);
    free(temp->file);
    free(temp);
    return;
  }

  /* display error msg */
  printf("memcheck error:  attempting to free memory address %p in file \"%s\", line %d.\n", ptr, file, line_num);
}

/* Same as "memcheck_malloc" but instead memcheck_"c"alloc:
    thus, same functionality, except temp_list address attribute "mem" shall hold a call to calloc instead */
void *memcheck_calloc( size_t nmemb, size_t size, char* file, int line_num ) {
  List *temp_list = malloc(sizeof(List)); /* give it some memory to exist */

  temp_list->mem = calloc(nmemb, size); /* call calloc instead of malloc to allocate memory */
  temp_list->file = strdup2(file);      /* strdup(2) -- string duplicate -- the file value "__.c" */
  temp_list->line_num = line_num;       /* copy the line # value (line in "__.c") */
  temp_list->next = g_first_item;       /* now, points to the previously most recent added item to the list */

  g_first_item = temp_list;             /* now points to the new list item we just added to the list */

  return temp_list->mem;
}

/* Searches through the entire linked list to find a match,
    If no match is found, return NULL
    Otherwise, realloc its memory to the new size
      Note: remember to update the file locate and line number (also remember to first free the old file location first) */
void *memcheck_realloc( void *ptr, size_t size, char* file, int line_num ) {
  List *temp = g_first_item;  /* create temp that's the same as the global */

  /* loops through the entire linked list */
  while(temp != NULL) {
    if(temp->mem == ptr) {  /* if it's a match */
      temp->mem = realloc(ptr, size); /* update the amount of memory it should have */

      free(temp->file);           /* must free the old file location allocated memory before... */
      temp->file = strdup2(file); /* getting the new file location (which calls a malloc in the process of string duplication) */
      temp->line_num = line_num;  /* also update the line # */

      return temp->mem;
    }

    temp = temp->next;  /* iterate to next item in list */
  }

  /* finished loop w/o finding match, thus it doesn't exist in the linked list */
  return NULL;
}
