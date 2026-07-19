#ifndef IO_H
#define IO_H

#include "../common.h"

/**
 * Flushes the input buffer by clearing any leftover characters from stdin
 * This should be called after scanf to ensure the next input is clean
 */
void flush_stdin(void);

#endif
