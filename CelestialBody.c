#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "CelestialBody.h"
#include "StringToolBox.h"


const char *str[eNofTypes] = {"Star", "Asteroid", "Planet"};

int initCelestialBody(CelestialBody *pBody) {
    printf("Celestial body initialization: \n");
    pBody->ID = getUniqueID();
    pBody->size = getSize();
    pBody->distance = getDistance();
    getCorrectDate(&pBody->dateOfDiscovery);
    getLocation(pBody);
    pBody->type = chooseCelestialBodyType();

    return 0;
}


int getUniqueID() {
    static int id = 100000;
    return id++;
}

int getSize() {
    int size;
    printf("Enter a radius: (in km)\n");
    scanf("%d", &size);
    return size;
}

int getDistance() {
    int distance;
    printf("Enter a distance: (in light years)\n");
    scanf("%d", &distance);
    return distance;
}

void getLocation(CelestialBody *pBody) {
    int xAxis, yAxis;

    do {
        printf("Type location of the object: (x and y axes from the earth, both between -50 and 50) \n");
        printf("Enter x-coordinate: ");
        scanf("%d", &xAxis);
        printf("Enter y-coordinate: ");
        scanf("%d", &yAxis);

        if (xAxis < -MAX_DISTANCE || xAxis > MAX_DISTANCE || yAxis < -MAX_DISTANCE || yAxis > MAX_DISTANCE) {
            printf("Both coordinates must be between -50 and 50.\n");
        } else {
            break;
        }
    } while (1);

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

    return (CelestialBodyType) choice;
}

void freeCelestialBody(CelestialBody *pBody) {
    free(pBody);
}

void printCelestialBody(const CelestialBody *pBody) {
    if (pBody != NULL) {
        printf("\nID:\t\t\t%d\n", pBody->ID);
        printf("Size:\t\t%d km\n", pBody->size);
        printf("Distance:\t%d light years away from earth\n", pBody->distance);
        printf("Type:\t\t%s\n", str[pBody->type]);
        printf("Location:\t(%d,%d)\n", pBody->location.x, pBody->location.y);
    }
}

void saveCelestialBodyToFileTxt(FILE *fp, const CelestialBody *pBody) {
    if (fp == NULL || pBody == NULL) {
        fprintf(stderr, "Error: Invalid file pointer or celestial body pointer.\n");
        return;
    }

    // Print celestial body details to the file in a single line
    fprintf(fp, "%d %d %d %d %d %d\n",
            pBody->ID,
            pBody->type,
            pBody->size,
            pBody->distance,
            pBody->location.x,
            pBody->location.y);
}

int loadCelestialBodyFromFile(CelestialBody *body, FILE *fp) {
    getUniqueID(); //to update unic id
    if (fp == NULL || body == NULL) {
        printf("Error: Invalid file pointer or celestial body pointer.\n");
        return 0; // Failure due to invalid pointers
    }

    // Read the celestial body data from a single line
    if (fscanf(fp, "%d %d %d %d %d %d",
               &body->ID,
               &body->type, // Assuming 'type' is read as an integer and matches enum values
               &body->size,
               &body->distance,
               &body->location.x,
               &body->location.y) != 6) {
        printf("Error reading celestial body data.\n");
        return 1;
    }


    return 0; // Success
}

int compareBodyByDistance(const void *pBody1, const void *pBody2){
    return 0;
}

int compareBodyByType(const void *pBody1, const void *pBody2){
    return 0;
}

int compareBodyByDate(const void *pBody1, const void *pBody2){
    return 0;
}