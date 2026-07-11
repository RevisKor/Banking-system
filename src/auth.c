// import the header file
#include "auth.h"


int get_username(Bank *bank, char **user_account) {
    char username[50];
    int is_user = 0, attempts = 3;

    // while the user hasn't entered a correct username and hasnt tried to for 3 times
    while (!is_user && attempts > 0) {

        attempts--;

        printf("Enter you username: ");     // prompt the user to enter their username
        scanf("%49s", username);

        // search for the username in the database
        for (int index = 0; index < bank->count; index++) {

            // the username has been found
            if (strcmp(username, bank->accounts[index].username) == 0) {

                if (!sign_in(bank->accounts[index].password)) {
                    *user_account = bank->accounts[index].username;
                    return 0;
                }
            }
        }

        // the account wasn't found maybe a typo? prompt again
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
    }

    printf("Thank you for banking with us.\n");
    return 1;
}

int sign_in(char *password) {
    int attempts = 3, is_logged_in = 0;

    // gives 3 attempts to enter password before terminating
    while (attempts > 0 && !is_logged_in) {
        char input[50];
        attempts--;

        printf("Please Enter the account password: ");
        scanf("%49s", input);

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

void check_length(const char *prompt, const char *id, char **checked, int min_len, int max_len) {
    char tmp[256] = "";
    int is_valid = 0;

    do {
        // prompt the user for a username
        printf("%s", prompt);
        if (scanf("%255s", tmp) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            printf("Invalid input. Please try again.\n");
            sleep(ONE_SECOND);
            continue;
        }

        int len = strlen(tmp);

        // check if the id meets the criteria and gives feedback
        if (len < min_len) {
            printf("%s too short!\n", id);
            sleep(ONE_SECOND);
            continue;
        }

        if (len > max_len) {
            printf("%s too long!\n", id);
            sleep(ONE_SECOND);
            continue;
        }

        // check for other criteria for specific id "password"
        if (strcmp(id, "password") == 0 && !validate_password(tmp)) {
            sleep(ONE_SECOND);
            printf("Password doesnt meet safety criteria\n");
            sleep(ONE_SECOND);
            printf("Try again\n");
            sleep(ONE_SECOND);
            continue;
        }

        // survived all the check
        is_valid = 1;
    } while (!is_valid);

    // allocate memory for the output checked string
    *checked = malloc(strlen(tmp) + 1);
    if (*checked != NULL) {
        strcpy(*checked, tmp);
    }
}

int validate_password(const char *password) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    int len = strlen(password);

    for (int index = 0; index < len; index++) {
        if (isupper((unsigned char)password[index])) {
            has_upper = 1;
        }
        if (islower((unsigned char)password[index])) {
            has_lower = 1;
        }
        if (isdigit((unsigned char)password[index])) {
            has_digit = 1;
        }
        if (ispunct((unsigned char)password[index])) {
            has_special = 1;
        }
    }

    int is_missing = 0;
    if (!has_upper  ) { printf("Password must contain Uppercase Letter\n" ); is_missing++; }
    if (!has_lower  ) { printf("Password must contain Lowercase Letter\n" ); is_missing++; }
    if (!has_digit  ) { printf("Password must contain Digit\n"            ); is_missing++; }
    if (!has_special) { printf("Password must contain Special Character\n"); is_missing++; }

    return (is_missing == 0);
}
