#include "task1.h"

void printIntegers(void *ptr, int numBytes) {
    /*Cast the void pointer to an unsigned char pointer for byte-by-byte access.*/ 
    unsigned char *bytePtr = (unsigned char *)ptr;
    printf("Starting at memory address %p\n", ptr);
    int i;
    for (i = 0; i < numBytes; i++) {
        
        printf("%003d: %d\n", i+1, bytePtr[i]);
    }
}