# MemoryCheckC
For C programs: this checks and alerts the user of any allocated memory not being freed and its location via file and line number upon exiting. It also alerts the user with file and line number when they try to free memory address that has not been allocated any memory.

*Do not use code from this or copy any aspects without explicit permission from creator*

Use the makefile to compile and view the executable file names to actually run the programs

# main.c
    Tester to show functionality of the memory checker program
    
# memcheck.c
    Redefines malloc, calloc, realloc, free, and main function to memcheck versions, thus allowing it to use a linked list structure to keep track of memory allocations and provide file and line number for errors with memory allocation and freeing.
