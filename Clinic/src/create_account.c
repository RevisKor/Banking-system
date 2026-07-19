// import header file
#include "../include/prototypes/create_account.h"
#include "../include/prototypes/io.h"

void create_account(Patient_database* database) {
    char username[65] =  "";
    char password[65] =  "";
    char password_hash[65] = "";

    char* username_ptr = username;
    char* password_ptr = password;

    int is_unique = 0;

    char gender;
    char birthdate[11] = {0};

    printf("===== Account Creation =====\n");

     // loop till the user enters a unique valid username
    while (!is_unique) {
        check_input_length("Enter you desired Username: ", "Username", &username_ptr, 4, 50);

        is_unique = 1;

        // loop for each username in the database
        for (int index = 0; index < database->count; index++) {

            // check if the username matches with the one that the user enetered
            if (strcmp(username, database->patients[index].username) == 0) {

                printf("Username Taken! Try again\n");
                sleep(ONE_SECOND);
                is_unique = 0;
                break;
            }
        }
    }

    // get the user's valid password
    check_input_length("Enter you desired Password: ", "password", &password_ptr, 8, 16);

    hash_password(password_ptr, password_hash);

    // get the gender
    
    get_date("Enter your birthdate", birthdate);
    get_gender(&gender);

    // check if there is space for the new account
    if (database->count >= database->capacity) {
        reallocate_data(database, PATIENT_TYPE);
    }
    
    // update the new account to database array
    int index = database->count;
    
    database->patients[index].patient_id = index + 100;

    database->patients[index].gender = gender;
    strcpy(database->patients[index].birth_date, birthdate);

    strcpy(database->patients[index].username, username);
    strcpy(database->patients[index].password_hash, password_hash);

    database->count++;
    
    printf("\n====================================\n");
    printf("| Patient ID: %d\n", database->patients[index].patient_id);
    printf("| Username: %s\n", username_ptr);
    printf("| Password: %s\n", password_ptr); 
    printf("====================================\n");
    printf("These are your Username and Password. Memorize them and do not share them!\n\n");
    
    flush_stdin();

    printf("Press Enter to continue... ");
    getchar();
}

void get_gender(char* gender) {
    char input_buffer;

    do {
        printf("What is yout gender? (M / F): ");
        scanf(" %c", &input_buffer);
        flush_stdin();

    } while (input_buffer != 'M' && input_buffer != 'm' && input_buffer != 'F' && input_buffer != 'f');

    *gender = input_buffer;
}
