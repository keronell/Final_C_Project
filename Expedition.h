#ifndef FINAL_C_PROJECT_EXPEDITION_H
#define FINAL_C_PROJECT_EXPEDITION_H

#include "Date.h"
#include "CelestialBody.h"
typedef enum
{
    eExplore, eColonial, eSpreadDemocracy, eNofOptions
} ExpeditionType;



typedef struct
{
    int             id;
    Date            startDate;
    int             duration; // approximate time the mission will take
    ExpeditionType  type;
    int    destinationID;
}Expedition;




int initExpedition (Expedition* expedition, CelestialBody* destination);
int getDuration ();
ExpeditionType chooseExpeditionType();
void freeExpedition(void* data);
void printExpedition (Expedition* expedition);

int saveExpeditionToFileBin(const Expedition* expedition, FILE* fp);
int loadExpeditionFromFileBin(Expedition* expedition, FILE* fp);

int saveExpeditionToFileTxt(const Expedition* pExpedition, FILE* fp);
int loadExpeditionFromFileTxt(FILE* fp, Expedition* expedition);


#endif //FINAL_C_PROJECT_EXPEDITION_H
