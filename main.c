#include <stdio.h>
#include <stdlib.h>



#include "CelestialBody.h"
#include "main.h"




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
    CelestialBody   body;

    if (initCelestialBody(&body) == 0) {
        printCelestialBody(&body);
    } else {
        printf("Failed to initialize Celestial Body.\n");
    }

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




    displayMenu();
}