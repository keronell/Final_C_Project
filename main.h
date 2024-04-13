#pragma once

#include "FileManager.h"
#include "SpaceMap.h"

#define SystemDataBin "AgencyManager.bin"
#define SystemDataTxt "SystemData.txt"

void welcomeScreen(SpaceControlSystem *pSystem, Agency *pAgency);
void displayMenu();
int menu();
void MapTest ();
int dataLoadLogic(SpaceControlSystem *pSystem, Agency *pAgency);


