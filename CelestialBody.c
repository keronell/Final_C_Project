#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "CelestialBody.h"
#include "StringToolBox.h"


const char* str[eNofTypes] = {"Star", "Asteroid", "Planet"};

int     initCelestialBody(CelestialBody* pBody)
{
    printf("Celestial body initialization: \n");
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
    pBody->location.x = xAxis;
    pBody->location.y = yAxis;
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

void freeCelestialBody(CelestialBody* pBody)
{
    free(pBody);
}

void    printCelestialBody(const CelestialBody* pBody) {
    if (pBody != NULL) {
        printf("\nID:\t\t\t%d\n", pBody->ID);
        printf("Size:\t\t%d km\n", pBody->size);
        printf("Distance:\t%d light years away from earth\n", pBody->distance);
        printf("Type:\t\t%s\n", str[pBody->type]);
        printf("Location:\t(%d,%d)\n", pBody->location.x, pBody->location.y);
    }
}

void saveCelestialBodyToFileTxt(FILE* fp, const CelestialBody* pBody) {
    if (fp == NULL || pBody == NULL) {
        fprintf(stderr, "Error: Invalid file pointer or celestial body pointer.\n");
        return;
    }

    // Print celestial body details to the file
    fprintf(fp, "Celestial Body ID: %d\n", pBody->ID);
    fprintf(fp, "Type: %s\n", str[pBody->type]); // Assumes 'str' is accessible here as well
    fprintf(fp, "Size: %d km\n", pBody->size);
    fprintf(fp, "Distance: %d light years\n", pBody->distance);
    fprintf(fp, "Location: (%d, %d)\n\n", pBody->location.x, pBody->location.y);
}

int loadCelestialBodyFromFile(CelestialBody* body, FILE* fp) {
    // Implement loading logic for a celestial body based on the format used in saveSystemToFileTxt
    char buffer[MAX_STR_LEN];
    if (fgets(buffer, sizeof(buffer), fp) == NULL) return 0; // Read body info line

    // Example of parsing the celestial body data
    sscanf(buffer, "ID: %d, Type: %d, Size: %d km, Distance: %d light years, Location: (%d,%d)\n",
           &body->ID, &body->type, &body->size, &body->distance, &body->location.x, &body->location.y);

    return 1;
}