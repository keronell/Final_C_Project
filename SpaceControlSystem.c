#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SpaceControlSystem.h"
#include "StringToolBox.h"


int initSystem(SpaceControlSystem *pSystem) {
    if (pSystem == NULL)
        return 1; // Indicate error


    // Allocate memory for the array of CelestialBody pointers with initial size of 1
    pSystem->CelestialBodyArr = (CelestialBody **) malloc(sizeof(CelestialBody *));
    if (pSystem->CelestialBodyArr == NULL)
        return -1; // Indicate error

    pSystem->CelestialBodyArr[0] = NULL; // Initialize the first pointer to NULL

    // Set numOfBodies to 0
    pSystem->numOfBodies = 0;

    // Set a default sorting option
    pSystem->sortOpt = eNone; // Or any other default sorting option

    //initSpaceMap(&pSystem->spaceMap); // alex added it


    return 0; // Success
}

int addCelestialBody(SpaceControlSystem *pSystem) {
    CelestialBody *newBody = (CelestialBody *) malloc(sizeof(CelestialBody));
    if (newBody == NULL) {
        printf("Error: Memory allocation for new CelestialBody failed.\n");
        return 1;
    }

    initCelestialBody(newBody);

    // Resize the array to hold one more CelestialBody pointer
    CelestialBody **tempArr = (CelestialBody **) realloc(pSystem->CelestialBodyArr,
                                                         (pSystem->numOfBodies + 1) * sizeof(CelestialBody *));
    if (tempArr == NULL) {
        printf("Error: Memory reallocation failed.\n");
        free(newBody);
        return -1;
    }

    pSystem->CelestialBodyArr = tempArr;
    pSystem->CelestialBodyArr[pSystem->numOfBodies] = newBody;
    pSystem->numOfBodies++;

    //addCelestialBodytoMap(&pSystem->spaceMap, newBody); // Adding each new body to the spaceMap
    return 0; // Success
}

int addExpeditionToAgency(Agency *pAgency, SpaceControlSystem *pSystem) {
    printAgencyManager(pAgency);
    int agencyIndex = -1;
    while (agencyIndex < 1 || agencyIndex > pAgency->agencyCounter) {
        printf("To which Agency you want to add an Expedition? Enter index (1 to %d): \n", pAgency->agencyCounter);
        scanf("%d", &agencyIndex);
        if (agencyIndex < 1 || agencyIndex > pAgency->agencyCounter) {
            printf("Invalid Agency index. Please try again.\n");
        } else {
            agencyIndex--; // Adjust for zero-indexed array
        }
    }

    if (pAgency->agencyArr[agencyIndex] == NULL) {
        printf("Selected Agency is not available.\n");
        return -1;
    }

    printf("Choose Celestial Bodies as a destination point:\n");
    for (int i = 0; i < pSystem->numOfBodies; i++) {
        printf("%d) ", i + 1);
        printCelestialBody(pSystem->CelestialBodyArr[0]);
    }

    int bodyIndex = -1;
    while (bodyIndex < 1 || bodyIndex > pSystem->numOfBodies) {
        printf("Select a celestial body for the expedition (enter index 1 to %d):\n", pSystem->numOfBodies);
        scanf("%d", &bodyIndex);
        if (bodyIndex < 1 || bodyIndex > pSystem->numOfBodies) {
            printf("Invalid Celestial Body index. Please try again.\n");
        } else {
            bodyIndex--;  // Adjust for zero-indexed array
        }
    }

    Expedition *newExpedition = (Expedition *) malloc(sizeof(Expedition));
    if (newExpedition == NULL) {
        printf("Failed to allocate memory for new Expedition.\n");
        return 1;
    }

    initExpedition(newExpedition, pSystem->CelestialBodyArr[bodyIndex]);
    printf("Expedition successfully added to Agency '%s'.\n", pAgency->agencyArr[agencyIndex]->name);
    return 0;
}


void freeSystem(SpaceControlSystem *pSystem, Agency *pAgency) {
    if (pSystem->CelestialBodyArr != NULL) {
        for (int i = 0; i < pSystem->numOfBodies; i++) {
            if (pSystem->CelestialBodyArr[i] != NULL) {
                freeCelestialBody(
                        pSystem->CelestialBodyArr[i]);  // Assumes this function correctly frees a CelestialBody
                pSystem->CelestialBodyArr[i] = NULL;
            }
        }
        free(pSystem->CelestialBodyArr);
        pSystem->CelestialBodyArr = NULL;
    }
    // freeSpaceMap(pSystem->spaceMap); // Uncomment and implement if there's a space map or similar structure

    if (pAgency != NULL) {
        freeAgencyManager(pAgency);
    }
}


void printSpaceControlSystem(const SpaceControlSystem *pSystem, const Agency* pAgency) {
    if (pSystem == NULL) {
        printf("Error: SpaceControlSystem pointer is NULL.\n");
        return;
    }

    printf("Number of Celestial Bodies: %d\n", pSystem->numOfBodies);
    printf("Celestial Bodies:\n");

    for (int i = 0; i < pSystem->numOfBodies; i++) {
        if (pSystem->CelestialBodyArr[i] != NULL) {
            printCelestialBody(pSystem->CelestialBodyArr[i]);
        } else {
            printf("Celestial Body %d: NULL\n", i);
        }
    }

    printAgencyManager(pAgency);
}

int saveSystemToFileTxt(const SpaceControlSystem *pSystem, const Agency *pAgency, const char *fileName) {
    if (pSystem == NULL) {
        printf("System is not initialized!\n");
        return 1;
    }

    FILE *fp = fopen(fileName, "w");
    if (!fp) {
        printf("Cannot open file ('%s') for writing.\n", fileName);
        return 1;
    }

    // Save the number of celestial bodies and the sorting option directly
    fprintf(fp, "%d %d\n", pSystem->numOfBodies, pSystem->sortOpt);

    // Save each celestial body directly
    for (int i = 0; i < pSystem->numOfBodies; i++) {
        if (pSystem->CelestialBodyArr[i] != NULL) {
            saveCelestialBodyToFileTxt(fp, pSystem->CelestialBodyArr[i]);
        }
    }

    // Save agencies directly
    if (saveManagerToFileTxt(fp, pAgency)) {
        printf("Failed to save Manager data to file!\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}

int loadSystemFromFileTxt(SpaceControlSystem *pSystem, Agency *pAgency, const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (!fp) {
        printf("Cannot open file ('%s') for reading.\n", fileName);
        return 1;
    }

    // Read the number of celestial bodies and sorting option
    if (fscanf(fp, "%d %d", &pSystem->numOfBodies, &pSystem->sortOpt) != 2) {
        printf("Failed to read system details.\n");
        fclose(fp);
        return 1;
    }

    // Allocate memory for celestial bodies
    pSystem->CelestialBodyArr = (CelestialBody**) malloc(pSystem->numOfBodies * sizeof(CelestialBody*));
    if (pSystem->CelestialBodyArr == NULL) {
        printf("Memory allocation failed for celestial bodies.\n");
        fclose(fp);
        return 1;
    }

    for (int i = 0; i < pSystem->numOfBodies; i++) {
        pSystem->CelestialBodyArr[i] = (CelestialBody*) malloc(sizeof(CelestialBody));
        if (pSystem->CelestialBodyArr[i] == NULL) {
            printf("Memory allocation failed for a celestial body.\n");
            fclose(fp);
            return 1;
        }
        if (loadCelestialBodyFromFile(pSystem->CelestialBodyArr[i], fp)) {
            printf("Failed to load celestial body.\n");
            fclose(fp);
            return 1;
        }
    }

    if (loadManagerFromFileTxt(pAgency, fp)) {
        printf("Failed to load agency details.\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}


eSortOption showSortMenu() {
    int opt;
    printf("Base on what field do you want to sort?\n");
    do {
        for (int i = 1; i < eNofSortOpt; i++)
            printf("Enter %d for %s\n", i, sortOptStr[i]);
        scanf("%d", &opt);
    } while (opt < 0 || opt >= eNofSortOpt);

    return (eSortOption) opt;
}


//void findCelestialBody(const SpaceControlSystem *pSystem) {
//    int (*compare)(const void *air1, const void *air2) = NULL;
//    CelestialBody b = {0};
//    CelestialBody *pBody = &b;
//
//    switch (pSystem->sortOpt) {
//        case eDistance:
//            printf("%s\t", "Origin:");
//            b.distance = getPositveInt(0);
//            compare = compareBodyByDistance;
//            break;
//
//        case eType:
//            printf("%s\t", "Destination:");
//            b.type = chooseCelestialBodyType();
//            compare = compareBodyByType;
//            break;
//
//        case eDate:
//            getCorrectDate(&b.dateOfDiscovery);
//            compare = compareBodyByDate;
//            break;
//
//    }
//
//    if (compare != NULL) {
//        CelestialBody **pBodies = bsearch(&pBody, pSystem->CelestialBodyArr, pSystem->numOfBodies,
//                                          sizeof(CelestialBody *), compare);
//        if (pBodies == NULL)
//            printf("Flight was not found\n");
//        else {
//            printf("Flight found, ");
//            printCelestialBody(pBody);
//        }
//    } else {
//        printf("The search cannot be performed, array not sorted\n");
//    }
//
//}

//void sortCelestialBody(SpaceControlSystem *pSystem) {
//    pComp->flightSortOpt = showSortMenu();
//    int (*compare)(const void *air1, const void *air2) = NULL;
//
//    switch (pComp->flightSortOpt) {
//        case eSourceCode:
//            compare = compareFlightBySourceCode;
//            break;
//        case eDestCode:
//            compare = compareFlightByDestCode;
//            break;
//        case eDate:
//            compare = compareFlightByDate;
//            break;
//    }
//
//    if (compare != NULL)
//        qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight * ), compare);
//
//}
//