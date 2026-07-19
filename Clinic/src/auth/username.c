// import the header file
#include "../../include/prototypes/auth/username.h"

int handle_username(Patient_database* database, Patient** patient) {
    char username[65];
    int attempts = 3;

    while (attempts > 0) {

        attempts--;

        printf("Enter your Username: ");
        scanf("%64s", username);

        if (strcmp(username, "admin") == 0) {
            if (check_admin_login()) {
                return 1;
            } else {
                return 2;
            }
        }

        // search for the username in the database
        for (int index = 0; index < database->count; index++) {
            
            // check for the case
            if (strcmp(username, database->patients[index].username) == 0) {
                
                if (sign_in(database->patients[index].password_hash)) {
                    return 1;
                } else {
                    *patient = &(database->patients[index]);
                    return 0;
                } 
            }
        }

        // the account wasnt found maybe the user has entered a type
        printf("Account not found please enter a correct username\n");
        sleep(ONE_SECOND);

    }

    // the account is not in the database then 
    printf("Coudn't find the Account in the database ...\n");
    sleep(ONE_SECOND);
    printf("Please consider creating an account\n");
    sleep(ONE_SECOND);
    printf("Exiting to Login screen ...\n");

    return 1;
}