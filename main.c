#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "account.h"
#include "tools.h"
#include "auth.h"
#include "ui.h"
#include "transactions.h"

int init_bank_system(Bank *bank);
int run_authentication_loop(Bank *bank, Account **user);
void run_user_session_loop(Bank *bank, Account *user);

int main() {
    Account *user = NULL;
    
    // initialize the bank structure
    Bank bank = { .accounts = NULL, 
                  .count = 0, 
                  .capacity = INITIAL_CAPACITY };

    // setup memory and load database
    if (init_bank_system(&bank) != 0) {
        return 1;
    }

    // run gateway logic for login or registration
    int is_logged_in = run_authentication_loop(&bank, &user);
    if (is_logged_in == -1) {
        return 0; 
    } else if (is_logged_in == -2) {
        return 1; 
    }

    // go to the account menu loop if they logged in
    if (is_logged_in) {
        run_user_session_loop(&bank, user);
    }

    return 0;
}

int init_bank_system(Bank *bank) {
    // initialize account array
    bank->accounts = malloc(bank->capacity * sizeof(Account));                    

    // check if memory was allocated
    if (bank->accounts == NULL) {
        printf("Memmory allocation failed ...\n");
        sleep(ONE_SECOND);
        printf("terminating\n");
        return 1;
    }

    // load the data into our bank
    if (load_data(ACCOUNTS_DATA, bank)) {
        return 1;
    }
    
    return 0;
}

int run_authentication_loop(Bank *bank, Account **user) {
    int choice;
    int login_attempts = 1;

    while (1) {
        // display the login menu and ask the user what action they wanna take
        display_menu_login(login_attempts);

        // check if scanf successfully read an integer
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            sleep(ONE_SECOND);
            
            // clear the invalid characters from the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            login_attempts++;
            continue; 
        }

        // take action
        switch (choice) {
            case 1: {
                int login_menu_option = get_username(bank, user);

                // if get_username return success enter the account and go to its logic
                if (login_menu_option == 0) {
                    return 1; 
                } else if (login_menu_option == 1) {
                    return -1; 
                }
                // note that option 2 falls through directly to create_account logic
            }

            /* fallthrough */

            case 2: 
                if (create_account(bank)) {
                    return -2; 
                }

                printf("Account created! ...\n");
                sleep(ONE_SECOND);
                printf("Exiting to login screen ...\n");
                sleep(ONE_SECOND);

                update_data(bank, ACCOUNTS_DATA);

                break;

            case 3: 
                printf("Thank you for banking with us!\n");
                printf("Exiting ...");
                sleep(ONE_SECOND);
                return -1;

            default: 
                printf("Invalid input please try again\n");
                sleep(ONE_SECOND);
                login_attempts++;
                break;
        }  
    }
}

void run_user_session_loop(Bank *bank, Account *user) {
    int choice;

    while (1) {
        display_menu_account(user->username);
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                display_balance(*user);
                break;

            case 2: 
                withdraw(user);
                break;

            case 3: 
                deposit(user);
                break;

            case 4:
                sleep(ONE_SECOND);
                printf("Thank you for banking with us!\n");
                // rewrite everything to the file when closing the app
                update_data(bank, ACCOUNTS_DATA);
                return; 
                
            default:
                sleep(ONE_SECOND);
                printf("Invalid input please try again\n");
                break;
        }
    }
}