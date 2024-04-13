#ifndef FINAL_C_PROJECT_SPACEAGENCY_H
#define FINAL_C_PROJECT_SPACEAGENCY_H

#include "Expedition.h"

typedef struct
{
    char* name;
    int expeditionID;

}SpaceAgency;

void     initSpaceAgency(SpaceAgency* pAgency);

void freeSpaceAgency(SpaceAgency* agency);
void    printSpaceAgency(const SpaceAgency* pAgency);

int saveSpaceAgencyToFileBin(const SpaceAgency* pAgency, FILE* fp);
int loadSpaceAgencyFromFileBin(SpaceAgency* pAgency, FILE* fp);

int saveSpaceAgencyToFileTxt(const SpaceAgency* pAgency, FILE* fp);
int loadSpaceAgencyFromFileTxt(SpaceAgency* pAgency, FILE* fp);

#endif //FINAL_C_PROJECT_SPACEAGENCY_H
