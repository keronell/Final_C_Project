#ifndef FINAL_C_PROJECT_SPACECONTROLSYSTEM_H
#define FINAL_C_PROJECT_SPACECONTROLSYSTEM_H
#include "GeneralList.h"
#include "CelestialBody.h"
#include "SpaceMap.h"
typedef enum { eNone, eDistance, eDate, eType, eNofSortOpt
} eSortOption;
static const char *sortOptStr[eNofSortOpt];
typedef struct {
    SpaceMap spaceMap;
    CelestialBody **CelestialBodyArr;
    int numOfBodies;
    eSortOption sortOpt;
} SpaceControlSystem;

int     initSystem(SpaceControlSystem *pSystem);
int     addCelestialBody(SpaceControlSystem *pSystem);
int     addExpeditionToAgency(Manager *pAgency, SpaceControlSystem *pSystem);

void    freeSystem(SpaceControlSystem *pSystem, Manager* pAgency);
void    printSpaceControlSystem(const SpaceControlSystem *pSystem, const Manager* pAgency);
void    printCelestialBodies(const SpaceControlSystem *pSystem);


int     saveSystemToFileTxt(const SpaceControlSystem *pSystem, const Manager *pAgency, const char *fileName);
int     loadSystemFromFileTxt(SpaceControlSystem *pSystem, Manager *pAgency, const char *fileName);

int     saveSystemToFileBin(const SpaceControlSystem *pSystem, const Manager *pAgency, const char *fileName);
int     loadSystemFromFileBin(SpaceControlSystem *pSystem, Manager *pAgency, const char *fileName) ;

void    findCelestialBody(const SpaceControlSystem *pSystem);
void    sortCelestialBody(SpaceControlSystem *pSystem);




#endif //FINAL_C_PROJECT_SPACECONTROLSYSTEM_H