//
// Created by Vlad Pavlyuk on 03/04/2024.
//

#include "Expedition.h"

int initExpedition (Expedition* expedition, CelestialBody* destination){
    if (!expedition || !destination) {
        printf("expedition or destination is null");
        return 1;
    }

    getCorrectDate(&expedition->startDate);
    expedition->duration = getDuration();
    expedition->type = chooseExpeditionType();
    expedition->destination = destination;
    expedition->id = expIdCount++;

    return 0;
}

int getDuration (){
    int num;

    while (1) {
        printf("Enter a positive integer: ");
        if (scanf("%d", &num) != 1 || num <= 0) {
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
ExpeditionType chooseExpeditionType(){
    int choice;
    printf("Choose the type the expedition:\n");
    for (int i = 0; i < eNofOptions; i++) {
        printf("[%d] %s\n", i, ExpeditonTypesStr[i]);
    }
    printf("Enter your choice (0 to %d): ", eNofOptions - 1);
    scanf("%d", &choice);

    while (choice < 0 || choice >= eNofOptions) {
        printf("Invalid choice. Please enter a number between 0 and %d: ", eNofOptions - 1);
        scanf("%d", &choice);
    }
    printf("\n\n");

    return (ExpeditionType)choice;

}

void printExpedtion (Expedition* expedition){
    printf("____________________\n");
    printf("mission:\nid: %d\n", expedition->id);
    printf("type: %s\n", ExpeditonTypesStr[expedition->type]);
    printf("target: %d\n", expedition->destination->ID);
    printf("start: %d##%d##%d\n", expedition->startDate.day, expedition->startDate.month, expedition->startDate.year);
    printf("duration: %d", expedition->duration);
}



























