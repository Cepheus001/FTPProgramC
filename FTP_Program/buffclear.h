#ifndef BUFF_CLEAR
#define BUFF_CLEAR

/*
int clearIntBuff() {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;
}
*/

void clearCharBuff() {
    char d;
    while ((d = getchar()) != '\n' && d != EOF);
}

#endif