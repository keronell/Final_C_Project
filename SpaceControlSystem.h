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

int initSystem(SpaceControlSystem *pSystem);

int addCelestialBody(SpaceControlSystem *pSystem, CelestialBody *newBody);

void spaceMap();

void freeAllAllocatedMemory(SpaceControlSystem *pSystem);

void printSpaceControlSystem(const SpaceControlSystem *pSystem);

void findCelestialBody (const SpaceControlSystem* pSystem);

void sortCelestialBody (SpaceControlSystem* pSystem);

#endif //FINAL_C_PROJECT_SPACECONTROLSYSTEM_H
