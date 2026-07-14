#ifndef TRANSACTION_H
#define TRANSACTION_H

// standard imports
#include <stdio.h>
#include "account.h"
#include "hash.h"

// prototypes
void display_balance(Account account);
void withdraw(Account *account);
void deposit(Account *account);
int change_password(Account *account);

#endif