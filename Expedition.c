#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "Expedition.h"
#include "FileManager.h"


const char* ExpeditionTypesStr[eNofOptions] = {"Explore", "Colonial", "Spread democracy"};
static int expIdCount = 30000;

int initExpedition (Expedition* expedition, CelestialBody* destination){
    if (!expedition || !destination) {
        printf("expedition or destination is null");
        return 1;
    }

    getCorrectDate(&expedition->startDate);
    expedition->duration = getDuration();
    expedition->type = chooseExpeditionType();
    expedition->destinationID = destination->ID;
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
        printf("[%d] %s\n", i, ExpeditionTypesStr[i]);
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

void freeExpedition(void* data)
{
    Expedition* expedition = (Expedition*)data;

    if (expedition != NULL)
        free(expedition);

}

void printExpedtion (Expedition* expedition){
    printf("____________________\n");
    printf("mission:\nid: %d\n", expedition->id);
    printf("type: %s\n", ExpeditionTypesStr[expedition->type]);
    printf("target: %d\n", expedition->destinationID);
    printf("start: %d##%d##%d\n", expedition->startDate.day, expedition->startDate.month, expedition->startDate.year);
    printf("duration: %d", expedition->duration);
}


int saveExpeditionToFile(const Expedition* expedition, FILE* fp)
{
    if (expedition == NULL || fp == NULL) {
        printf("Invalid parameters for saving expedition.\n");
        return 0;
    }

    // Write the Expedition ID
    if (fwrite(&expedition->id, sizeof(expedition->id), 1, fp) != 1) {
        printf("Failed to write expedition ID.\n");
        return 0;
    }

    // Write the Expedition Type
    if (fwrite(&expedition->type, sizeof(expedition->type), 1, fp) != 1) {
        printf("Failed to write expedition type.\n");
        return 0;
    }

    // Write the destination ID
    if (writeIntToFile(expedition->destinationID,fp,  "Failed to write destination ID.\n") != 1) {
        return 0;
    }

    // Write the start date
    if (fwrite(&expedition->startDate, sizeof(expedition->startDate), 1, fp) != 1) {
        printf("Failed to write start date.\n");
        return 0;
    }

    // Write the duration of the expedition
    if (writeIntToFile(expedition->duration,fp, "Failed to write duration.\n") != 1) {
        return 0;
    }

    return 1; // Success
}

int loadExpeditionFromFile(Expedition* expedition, FILE* fp)
{
    if (expedition == NULL || fp == NULL) {
        printf("Invalid parameters for loading expedition.\n");
        return 0;
    }

    // Read the Expedition ID
    if (!readIntFromFile(&(expedition->id), fp, "Failed to read expedition ID.\n")) {
        return 0;
    }

    // Read the Expedition Type
    if (!readIntFromFile((int*)&(expedition->type), fp, "Failed to read expedition type.\n")) {
        return 0;
    }

    int destinationId;
    if (!readIntFromFile(&expedition->destinationID, fp, "Failed to read destination ID.\n")) {
        return 0;
    }
    if (!readIntFromFile(&(expedition->startDate.day), fp, "Failed to read start day.\n")) {
        return 0;
    }
    if (!readIntFromFile(&(expedition->startDate.month), fp, "Failed to read start month.\n")) {
        return 0;
    }
    if (!readIntFromFile(&(expedition->startDate.year), fp, "Failed to read start year.\n")) {
        return 0;
    }

    if (!readIntFromFile(&(expedition->duration), fp, "Failed to read duration.\n")) {
        return 0;
    }

    return 1; // Success
}