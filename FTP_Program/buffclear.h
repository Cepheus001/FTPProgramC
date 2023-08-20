#ifndef BUFF_CLEAR
#define BUFF_CLEAR


int clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;
}

#endif