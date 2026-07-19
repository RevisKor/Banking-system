#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

// imports
#include "../common.h"
#include "auth/password.h"
#include "auth/username.h"
#include "auth/validate.h"
#include "hash/hash.h"
#include "database/load_data.h"
#include "database/update_data.h"
#include "auth/date.h"

// prototypes
void create_account(Patient_database* database);
void get_gender(char* gender);

#endif