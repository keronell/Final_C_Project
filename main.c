#include <stdio.h>
#include <stdlib.h>

#include "SpaceControlSystem.h"
#include "AgencyManager.h"
#include "main.h"

void welcomeScreen(SpaceControlSystem *pSystem, Agency *pAgency)
{
    printf("\n--- Welcome to Space Control System  ---\n");
    if(dataLoadLogic(pSystem, pAgency)) {
        printf("Failed reading data from file!\n");
        printf("---- INITIALIZING FRESH START SYSTEM CREATION ----\n");
        if(initSystem(pSystem)){
            printf("Failed to initialize System!\n");
            return;
        } else if(initAgency(pAgency)){
            printf("Failed to initialize Agency manager!\n");
            return;
        }
    }
    else
        printf("---- DATABASE LOADED SUCCESSFULLY ----\n");
}

void displayMenu()
{

    printf("1. Add Celestial body.\n");
    printf("2. Add agency to Agency Manager.\n");
    printf("3. Start new Expedition.\n");
    printf("4. Print current Space map.\n");
    printf("5. Print Expedition list.\n");
    printf("6. Print Celestial bodies DataBase.\n");
    printf("7. Print all System Data.\n");
    printf("8. Search for Celestial body in DataBase.\n");
    printf("9. Sort Celestial Bodies.\n");
    printf("0. Save current Data and EXIT.\n");

}



int main() {

    SpaceControlSystem pSystem;
    Agency pManager;

    welcomeScreen(&pSystem,&pManager);
    int choice;

    while(1) {
        displayMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                if(addCelestialBody(&pSystem))
                    printf("Failed to add new Celestial Body!\n");
                break;
            case 2:
               if(addSpaceAgency(&pManager))
                   printf("Failed to add new Agency to Manager!\n");
                break;
            case 3:
                if(addExpeditionToAgency(&pManager,&pSystem))
                    printf("Failed to create new Expedition!\n");
                break;
            case 4:
                printf("Printing the current Space Map...\n");
                break;
            case 5:
                printf("Printing the Expedition List...\n");
                // Call printExpeditionList() here
                break;
            case 6:
                printf("Printing the Celestial Bodies DataBase...\n");
                // Call printCelestialBodiesDB() here
                break;
            case 7:
                printf("Printing all System Data...\n");
                // Call printSystemData() here
                break;
            case 8:
                printf("Searching for a Celestial Body in DataBase...\n");
                // Call searchCelestialBody() here
                break;
            case 9:
                printf("Sorting Celestial Bodies...\n");
                // Call sortCelestialBodies() here
                break;
            case 0:
                printf("Saving current Data and exiting...\n");
                // Call saveDataAndExit() here
                exit(0);
                break;
            default:
                printf("Invalid choice, please enter a number from 0 to 9.\n");
                break;
        }
    }

    return 0;
}


int dataLoadLogic(SpaceControlSystem *pSystem, Agency *pAgency)
{
    int choice = -1;

    while (choice < 3 && choice >0) {
        printf("Choose from which origin you want to Load data:\n");
        printf("1] Binary file.\n");
        printf("2] Text file.\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
//                loadSystemFromFileBin(pSystem, pAgency,SystemDataBin )
                break;
            case 2:
                if(loadSystemFromFileTxt(pSystem, pAgency,SystemDataTxt ))
                    return 1;
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}