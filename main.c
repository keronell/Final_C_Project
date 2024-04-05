#include <stdio.h>
#include <stdlib.h>



#include "CelestialBody.h"
#include "main.h"




void displayMenu() {

    //  menu options:
    //  automatic DB load
    //  add Celestial body
    //  add expedition
    //  add agency
    //  print space map
    //  calculate expedition time
    //  print all bodies DB
    //  print all expeditions
    //  print all agencies

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