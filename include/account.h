#ifndef ACCOUNT_H
#define ACCOUNT_H

// standard imports
#include <stdio.h>
#include <string.h>

// structs

typedef struct {
    int ID;
    char username[50];
    char password[16];
    float balance;
} Account;

typedef struct {
    Account *accounts;
    int count;
    int capacity;
} Bank;

// constants
#define INITIAL_CAPACITY 10
#define ACCOUNTS_DATA "../data/accounts.txt"


#endif