#ifndef FINAL_C_PROJECT_SPACEAGENCY_H
#define FINAL_C_PROJECT_SPACEAGENCY_H

#include "Expedition.h"
//#include "AgencyManager.h"

typedef struct
{
    char* name;
    int expeditionID;
    int numOfBodiesFound;

}SpaceAgency;

void     initSpaceAgency(SpaceAgency* pAgency);
void    setName(SpaceAgency* pAgency);
int     initAgencyExpedition(SpaceAgency* pAgency, CelestialBody* destination);

int     addExpedition(SpaceAgency *pAgency, Expedition* pExpedition);
void freeSpaceAgency(SpaceAgency* agency);
void    printSpaceAgency(const SpaceAgency* pAgency);

int     saveSpaceAgencyToFile(const SpaceAgency* pAgency, FILE *fp);
int loadSpaceAgencyFromFile(SpaceAgency** pAgency, FILE* fp);

#endif //FINAL_C_PROJECT_SPACEAGENCY_H
