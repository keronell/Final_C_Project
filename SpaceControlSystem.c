#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SpaceControlSystem.h"


int initSystem(SpaceControlSystem* pSystem)
{
    if (pSystem == NULL)
        return 1; // Indicate error


    // Allocate memory for the array of CelestialBody pointers with initial size of 1
    pSystem->CelestialBodyArr = (CelestialBody**)malloc(sizeof(CelestialBody*));
    if (pSystem->CelestialBodyArr == NULL)
        return -1; // Indicate error

    pSystem->CelestialBodyArr[0] = NULL; // Initialize the first pointer to NULL

    // Set numOfBodies to 0
    pSystem->numOfBodies = 0;

    // Set a default sorting option
    pSystem->sortOpt = eID; // Or any other default sorting option

    initSpaceMap(&pSystem->spaceMap); // alex added it


    return 0; // Success
}

int addCelestialBody(SpaceControlSystem* pSystem, CelestialBody* newBody)
{
    if (pSystem == NULL || newBody == NULL)
    {
        printf("Error: Invalid parameters.\n");
        return -1;
    }

    // Resize the array to hold one more CelestialBody pointer
    CelestialBody** tempArr = (CelestialBody**)realloc(pSystem->CelestialBodyArr, (pSystem->numOfBodies + 1) * sizeof(CelestialBody*));
    if (tempArr == NULL)
    {
        printf("Error: Memory reallocation failed.\n");
        return -1;
    }

    pSystem->CelestialBodyArr = tempArr;
    pSystem->CelestialBodyArr[pSystem->numOfBodies] = newBody;
    pSystem->numOfBodies++;

    addCelestialBodytoMap(&pSystem->spaceMap, newBody); //adding each new body to the spaceMap
    return 0; // Success
}

void freeAllAllocatedMemory(SpaceControlSystem* pSystem) {
    if (pSystem == NULL) {
        return;
    }

    if (pSystem->CelestialBodyArr != NULL) {
        for (int i = 0; i < pSystem->numOfBodies; i++) {
            if (pSystem->CelestialBodyArr[i] != NULL) {
                freeCelestialBody(pSystem->CelestialBodyArr[i]);
                pSystem->CelestialBodyArr[i] = NULL;
            }
        }
        free(pSystem->CelestialBodyArr);
        pSystem->CelestialBodyArr = NULL;
    }
}

void printSpaceControlSystem(const SpaceControlSystem* pSystem)
{
    if (pSystem == NULL)
    {
        printf("Error: SpaceControlSystem pointer is NULL.\n");
        return;
    }

    printf("Number of Celestial Bodies: %d\n", pSystem->numOfBodies);
    printf("Celestial Bodies:\n");

    for (int i = 0; i < pSystem->numOfBodies; i++)
    {
        if (pSystem->CelestialBodyArr[i] != NULL)
        {
            printCelestialBody(pSystem->CelestialBodyArr[i]);
        }
        else
        {
            printf("Celestial Body %d: NULL\n", i);
        }
    }
}