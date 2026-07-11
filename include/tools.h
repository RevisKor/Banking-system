#ifndef TOOLS_H
#define TOOLS_H

// standard imports
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "account.h"

// constants
#define ONE_SECOND 1

// prototypes
int load_data(const char *file, Bank *bank);
int reallocate_accounts(Bank *bank);

#endif