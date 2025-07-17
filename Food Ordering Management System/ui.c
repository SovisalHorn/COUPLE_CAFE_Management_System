// ui.c
#include <stdio.h>
#include <string.h>

void drawLine(void) {
    printf("+----------------------------------------------------------+\n");
}

void printCenter(const char* text) {
    int width = 58;
    int len = (int)strlen(text);
    int padding = (width - len) / 2;
    printf("%*s%s%*s\n", padding, "", text, padding + (len % 2 == 0 ? 0 : 1), "");
}

void loadingDots(const char* message) {
    printf("%s", message);
    fflush(stdout);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        //usleep(300000);
    }
    printf("\n");
}

void asciiBanner() {
    drawLine();
    printCenter("💘 Welcome to Café COUPLE 💘");
    drawLine();
}
