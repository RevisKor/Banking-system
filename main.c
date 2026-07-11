#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "tools.h"
#include "auth.h"
#include "ui.h"

int main() {
    char *user = NULL;
    int choice, is_logged_in = 0, login_attempts = 1;

    // initialize the bank structure
    Bank bank = {   .accounts = NULL, 
                    .count = 0, 
                    .capacity = INITIAL_CAPACITY };

    // initialize account array
    bank.accounts = malloc(bank.capacity * sizeof(Account));                    

    // check if memmory was allocated
    if (bank.accounts == NULL) {
        printf("Memmory allocation failed ...\n");
        sleep(ONE_SECOND);
        printf("terminating\n");
        return 1;
    }

    // load the data into our bank
    if (load_data(ACCOUNTS_DATA, &bank)) {return 1;}

    while (!is_logged_in) {

        // display the login menu and ask the user what action they wanna take
        display_menu_login(login_attempts);

        // Check if scanf successfully read an integer
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            sleep(ONE_SECOND);
            
            // Clear the invalid characters from the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            login_attempts++;
            continue; // Skip the switch statement and restart the loop
        }

        // take action 
        switch (choice) {
            case 1: {int login_menu_option = get_username(&bank, &user);

                    // if get_username return success enter the account and go to its logic
                    if (login_menu_option == 0) {
                        is_logged_in = 1;
                        break;

                    // if get_username return 1 then we should terminate the program
                    } else if (login_menu_option == 1) {
                        return 0;
                        break;
                    }

                    /*  note the there is another option which it return 2 
                        in that case it just goes on and executes the next case 
                        which will be create_account() logic  */}
                    /* fallthrough */

            case 2: if(create_account(&bank)) {
                        return 1;
                    };

                    printf("Logging in ...\n");
                    sleep(ONE_SECOND);

                    break;

            case 3: printf("Thank you for banking with us!\n");
                    printf("Exiting ...");
                    sleep(ONE_SECOND);

                    return 0;

            default: 
                    printf("Invalid input please try again\n");
                    sleep(ONE_SECOND);
                    login_attempts++;
                    break;
        }  
    }

    while (is_logged_in) {
        display_menu_account(user);
        scanf("%d", &choice);

        switch(choice) {
            case 4:
                printf("Thank you for banking with us!\n");
                return 0;
            default:
                printf("Invalid input please try again\n");
                break;
        }
    }

    return 0;
}