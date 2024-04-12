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
    if (fprintf(fp, "Agency Name: %s\n", pAgency->name) < 0 ||
        fprintf(fp, "Expedition ID: %d\n\n", pAgency->expeditionID) < 0) {
        printf("Failed to write agency data to file.\n");
        return 0;
    }
    return 1;
}
int loadSpaceAgencyToFileTxt(SpaceAgency* pAgency, FILE* fp)
{
    if (pAgency == NULL || fp == NULL) {
        printf("Invalid parameters.\n");
        return 0;
    }

    // Read the agency name from the file
    pAgency->name = getStrExactNameFromFile("Reading Agency Name:", fp);
    if (pAgency->name == NULL) {
        printf("Failed to read agency name from file or name is not available.\n");
        return 0;
    }

    // Read the expedition ID from the file
    char buffer[MAX_STR_LEN];
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        printf("Failed to read expedition ID from file.\n");
        free(pAgency->name);
        return 0;
    }
    if (sscanf(buffer, "Expedition ID: %d", &pAgency->expeditionID) != 1) {
        printf("Expedition ID formatted incorrectly or missing.\n");
        free(pAgency->name);
        return 0;
    }

    return 1; // Successfully loaded the agency data
}
