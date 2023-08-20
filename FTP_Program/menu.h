#ifndef MENU_MAIN
#define MENU_MAIN

#include "buffclear.h"
#include "createprof.h"

void menucall();

typedef void (*callmenu)();


int mainmenu() { //main menu function with basic menu functions

    callmenu CallMenu0 = menucall;

    int input;
    system("cls");
    printf("\n====================\n");
    printf("[1] - Create Profile\n");
    printf("[2] - Select Profile\n");
    printf("[3] - Exit          \n");
    printf("====================\n\n");
    printf("Enter Input: ");
    scanf("%d", &input);
    switch(input) {
        case 1:
            clearInputBuffer();
            createProfile();
            break;
        case 2:
            clearInputBuffer();
            break;
        case 3:
            clearInputBuffer();
            break;
        default:
            printf("\nError. Input is Invalid.\n");
            clearInputBuffer();
            (*CallMenu0)();
            break;
    }
    clearInputBuffer();
    return 0;
}

void menucall() {
    mainmenu();
}

#endif