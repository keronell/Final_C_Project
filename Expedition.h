#ifndef FINAL_C_PROJECT_EXPEDITION_H
#define FINAL_C_PROJECT_EXPEDITION_H

#include "Date.h"
typedef enum
{
    eExplore, eColonial, eSpreadDemocracy, eNofOptions
} ExpeditionType;

typedef struct
{
    Date            startDate;
    Date            endDate;
    ExpeditionType  type;
    int             destPoints;

}Expedition;
#endif //FINAL_C_PROJECT_EXPEDITION_H
