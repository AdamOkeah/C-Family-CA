#include <stdio.h>
#include <stdlib.h>


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

    fclose(fp1);
    fclose(fp2);
}
void printFileBackwards(char *fileIn, char *fileOut);



