#ifndef FINAL_C_PROJECT_CELESTIALBODY_H
#define FINAL_C_PROJECT_CELESTIALBODY_H



#include "Location.h"

typedef enum
{
    eStar, eAsteroid, ePlanet, eNofTypes
} CelestialBodyType;

const char* str[eNofTypes] = {"Star", "Asteroid", "Planet"};


typedef struct
{
    int                 ID;
    int                 size;
    int                 distance;
    //SpaceAgency*      foundBy;
    Location            location;
    CelestialBodyType   type;
}CelestialBody;

static int idCounter = 10000;


int     initCelestialBody(CelestialBody* pBody);
int     getSize();
int     getDistance();
void    getLocation(CelestialBody* pBody);
CelestialBodyType   chooseCelestialBodyType();

void printCelestialBody(const CelestialBody* pBody);

#endif //FINAL_C_PROJECT_CELESTIALBODY_H
