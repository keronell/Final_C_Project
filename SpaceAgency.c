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

    pAgency->expeditionID =  0;

}

void setName(SpaceAgency *pAgency) {
    char temp[255];
    myGets(temp, MAX_STR_LEN, stdin);
    pAgency->name = temp;


}

int addExpedition(SpaceAgency *pAgency, Expedition* pExpedition) {
    pAgency->expeditionID = pExpedition->id;
    return 0;
}

int initAgencyExpedition(SpaceAgency *pAgency, CelestialBody *destination) {

    return 0;
}

void freeSpaceAgency(SpaceAgency* agency) {
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


int     saveSpaceAgencyToFile(const SpaceAgency* pAgency, FILE *fp)
{
    if (fwrite(pAgency, sizeof(SpaceAgency), 1, fp) != 1)
    {
        printf("Error saving Agency!\n");
        return 0;
    }
    if(pAgency->expeditionID != 0)
        if(!writeIntToFile(pAgency->expeditionID, fp, "Error write Agency expedition ID!\n"))
            return 0;
    return 1;
}

int loadSpaceAgencyFromFile(SpaceAgency** pAgency, FILE* fp)
{
    if (fp == NULL) {
        printf("Can't open the file.\n");
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

    if (!readIntFromFile(&((*pAgency)->numOfBodiesFound), fp, "Failed to read number of celestial bodies.\n")) {
        free((*pAgency)->name);
        free(*pAgency);
        *pAgency = NULL;
        return 0;
    }

    int expeditionId;
    if (!readIntFromFile(&(*pAgency)->expeditionID, fp, "Failed to read expedition ID.\n")) {
        free((*pAgency)->name);
        free(*pAgency);
        *pAgency = NULL;
        return 0;
    }

    return 1;

}
