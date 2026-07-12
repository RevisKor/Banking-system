#ifndef UI_H
#define UI_H

// Shared bank/account type definitions.
#include "account.h"

// Menu display API.
void display_menu_login(int count);
void display_menu_account(char *username);
void display_admin_menu();

#endif
