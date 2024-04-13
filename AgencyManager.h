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
void freeAgencyManager(Agency* pAgency);

int		saveManagerToFileBin(FILE *fp, const Agency* pAgency);
int loadManagerFromFileBin(Agency* pAgency, const char* fileName);

int saveManagerToFileTxt(FILE *fp, const Agency* pAgency);
int loadManagerFromFileTxt(Agency *pAgency, FILE* fp);

void printAgencyManager(const Agency* pAgency);



#endif //FINAL_C_PROJECT_AGENCYMANAGER_H
