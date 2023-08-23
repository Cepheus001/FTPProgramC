#ifndef SELECT_PROF
#define SELECT_PROF

void menucall();

typedef void (*callmenu)();

void takeInputDir() {

    callmenu CallMenu4 = menucall;

    int entryDir;

    printf("Enter Numbers 1 through 9 to make a selection: ");
    scanf("%d", &entryDir);
    switch(entryDir) {

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
    closedir(dir);

} 

#endif