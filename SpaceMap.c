#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SpaceMap.h"
#include "input.h"




void addEarth (SpaceMap* spaceMap) {
    CelestialBody Earth = {0000, 1000, 0, spaceMap->rows/2, spaceMap->cols/2, ePlanet};
    addCelestialBodytoMap(spaceMap, &Earth);
}

int initSpaceMap (SpaceMap* spaceMap){
    int size;
    printf("\n\nMap Initialization: \n");
    printf("enter size of the map: ");
    size = getPositveInt(10);
    spaceMap->rows = size;
    spaceMap->cols = size;
    
    spaceMap->data = malloc(spaceMap->rows * sizeof(int*));
    if (spaceMap->data == NULL) return 1;
    for (int i = 0; i < spaceMap->rows; i++) {
        spaceMap->data[i] = malloc(spaceMap->cols * sizeof(int));
        if (!spaceMap->data[i]) return 1;
    }



    return 0;
}


int addCelestialBodytoMap (SpaceMap* spaceMap, CelestialBody* newBody){
    int radius;
    char sign;
    
    if (!spaceMap || !newBody) {
        printf("cant add new body");
        return 1;
    }

    switch (newBody->type) {
        case eAsteroid:
            radius = 1;
            sign = '!';
            break;
        case ePlanet:
            radius = 2;
            sign = 'o';
            break;
        case eStar:
            radius = 3;
            sign = '*';
            break;
        case eNofTypes:
            radius = 0;
            return 1;
            break;
    }
    
    addCircleToMatrix(spaceMap,newBody->location, radius);
    return 0;
}

int     addExpeditiontoMap(Expedition pExpedition);
int rmCelestialBody (CelestialBody* body);
int rmExpedition (Expedition* expedition);
void freeSpaceMap (SpaceMap* spaceMap);




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


void printSpaceMap(SpaceMap * matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%c ", matrix->data[i][j] ? '*' : ' '); // Print '*' if the element is 1, else print ' '
        }
        printf("\n");
    }
}



//void plotPoint(SpaceMap * matrix, int x, int y, char symbol) {
//    if (x >= 0 && x < matrix->cols && y >= 0 && y < matrix->rows) {
//        matrix->data[y][x] = symbol;
//    }
//}
//
//void drawLine(SpaceMap * matrix, Point start, Point end, char symbol) {
//    int dx = abs(end.x - start.x);
//    int dy = abs(end.y - start.y);
//    int sx = start.x < end.x ? 1 : -1;
//    int sy = start.y < end.y ? 1 : -1;
//    int err = dx - dy;
//    int e2;
//
//    while (1) {
//        plotPoint(matrix, start.x, start.y, symbol);
//        if (start.x == end.x && start.y == end.y) break;
//        e2 = 2 * err;
//        if (e2 > -dy) {
//            err -= dy;
//            start.x += sx;
//        }
//        if (e2 < dx) {
//            err += dx;
//            start.y += sy;
//        }
//    }
//}
//
//void connectDotsWithoutCrossing(SpaceMap * matrix,  dot1, Point dot2, char symbol) {
//    int dx = abs(dot2.x - dot1.x);
//    int dy = abs(dot2.y - dot1.y);
//
//    if (dx > dy) {
//        if (dot1.x > dot2.x) {
//            drawLine(matrix, dot2, dot1, symbol);
//        } else {
//            drawLine(matrix, dot1, dot2, symbol);
//        }
//    } else {
//        if (dot1.y > dot2.y) {
//            drawLine(matrix, dot2, dot1, symbol);
//        } else {
//            drawLine(matrix, dot1, dot2, symbol);
//        }
//    }
//}


