#ifndef AUTH_H
#define AUTH_H

// Shared bank/account type definitions.
#include "account.h"
#include "hash.h"

// Authentication and password-validation API.
int get_username(Bank *bank, Account **user);
int sign_in(char *password);
void check_length(const char *prompt, const char *id, char **checked, int min_len, int max_len);
int validate_password(const char *password);

extern char message[512];
#endif
