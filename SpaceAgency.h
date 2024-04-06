#ifndef FINAL_C_PROJECT_SPACEAGENCY_H
#define FINAL_C_PROJECT_SPACEAGENCY_H

#include "Expedition.h"
typedef struct
{
    char* name;
    Expedition expedition;

}SpaceAgency;

void     initSpaceAgency(SpaceAgency* pAgency);
void    setName(SpaceAgency* pAgency);

int     addExpedition(Expedition pExpedition);



#endif //FINAL_C_PROJECT_SPACEAGENCY_H
