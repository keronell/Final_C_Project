#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SpaceAgency.h"
#include "StringToolBox.h"
#include "Expedition.h"


void     initSpaceAgency(SpaceAgency* pAgency)
{
    if (pAgency == NULL)
        return;

    printf("Enter Agency name\t");
    setName(pAgency);

    pAgency->numOfBodiesFound = 0;

    // The expedition field is not initialized here

}

void    setName(SpaceAgency* pAgency)
{
    char temp[255];
    myGets(temp, MAX_STR_LEN, stdin);
    pAgency->name = temp;
}

int     addExpedition(Expedition pExpedition)
{

    return 0;
}

void printSpaceAgency(const SpaceAgency* pAgency)
{
    if (pAgency == NULL)
    {
        printf("Space Agency data is not available.\n");
        return;
    }

    printf("Space Agency Name:\t\t %s\n", pAgency->name);
    printf("Number of Celestial Bodies Found:\t %d\n", pAgency->numOfBodiesFound);

    // If you had more information about expeditions, you could print it here.
    // For example: printExpeditions(pAgency->expedition);
}
