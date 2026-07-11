#ifndef ACCOUNT_H
#define ACCOUNT_H

// standard imports
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// structs

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

// constants
#define INITIAL_CAPACITY 10
#define ACCOUNTS_DATA "data/accounts.txt"
#define ONE_SECOND 1

// prototype
int get_username(Bank *bank, char **user_account);
int sign_in(char *password);

void display_menu_login(int count);
void display_menu_account(char *username);

int create_account(Bank *bank);
void check_length(const char *prompt, char *id, char **checked, int upper_bounds, int lower_bounds);
int validate_password(const char *password);
void add_account_to_database(const char *file, const Account *account);


#endif