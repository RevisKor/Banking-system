#ifndef AUTH_H
#define AUTH_H

// Shared bank/account type definitions.
#include "account.h"

// Authentication and password-validation API.
int get_username(Bank *bank, char **user_account);
int sign_in(char *password);
void check_length(const char *prompt, const char *id, char **checked, int min_len, int max_len);
int validate_password(const char *password);

#endif
