// import the header file
#include "../include/account.h"

void display_menu_login() {
    printf("Hello and welcome to our Bank\n");
    sleep(ONE_SECOND);
    printf("===== Account MANAGEMENT =====\n");
    printf("1. Log in\n");
    printf("2. Create account\n");
    printf("3. Exit\n");
    printf("=============================\n");
}

int get_username(Bank *bank, char **user_account) {
    char username[50];
    int is_user = 0, attempts = 3;

    // while the user hasn't entered a correct username and hasnt tried to for 3 times
    while (!is_user && attempts > 0) {

        attempts--;

        printf("Enter you username: ");     // prompt the user to enter their username
        scanf("%s", username);

        // search for the username in the database
            for (int index = 0; index < bank->count; index++) {
            
                // the username has been found
                if (strcmp(username, bank->accounts[index].username) == 0) {
                    
                    if(!sign_in(bank->accounts[index].password)) {
                        *user_account = bank->accounts[index].username;
                        return 0;
                    }
            }
        }

        // the account wasn't found maybe a typo? propmt again
        printf("Account not found please enter a correct username\n");
        sleep(ONE_SECOND);
    }

    // maybe the user doesnt have an account ask them if they wanna create one
    printf("You seem to not have an account\n");
    sleep(ONE_SECOND);

    char create;
    printf("Would you like to create one? (y / n) \n");
    scanf(" %c", &create);

    if (create == 'y' || create == 'Y') {
        return 2;
    } else {
        printf("Thank you for banking with us.\n");
        return 1;
    }

    /* 
    ! Note: these return are to later be handled by case in main
        return 1 ---> will terminate the program
        return 2 ---> will take the user to the create_account() logic
    */
}

int sign_in(char *password) {
    int attempts = 3, is_logged_in = 0;

    // gives 3 attempts to enter password before terminating
    while (attempts > 0 && !is_logged_in) {
        char input[50];
        attempts--;

        printf("Please Enter the account password: ");
        scanf("%s", input);

        // check if the input_password = the password linked to the account
        if (strcmp(input, password) == 0) {
            is_logged_in = 1;
        }
    }

    if (is_logged_in) {
        printf("Access Granted\n");
            return 0;
            
    } else {
        printf("Access denied\n");
            return 1;

    }

    /* 
    ! Note: these return are to later be handled by case in get_username
        return 0 ---> will login
        return 1 ---> will leave the function and go back to the display menu
    */
}

void display_menu_account(char *username) {
    printf("\n===== Account: %s =====\n", username);
    printf("1. Display balance\n");
    printf("2. Withdraw\n");
    printf("3. Deposit\n");
    printf("4. Exit\n");
    printf("=============================\n");
}