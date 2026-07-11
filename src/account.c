// import needed headers
#include "account.h"
#include "auth.h"
#include "ui.h"

int create_account(Bank *bank) {
    int is_unique = 0;
    char *username = NULL;
    char *password = NULL;

    printf("===== Account Creation =====\n");

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

    check_length("Enter you desired Password: ", "password", &password, 8, 16);

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

        bank->accounts = tmp;
    }

    int idx = bank->count;
    bank->accounts[idx].ID = idx + 1000;
    bank->accounts[idx].balance = 0.0f;
    snprintf(bank->accounts[idx].username, sizeof(bank->accounts[idx].username), "%s", username);
    snprintf(bank->accounts[idx].password, sizeof(bank->accounts[idx].password), "%s", password);
    bank->count++;

    if (add_account_to_database(ACCOUNTS_DATA, &bank->accounts[idx]) != 0) {
        free(username);
        free(password);
        return 1;
    }

    free(username);
    free(password);
    return 0;
}