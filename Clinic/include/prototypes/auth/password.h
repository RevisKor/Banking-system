#ifndef PASSWORD_H
#define PASSWORD_H

#include "../../common.h"
#include "../hash/hash.h"

// prototypes
int sign_in(char* account_password);
int check_admin_login();

#endif