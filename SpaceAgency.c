#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SpaceAgency.h"
#include "StringToolBox.h"
#include "Expedition.h"


void     initSpaceAgency(SpaceAgency* pAgency)
{
    printf("Enter Agency name\t");
    setName(pAgency);
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