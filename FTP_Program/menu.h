#ifndef MENU_MAIN
#define MENU_MAIN

#include "createprof.h"
#include "profSelect.h"

void menucall();

typedef void (*callmenu)();

int mainmenu() { //main menu function with basic menu functions

    callmenu CallMenu0 = menucall;

    char input[10];
    system("cls");
    printf("\n====================\n");
    printf("[1] - Create Profile\n");
    printf("[2] - Select Profile\n");
    printf("[3] - Exit          \n");
    printf("====================\n\n");
    printf("Enter Input: ");
    gets(input);
    switch(*input) {
        case '1':
            fflush(stdin);
            createProfileMenu();
            break;
        case '2':
            fflush(stdin);
            viewProf();
            break;
        case '3':
            break;
        default:
            printf("\nError. Input is Invalid.\n");
            fflush(stdin);
            (*CallMenu0)();
            break;
    }
    fflush(stdin);
    return 0;
}

void menucall() {
    mainmenu();
}

#endif