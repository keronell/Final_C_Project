//
// Created by Vlad Pavlyuk on 05/04/2024.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SpaceMap.h"

int initSpaceMap (SpaceMap* spaceMap){
    printf("\n\nMap Initialization: \n");
    getTwoPositiveIntegers(&spaceMap->rows, &spaceMap->cols);
    spaceMap->data = malloc(spaceMap->rows * sizeof(int*));
    if (spaceMap->data == NULL) return 1;
    for (int i = 0; i < spaceMap->rows; i++) {
        spaceMap->data[i] = malloc(spaceMap->cols * sizeof(int));
        if (!spaceMap->data[i]) return 1;
    }
    return 0;
}


int addCelestialBodytoMap (SpaceMap* spaceMap, CelestialBody* newBody){
    if (!spaceMap || !newBody) {
        printf("cant add new body");
        return 1;
    }
//    int radius = newBody->size;
        int radius = 2;

    addCircleToMatrix(spaceMap,newBody->location, radius);
    return 0;
}

int     addExpeditiontoMap(Expedition pExpedition);
int rmCelestialBody (CelestialBody* body);
int rmExpedition (Expedition* expedition);
void freeSpaceMap (SpaceMap* spaceMap);


void getTwoPositiveIntegers (int* rows, int* columns) {
    do {
        printf("enter height: ");
        scanf("%d", rows);
    } while (*rows <= 0);  // Repeat until a positive integer is entered

    do {
        printf("enter length: ");
        scanf("%d", columns);
    } while (*columns <= 0);  // Repeat until a positive integer is entered
}


//void freeMatrix(SpaceMap *matrix) {
//    for (int i = 0; i < matrix->rows; i++) {
//        free(matrix->data[i]);
//    }
//    free(matrix->data);
//    free(matrix);
//}


void markCircleCells(SpaceMap * matrix, Location center, int radius) {
    for (int i = center.x - radius; i <= center.x + radius; i++) {
        for (int j = center.y - radius; j <= center.y + radius; j++) {
            if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols) {
                double distance = sqrt(pow(i - center.x, 2) + pow(j - center.y, 2));
                if (distance <= radius) {
                    matrix->data[i][j] = 1; // Mark cell as part of a circle
                }
            }
        }
    }
}

void addCircleToMatrix(SpaceMap * matrix, Location center, int radius) {
    // Check if the new circle overlaps with existing circles
    for (int i = center.x - radius - 1; i <= center.x + radius + 1; i++) {
        for (int j = center.y - radius - 1; j <= center.y + radius + 1; j++) {
            if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols && matrix->data[i][j] == 1) {
                // Circle overlaps with an existing circle, so we cannot add it
                printf("Cannot add circle. Overlaps with existing circle.\n");
                return;
            }
        }
    }

    // Mark cells of the new circle as part of it
    markCircleCells(matrix, center, radius);
}


void printMatrix(SpaceMap * matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%c ", matrix->data[i][j] ? '*' : ' '); // Print '*' if the element is 1, else print ' '
        }
        printf("\n");
    }
}