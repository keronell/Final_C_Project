#ifndef FINAL_C_PROJECT_CELESTIALBODY_H
#define FINAL_C_PROJECT_CELESTIALBODY_H
#include "Location.h"
#include "Date.h"
#define MAX_DISTANCE 50
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


void saveCelestialBodyToFileTxt(FILE* fp, const CelestialBody* pBody);
int loadCelestialBodyFromFile(CelestialBody* body, FILE* fp);

int saveCelestialBodyToFileBin(const CelestialBody *pBody, FILE *fp);
int loadCelestialBodyFromFileBin(CelestialBody *pBody, FILE *fp);

int	    compareBodyByDistance(const void* body1, const void* body2);
int		compareBodyByDate(const void* body1, const void* body2);
int		compareBodyByType(const void* body1, const void* body2);

#endif //FINAL_C_PROJECT_CELESTIALBODY_H