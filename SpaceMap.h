#ifndef FINAL_C_PROJECT_SPACEMAP_H
#define FINAL_C_PROJECT_SPACEMAP_H

#include "CelestialBody.h"
#include "Expedition.h"

typedef struct {
    int rows;
    int cols;
    int **data;
} SpaceMap;

int initSpaceMap (SpaceMap* spaceMap);

int addCelestialBodytoMap (SpaceMap* spaceMap, CelestialBody* newBody);
int addExpedition (Expedition* newExpedition);
int rmCelestialBody (CelestialBody* body);
int rmExpedition (Expedition* expedition);

void freeSpaceMap (SpaceMap* spaceMap);

void printMatrix(SpaceMap * matrix);
void getTwoPositiveIntegers(int* rows, int* columns);
void addCircleToMatrix(SpaceMap * matrix, Location center, int radius);
void markCircleCells(SpaceMap * matrix, Location center, int radius);


#endif //FINAL_C_PROJECT_SPACEMAP_H
