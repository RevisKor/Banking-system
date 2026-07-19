#ifndef LOAD_DATA_H
#define LOAD_DATA_H

// imports
#include "../../common.h"

// prototypes
void handle_allocation_failure(void* database_ptr, Database_type type);
void reallocate_data(void* database_ptr, Database_type type);
void load_data(const char* file, void* database_ptr, Database_type type);

#endif
