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
        printf("Enter expected duration in years: ");
        if (scanf("%d", &num) != 1 || num <= 0) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a positive integer.\n");
        } else {
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

void printExpedition (Expedition* expedition){
    if (expedition == NULL) {
        printf("Invalid parameters.\n");
        return;
    }
    printf("____________________\n");
    printf("Expedition:\nid: %d\n", expedition->id);
    printf("Goal: %s\n", ExpeditionTypesStr[expedition->type]);
    printf("Destination ID: %d\n", expedition->destinationID);
    printf("Expedition starts: %d/%d/%d\n", expedition->startDate.day, expedition->startDate.month, expedition->startDate.year);
    printf("Duration: %d\n", expedition->duration);
}


int saveExpeditionToFileBin(const Expedition* expedition, FILE* fp)
{
    if (expedition == NULL || fp == NULL) {
        printf("Invalid parameters for saving expedition.\n");
        return 1;
    }

    if (fwrite(&expedition->id, sizeof(expedition->id), 1, fp) != 1) {
        printf("Failed to write expedition ID.\n");
        return 1;
    }


    if (fwrite(&expedition->type, sizeof(expedition->type), 1, fp) != 1) {
        printf("Failed to write expedition type.\n");
        return 1;
    }


    if (writeIntToFile(expedition->destinationID, fp, "Failed to write destination ID.\n") != 1) {
        return 1; // Error
    }


    if (fwrite(&expedition->startDate, sizeof(expedition->startDate), 1, fp) != 1) {
        printf("Failed to write start date.\n");
        return 1;
    }


    if (writeIntToFile(expedition->duration, fp, "Failed to write duration.\n") != 1) {
        return 1; // Error
    }

    return 0; // Success
}


int loadExpeditionFromFileBin(Expedition* expedition, FILE* fp) {
    if (expedition == NULL || fp == NULL) {
        printf("Invalid parameters for loading expedition.\n");
        return 1;
    }


    if (fread(&(expedition->id), sizeof(expedition->id), 1, fp) != 1) {
        printf("Failed to read expedition ID.\n");
        return 1;
    }


    int typeTemp;
    if (fread(&typeTemp, sizeof(typeTemp), 1, fp) != 1) {
        printf("Failed to read expedition type.\n");
        return 1;
    }
    expedition->type = (ExpeditionType)typeTemp; // Cast and assign to enum type


    if (fread(&(expedition->destinationID), sizeof(expedition->destinationID), 1, fp) != 1) {
        printf("Failed to read destination ID.\n");
        return 1;
    }


    if (fread(&(expedition->startDate.day), sizeof(expedition->startDate.day), 1, fp) != 1) {
        printf("Failed to read start day.\n");
        return 1;
    }
    if (fread(&(expedition->startDate.month), sizeof(expedition->startDate.month), 1, fp) != 1) {
        printf("Failed to read start month.\n");
        return 1;
    }
    if (fread(&(expedition->startDate.year), sizeof(expedition->startDate.year), 1, fp) != 1) {
        printf("Failed to read start year.\n");
        return 1;
    }


    if (fread(&(expedition->duration), sizeof(expedition->duration), 1, fp) != 1) {
        printf("Failed to read duration.\n");
        return 1;
    }

    return 0;
}




int saveExpeditionToFileTxt(const Expedition* pExpedition, FILE* fp) {
    if (!fp || !pExpedition) {
        printf("Invalid file pointer or expedition data.\n");
        return 1;
    }


    printf("Debug: Saving Expedition ID %d, Duration %d, Dest ID %d, Type %d, Date %d-%d-%d\n",
           pExpedition->id,
           pExpedition->duration,
           pExpedition->destinationID,
           pExpedition->type,
           pExpedition->startDate.year,
           pExpedition->startDate.month,
           pExpedition->startDate.day);

    if (fprintf(fp, "%d %d %d %d %d-%d-%d\n",
                pExpedition->id,
                pExpedition->duration,
                pExpedition->destinationID,
                pExpedition->type,
                pExpedition->startDate.year,
                pExpedition->startDate.month,
                pExpedition->startDate.day) < 0) {
        printf("Failed to write expedition data to file.\n");
        return 1;
    }
    return 0;
}
int loadExpeditionFromFileTxt(Expedition* expedition, FILE* fp) {
    if (!fp || !expedition) {
        printf("Invalid parameters for loading expedition.\n");
        return 1;
    }


    if (fscanf(fp, "%d %d %d %d %d-%d-%d\n",
               &expedition->id,
               &expedition->duration,
               &expedition->destinationID,
               (int*)&expedition->type,
               &expedition->startDate.year,
               &expedition->startDate.month,
               &expedition->startDate.day) != 7) {
        printf("Failed to read expedition data from file.\n");
        return 1;
    }

    return 0;
}