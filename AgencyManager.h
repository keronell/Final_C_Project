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
}Manager;

int initAgency(Manager* pAgency);

int addSpaceAgency(Manager* pAgency);
void freeAgencyManager(Manager* pAgency);

int		saveManagerToFileBin(FILE *fp, const Manager* pAgency);
int loadManagerFromFileBin(Manager* pAgency, const char* fileName);

int saveManagerToFileTxt(FILE *fp, const Manager* pAgency);
int loadManagerFromFileTxt(Manager *pAgency, FILE* fp);

void printAgencyManager(const Manager* pAgency);



#endif //FINAL_C_PROJECT_AGENCYMANAGER_H
