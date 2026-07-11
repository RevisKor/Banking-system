#ifndef ACCOUNT_H
#define ACCOUNT_H

// Standard library headers used by the shared account model.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Shared account and bank data model.
typedef struct {
    int ID;
    char username[50];
    char password[24];
    float balance;
} Account;

typedef struct {
    Account *accounts;
    int count;
    int capacity;
} Bank;

// Shared constants used across the banking modules.
#define INITIAL_CAPACITY 10
#define ACCOUNTS_DATA "data/accounts.txt"
#define ONE_SECOND 1

// Core account creation API.
int create_account(Bank *bank);

#endif