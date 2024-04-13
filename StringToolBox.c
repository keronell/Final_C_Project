#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "StringToolBox.h"




char* getStrExactName(const char* msg) {
    char* str;
    char temp[MAX_STR_LEN];

    // Print the message, if any
    if (msg != NULL) {
        printf("%s", msg);
    }

    // Clear input buffer to avoid reading a leftover newline character
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // Read string from user
    if (fgets(temp, MAX_STR_LEN, stdin) == NULL) {
        return NULL;
    }

    // Remove newline character if it's read
    temp[strcspn(temp, "\n")] = '\0';

    // Allocate memory and copy the string into it
    str = (char*)malloc(strlen(temp) + 1);
    if (str == NULL) {
        return NULL; // Memory allocation failed
    }
    strcpy(str, temp);

    return str;
}

char* getDynStr(char* str)
{
    char* theStr;
    theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if (!theStr)
        return NULL;

    strcpy(theStr, str);
    return theStr;
}



char*  myGets(char* buffer, int size, FILE* fp)
{
    if (buffer != NULL && size > 0)
    {
        if (fgets(buffer, size, fp))
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            return buffer;
        }
        buffer[0] = '\0';
    }
    return NULL;
}

char* getStrExactNameFromFile(const char* msg, FILE* fp) {
    char* str;
    char temp[MAX_STR_LEN];
    if (msg) printf("%s\t", msg);
    if (myGets(temp, MAX_STR_LEN, fp) == NULL) {
        return NULL;
    }

    str = getDynStr(temp);
    return str;
}