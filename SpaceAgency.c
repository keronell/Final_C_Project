#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "SpaceAgency.h"
#include "StringToolBox.h"
#include "Expedition.h"
#include "FileManager.h"


void initSpaceAgency(SpaceAgency *pAgency) {
    if (pAgency == NULL)
        return;

    pAgency->name = getStrExactName("Enter Agency name:\n");
    pAgency->expeditionID = 0;

}

int addExpedition(SpaceAgency *pAgency, Expedition *pExpedition) {
    pAgency->expeditionID = pExpedition->id;
    return 0;
}

void initAgencyExpedition(SpaceAgency *pAgency, CelestialBody *destination) {
pAgency->expeditionID = destination->ID;
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

    printf("Expedition destination ID: \t %d\n", pAgency->expeditionID);
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


    // Read the expedition ID
    if (!readIntFromFile(&(*pAgency)->expeditionID, fp, "Failed to read expedition ID.\n")) {
        free((*pAgency)->name);
        free(*pAgency);
        *pAgency = NULL;
        return 0;
    }

    return 1;
}

int saveSpaceAgencyToFileTxt(const SpaceAgency* pAgency, FILE* fp) {
    if (fp == NULL || pAgency == NULL) {
        printf("Invalid file pointer or agency pointer.\n");
        return 1;
    }

    // Write agency name and expedition ID directly to the file
    if (fprintf(fp, "%s %d\n", pAgency->name, pAgency->expeditionID) < 0) {
        printf("Failed to write agency data to file.\n");
        return 1;
    }
    return 0;
}
int loadSpaceAgencyFromFileTxt(SpaceAgency* pAgency, FILE* fp) {
    if (fp == NULL || pAgency == NULL) {
        printf("Invalid file pointer or agency pointer.\n");
        return 1;
    }

    // Read the agency name and the expedition ID in one go.
    char nameBuffer[100];  // Increase size as needed
    int expeditionID;
    if (fscanf(fp, "%99s %d", nameBuffer, &expeditionID) != 2) {  // Use %99s to prevent buffer overflow
        printf("Failed to read agency name and expedition ID from file.\n");
        return 1;
    }

    // Allocate memory for the agency name
    pAgency->name = strdup(nameBuffer);
    if (pAgency->name == NULL) {
        printf("Failed to allocate memory for agency name.\n");
        return 1;
    }

    pAgency->expeditionID = expeditionID;

    // Consume the newline character if necessary to clean up for the next read
    fscanf(fp, "\n");

    return 0;
}
