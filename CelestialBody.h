#ifndef FINAL_C_PROJECT_CELESTIALBODY_H
#define FINAL_C_PROJECT_CELESTIALBODY_H



#include "Location.h"
#include "Date.h"

typedef enum
{
    eStar, eAsteroid, ePlanet, eNofTypes
} CelestialBodyType;


typedef struct
{
    int                 ID;
    int                 size;
    int                 distance;
    Date                dateOfDiscovery;
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

#endif //FINAL_C_PROJECT_CELESTIALBODY_H
