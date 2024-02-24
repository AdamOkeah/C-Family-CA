#include <stdio.h>
#include <stdlib.h>
#include "msString.h"


void printIntegers(void *ptr, int numBytes);

void printFileBackwards(char *fileIn, char *fileOut);



void printIntegers(void *ptr, int numBytes) {
    /* Cast the void pointer to an int pointer for integer-by-integer access. */
    int *intPtr = (int *)ptr;
    printf("Starting at memory address %p\n", ptr);
    
    int i;
    for (i=0; i < numBytes; i++) {
        printf("%03d: %d\n", i + 1, intPtr[i]);
    }
}

void printFileBackwards(char *fileIn, char *fileOut) {
    FILE *fp1 = fopen(fileIn, "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Unable to open file %s\n", fileIn);
        exit(EXIT_FAILURE);
    }

    FILE *fp2 = fopen(fileOut, "w");
    if (fp2 == NULL) {
        fprintf(stderr, "Unable to open file %s\n", fileOut);
        fclose(fp1); /*Close the opened file before exiting*/
        exit(EXIT_FAILURE);
    }

    fseek(fp1, 0, SEEK_END);
    long fileSize = ftell(fp1);

    long pos;
    for (pos = fileSize - 1; pos >= 0; pos--) {
        fseek(fp1, pos, SEEK_SET);
        int ch = fgetc(fp1);
        if (ch != '%') {
            fputc(ch, fp2);
        }
    }



    fclose(fp1); /*Fix memory leak*/
    fclose(fp2);
    printf("File Writing Complete\n");
}




int main(int argc, char *argv[]){


    printf("printIntegers Test 1\n\n");

    int num[4] = {12, 43, 29, 56};
    void *numptr = &num;
    
    printIntegers(numptr, 4);

    
    printf("printIntegers Test 2\n\n");
    int numbers[] = {1, 10, 28};
    printIntegers(numbers, 3);


    printf("\n\nTask 2 Test Starting.\n\n");
    printFileBackwards(argv[1], argv[2]);
    printf("Task 2 Test Completed. Check FileOut.\n\n");




    printf("Task 3: msString Test Output\n\n");

    msString ms = msSetString("Hello");
    msString ms2 = msSetString(" World!");
    msString mscopy = NULL;

printf("String |%s| is %ld characters long (%p).\n",
       msGetString(ms), msLength(ms), (void*)ms);
msCopy(&mscopy, ms);
printf("Copied string |%s| is %ld characters long (%p).\n",
       msGetString(mscopy), msLength(mscopy), (void*)mscopy);



printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
printf("Compare ms with ms2: %d\n", msCompare(ms, ms2));
printf("Compare ms with 'Hello': %d\n", msCompareString(ms, "Hello"));
printf("Compare ms with 'HelloX': %d\n", msCompareString(ms, "HelloX"));
printf("Compare ms with 'Hella': %d\n", msCompareString(ms, "Hella"));
msConcatenate(&mscopy, ms2);
printf("Concatenated string |%s| is %ld characters long (%p).\n",
       msGetString(mscopy), msLength(mscopy), (void*)mscopy);
    
return 0;

free(ms);
free(ms2);
free(msCopy);


}

