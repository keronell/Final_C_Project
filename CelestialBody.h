#ifndef FINAL_C_PROJECT_CELESTIALBODY_H
#define FINAL_C_PROJECT_CELESTIALBODY_H



#include "Location.h"

typedef enum
{
    eStar, eAsteroid, ePlanet, eNofTypes
} CelestialBodyType;


typedef struct
{
    int                 ID;
    int                 size;
    int                 distance;
    Location            location;
    CelestialBodyType   type;
}CelestialBody;




int     initCelestialBody(CelestialBody* pBody);
int     getUniqueID();
int     getSize();
int     getDistance();
void    getLocation(CelestialBody* pBody);
CelestialBodyType   chooseCelestialBodyType();

void freeCelestialBody(CelestialBody* pBody);

void printCelestialBody(const CelestialBody* pBody);

void saveCelestialBodyToFileTxt(FILE* fp, const CelestialBody* pBody);
int loadCelestialBodyFromFile(CelestialBody* body, FILE* fp);

#endif //FINAL_C_PROJECT_CELESTIALBODY_H
