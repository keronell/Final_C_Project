#include "main.h"

int main() {
    int option;
    int stop = 0;

    do {
        option = menu();
        switch (option) {
            // case
            case EXIT:
                printf("Bye bye\n");
                stop = 1;
                break;

            default:
                printf("Wrong option\n");
                break;
        }
    } while (!stop);
}

system("pause");
return 1;
}

int menu()
{
    int option;
    printf("\n\n");
    printf("Please choose one of the following options\n");
    for(int i = 0 ; i < eNofOptions ; i++)
        printf("%d - %s\n",i,str[i]);
    printf("%d - Quit\n", EXIT);
    scanf("%d", &option);

    //clean buffer
    char tav;
    scanf("%c", &tav);
    return option;
}