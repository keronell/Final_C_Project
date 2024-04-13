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

    pAgency->name = getStrExactName("Enter Manager name:\n");
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
        printf("Space Manager data is not available.\n");
        return;
    }

    printf("Space Manager Name:\t\t %s\n", pAgency->name);

    printf("Expedition destination ID: \t %d\n", pAgency->expeditionID);
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
    char nameBuffer[MAX_STR_LEN];  // Increase size as needed
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

int saveSpaceAgencyToFileBin(const SpaceAgency* pAgency, FILE* fp) {
    if (fp == NULL || pAgency == NULL) {
        fprintf(stderr, "Invalid file pointer or agency pointer.\n");
        return 1; // Error
    }

    // Save the length of the agency name and the name itself
    int nameLength = strlen(pAgency->name) + 1; // Include null terminator
    if (fwrite(&nameLength, sizeof(nameLength), 1, fp) != 1 ||
        fwrite(pAgency->name, sizeof(char), nameLength, fp) != nameLength) {
        fprintf(stderr, "Failed to write agency name.\n");
        return 1; // Error
    }

    // Save the expedition ID
    if (fwrite(&pAgency->expeditionID, sizeof(pAgency->expeditionID), 1, fp) != 1) {
        fprintf(stderr, "Failed to write expedition ID.\n");
        return 1; // Error
    }

    return 0; // Success
}

int loadSpaceAgencyFromFileBin(SpaceAgency* pAgency, FILE* fp) {
    if (fp == NULL || pAgency == NULL) {
        printf("Invalid file pointer or agency pointer.\n");
        return 1; // Error
    }

    // Read the length of the agency name and the name itself
    int nameLength;
    if (fread(&nameLength, sizeof(nameLength), 1, fp) != 1) {
        printf("Failed to read the length of agency name.\n");
        return 1; // Error
    }

    // Allocate memory for the agency name
    pAgency->name = (char*)malloc(nameLength * sizeof(char));
    if (pAgency->name == NULL) {
        printf("Memory allocation failed for agency name.\n");
        return 1; // Error
    }

    if (fread(pAgency->name, sizeof(char), nameLength, fp) != nameLength) {
        printf("Failed to read agency name.\n");
        free(pAgency->name);
        return 1; // Error
    }

    // Read the expedition ID
    if (fread(&pAgency->expeditionID, sizeof(pAgency->expeditionID), 1, fp) != 1) {
        printf("Failed to read expedition ID.\n");
        free(pAgency->name);
        return 1; // Error
    }

    return 0; // Success
}

