#ifndef UPDATE_DATA_H
#define UPDATE_DATA_H

// imports
#include "../../common.h"

// prototypes
void add_to_database(const char *file, void* entry, Database_type type);
void update_data(const char* file, void* database_ptr, Database_type type);

#endif
