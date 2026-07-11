// import the header file
#include "../include/account.h"

void display_menu_login(int count) {
    if (count <= 1) {
        printf("Hello and welcome to our Bank\n");
    }
    sleep(ONE_SECOND);
    printf("===== Account MANAGEMENT =====\n");
    printf("1. Log in\n");
    printf("2. Create account\n");
    printf("3. Exit\n");
    printf("=============================\n");
}

void display_menu_account(char *username) {
    printf("\n===== Account: %s =====\n", username);
    printf("1. Display balance\n");
    printf("2. Withdraw\n");
    printf("3. Deposit\n");
    printf("4. Exit\n");
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

int create_account(Bank *bank) {
    int is_unique = 0;
    char username[50];
    char password[24];

    // ptrs to the pass, user names
    char *ptr_username = username;
    char *ptr_password = password;

    printf("===== Account Creation =====\n");
    
    while(!is_unique) {

        check_length("Enter you desired Username: ", "Username", &ptr_username, 50, 4);

        // check if the username is already used
        for (int index = 0; index < bank->count; index++) {
            
                // the username has been found
                if (strcmp(username, bank->accounts[index].username) == 0) {
                    printf("Username Taken! Try again\n");
                    sleep(ONE_SECOND);
                     continue;
            }
        }
        is_unique = 1;
    }

    // check and validate the password
    check_length("Enter you desired Password: ", "password", &ptr_password, 16, 8);

    if (bank->count >= bank->capacity) {
        bank->capacity *= 2;
        Account *tmp = realloc(bank->accounts, bank->capacity * sizeof(Account));

        if (tmp == NULL) {
            printf("Memmory allocation failed ...\n");
            sleep(ONE_SECOND);
            printf("terminating\n");
            return 1;   //  TODO: add specific error codes
        }

        bank->accounts = tmp;
    }
    // increment
    bank->count++;

    // define the user's account and then push it to the file
    int idx = bank->count;

    bank->accounts[idx].ID  = idx + 1000;       // initialize the ID
    bank->accounts[idx].balance = 0.0f;         // initialize the balance

    // assign username & password
    snprintf(bank->accounts[idx].username, sizeof(bank->accounts[idx].username), "%s", username);
    snprintf(bank->accounts[idx].password, sizeof(bank->accounts[idx].password), "%s", password);

    // add to file
    add_account_to_database(ACCOUNTS_DATA, &(bank->accounts[idx]));

    return 0;

}

void check_length(const char *prompt, char *id, char **checked, int upper_bounds, int lower_bounds) {
    char tmp[256] = "";
    int is_valid = 0;

    do {
        // prompt the user for a username
        printf("%s", prompt);
        if((scanf("%255s", tmp)) != 1) {
            // do while failing to get a valid input
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            continue;
        }

        int len = strlen(tmp);

        // check if the id meets the criteria and gives feedback
        if (len < lower_bounds) {
            printf("%s too short!\n", id);
            sleep(ONE_SECOND);
            continue;

        } else if (len > upper_bounds) {
            printf("%s too long!\n", id);
            sleep(ONE_SECOND);
            continue;
        }

        // check for other criteria for specific id "password"
        if (strcmp(id, "password") == 0) {
            if (!validate_password(tmp)) {

                sleep(ONE_SECOND);
                printf("Password doesnt meet safety criteria\n");
                sleep(ONE_SECOND);
                printf("Try again\n");
                sleep(ONE_SECOND);
                
                continue;
            }
        }

        // survived all the check
        is_valid = 1;

    } while (!is_valid);

    // copy the tmp where it should be
    strcpy(*checked, tmp);
    
        
}

int validate_password(const char *password) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;

    int len = strlen(password);

    for (int index = 0; index < len; index++) {
        
        if (isupper(password[index])) {has_upper = 1;}     // if it has at least one uppercase this will be true
        if (islower(password[index])) {has_lower = 1;}     // if it has at least one lowercase this will be true
        if (isdigit(password[index])) {has_digit = 1;}     // if it has at least one digit this will be true
        if (ispunct(password[index])) {has_special = 1;}   // if it has at least one special character this will be true

    }
    int is_missing = 0;
    if(!has_upper  ) {printf("Password must contain Uppercase Letter\n" ); is_missing++;}
    if(!has_lower  ) {printf("Password must contain Lowercase Letter\n" ); is_missing++;}
    if(!has_digit  ) {printf("Password must contain Digit\n"            ); is_missing++;}
    if(!has_special) {printf("Password must contain Special Character\n"); is_missing++;}
    
    return (is_missing == 0);
}

void add_account_to_database(const char *file, const Account *account) {
    // open the file 
    FILE *data = fopen(file, "a");

    if (data == NULL) {
        printf("Loading file failed ... \n");
        sleep(ONE_SECOND);
        printf("Terminating\n");
        sleep(ONE_SECOND);
    }

    // print data to the file
    fprintf(data, "%d %s %s %f\n", 
        account->ID,
        account->username,
        account->password,
        account->balance);

    fclose(data);   
}