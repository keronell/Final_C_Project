#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "AgencyManager.h"


#define MAX_AGENCIES 10 // Define the maximum number of agencies

int initAgency(Agency* pAgency)
{
    if (pAgency == NULL)
        return 1;

    // Initialize agencyCounter to 0
    pAgency->agencyCounter = 0;

    // Allocate memory for agencyArr
    pAgency->agencyArr = (SpaceAgency**)malloc(MAX_AGENCIES * sizeof(SpaceAgency*));
    if (pAgency->agencyArr == NULL)
    {
        // Handle memory allocation failure using printf
        return 1;
    }

    // Initialize each element in agencyArr to NULL
    for (int i = 0; i < MAX_AGENCIES; i++)
    {
        pAgency->agencyArr[i] = NULL;
    }
    return 0;

    // The numOfExpeditions and expeditionList fields are not initialized here


}
