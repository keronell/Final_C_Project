#ifndef FINAL_C_PROJECT_AGENCYMANAGER_H
#define FINAL_C_PROJECT_AGENCYMANAGER_H

#include"SpaceAgency.h"
#include "GeneralList.h"

typedef struct
{
    int			agencyCounter;
    SpaceAgency**	agencyArr;
    LIST		expeditionList;
}Agency;


#endif //FINAL_C_PROJECT_AGENCYMANAGER_H
