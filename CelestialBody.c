#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "CelestialBody.h"
#include "FileManager.h"


const char *str[eNofTypes] = {"Star", "Asteroid", "Planet"};

int initCelestialBody(CelestialBody *pBody) {
    printf("Celestial body initialization: \n");
    pBody->ID = getUniqueID();
    pBody->size = getSize();
    pBody->distance = getDistance();
    setCurrentDate(&pBody->dateOfDiscovery);
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
        printf("Type location of the object: (x and y axes from the earth, both between 0 and %d) \n",MAX_DISTANCE);
        printf("Enter x-coordinate: ");
        scanf("%d", &xAxis);
        printf("Enter y-coordinate: ");
        scanf("%d", &yAxis);

        if (xAxis < 0 || xAxis > MAX_DISTANCE || yAxis < 0 || yAxis > MAX_DISTANCE) {
            printf("Both coordinates must be between 0 and %d.\n", MAX_DISTANCE);
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
        return 1;
    }

    if (fscanf(fp, "%d %d %d %d %d %d",
               &body->ID,
               &body->type,
               &body->size,
               &body->distance,
               &body->location.x,
               &body->location.y) != 6) {
        printf("Error reading celestial body data.\n");
        return 1;
    }


    return 0;
}


int saveCelestialBodyToFileBin(const CelestialBody *pBody, FILE *fp) {
    if (fp == NULL || pBody == NULL) {
        fprintf(stderr, "Error: Invalid file pointer or celestial body pointer.\n");
        return 1;
    }

    if (!writeIntToFile(pBody->ID, fp, "Error writing celestial body ID.\n")) return 1;
    if (!writeIntToFile(pBody->type, fp, "Error writing celestial body type.\n")) return 1;
    if (!writeIntToFile(pBody->size, fp, "Error writing celestial body size.\n")) return 1;
    if (!writeIntToFile(pBody->distance, fp, "Error writing celestial body distance.\n")) return 1;
    if (!writeIntToFile(pBody->location.x, fp, "Error writing celestial body location x.\n")) return 1;
    if (!writeIntToFile(pBody->location.y, fp, "Error writing celestial body location y.\n")) return 1;

    return 0;
}


int loadCelestialBodyFromFileBin(CelestialBody *pBody, FILE *fp) {
    if (fp == NULL || pBody == NULL) {
        printf("Error: Invalid file pointer or celestial body pointer.\n");
        return 1;
    }

    int tempType;


    if (!readIntFromFile(&pBody->ID, fp, "Error reading celestial body ID.\n")) return 1;
    if (!readIntFromFile(&tempType, fp, "Error reading celestial body type.\n")) return 1;
    pBody->type = (CelestialBodyType)tempType;
    if (!readIntFromFile(&pBody->size, fp, "Error reading celestial body size.\n")) return 1;
    if (!readIntFromFile(&pBody->distance, fp, "Error reading celestial body distance.\n")) return 1;
    if (!readIntFromFile(&pBody->location.x, fp, "Error reading celestial body location x.\n")) return 1;
    if (!readIntFromFile(&pBody->location.y, fp, "Error reading celestial body location y.\n")) return 1;

    return 0;
}


int compareBodyByDistance(const void *body1, const void *body2){
    const CelestialBody * pBody1 = *(const CelestialBody **)body1;
    const CelestialBody * pBody2 = *(const CelestialBody **)body2;
    return pBody1->distance - pBody2->distance;
}

int compareBodyByType(const void *body1, const void *body2){
    const CelestialBody * pBody1 = *(const CelestialBody **)body1;
    const CelestialBody * pBody2 = *(const CelestialBody **)body2;
    return pBody1->type - pBody2->type;
}

int compareBodyByDate(const void *body1, const void *body2) {
    const CelestialBody *pBody1 = *(const CelestialBody **) body1;
    const CelestialBody *pBody2 = *(const CelestialBody **) body2;
    return compareDate(&pBody1->dateOfDiscovery, &pBody2->dateOfDiscovery);
}