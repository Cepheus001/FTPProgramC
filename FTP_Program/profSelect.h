#ifndef SELECT_PROF
#define SELECT_PROF

void menucall();

void callViewProf();

typedef void (*CallViewProf)();

typedef void (*callmenu)();

typedef void (*callclosedir)(DIR *dir);

void closeDirectoryView(DIR *dir);

void takeInputDir(DIR *dir) {

    callmenu CallMenu4 = menucall;
    callclosedir CallCloseDir = closeDirectoryView;
    CallViewProf callviewprof = callViewProf;

    char entryDir[4];

    printf("\nDirectories/Files [0-9]  Quit [Q]");
    printf("\nMake a selection here: ");
    fgets(entryDir, 4, stdin);
    switch(*entryDir) {
        case 'q': case 'Q':
            fflush(stdin);
            (*CallCloseDir)(dir);
        default:
            printf("Error. Invalid Input.");
            (*callviewprof)();
    }
}

void viewProf() {

    system("cls");

    callmenu CallMenu3 = menucall;

    DIR *dir = opendir("Profiles\\");

    if (dir == NULL) {
        perror("Directory could not be fetched.");
        (*CallMenu3)();
    }

    struct dirent *dirEntry;

    while ((dirEntry = readdir(dir)) != NULL) {
        if (strncmp(dirEntry->d_name, ".", 2) == 0 || strncmp(dirEntry->d_name, "..", 4) == 0) {
            continue; 
        }

        char path[1024];
        snprintf(path, sizeof(path), "Profiles/%s", dirEntry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0) {
            if (S_ISREG(statbuf.st_mode)) {
                printf("\nFile: %s\n", dirEntry->d_name);
            } else if (S_ISDIR(statbuf.st_mode)) {
                printf("\nDirectory: %s\n", dirEntry->d_name);
            }
        } else {
            perror("Error getting file status");
            (*CallMenu3)();
        }
    }
    takeInputDir(dir);
} 

void callViewProf() {
    viewProf();
}

void closeDirectoryView(DIR *dir) {
    
    callmenu CallMenu5 = menucall;
    closedir(dir);
    (*CallMenu5)();  
}

#endif