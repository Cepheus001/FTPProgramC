#ifndef PROFILE_CREATE
#define PROFILE_CREATE


void menucall();

void CallCrProf();

void storeProfile();

typedef void (*callmenu)();

typedef void (*callCreateProf)();

typedef void (*strProf)();

typedef struct {
    char URI_SERV[256];
    char FTPPSWD[64];
    char FTPUSR[64];
} profileFTP;

int createProfileMenu() {
    profileFTP *usrprofile;

    callmenu CallMenu1 = menucall;
    callCreateProf CallProf = CallCrProf;
    strProf StoreProfile = storeProfile;

    char yn[10];

    system("cls");
    printf("Enter the Desired URI you wish to connect to: ");
    scanf(" %255s", &usrprofile->URI_SERV);
    clearCharBuff();
    system("cls");
    printf("Is this the correct information? Your URI is: %s", usrprofile->URI_SERV);
    printf("\nType [Y/N] to continue: ");
    gets(yn);
    printf("\n");
    switch(*yn) {
        case 'y': case 'Y':
            system("cls");
            fflush(stdin);
            char yn3[10];
            printf("Would you like to login anonymously? [Y/N]");
            gets(yn3);
            switch(*yn3) {
                case 'y': case 'Y':
                    system("cls");
                    fflush(stdin);
                    const char* anonlogin = "anonymous";
                    strncpy(usrprofile->FTPUSR, anonlogin, 64);
                    strncpy(usrprofile->FTPPSWD, anonlogin, 64);
                    break;
                case 'n': case 'N':
                    system("cls");
                    fflush(stdin);
                    char yn4[10];
                    printf("Would you like to go back to:\n");
                    printf("[1] - Main Menu\n");
                    printf("[2] - Restart Profile Creation\n");
                    printf("\nOr continue?\n");
                    printf("[3] - Create Custom Profile\n");
                    printf("\nEnter your choice here: ");
                    gets(yn4);
                    switch(*yn4) {
                        case '1':
                            system("cls");
                            fflush(stdin);
                            (*CallMenu1)();
                            break;
                        case '2':
                            system("cls");
                            fflush(stdin);
                            (*CallProf)();
                            break;
                        case '3':
                            system("cls");
                            fflush(stdin);
                            printf("Enter your FTP Username here: ");
                            gets(usrprofile->FTPUSR);
                            system("cls");
                            fflush(stdin);
                            printf("Enter your FTP Password here: ");
                            gets(usrprofile->FTPPSWD);
                            system("cls");
                            fflush(stdin);
                            char yn5[10];
                            printf("Are these the correct credentials?\n");
                            printf("\n%s\n", usrprofile->FTPUSR);
                            printf("%s\n", usrprofile->FTPPSWD);
                            printf("Type [Y/N] to Continue: ");
                            gets(yn5);
                            switch(*yn5) {
                            case 'Y': case 'y':
                                fflush(stdin);
                                (*StoreProfile)();
                                break;
                            case 'N': case 'n':
                                fflush(stdin);
                                (*CallProf)();
                                break;
                            default:
                                printf("Invalid Input. Exiting...");
                                sleep(2);
                                system("cls");
                                fflush(stdin);
                                (*CallProf)();
                                break;
                            }
                            break;
                        default:
                            printf("Invalid Input. Exiting...");
                            sleep(2);
                            system("cls");
                            fflush(stdin);
                            (*CallProf)();
                            break;
                    }
                    break;
                default:
                    printf("Invalid Input. Exiting...");
                    sleep(2);
                    system("cls");
                    fflush(stdin);
                    (*CallProf)();
                    break;
            }
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
                    (*CallProf)();
                    break;
                default:
                    printf("Invalid Input. Exiting...");
                    sleep(2);
                    system("cls");
                    fflush(stdin);
                    (*CallMenu1)();
                    break;
            }
            break;
        default:
            printf("\nInvalid input. Resetting...");
            sleep(2);
            fflush(stdin);
            (*CallMenu1)();
            break;
    }
    fflush(stdin);
    return 0;
}

void storeProfile() {
    const char *CheckDir = "Profiles";

    struct stat dirStat;
    if(stat(CheckDir, &dirStat) == 0) {
        if (S_ISDIR(dirStat.st_mode)) {
            printf("This directory exists!\n");
        } else {
            printf("Path exists, but it's not a directory.\n");
        }
    } else {
        printf("Directory does not exist.\n");
    }
}

void CallstrProf() {
    storeProfile();
}

void CallCrProf() {
    createProfileMenu();
}

#endif