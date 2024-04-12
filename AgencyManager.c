#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "AgencyManager.h"



int initAgency(Agency* pAgency)
{
    if (pAgency == NULL)
        return 1;

    // Initialize agencyCounter to 0
    pAgency->agencyCounter = 0;

    // Allocate memory for agencyArr
    pAgency->agencyArr = (SpaceAgency**)malloc(sizeof(SpaceAgency*));
    if (pAgency->agencyArr == NULL)
        return 1;

    pAgency->numOfExpeditions = 0;
    if(!L_init(&(pAgency->expeditionList)))
        return 1;

    return 0;
}

int addSpaceAgency(Agency* pAgency, SpaceAgency* newAgency)
{
    if (pAgency == NULL || newAgency == NULL)
    {
        printf("Error: Invalid parameters.\n");
        return 1; // Error code
    }

    int newSize = pAgency->agencyCounter + 1;
    SpaceAgency** tempArr = (SpaceAgency**)realloc(pAgency->agencyArr, newSize * sizeof(SpaceAgency*));
    if (tempArr == NULL)
    {
        printf("Error: Memory reallocation failed.\n");
        return 1; // Error code
    }

    pAgency->agencyArr = tempArr;

    pAgency->agencyArr[pAgency->agencyCounter] = newAgency;
    pAgency->agencyCounter++;

    return 0; // Success
}

void freeAgency(Agency* pAgency) {
    if (pAgency == NULL) {
        return;
    }

    if (pAgency->agencyArr != NULL) {
        for (int i = 0; i < pAgency->agencyCounter; i++) {
            if (pAgency->agencyArr[i] != NULL) {
                freeSpaceAgency(pAgency->agencyArr[i]);
                pAgency->agencyArr[i] = NULL;
            }
        }
        free(pAgency->agencyArr);
        pAgency->agencyArr = NULL;
    }

    if (!L_free(&(pAgency->expeditionList), freeExpedition)) {
        printf("Failed to free list of expeditions.\n");
    }

    pAgency->agencyCounter = 0;
    pAgency->numOfExpeditions = 0;
}

