#ifndef FINAL_C_PROJECT_CELESTIALBODY_H
#define FINAL_C_PROJECT_CELESTIALBODY_H


typedef enum
{
    eStar, eAsteroid, ePlanet, eNofOptions
} CelestialBodyType;

typedef struct CelestialBody
{
    int ID;
    CelestialBodyType type;
    int size;
    int distance;
    char* foundBy;
};

const char* str[eNofOptions];
#endif //FINAL_C_PROJECT_CELESTIALBODY_H
