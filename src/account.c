// import needed headers
#include "account.h"
#include "auth.h"
#include "ui.h"
#include "tools.h"

int create_account(Bank *bank) {
    int is_unique = 0;

    char username[256] = "";
    char password[256] = "";

    char *username_ptr = username;
    char *password_ptr = password;

    printf("===== Account Creation =====\n");

    // loop till the user enters a unique valid username
    while (!is_unique) {
        check_length("Enter you desired Username: ", "Username", &username_ptr, 4, 50);

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
    check_length("Enter you desired Password: ", "password", &password_ptr, 8, 16);

    char hashed_password[65] = {0};
    hash_password(password_ptr, hashed_password);

    snprintf(message, sizeof(message), "| Username: %s\n| Password: %s\n", username_ptr, password_ptr);

    // check if there is space for the new account in bank
    if (bank->count >= bank->capacity) {
        bank->capacity *= 2;
        Account *tmp = realloc(bank->accounts, bank->capacity * sizeof(Account));
        if (tmp == NULL) {

            printf("Memory allocation failed ...\n");
            sleep(ONE_SECOND);
            printf("terminating\n");

            return 1;
        }
        // accounts arr new location
        bank->accounts = tmp;
    }
    
    // get the index
    int idx = bank->count;

    // increment
    bank->count++;

    bank->accounts[idx].ID = idx + 1000;        // init the ID of the user
    bank->accounts[idx].balance = 0.0f;         // init the balance of the user
        
    // init the username /password of the user
    snprintf(bank->accounts[idx].username, sizeof(bank->accounts[idx].username), "%s", username_ptr);
    snprintf(bank->accounts[idx].password, sizeof(bank->accounts[idx].password), "%s", hashed_password);
    
    // show the user their details
    printf("====================================\n");
    printf("%s", message);
    printf("====================================\n");
    printf("These are your Username and Password, memorise them and don't share them\n");
    sleep(ONE_SECOND);
    printf("Press any key to continue ");
    getchar();

    // add the account to the database
    if (add_account_to_database(ACCOUNTS_DATA, &(bank->accounts[idx])) != 0) {
        return 1;
    }

    return 0;
}