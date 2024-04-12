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

int		saveManagerToFileBin(const Agency* pAgency, const char* fileName)
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
        if (!saveSpaceAgencyToFileBin(pAgency->agencyArr[i], fp))
            return 0;
    }

    if (!writeIntToFile(pAgency->numOfExpeditions, fp, "Error write number of expeditions!\n"))
        return 0;

    NODE* currentNode = pAgency->expeditionList.head.next; // Starting from the first expedition
    while (currentNode != NULL) {
        if (!saveExpeditionToFileBin(currentNode->key, fp)) {
            printf("Error writing expedition to file!\n");
            fclose(fp);
            return 0;
        }
        currentNode = currentNode->next;
    }

    fclose(fp);
    return 1;
}

int loadManagerFromFileBin(Agency* pAgency, const char* fileName) {
    FILE* fp;
    fp = fopen(fileName, "rb");  // Open file in binary read mode
    if (!fp) {
        printf("Error open Agency file to read\n");
        return 0;
    }

    // Read number of agencies
    if (!readIntFromFile(&pAgency->agencyCounter, fp, "Error read number of agencies!\n")) {
        fclose(fp);
        return 0;
    }

    // Allocate memory for agencyArr
    pAgency->agencyArr = (SpaceAgency**)malloc(pAgency->agencyCounter * sizeof(SpaceAgency*));
    if (!pAgency->agencyArr) {
        printf("Error allocating memory for agencies\n");
        fclose(fp);
        return 0;
    }

    // Read each agency
    for (int i = 0; i < pAgency->agencyCounter; i++) {
        pAgency->agencyArr[i] = (SpaceAgency*) malloc(sizeof(SpaceAgency));
        if (!loadSpaceAgencyFromFileBin(&pAgency->agencyArr[i], fp)) {
            // Clean up already loaded agencies before returning error
            for (int j = 0; j < i; j++) {
                freeSpaceAgency(pAgency->agencyArr[j]);
            }
            free(pAgency->agencyArr);
            fclose(fp);
            return 0;
        }
    }

    // Read number of expeditions
    if (!readIntFromFile(&pAgency->numOfExpeditions, fp, "Error read number of expeditions!\n")) {
        // Clean up loaded agencies before returning error
        for (int i = 0; i < pAgency->agencyCounter; i++) {
            freeSpaceAgency(pAgency->agencyArr[i]);
        }
        free(pAgency->agencyArr);
        fclose(fp);
        return 0;
    }

    // Initialize expedition list
    L_init(&pAgency->expeditionList);

    // Load expedition list
    NODE* currentNode = &pAgency->expeditionList.head;  // Temporary node to start the chain
    for (int i = 0; i < pAgency->numOfExpeditions; i++) {
        NODE* newNode = (NODE*) malloc(sizeof(NODE));  // Allocate memory for a new node
        if (newNode == NULL || !loadExpeditionFromFileBin(newNode, fp)) {
            // Clean up everything if loading fails
            while (pAgency->expeditionList.head.next) {
                NODE* temp = pAgency->expeditionList.head.next;
                pAgency->expeditionList.head.next = temp->next;
                freeExpedition(temp->key);
                free(temp);
            }
            for (int j = 0; j < pAgency->agencyCounter; j++) {
                freeSpaceAgency(pAgency->agencyArr[j]);
            }
            free(pAgency->agencyArr);
            fclose(fp);
            return 0;
        }
        currentNode->next = newNode;  // Link the new node into the list
        currentNode = newNode;  // Move the current node marker to the new node
    }
    currentNode->next = NULL;  // Terminate the last node

    fclose(fp);
    return 1;
}

int saveManagerToFileTxt(const Agency* pAgency, const char* fileName) {
    if (pAgency == NULL) {
        printf("Invalid Agency pointer.\n");
        return 0;
    }

    FILE* fp = fopen(fileName, "w");  // Open file in write mode
    if (!fp) {
        printf("Error opening file to write.\n");
        return 0;
    }

    // Write the number of agencies
    if (!writeIntToFile(pAgency->agencyCounter, fp, "Error writing number of agencies!\n")) {
        fclose(fp);
        return 0;
    }

    // Iterate over each SpaceAgency and write its details to the file
    for (int i = 0; i < pAgency->agencyCounter; i++) {
        if (!saveSpaceAgencyToFileTxt(pAgency->agencyArr[i], fp)) {
            fclose(fp);
            return 0;
        }
    }

    // Close the file
    fclose(fp);
    return 1;
}
