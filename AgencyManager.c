#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AgencyManager.h"


int initAgency(Manager* pAgency)
{
    if (pAgency == NULL)
        return 1;
    // Initialize agencyCounter to 0
    pAgency->agencyCounter = 0;
    pAgency->agencyArr = (SpaceAgency**)malloc(sizeof(SpaceAgency*));
    if (pAgency->agencyArr == NULL)
        return 1;
    pAgency->numOfExpeditions = 0;
    if(!L_init(&(pAgency->expeditionList)))
        return 1;
    return 0;
}

int addSpaceAgency(Manager* pAgency)
{
    SpaceAgency* newAgency = (SpaceAgency*)malloc(sizeof(SpaceAgency));
    if (newAgency == NULL) {
        printf("Error: Memory allocation for new SpaceAgency failed.\n");
        return 1;
    }


    initSpaceAgency(newAgency);


    int newSize = pAgency->agencyCounter + 1;
    SpaceAgency** tempArr = (SpaceAgency**)realloc(pAgency->agencyArr, newSize * sizeof(SpaceAgency*));
    if (tempArr == NULL) {
        printf("Error: Memory reallocation failed.\n");
        free(newAgency);
        return 1;
    }

    pAgency->agencyArr = tempArr;
    pAgency->agencyArr[pAgency->agencyCounter] = newAgency;
    pAgency->agencyCounter++;

    return 0;
}

void freeAgencyManager(Manager* pAgency) {

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

int saveManagerToFileTxt(FILE *fp, const Manager* pAgency) {

    if (fp == NULL || pAgency == NULL) {
        fprintf(stderr, "Invalid file pointer or agency pointer.\n");
        return 1;
    }


    printf("Saving %d agencies and %d expeditions.\n", pAgency->agencyCounter, pAgency->numOfExpeditions);


    fprintf(fp, "%d %d\n", pAgency->agencyCounter, pAgency->numOfExpeditions);

    // Save each agency
    for (int i = 0; i < pAgency->agencyCounter; i++) {
        if (saveSpaceAgencyToFileTxt(pAgency->agencyArr[i], fp)) {
            fprintf(stderr, "Failed to save agency data.\n");
            return 1;
        }
    }


    NODE* currentNode = pAgency->expeditionList.head.next;
    while (currentNode != NULL) {
        if (saveExpeditionToFileTxt(currentNode->key, fp)) {
            return 1;
        }
        currentNode = currentNode->next;
    }
    return 0;
}
int loadManagerFromFileTxt(Manager *pAgency, FILE* fp) {
    if (fscanf(fp, "%d %d", &pAgency->agencyCounter, &pAgency->numOfExpeditions) != 2) {
        printf("Failed to read the number of agencies and expeditions.\n");
        return 1;
    }


    pAgency->agencyArr = (SpaceAgency**)malloc(pAgency->agencyCounter * sizeof(SpaceAgency*));
    if (pAgency->agencyArr == NULL) {
        printf("Memory allocation failed for agencies.\n");
        return 1;
    }

    for (int i = 0; i < pAgency->agencyCounter; i++) {
        pAgency->agencyArr[i] = (SpaceAgency*)malloc(sizeof(SpaceAgency));
        if (pAgency->agencyArr[i] == NULL) {
            printf("Memory allocation failed for an agency.\n");
            return 1;
        }
        if (loadSpaceAgencyFromFileTxt(pAgency->agencyArr[i], fp)) {
            printf("Failed to load agency data.\n");
            return 1;
        }
    }

    L_init(&pAgency->expeditionList);
    for (int i = 0; i < pAgency->numOfExpeditions; i++) {
        NODE* newNode = (NODE*)malloc(sizeof(NODE));
        if (newNode == NULL) {
            printf("Failed to allocate memory for a new expedition node.\n");
            return 1;
        }
        newNode->key = (Expedition*)malloc(sizeof(Expedition));
        if (newNode->key == NULL) {
            printf("Failed to allocate memory for new Expedition.\n");
            free(newNode);
            return 1;
        }


        if (loadExpeditionFromFileTxt((Expedition*)newNode->key, fp)) {
            printf("Failed to load expedition.\n");
            free(newNode->key);
            free(newNode);
            return 1;
        }
        newNode->next = pAgency->expeditionList.head.next;
        pAgency->expeditionList.head.next = newNode;
    }

    return 0;
}

int saveManagerToFileBin(FILE *fp, const Manager* pAgency) {
    if (fp == NULL || pAgency == NULL) {
        fprintf(stderr, "Invalid file pointer or agency pointer.\n");
        return 1; // Error
    }

    if (fwrite(&pAgency->agencyCounter, sizeof(pAgency->agencyCounter), 1, fp) != 1 ||
        fwrite(&pAgency->numOfExpeditions, sizeof(pAgency->numOfExpeditions), 1, fp) != 1) {
        fprintf(stderr, "Failed to write header data for manager.\n");
        return 1; // Error
    }

    for (int i = 0; i < pAgency->agencyCounter; i++) {
        if (saveSpaceAgencyToFileBin(pAgency->agencyArr[i], fp)) {
            return 1; // Error
        }
    }

    NODE* currentNode = pAgency->expeditionList.head.next;
    while (currentNode != NULL) {
        if (saveExpeditionToFileBin((Expedition*)currentNode->key, fp)) {
            return 1; // Error
        }
        currentNode = currentNode->next;
    }
    return 0; // Success
}

int loadManagerFromFileBin(Manager *pAgency, FILE* fp) {
    if (fp == NULL || pAgency == NULL) {
        printf("Invalid file pointer or agency pointer.\n");
        return 1;
    }

    if (fread(&pAgency->agencyCounter, sizeof(pAgency->agencyCounter), 1, fp) != 1 ||
        fread(&pAgency->numOfExpeditions, sizeof(pAgency->numOfExpeditions), 1, fp) != 1) {
        printf("Failed to read header data for manager.\n");
        return 1;
    }

    pAgency->agencyArr = (SpaceAgency**)malloc(pAgency->agencyCounter * sizeof(SpaceAgency*));
    if (pAgency->agencyArr == NULL) {
        printf("Memory allocation failed for agencies.\n");
        return 1;
    }

    for (int i = 0; i < pAgency->agencyCounter; i++) {
        pAgency->agencyArr[i] = (SpaceAgency*)malloc(sizeof(SpaceAgency));
        if (pAgency->agencyArr[i] == NULL) {
            printf("Memory allocation failed for an agency.\n");
            return 1;
        }
        if (loadSpaceAgencyFromFileBin(pAgency->agencyArr[i], fp)) {
            printf("Failed to load agency data.\n");
            return 1;
        }
    }

    L_init(&pAgency->expeditionList);
    for (int i = 0; i < pAgency->numOfExpeditions; i++) {
        NODE* newNode = (NODE*)malloc(sizeof(NODE));
        if (newNode == NULL) {
            printf("Failed to allocate memory for a new expedition node.\n");
            return 1;
        }
        newNode->key = (Expedition*)malloc(sizeof(Expedition));
        if (newNode->key == NULL) {
            printf("Failed to allocate memory for new Expedition.\n");
            free(newNode);
            return 1;
        }
        if (loadExpeditionFromFileBin((Expedition*)newNode->key, fp)) {
            printf("Failed to load expedition.\n");
            free(newNode->key);
            free(newNode);
            return 1;
        }
        newNode->next = pAgency->expeditionList.head.next;
        pAgency->expeditionList.head.next = newNode;
    }

    return 0;
}


void printAgencyManager(const Manager* pAgency)
{
    if (pAgency == NULL) {
        printf("Error: Agency manager pointer is NULL.\n");
    } else {

        printf("AgencyManager Details:\n");
        printf("Total Agencies: %d\n", pAgency->agencyCounter);
        printf("Total Expeditions Managed: %d\n\n", pAgency->numOfExpeditions);

        for (int i = 0; i < pAgency->agencyCounter; i++) {
            SpaceAgency* agency = pAgency->agencyArr[i];
            if (agency != NULL) {
                printf("Agency -  %d:\n", i + 1);
                printSpaceAgency(agency);
                printf("\n");
            } else {
                printf("Agency [%d]: [Data Not Available]\n", i + 1);
            }
        }

        printf("Expedition Details:\n");
        if(pAgency->numOfExpeditions < 1) {
            printf("Currently there is no Expeditions planned!\n");
            return;
        }
        NODE* currentNode = pAgency->expeditionList.head.next;
        while (currentNode != NULL && currentNode->key != NULL) {
            printExpedition((Expedition*)currentNode->key);
            currentNode = currentNode->next;
        }
    }
}

void printExpeditionList(Manager* pAgency)
{
    if (pAgency == NULL) {
        printf("Error: Manager pointer is NULL.\n");
        return;
    }

    if (pAgency->expeditionList.head.next == NULL) {
        printf("No expeditions in the list.\n");
        return;
    }

    printf("Expedition List:\n");
    NODE* currentNode = pAgency->expeditionList.head.next;
    int count = 0;
    while (currentNode != NULL) {
        printf("Expedition %d:\n", ++count);
        if (currentNode->key != NULL) {
            printExpedition((Expedition*)currentNode->key);
        } else {
            printf("  Warning: Null expedition data.\n");
        }
        currentNode = currentNode->next;
    }
}
