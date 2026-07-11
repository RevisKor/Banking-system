#ifndef TOOLS_H
#define TOOLS_H

// Shared bank/account type definitions.
#include "account.h"

// Persistence and account-database helper API.
int load_data(const char *file, Bank *bank);
int reallocate_accounts(Bank *bank);
int add_account_to_database(const char *file, const Account *account);

#endif