// import the header file
#include "../../include/prototypes/auth/password.h"
#include "../../include/prototypes/io.h"

int sign_in(char* account_password) {
    int attempts = 3, is_logged_in = 0;
    char input_hash[65];

    // gives the user 3 attempts to enter the password
    while((attempts > 0) && !is_logged_in) {
        char input_buffer[65];
        attempts--;

        printf("Please Enter the account password: ");
        scanf("%64s", input_buffer);
        flush_stdin();

        // check if the input text hashed equals the hash linked to the account
        hash_password(input_buffer, input_hash);
        if (strcmp(input_hash, account_password) == 0) {
            is_logged_in = 1;
        }
    }

    if (is_logged_in) {
        printf("Access Granted\n");
        return 0;

    } else {
        printf("Access denied\n");
        printf("Exiting to Login screen\n");
        sleep(ONE_SECOND);
        return 1;
    }
}

int check_admin_login() {
    int attempts = 3, is_logged_in = 0;

    // gives the user 3 attempts to enter the password
    while((attempts > 0) && !is_logged_in) {
        char input_buffer[65];
        attempts--;

        printf("Please Enter the admin password: ");
        scanf("%64s", input_buffer);
        flush_stdin();

        
        if (strcmp(input_buffer, "Admin@2026") == 0) {
            is_logged_in = 1;
        }
    }

    if (is_logged_in) {
        printf("Access Granted\n");
        return 0;

    } else {
        printf("Access denied\n");
        printf("Exiting to Login screen\n");
        sleep(ONE_SECOND);
        return 1;
    }
}
