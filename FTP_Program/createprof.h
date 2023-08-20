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

    char yn[10];

    system("cls");
    printf("Enter the Desired URI you wish to connect to: ");
    scanf(" %255s", &usrprofile.URI_SERV);
    clearCharBuff();
    system("cls");
    printf("Is this the correct information? Your URI is: %s", usrprofile.URI_SERV);
    printf("\nType [Y/N] to continue: ");
    gets(yn);
    printf("\n");
    switch(*yn) {
        case 'y': case 'Y':
            system("cls");
            fflush(stdin);
            break;
        case 'n': case 'N':
            fflush(stdin);
            char yn2[10];
            system("cls");
            printf("Would you like to go back to the main menu?\n");
            printf("[1] - Main Menu\n");
            printf("[2] - Restart Profile Creation\n");
            printf("\nEnter your choice here: ");
            gets(yn2);
            switch(*yn2) {
                case '1':
                    system("cls");
                    fflush(stdin);
                    (*CallMenu1)();
                    break;
                case '2':
                    fflush(stdin);
                    (*CallMenu1)();
                    break;
                default:
                    printf("Invalid Input. Exiting...");
                    sleep(3);
                    system("cls");

                    fflush(stdin);
                    (*CallMenu1)();
                    break;
            }
            break;
        default:
            printf("\nInvalid input. Resetting...");
            sleep(3);
            fflush(stdin);
            (*CallMenu1)();
            break;
    }
    fflush(stdin);
    return 0;
}

#endif