#ifndef FINAL_C_PROJECT_AGENCYMANAGER_H
#define FINAL_C_PROJECT_AGENCYMANAGER_H

#include"SpaceAgency.h"
#include "GeneralList.h"

typedef struct
{
    int		    agencyCounter;
    SpaceAgency**	agencyArr;
    int         numOfExpeditions;
    LIST        expeditionList;
}Agency;

int initAgency(Agency* pAgency);

int addSpaceAgency(Agency* pAgency, SpaceAgency* newAgency);
void freeAgency(Agency* pAgency);
Expedition* findExpeditionById(Agency* pManager, int id);

int		saveManagerToFileBin(const Agency* pAgency, const char* fileName);
int		saveManagerToFileBinary(const Agency* pAgency, const char* fileName);

int loadManagerFromFileBin(Agency* pAgency, const char* fileName);



#endif //FINAL_C_PROJECT_AGENCYMANAGER_H
