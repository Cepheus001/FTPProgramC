#ifndef PROFILE_CREATE
#define PROFILE_CREATE

void menucall();

typedef void (*callmenu)();

typedef struct {
    char URI_SERV[256];
    char FTPPSWD[64];
    char FTPUSR[64];
} profileFTP;

int createProfile() {
    profileFTP usrprofile;

    callmenu CallMenu1 = menucall;

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
                clearInputBuffer();
                (*CallMenu1)();
            } else if (yn2 == 2) {
                clearInputBuffer();
                (*CallMenu1)();
            } else {
                printf("Invalid Input. Exiting...");
                sleep(3);
                system("cls");
                clearInputBuffer();
                (*CallMenu1)();
            }
            break;
        default:
            printf("\nInvalid input. Resetting...");
            sleep(3);
            clearInputBuffer();
            (*CallMenu1)();
    }
    clearInputBuffer();
    return 0;
}

#endif