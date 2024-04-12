#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "AgencyManager.h"
#include "FileManager.h"


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

int getNumOfExpeditions()
{

}

Expedition* findExpeditionById(Agency* pManager, int id)
{
    if (pManager == NULL) {
        printf("Agency pointer is NULL.\n");
        return NULL;
    }

    NODE* currentNode = pManager->expeditionList.head.next;
    while (currentNode != NULL) {
        Expedition* expedition = (Expedition*) currentNode->key;
        if (expedition != NULL && expedition->id == id) {
            return expedition;
        }
        currentNode = currentNode->next;
    }
    return NULL;

}

int		saveManagerToFile(const Agency* pAgency, const char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "wb");
    if (!fp) {
        printf("Error open Agency file to write\n");
        return 0;
    }

    if (!writeIntToFile(pAgency->agencyCounter, fp, "Error write number of agencies!\n"))
        return 0;


    for (int i = 0; i < pAgency->agencyCounter; i++)
    {
        if (!saveSpaceAgencyToFile(pAgency->agencyArr[i], fp))
            return 0;
    }

    if (!writeIntToFile(pAgency->numOfExpeditions, fp, "Error write number of expeditions!\n"))
        return 0;

    NODE* currentNode = pAgency->expeditionList.head.next; // Starting from the first expedition
    while (currentNode != NULL) {
        if (!saveExpeditionToFile(currentNode->key, fp)) {
            printf("Error writing expedition to file!\n");
            fclose(fp);
            return 0;
        }
        currentNode = currentNode->next;
    }

    fclose(fp);
    return 1;
}

int loadManagerFromFile(Agency* pAgency, const char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "rb");  // Open file in binary read mode
    if (!fp) {
        printf("Error open Agency file to read\n");
        return 0;
    }

    // Read number of agencies
    int agencyCount = readIntFromFile(fp, "Error read number of agencies!\n");
    if (agencyCount < 0) {
        fclose(fp);
        return 0;
    }
    pAgency->agencyCounter = agencyCount;

    // Allocate memory for agencyArr
    pAgency->agencyArr = (SpaceAgency**)malloc(agencyCount * sizeof(SpaceAgency*));
    if (!pAgency->agencyArr) {
        printf("Error allocating memory for agencies\n");
        fclose(fp);
        return 0;
    }

    // Read each agency
    for (int i = 0; i < agencyCount; i++) {
        if (!loadSpaceAgencyFromFile(&pAgency->agencyArr[i], fp)) {
            fclose(fp);
            return 0;
        }
    }

    // Read number of expeditions
    int expeditionCount = readIntFromFile(fp, "Error read number of expeditions!\n");
    if (expeditionCount < 0) {
        fclose(fp);
        return 0;
    }
    pAgency->numOfExpeditions = expeditionCount;

    // Initialize expedition list
    L_init(&pAgency->expeditionList);

    // Load expedition list
    NODE* currentNode = &pAgency->expeditionList.head;
    for (int i = 0; i < expeditionCount; i++) {
        if (!loadExpeditionFromFile(currentNode, fp)) {
            fclose(fp);
            return 0;
        }
        currentNode = currentNode->next;
    }

    fclose(fp);
    return 1;
}
