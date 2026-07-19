// input/output utility functions
#include "../include/prototypes/io.h"

void flush_stdin(void) {
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
}
