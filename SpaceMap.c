#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SpaceMap.h"

int initSpaceMap (SpaceMap* spaceMap){
    getTwoPositiveIntegers(&spaceMap->rows, &spaceMap->cols);
    spaceMap->data = malloc(spaceMap->rows * sizeof(int*));
    if (spaceMap->data == NULL) return 1;
    for (int i = 0; i < spaceMap->rows; i++) {
        spaceMap->data[i] = malloc(spaceMap->cols * sizeof(int));
        if (!spaceMap->data[i]) return 1;
    }
    return 0;
}


int addCelestialBody (SpaceMap* spaceMap, CelestialBody* newBody){
    if (!spaceMap || !newBody) {
        printf("cant add new body");
        return 0;
    }
//    int radius = newBody->size;
        int radius = 3;

        int x = newBody->location.xAxis;
        int y = newBody->location.yAxis;

    addCircleToMatrix(spaceMap, x, y, radius);

}

int addExpedition (Expedition* newExpedition);
int rmCelestialBody (CelestialBody* body);
int rmExpedition (Expedition* expedition);
void freeSpaceMap (SpaceMap* spaceMap);


void getTwoPositiveIntegers (int* rows, int* columns) {
    do {
        printf("enter height: ");
        scanf("%d\n", rows);
    } while (*rows <= 0);  // Repeat until a positive integer is entered

    do {
        printf("enter length: ");
        scanf("%d\n", columns);
    } while (*columns <= 0);  // Repeat until a positive integer is entered
}


//void freeMatrix(SpaceMap *matrix) {
//    for (int i = 0; i < matrix->rows; i++) {
//        free(matrix->data[i]);
//    }
//    free(matrix->data);
//    free(matrix);
//}


void addCircleToMatrix(SpaceMap * spaceMap, int centerX, int centerY, int radius) {
    for (int i = 0; i < spaceMap->rows; i++) {
        for (int j = 0; j < spaceMap->cols; j++) {
            // Calculate distance from center to (i, j) using Euclidean distance formula
            double distance = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

            // Check if the distance is less than or equal to the radius (outline of circle)
            if (distance <= radius + 0.5 && distance >= radius - 0.5) {
                spaceMap->data[i][j] = 1; // Set the element to represent the circle's outline
            }
        }
    }
}

void printMatrix(SpaceMap * matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%c ", matrix->data[i][j] ? '*' : ' '); // Print '*' if the element is 1, else print ' '
        }
        printf("\n");
    }
}