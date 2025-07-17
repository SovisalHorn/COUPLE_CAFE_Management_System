#ifndef UI_H
#define UI_H

// ANSI color codes for Unix terminals
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

void drawLine(void);
void printCenter(const char* text);
void asciiBanner();
void loadingDots(const char* message);

#endif
