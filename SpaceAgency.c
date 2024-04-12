#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SpaceAgency.h"
#include "StringToolBox.h"
#include "Expedition.h"
#include "FileManager.h"


void initSpaceAgency(SpaceAgency *pAgency) {
    if (pAgency == NULL)
        return;

    printf("Enter Agency name\t");
    setName(pAgency);

    pAgency->numOfBodiesFound = 0;

    pAgency->expeditionID = 0;

}

void setName(SpaceAgency *pAgency) {
    char temp[255];
    myGets(temp, MAX_STR_LEN, stdin);
    pAgency->name = temp;


}

int addExpedition(SpaceAgency *pAgency, Expedition *pExpedition) {
    pAgency->expeditionID = pExpedition->id;
    return 0;
}

int initAgencyExpedition(SpaceAgency *pAgency, CelestialBody *destination) {

    return 0;
}

void freeSpaceAgency(SpaceAgency *agency) {
    if (agency != NULL)
        free(agency);
}


void printSpaceAgency(const SpaceAgency *pAgency) {
    if (pAgency == NULL) {
        printf("Space Agency data is not available.\n");
        return;
    }

    printf("Space Agency Name:\t\t %s\n", pAgency->name);
    printf("Number of Celestial Bodies Found:\t %d\n", pAgency->numOfBodiesFound);

    // If you had more information about expeditions, you could print it here.
    // For example: printExpeditions(pAgency->expedition);
}


int saveSpaceAgencyToFileBin(const SpaceAgency *pAgency, FILE *fp) {
    if (pAgency == NULL || fp == NULL) {
        printf("Invalid function parameter.\n");
        return 0;
    }

    // Save the agency name if present
    if (!writeStringToFile(pAgency->name, fp, "Error writing agency name.\n")) {
        return 0;
    }

    // Save the number of bodies found
    if (!writeIntToFile(pAgency->numOfBodiesFound, fp, "Error writing number of bodies found.\n")) {
        return 0;
    }

    // Save the expedition ID
    if (!writeIntToFile(pAgency->expeditionID, fp, "Error writing agency expedition ID!\n")) {
        return 0;
    }

    return 1;
}

int loadSpaceAgencyFromFileBin(SpaceAgency **pAgency, FILE *fp) {
    if (fp == NULL) {
        printf("File pointer is NULL.\n");
        return 0;
    }

    *pAgency = (SpaceAgency*)malloc(sizeof(SpaceAgency));
    if (*pAgency == NULL) {
        printf("Memory allocation failed for SpaceAgency.\n");
        return 0;
    }

    // Read the name of the agency
    char* name = readStringFromFile(fp, "Failed to read agency name.\n");
    if (name == NULL) {
        free(*pAgency);
        *pAgency = NULL;
        return 0;
    }
    (*pAgency)->name = name;

    // Read the number of bodies found
    if (!readIntFromFile(&((*pAgency)->numOfBodiesFound), fp, "Failed to read number of celestial bodies.\n")) {
        free((*pAgency)->name);
        free(*pAgency);
        *pAgency = NULL;
        return 0;
    }

    // Read the expedition ID
    if (!readIntFromFile(&(*pAgency)->expeditionID, fp, "Failed to read expedition ID.\n")) {
        free((*pAgency)->name);
        free(*pAgency);
        *pAgency = NULL;
        return 0;
    }

    return 1;
}
