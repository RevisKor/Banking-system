#include <stdio.h>
#include <stdlib.h>
#include "include/account.h"
#include "include/tools.h"

int main() {
    char *user = NULL;
    int choice, is_logged_in = 0;
    
    Bank bank = {malloc(bank.capacity * sizeof(Account)), 0, INITIAL_CAPACITY };

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
        display_menu_login();
        scanf("%d", &choice);

        // take action 
        switch (choice) {
            case 1: int login_menu_option = get_username(&bank, &user);

                    // if get_username return success enter the account and go to its logic
                    if (login_menu_option == 0) {
                        display_menu_account(user);
                        is_logged_in = 1;
                        break;

                    // if get_username return 1 then we should terminate the program
                    } else if (login_menu_option == 1) {
                        return 0;
                    }

                    /*  note the there is another option which it return 2 
                        in that case it just goes on and executes the next case 
                        which will be create_account() logic  */

            case 2: // create_account()

            case 3: printf("Thank you for banking with us!\n");
                    printf("Exiting ...");
                    sleep(ONE_SECOND);

                    return 0;

            default: 
                    printf("Invalid input please try again\n");
                    break;
        }
    }

    while (is_logged_in) {
        display_menu_account(&user);
        scanf("%d", &choice);

        switch(choice) {
            
        }
    }
    return 0;
}