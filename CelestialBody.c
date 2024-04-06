#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "CelestialBody.h"


const char* str[eNofTypes] = {"Star", "Asteroid", "Planet"};

int     initCelestialBody(CelestialBody* pBody)
{
    pBody->ID = getUniqueID();
    pBody->size = getSize();
    pBody->distance = getDistance();
    getLocation(pBody);
    pBody->type = chooseCelestialBodyType();

    return 0;
}


int      getUniqueID()
{
    static int id = 100000;
    return id++;
}

int     getSize()
{
    int size;
    printf("Enter a radius: (in km)\n");
    scanf("%d", &size);
    return size;
}

int    getDistance()
{
    int distance;
    printf("Enter a distance: (in light years)\n");
    scanf("%d", &distance);
    return distance;
}

void    getLocation(CelestialBody* pBody)
{
    int xAxis;
    int yAxis;

    printf("Type location of the object: (x and y axes from the earth) \n");
    scanf("%d %d", &xAxis, &yAxis);
    pBody->location.xAxis = xAxis;
    pBody->location.yAxis = yAxis;
}

CelestialBodyType chooseCelestialBodyType() {
    int choice;
    printf("Choose the type of Celestial Body:\n");
    for (int i = 0; i < eNofTypes; i++) {
        printf("[%d] %s\n", i, str[i]);
    }
    printf("Enter your choice (0 to %d): ", eNofTypes - 1);
    scanf("%d", &choice);

    while (choice < 0 || choice >= eNofTypes) {
        printf("Invalid choice. Please enter a number between 0 and %d: ", eNofTypes - 1);
        scanf("%d", &choice);
    }

    return (CelestialBodyType)choice;
}

void    printCelestialBody(const CelestialBody* pBody) {
    if (pBody != NULL) {
        printf("\nID:\t\t\t%d\n", pBody->ID);
        printf("Size:\t\t%d km\n", pBody->size);
        printf("Distance:\t%d light years away from earth\n", pBody->distance);
        printf("Type:\t\t%s\n", str[pBody->type]);
        printf("Location:\t(%d,%d)\n", pBody->location.xAxis, pBody->location.yAxis);
    }
}