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

int addSpaceAgency(Agency* pAgency);
void freeAgency(Agency* pAgency);

int		saveManagerToFileBin(const Agency* pAgency, const char* fileName);
int loadManagerFromFileBin(Agency* pAgency, const char* fileName);

int saveManagerToFileTxt(const Agency* pAgency, const char* fileName);

void printAgency(const Agency* pAgency);



#endif //FINAL_C_PROJECT_AGENCYMANAGER_H
