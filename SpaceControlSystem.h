#ifndef FINAL_C_PROJECT_SPACECONTROLSYSTEM_H
#define FINAL_C_PROJECT_SPACECONTROLSYSTEM_H
#include "GeneralList.h"

typedef enum { eID, eSize, eDistance,eFoundBy,eType, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];


typedef struct SpaceControlSystem
{
    LIST    CelestialBodyList;
    int     numOfBodies;
    eSortOption sortOpt;

};

int     initSystemFromFile();
void    initSystem();

void    spaceMap();
#endif //FINAL_C_PROJECT_SPACECONTROLSYSTEM_H
