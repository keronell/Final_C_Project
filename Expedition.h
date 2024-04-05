#ifndef FINAL_C_PROJECT_EXPEDITION_H
#define FINAL_C_PROJECT_EXPEDITION_H

#include "Date.h"
typedef enum
{
    eExplore, eColonial, eNofOptions
} ExpeditionType;
typedef struct Expedition
{
    Date    startDate;
    Date    endDate;
    ExpeditionType  type;
    int     destPoints;

};
#endif //FINAL_C_PROJECT_EXPEDITION_H
