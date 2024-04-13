#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SpaceControlSystem.h"
#include "StringToolBox.h"


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
    printf("Number of Celestial Bodies: %d\n", pSystem->numOfBodies);
    printf("Celestial Bodies:\n");

    for (int i = 0; i < pSystem->numOfBodies; i++)
    {
        if (pSystem->CelestialBodyArr[i] != NULL)
            printCelestialBody(pSystem->CelestialBodyArr[i]);
        else
            printf("Celestial Body %d: NULL\n", i);
    }
}

int saveSystemToFileTxt(const SpaceControlSystem *pSystem, const Agency *pAgency, const char *fileName)
{
    if (pSystem == NULL) {
        printf("System is not initialized! \n");
        return 1;
    }

    FILE *fp = fopen(fileName, "w");
    if (!fp) {
        printf("Cant open file ('%s') for writing.\n", fileName);
        return 1;
    }

    // Write the details of the Space Control System
    fprintf(fp, "Space Control System Details:\n");
    fprintf(fp, "Total Celestial Bodies: %d\n", pSystem->numOfBodies);
    fprintf(fp, "Sorting Option: %d\n\n", pSystem->sortOpt);

    for (int i = 0; i < pSystem->numOfBodies; i++) {
        fprintf(fp, "Celestial Body %d:\n", i + 1);
        if (pSystem->CelestialBodyArr[i] != NULL) {
            saveCelestialBodyToFileTxt(fp, pSystem->CelestialBodyArr[i]);
        } else {
            fprintf(fp, "  [Data Not Available]\n");
        }
    }
    if(saveManagerToFileTxt(pAgency,fileName)){
        printf("Failed to save Manager data to file!\n");
        return 1;
    }


    fclose(fp);
    return 0;
}

int loadSystemFromFileTxt(SpaceControlSystem *pSystem, Agency *pAgency, const char *fileName) {
    if (pSystem == NULL) {
        printf("System is not initialized! \n");
        return 1;
    }

    FILE *fp = fopen(fileName, "r");
    if (!fp) {
        printf("Cannot open file ('%s') for reading.\n", fileName);
        return 1;
    }

    char buffer[MAX_STR_LEN];
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        fclose(fp);
        return 1;
    }

    int numOfBodies;
    if (fscanf(fp, "Total Celestial Bodies: %d\n", &numOfBodies) != 1) {
        fclose(fp);
        return 1;
    }

    int sortOpt;
    if (fscanf(fp, "Sorting Option: %d\n\n", &sortOpt) != 1) {
        fclose(fp);
        return 1; // Error parsing sorting option
    }

    // Initialize the system with obtained data
    pSystem->numOfBodies = numOfBodies;
    pSystem->sortOpt = sortOpt;

    // Allocate memory for celestial bodies array
    pSystem->CelestialBodyArr = (CelestialBody**)malloc(numOfBodies * sizeof(CelestialBody*));
    if (pSystem->CelestialBodyArr == NULL) {
        fclose(fp);
        return 1; // Memory allocation failed
    }

    // Read celestial bodies
    for (int i = 0; i < numOfBodies; i++) {
        fgets(buffer, sizeof(buffer), fp); // Read header line for each body
        pSystem->CelestialBodyArr[i] = (CelestialBody*)malloc(sizeof(CelestialBody));
        if (pSystem->CelestialBodyArr[i] == NULL) {
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(pSystem->CelestialBodyArr[j]);
            }
            free(pSystem->CelestialBodyArr);
            fclose(fp);
            return 1;
        }
        loadCelestialBodyFromFile(pSystem->CelestialBodyArr[i], fp);
    }

    // Optional: Load additional system components, like agencies
    fclose(fp);
    return 0;
}
