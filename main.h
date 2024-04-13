#pragma once

#define SystemDataBin "AgencyManager.bin"
#define SystemDataTxt "SystemData.txt"

void welcomeScreen(SpaceControlSystem *pSystem, Agency *pAgency);
void displayMenu();

int menu();

void MapTest();


//Save, Load functions
int dataLoadLogic(SpaceControlSystem *pSystem, Agency *pAgency);
void dataSaveLogic(const SpaceControlSystem *pSystem, const Agency *pAgency);
