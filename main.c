#include <stdio.h>
#include <stdlib.h>



#include "SpaceControlSystem.h"
#include "AgencyManager.h"
#include "CelestialBody.h"
#include "Expedition.h"
#include "main.h"
void MapTest (){
    int choice  = 1;

    if (choice == 1){
        SpaceMap myMap;
        initSpaceMap(&myMap);

        CelestialBody body1;
        initCelestialBody(&body1);

        CelestialBody body2;
        initCelestialBody(&body2);


        addCelestialBodytoMap(&myMap, &body1);
        addCelestialBodytoMap(&myMap, &body2);

        printSpaceMap(&myMap);
    }

}



void displayMenu() {

    //  menu options:
    //  automatic DB load
    //  1) add Celestial body
    //  2) add expedition
    //  3) add agency
    //  4) print space map
    //  5) calculate expedition time
    //  6) print all bodies DB
    //  7) print all expeditions
    //  8) print all agencies

//    printf("\n--- Welcome to Space Control System  ---\n");
//    printf("---- LOADING CELESTIAL BODIES DATABASE ----\n");
//    if(loadDB())
//        printf("---- DATABASE LOADED SUCCESSFULLY ----\n");
//    else
//        printf("Error while loading Database!\n");
//
//    printf("1. Option One\n");
//    printf("2. Option Two\n");
//    printf("3. Option Three\n");
//    printf("4. Exit\n");
//    printf("Enter your choice (1-4): ");
    SpaceControlSystem controlSystem;
    initSystem(&controlSystem);

    // Initialize Agency Manager
    Agency agencyManager;
    initAgency(&agencyManager);

    // Initialize 3 Space Agencies
    SpaceAgency agency1, agency2, agency3;
    initSpaceAgency(&agency1);
    initSpaceAgency(&agency2);
    initSpaceAgency(&agency3);

    // Add Space Agencies to Agency Manager
    addSpaceAgency(&agencyManager, &agency1);
    addSpaceAgency(&agencyManager, &agency2);
    addSpaceAgency(&agencyManager, &agency3);

    // Initialize 10 Celestial Bodies
    CelestialBody bodies[10];
    for (int i = 0; i < 3; i++) {
        initCelestialBody(&bodies[i]);
        // Add each celestial body to the Space Control System
        addCelestialBody(&controlSystem, &bodies[i]);
    }

    Expedition expedition1, expedition2;

    if (initExpedition(&expedition1, &bodies[0]) != 0) {
        printf("Failed to initialize the first expedition.\n");
        return ;
    }

    if (initExpedition(&expedition2, &bodies[1]) != 0) {
        printf("Failed to initialize the second expedition.\n");
        return ;
    }


    saveManagerToFileTxt(&agencyManager, AgencyManagerTxt);
//    loadManagerFromFileBin(&agencyManager,AgencyManagerBin);

    printExpedtion(&expedition1);
    printExpedtion(&expedition2);

}



int main() {
//    int choice;
//    char term;
//
//    while(1) {
//        displayMenu();
//
//        if (scanf("%d%c", &choice, &term) != 2 || term != '\n') {
//            printf("Invalid input, please enter a number.\n");
//            // Clear the input buffer
//            while (getchar() != '\n');
//        } else {
//            switch (choice) {
//                case 1:
//
//                    break;
//                case 2:
//
//                    break;
//                case 3:
//
//                    break;
//                case 4:
//                    printf("Exiting the program.\n");
//                    return 0;
//                default:
//                    printf("Invalid choice, please try again.\n");
//            }
//        }
//    }



//    MapTest();
    displayMenu();
}