// import needed headers
#include "account.h"
#include "auth.h"
#include "ui.h"
#include "tools.h"

int create_account(Bank *bank) {
    int is_unique = 0;
    char *username = NULL;
    char *password = NULL;

    printf("===== Account Creation =====\n");

    // loop till the user enters a unique valid username
    while (!is_unique) {
        check_length("Enter you desired Username: ", "Username", &username, 4, 50);

        is_unique = 1;
        for (int index = 0; index < bank->count; index++) {
            if (strcmp(username, bank->accounts[index].username) == 0) {
                printf("Username Taken! Try again\n");
                sleep(ONE_SECOND);
                is_unique = 0;
                break;
            }
        }
    }

    // get the user's valid password
    check_length("Enter you desired Password: ", "password", &password, 8, 16);

    // check if there is space for the new account in bank
    if (bank->count >= bank->capacity) {
        bank->capacity *= 2;
        Account *tmp = realloc(bank->accounts, bank->capacity * sizeof(Account));
        if (tmp == NULL) {

            printf("Memory allocation failed ...\n");
            sleep(ONE_SECOND);
            printf("terminating\n");

            free(username);
            free(password);
            return 1;
        }
        // accounts arr new location
        bank->accounts = tmp;
    }
    
    // increment
    bank->count++;

    // get the index
    int idx = bank->count;

    bank->accounts[idx].ID = idx + 1000;        // init the ID of the user
    bank->accounts[idx].balance = 0.0f;         // init the balance of the user

    // init the username /password of the user
    snprintf(bank->accounts[idx].username, sizeof(bank->accounts[idx].username), "%s", username);
    snprintf(bank->accounts[idx].password, sizeof(bank->accounts[idx].password), "%s", password);
    
    // add the account to the database
    if (add_account_to_database(ACCOUNTS_DATA, &bank->accounts[idx]) != 0) {
        free(username);
        free(password);
        return 1;
    }

    free(username);
    free(password);
    return 0;
}