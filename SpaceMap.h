#ifndef FINAL_C_PROJECT_SPACEMAP_H
#define FINAL_C_PROJECT_SPACEMAP_H

#include "CelestialBody.h"
#include "Expedition.h"
#include "input.h"
#include "AgencyManager.h"
typedef struct {

    int rows;
    int cols;
    int** data;

} SpaceMap;


typedef  Manager Manager;

int initSpaceMap (SpaceMap* spaceMap);

int addCelestialBodytoMap(SpaceMap* spaceMap, CelestialBody *body);
int addExpeditiontoMap(SpaceMap* spaceMap, Expedition* expedition);

void freeSpaceMap (SpaceMap* spaceMap);

void printSpaceMap(SpaceMap * matrix);
void getTwoPositiveIntegers(int* rows, int* columns);
void addCircleToMatrix(SpaceMap * matrix, Location center, int radius);
void markCircleCells(SpaceMap * matrix, Location center, int radius);
void addEarth (SpaceMap* spaceMap);




#endif //FINAL_C_PROJECT_SPACEMAP_H
