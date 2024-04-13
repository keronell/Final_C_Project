#ifndef FINAL_C_PROJECT_SPACECONTROLSYSTEM_H
#define FINAL_C_PROJECT_SPACECONTROLSYSTEM_H

#include "GeneralList.h"
#include "CelestialBody.h"
#include "SpaceMap.h"

typedef enum {
    eID, eSize, eDistance, eFoundBy, eType, eNofSortOpt
} eSortOption;
static const char *sortOptStr[eNofSortOpt];


typedef struct {
    SpaceMap spaceMap;
    CelestialBody **CelestialBodyArr;
    int numOfBodies;
    eSortOption sortOpt;


} SpaceControlSystem;

int initSystem(SpaceControlSystem *pSystem);
int addCelestialBody(SpaceControlSystem *pSystem, CelestialBody *newBody);

void spaceMap();
void freeAllAllocatedMemory(SpaceControlSystem *pSystem);
void printSpaceControlSystem(const SpaceControlSystem *pSystem);

int saveSystemToFileTxt(const SpaceControlSystem *pSystem, const Agency *pAgency, const char *fileName);
int loadSystemFromFileTxt(SpaceControlSystem *pSystem, Agency *pAgency, const char *fileName);

int saveSystemToFileBin(const SpaceControlSystem *pSystem, const Agency *pAgency, const char *fileName);
int loadSystemFromFileBin(SpaceControlSystem *pSystem, Agency *pAgency, char *fileName);


#endif //FINAL_C_PROJECT_SPACECONTROLSYSTEM_H
