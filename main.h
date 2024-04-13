#pragma once

#define SystemDataBin "Manager.bin"
#define SystemDataTxt "SystemData.txt"

void welcomeScreen(SpaceControlSystem *pSystem, Manager *pAgency);
void displayMenu();

int menu();

void MapTest();


//Save, Load functions
int dataLoadLogic(SpaceControlSystem *pSystem, Manager *pAgency);
void dataSaveLogic(const SpaceControlSystem *pSystem, const Manager *pAgency);
