//
// Created by Alex Levi on 12/04/2024.
//
#include "input.h"

int getPositveInt (int lowerBound){
    int num;

    while (1) {

        if (scanf("%d", &num) != 1 || num <= lowerBound) {
            // Clear input buffer
            while (getchar() != '\n');
            printf("Invalid input. Please enter a positive integer.\n");
        } else {
            // Clear input buffer
            while (getchar() != '\n');
            return num;
        }
    }
}