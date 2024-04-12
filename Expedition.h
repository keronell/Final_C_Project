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
    CelestialBody*   destination;
}Expedition;




int initExpedition (Expedition* expedition, CelestialBody* destination);
int getDuration ();
ExpeditionType chooseExpeditionType();
void freeExpedition(void* data);
void printExpedtion (Expedition* expedition);

#endif //FINAL_C_PROJECT_EXPEDITION_H
