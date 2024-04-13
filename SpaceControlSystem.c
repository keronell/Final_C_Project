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

    addCelestialBodytoMap(&pSystem->spaceMap, newBody); // Adding each new body to the spaceMap
    return 0; // Success
}

int addExpeditionToAgency(Manager *pAgency, SpaceControlSystem *pSystem) {
    printAgencyManager(pAgency);
    int agencyIndex = -1;
    while (agencyIndex < 1 || agencyIndex > pAgency->agencyCounter) {
        printf("To which Manager you want to add an Expedition? Enter index (1 to %d): \n", pAgency->agencyCounter);
        scanf("%d", &agencyIndex);
        while (getchar() != '\n'); // Flush the newline character left by scanf

        if (agencyIndex < 1 || agencyIndex > pAgency->agencyCounter) {
            printf("Invalid Manager index. Please try again.\n");
        } else {
            agencyIndex--; // Adjust for zero-indexed array
            break; // Correct index selected, exit the loop
        }
    }

    if (pAgency->agencyArr[agencyIndex] == NULL) {
        printf("Selected Manager is not available.\n");
        return -1;
    }

    printf("Choose Celestial Bodies as a destination point:\n");
    for (int i = 0; i < pSystem->numOfBodies; i++) {
        printf("Celestial body number - %d ", i + 1);
        printCelestialBody(pSystem->CelestialBodyArr[0]);
    }

    int bodyIndex = -1;
    while (bodyIndex < 1 || bodyIndex > pSystem->numOfBodies) {
        printf("Select a celestial body for the expedition (enter index 1 to %d):\n", pSystem->numOfBodies);
        scanf("%d", &bodyIndex);
        while (getchar() != '\n'); // Flush the newline character left by scanf

        if (bodyIndex < 1 || bodyIndex > pSystem->numOfBodies) {
            printf("Invalid Celestial Body index. Please try again.\n");
        } else {
            bodyIndex--;
            break;
        }
    }

    Expedition *newExpedition = (Expedition *) malloc(sizeof(Expedition));
    if (newExpedition == NULL) {
        printf("Failed to allocate memory for new Expedition.\n");
        return 1;
    }

    initExpedition(newExpedition, pSystem->CelestialBodyArr[bodyIndex]);

    NODE* newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode == NULL) {
        printf("Failed to allocate memory for new list node.\n");
        free(newExpedition);
        return -1;
    }
    newNode->key = newExpedition;
    newNode->next = pAgency->expeditionList.head.next;
    pAgency->expeditionList.head.next = newNode;
    printExpedition(newExpedition);
    pAgency->agencyArr[agencyIndex]->expeditionID = newExpedition->id;
    pAgency->numOfExpeditions++;
    printf("Expedition successfully added to Manager '%s'.\n", pAgency->agencyArr[agencyIndex]->name);

    return 0;
}


void freeSystem(SpaceControlSystem *pSystem, Manager *pAgency) {
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


void printSpaceControlSystem(const SpaceControlSystem *pSystem, const Manager* pAgency) {
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
            printf("Celestial Body [%d]: NULL\n", i);
        }
    }

    printAgencyManager(pAgency);
}

int saveSystemToFileTxt(const SpaceControlSystem *pSystem, const Manager *pAgency, const char *fileName) {
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

int loadSystemFromFileTxt(SpaceControlSystem *pSystem, Manager *pAgency, const char *fileName) {
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


void findCelestialBody(const SpaceControlSystem *pSystem) {
    int (*compare)(const void *air1, const void *air2) = NULL;
    CelestialBody b = {0};
    CelestialBody *pBody = &b;

    switch (pSystem->sortOpt) {
        case eDistance:
            printf("%s\t", "Origin:");
            b.distance = getPositveInt(0);
            compare = compareBodyByDistance;
            break;

        case eType:
            printf("%s\t", "Destination:");
            b.type = chooseCelestialBodyType();
            compare = compareBodyByType;
            break;

        case eDate:
            getCorrectDate(&b.dateOfDiscovery);
            compare = compareBodyByDate;
            break;
        default:
            printf("cant find as the array is not sorted");
            return;

    }

    if (compare != NULL) {
        CelestialBody **pBodies = bsearch(&pBody, pSystem->CelestialBodyArr, pSystem->numOfBodies,
                                          sizeof(CelestialBody *), compare);
        if (pBodies == NULL)
            printf("Flight was not found\n");
        else {
            printf("Flight found, ");
            printCelestialBody(pBody);
        }
    } else {
        printf("The search cannot be performed, array not sorted\n");
    }

}

void sortCelestialBody(SpaceControlSystem *pSystem) {
    pSystem->sortOpt = showSortMenu();
    int (*compare)(const void *air1, const void *air2) = NULL;

    switch (pSystem->sortOpt) {
        case eDistance:
            compare = compareBodyByDistance;
            break;
        case eType:
            compare = compareBodyByType;
            break;
        case eDate:
            compare = compareBodyByDate;
            break;
        default:
            return;
    }

    if (compare != NULL)
        qsort(pSystem->CelestialBodyArr, pSystem->numOfBodies, sizeof(CelestialBody * ), compare);

}


int saveSystemToFileBin(const SpaceControlSystem *pSystem, const Manager *pAgency, const char *fileName) {
    FILE *fp = fopen(fileName, "wb");  // Open the file in binary write mode
    if (!fp) {
        printf("Cannot open file ('%s') for writing.\n", fileName);
        return 1;
    }

    // Save number of celestial bodies
    if (fwrite(&pSystem->numOfBodies, sizeof(pSystem->numOfBodies), 1, fp) != 1) {
        printf("Failed to write number of celestial bodies.\n");
        fclose(fp);
        return 1;
    }

    // Save celestial bodies
    for (int i = 0; i < pSystem->numOfBodies; i++) {
        if (pSystem->CelestialBodyArr[i] && saveCelestialBodyToFileBin(pSystem->CelestialBodyArr[i], fp)) {
            fclose(fp);
            return 1;  // Return 1 for error
        }
    }

    // Save the agency information
    if (saveManagerToFileBin(fp, pAgency)) {
        fclose(fp);
        return 1;  // Return 1 for error
    }

    fclose(fp);
    return 0;
}

int loadSystemFromFileBin(SpaceControlSystem *pSystem, Manager *pAgency, const char *fileName) {
    FILE *fp = fopen(fileName, "rb");  // Open the file in binary read mode
    if (!fp) {
        printf("Cannot open file ('%s') for reading.\n", fileName);
        return 1;
    }

    // Read number of celestial bodies
    if (fread(&pSystem->numOfBodies, sizeof(pSystem->numOfBodies), 1, fp) != 1) {
        printf("Failed to read number of celestial bodies.\n");
        fclose(fp);
        return 1;
    }

    // Allocate and load celestial bodies
    pSystem->CelestialBodyArr = (CelestialBody **)malloc(pSystem->numOfBodies * sizeof(CelestialBody *));
    if (pSystem->CelestialBodyArr == NULL) {
        printf("Memory allocation failed for celestial bodies.\n");
        fclose(fp);
        return 1;
    }

    for (int i = 0; i < pSystem->numOfBodies; i++) {
        pSystem->CelestialBodyArr[i] = (CelestialBody *)malloc(sizeof(CelestialBody));
        if (pSystem->CelestialBodyArr[i] == NULL || loadCelestialBodyFromFileBin(pSystem->CelestialBodyArr[i], fp)) {
            fclose(fp);
            return 1;  // Return 1 for error
        }
    }

    // Load the agency information
    if (loadManagerFromFileBin(pAgency, fp)) {
        fclose(fp);
        return 1;  // Return 1 for error
    }

    fclose(fp);
    return 0;
}

