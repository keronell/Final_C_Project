#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "StringToolBox.h"




char* getStrExactName(const char* msg)
{
    char* str;
    char temp[MAX_STR_LEN];
    printf("%s\t", msg);
    myGets(temp, MAX_STR_LEN,stdin);

    str = getDynStr(temp);
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
    if (msg) printf("%s\t", msg); // Optionally print a message if provided (can be NULL if not needed)
    if (myGets(temp, MAX_STR_LEN, fp) == NULL) {
        return NULL; // Failed to read string
    }

    str = getDynStr(temp);
    return str;
}