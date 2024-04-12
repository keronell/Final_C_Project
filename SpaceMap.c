//
// Created by Vlad Pavlyuk on 05/04/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "SpaceMap.h"

int initSpaceMap (SpaceMap* spaceMap){
    getTwoPositiveIntegers(&spaceMap->rows, &spaceMap->cols);
    spaceMap->data = malloc(spaceMap->rows * sizeof(char *));
    if (spaceMap->data == NULL) return 1;
    for (int i = 0; i < spaceMap->rows; i++) {
        spaceMap->data[i] = malloc(spaceMap->cols * sizeof(char));
        if (!spaceMap->data[i]) return 1;
    }
    return 0;
}


int addCelestialBody (CelestialBody* newBody);
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

//Matrix* createMatrix(int rows, int cols) {
//    Matrix *matrix = malloc(sizeof(Matrix));
//    matrix->rows = rows;
//    matrix->cols = cols;
//    matrix->data = malloc(rows * sizeof(int *));
//    for (int i = 0; i < rows; i++) {
//        matrix->data[i] = malloc(cols * sizeof(int));
//    }
//    return matrix;
//}
//
//void freeMatrix(Matrix *matrix) {
//    for (int i = 0; i < matrix->rows; i++) {
//        free(matrix->data[i]);
//    }
//    free(matrix->data);
//    free(matrix);
//}
