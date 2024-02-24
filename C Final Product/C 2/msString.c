#include "msString.h"

msString msSetString(char *stringToSet) {

    long int lengthOfString = strlen(stringToSet); /* Calculate string length */
    msString string;

    /* Allocate memory for the msString*/
    if (!(string = malloc(sizeof(long int) + lengthOfString))) {
        msError("Out of memory\n");
    }
    /* Copy the length and content into the allocated memory */
    memcpy(string, &lengthOfString, sizeof(long int));
    memcpy((char*)string + sizeof(long int), stringToSet, lengthOfString);
    return string;
}


char *msGetString(msString inputString) {
    long int length; /* Extract the string length */
    memcpy(&length, inputString, sizeof(long int));
    char *output;

    /* Allocate memory for the C string, including space for the null terminator */
    if (!(output = malloc(length + 1))) {
        msError("Out of memory\n");
    }
    /* Copy the string content and null-terminate it */
    memcpy(output, (char *)inputString + sizeof(long int), length);
    output[length] = '\0';
    return output;
}


void msCopy(msString *destination, msString src) {
    long int length = msLength(src); /* Get the length of src */
    msString tempDest;

    /* Allocate memory for the new destination msString */
    if (!(tempDest = malloc((sizeof(long int) + length )))) {
        msError("Out of memory\n");
    }
    /* Copy the entire src msString, including its length prefix */
    memcpy(tempDest, src, sizeof(long int) + length);
    /* Free the old destination memory if necessary */
    if (*destination) {
        free(*destination);
    }
    *destination = tempDest; /* Update the destination pointer */
}


long int msLength(msString input) {
    return *(long int*)input;
}


void msConcatenate(msString *destination, msString src) {
    long int destLength = msLength(*destination);
    long int srcLength = msLength(src);
    long int totalLength = destLength + srcLength;

    /* Allocate new memory for the concatenated string */
    msString newDest = malloc(sizeof(long int) + totalLength);
    if (!newDest) {
        msError("Out of memory\n");
    }

    /* Copy the original destination string's length and content */
    memcpy(newDest, &totalLength, sizeof(long int));
    memcpy((char*)newDest + sizeof(long int), (char*)*destination + sizeof(long int), destLength);

    /* Append the source string content */
    memcpy((char*)newDest + sizeof(long int) + destLength, (char*)src + sizeof(long int), srcLength);

    /* Free the old destination string and update the pointer */
    free(*destination);
    *destination = newDest;
}




int msCompare(msString msString1, msString msString2) {

    if (msString1 == msString2) return 0; /* Compare memory addresseses */
    long int length1 = msLength(msString1), length2 = msLength(msString2);
    if (length1 != length2) return 1; /* Different lengths means not identical */
    /* Compare string content */
    return memcmp((char*)msString1 + sizeof(long int), (char*)msString2 + sizeof(long int), length1) == 0 ? 0 : 1;
}


int msCompareString(msString ms, char *s) {
    long len = *(long *)ms;
    size_t len_s = strlen(s);
    if (len != len_s) return 1;
    return memcmp(ms + sizeof(long), s, len) == 0 ? 0 : 1;
}

static void msError(char *errorMessage) {
    printf("Error: %s\n", errorMessage); 
    exit(EXIT_FAILURE); 
}