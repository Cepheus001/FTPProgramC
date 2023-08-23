#ifndef PROFILE_CREATE
#define PROFILE_CREATE

typedef struct profileFTP {
    char URI_SERV[256];
    char FTPPSWD[64];
    char FTPUSR[64];
} profileFTP;

void menucall();

void CallCrProf();

void checkDir();

void storeProfile();

typedef void (*callmenu)();

typedef void (*callCreateProf)();

typedef void (*chkDir)(profileFTP *usrprofileptr);

typedef void (*strProf)(profileFTP *usrprofileptr);

void CallstrProf(profileFTP *usrprofileptr);

void CallchkProf(profileFTP *usrprofile);

int createProfileMenu() {
    profileFTP usrprofile;

    profileFTP *usrprofileptr = &usrprofile;

    callmenu CallMenu1 = menucall;
    callCreateProf CallProf = CallCrProf;
    chkDir chkdir = checkDir;

    char yn[10];

    system("cls");
    printf("Enter the Desired URI you wish to connect to: ");
    scanf(" %255s", &usrprofileptr->URI_SERV);
    clearCharBuff();
    system("cls");
    printf("Is this the correct information? Your URI is: %s", usrprofileptr->URI_SERV);
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
                    char* anonlogin = "anonymous";
                    strncpy(usrprofileptr->FTPUSR, anonlogin, 64);
                    strncpy(usrprofileptr->FTPPSWD, anonlogin, 64);
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
                            fgets(usrprofileptr->FTPUSR, sizeof(profileFTP), stdin);
                            system("cls");
                            fflush(stdin);
                            printf("Enter your FTP Password here: ");
                            fgets(usrprofileptr->FTPPSWD, sizeof(profileFTP), stdin);
                            system("cls");
                            fflush(stdin);
                            char yn5[10];
                            printf("Are these the correct credentials?\n");
                            printf("\n%s\n", usrprofileptr->FTPUSR);
                            printf("%s\n", usrprofileptr->FTPPSWD);
                            printf("Type [Y/N] to Continue: ");
                            gets(yn5);
                            switch(*yn5) {
                            case 'Y': case 'y':
                                fflush(stdin);
                                (*chkdir)(usrprofileptr);
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

void checkDir(profileFTP *usrprofileptr) {

    strProf strprof = storeProfile;
    callmenu CallMenu1 = menucall;

    const char *CheckDir = "Profiles";

    struct stat dirStat;
    if(stat(CheckDir, &dirStat) == 0) {
        if (S_ISDIR(dirStat.st_mode)) {
            printf("This directory exists!\n");
            sleep(2);
            system("cls");
            (*strprof)(usrprofileptr);
        } else {
            printf("Path exists, but it's not a directory.\n");
            sleep(2);
            (*CallMenu1)();
        }
    } else {
        printf("Directory does not exist.\n");
        CreateDirectory("Profiles/", NULL);
        printf("Directory has been created!\n");
        sleep(2);
        system("cls");
        (*strprof)(usrprofileptr);
    }
}

void storeProfile(profileFTP *usrprofileptr) {
    
    callmenu CallMenu2 = menucall;

    char filename[20];
    char dir[128] = "Profiles\\";

    printf("This is your FTP profile!\n\n");
    printf("Username: %s\n", usrprofileptr->FTPUSR);
    printf("Password: %s\n", usrprofileptr->FTPPSWD);
    sleep(2);
    system("cls");
    printf("Enter the file name here: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    for (int i = 0; filename[i] != '\0'; i++) {
        if (isspace(filename[i])) {
            filename[i] = '_';
        }
    }

    strncat(dir, filename, 64);
    strncat(dir, ".dat", 6);

    FILE *fp = fopen(dir, "w");
    if (fp == NULL) {
        perror("An error occured while opening the file!");
        sleep(2);
        system("cls");
        printf("Going back to main menu...");
        sleep(2);
        (*CallMenu2)();
    }

    fprintf(fp, "%s\n", usrprofileptr->URI_SERV);
    fprintf(fp, "%s\n", usrprofileptr->FTPUSR);
    fprintf(fp, "%s\n", usrprofileptr->FTPPSWD);

    fclose(fp);

    system("cls");
    printf("The file has been successfully added!");
    sleep(2);
    (*CallMenu2)();
}

void CallstrProf(profileFTP *usrprofileptr) {
    storeProfile(usrprofileptr);
}

void CallchkProf(profileFTP *usrprofileptr) {
    checkDir(usrprofileptr);
}

void CallCrProf() {
    createProfileMenu();
}

#endif