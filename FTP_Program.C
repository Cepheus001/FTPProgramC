#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
//#include <curl/curl.h>
#include <unistd.h>

void launchmain();

typedef void (*funcMainPtr)();

typedef struct Node_NoArgs {
    void (*PtrForFunc)();
    struct Node_NoArgs *next;
} Node_NoArgs;

typedef struct {
    char URI_SERV[256];
    char FTPPSWD[64];
    char FTPUSR[64];
} profileFTP;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void nodeAdd_NoArgs(Node_NoArgs **head, void (*PtrForFunc)()) {
    Node_NoArgs *node_new =(Node_NoArgs*)malloc(sizeof(Node_NoArgs));
    node_new->PtrForFunc = PtrForFunc;
    node_new->next = *head;
    *head = node_new;
}

void list_Free(Node_NoArgs *head) {
    while (head != NULL) {
        Node_NoArgs* tmp = head;
        head = head->next;
        free(tmp);
    }
}

void func_Call_Index_NoArgs(Node_NoArgs *head, int index) {
    int i = 0;
    while (head != NULL) {
        if (i == index) {
            head->PtrForFunc();
            return;
        }
        head = head->next;
        i++;
    }
    printf("Invalid Index entry. Exiting...");
}

void profileLoad(profileFTP *profile, const char *filename) {
    FILE *ProfileFTPFile = fopen(filename, "rb");
    if (!ProfileFTPFile) {
        fprintf(stderr, "Error - Unable to read file: %s\n", ProfileFTPFile);
        return;
    }
    fread(profile, sizeof(profileFTP), 1, ProfileFTPFile);
    fclose(ProfileFTPFile);
}

void saveProfile(const profileFTP *profile, const char *filename) {
    system("cls");
    FILE *ProfileFTPFile = fopen(filename, "wb");
    if (!ProfileFTPFile) {
        fprintf(stderr, "Error - Unable to open file to write to: %s\n", filename);
        return;
    }
    fwrite(profile, sizeof(profileFTP), 1, ProfileFTPFile);
    fclose(ProfileFTPFile);
}

void createProfile() {
    profileFTP usrprofile;
    Node_NoArgs *linkedlist = NULL;

    nodeAdd_NoArgs(&linkedlist, createProfile);

    funcMainPtr funcmainptr = launchmain;

    char yn;

    system("cls");
    printf("Enter the Desired URI you wish to connect to: ");
    scanf("%255s", &usrprofile.URI_SERV);
    system("cls");
    printf("Is this the correct information? Your URI is: %s", usrprofile.URI_SERV);
    printf("\nType [Y/N] to continue: ");
    scanf("%s", yn);
    switch(yn) {
        case 'y':
            system("cls");
            clearInputBuffer();
            break;
        case 'n':
            int yn2;
            system("cls");
            printf("\nWould you like to go back to the main menu?\n");
            printf("[1] - Main Menu\n");
            printf("[2] - Restart Profile Creation\n");
            scanf("%d", &yn2);
            if (yn2 == 1) {
                system("cls");
                list_Free(linkedlist);
                clearInputBuffer();
                (*funcmainptr)();
            } else if (yn2 == 2) {
                list_Free(linkedlist);
                clearInputBuffer();
                (*funcmainptr)();
            } else {
                printf("Invalid Input. Exiting...");
                sleep(3);
                system("cls");
                list_Free(linkedlist);
                clearInputBuffer();
                (*funcmainptr)();
            }
            break;
        default:
            printf("\nInvalid input. Resetting...");
            sleep(3);
            clearInputBuffer();
            list_Free(linkedlist);
            (*funcmainptr)();
    }
    clearInputBuffer();
}

void mainmenu() { //main menu function with basic menu functions
    
    Node_NoArgs *linkedlist = NULL;

    funcMainPtr funcmainptr = launchmain;

   // nodeAdd_NoArgs(&linkedlist, exit);
    nodeAdd_NoArgs(&linkedlist, createProfile);

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
            list_Free(linkedlist);
            clearInputBuffer();
            func_Call_Index_NoArgs(linkedlist, 0);
            break;
        case 2:
            list_Free(linkedlist);
            clearInputBuffer();
            break;
        case 3:
            list_Free(linkedlist);
            clearInputBuffer();
            break;
        default:
            printf("\nError. Input is Invalid.\n");
            clearInputBuffer();
            list_Free(linkedlist);
            (*funcmainptr)();
            break;
    }
    clearInputBuffer();
}

int main() {

    launchmain();

    return 0;
}

void launchmain() {
    mainmenu();
}