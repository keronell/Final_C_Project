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

#endif //FINAL_C_PROJECT_AGENCYMANAGER_H
