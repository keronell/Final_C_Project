#include <stdio.h>
#include <stdlib.h>

#include "AgencyManager.h"
#include "SpaceControlSystem.h"
#include "SpaceMap.h"


#include "main.h"



void welcomeScreen(SpaceControlSystem *pSystem, Manager *pAgency)
{
    printf("\n--- Welcome to Space Control System  ---\n");
    if(dataLoadLogic(pSystem, pAgency)) {
        printf("---- INITIALIZING FRESH START SYSTEM CREATION ----\n");
        if(initSystem(pSystem)){
            printf("Failed to initialize System!\n");
            return;
        } else if(initAgency(pAgency)){
            printf("Failed to initialize Manager manager!\n");
            return;
        }
    }
    else
        printf("---- DATABASE LOADED SUCCESSFULLY ----\n");
}

void displayMenu()
{

    printf("\n1. Add Celestial body.\n");
    printf("2. Add agency to Agency Manager.\n");
    printf("3. Start new Expedition.\n");
    printf("4. Print all Agencies.\n");
    printf("5. Print Expedition list.\n");
    printf("6. Print Celestial bodies DataBase.\n");
    printf("7. Print all System Data.\n");
    printf("8. Search for Celestial body in DataBase.\n");
    printf("9. Sort Celestial Bodies.\n");
    printf("10. Show map of Celestial Bodies.\n");
    printf("0. Save current Data and EXIT.\n");

}



int main() {

    SpaceControlSystem pSystem;
    Manager pManager;

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
                    printf("Failed to add new Manager to Manager!\n");
                break;
            case 3:
                if(addExpeditionToAgency(&pManager,&pSystem))
                    printf("Failed to create new Expedition!\n");
                break;
            case 4:
                printAgencyManager(&pManager);
                break;
            case 5:
                printExpeditionList( &pManager);
                break;
            case 6:
                printCelestialBodies(&pSystem);
                break;
            case 7:
                printSpaceControlSystem(&pSystem, &pManager);
                break;
            case 8:
                sortCelestialBody(&pSystem);
                break;
            case 9:
                findCelestialBody(&pSystem);
                break;
            case 10:
                printSpaceMap(&pSystem.spaceMap);
                break;
            case 0:
                printf("Saving current Data and exiting...\n");
                dataSaveLogic(&pSystem,&pManager);
                    freeSystem(&pSystem,&pManager);
                exit(0);
                break;
            default:
                printf("Invalid choice, please enter a number from 0 to 9.\n");
                break;
        }

    }


}


int dataLoadLogic(SpaceControlSystem *pSystem, Manager *pAgency)
{
    int choice = -1;

    while (choice != 0) {
        printf("Choose from which origin you want to Load data:\n");
        printf("1] Binary file.\n");
        printf("2] Text file.\n");
        printf("0] Create fresh start.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:

                if (loadSystemFromFileBin(pSystem, pAgency, SystemDataBin)) {
                    printf("Failed to load from binary file.\n");
                    return 1;
                }
                return 0;

            case 2:
                if (loadSystemFromFileTxt(pSystem, pAgency, SystemDataTxt)) {
                    printf("Failed to load from text file.\n");
                    return 1;
                }
                return 0;

            case 0:
                printf("creating...\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
    return 1;
}

void dataSaveLogic(const SpaceControlSystem *pSystem, const Manager *pAgency)
{

    if(saveSystemToFileTxt(pSystem, pAgency,SystemDataTxt))
        printf("Failed to save in to text file.\n");


    if(saveSystemToFileBin(pSystem, pAgency, SystemDataBin))
        printf("Failed to save in to binary file.\n");
}