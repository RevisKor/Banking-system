// import the header file
#include "../../include/prototypes/auth/validate.h"
#include "../../include/prototypes/io.h"

void check_input_length(const char *display_prompt, const char *field_identifier, char **destination_buffer, int minimum_allowed_length, int maximum_allowed_length) {
    char input_buffer[256] = "";
    int input_is_valid = 0;

    do {
        // prompt the user for a username
        printf("%s", display_prompt);

        if (scanf(" %255s", input_buffer) != 1) {
            flush_stdin();
            
            printf("Invalid input. Please try again.\n");
            sleep(ONE_SECOND);
            continue;
        }

        // Clean up the leftover newline
        flush_stdin();
          
        int current_input_length = strlen(input_buffer);

        // check if the id meets the criteria and gives feedback
        if (current_input_length < minimum_allowed_length) {
            printf("%s too short!\n", field_identifier);
            sleep(ONE_SECOND);
            continue;
        }

        if (current_input_length > maximum_allowed_length) {
            printf("%s too long!\n", field_identifier);
            sleep(ONE_SECOND);
            continue;
        }

        // check for other criteria for specific id "password"
        if (strcmp(field_identifier, "password") == 0 && !validate_password(input_buffer)) {
            sleep(ONE_SECOND);
            printf("Password doesnt meet safety criteria\n");
            sleep(ONE_SECOND);
            printf("Try again\n");
            sleep(ONE_SECOND);
            continue;
        }
        
        // survived all the check
        input_is_valid = 1;

    } while (!input_is_valid);
    
    strcpy(*destination_buffer, input_buffer);
    return;
}

int validate_password(const char *password) {
    int has_uppercase_letter = 0, has_lowercase_letter = 0, has_numeric_digit = 0, has_special_character = 0;
    int password_length = strlen(password);

    for (int character_index = 0; character_index < password_length; character_index++) {
        if (isupper((unsigned char)password[character_index])) {
            has_uppercase_letter = 1;
        }
        if (islower((unsigned char)password[character_index])) {
            has_lowercase_letter = 1;
        }
        if (isdigit((unsigned char)password[character_index])) {
            has_numeric_digit = 1;
        }
        if (ispunct((unsigned char)password[character_index])) {
            has_special_character = 1;
        }
    }

    int total_missing_requirements = 0;
    if (!has_uppercase_letter  ) { printf("Password must contain Uppercase Letter\n" ); total_missing_requirements++; }
    if (!has_lowercase_letter  ) { printf("Password must contain Lowercase Letter\n" ); total_missing_requirements++; }
    if (!has_numeric_digit  ) { printf("Password must contain Digit\n"            ); total_missing_requirements++; }
    if (!has_special_character) { printf("Password must contain Special Character\n"); total_missing_requirements++; }

    return (total_missing_requirements == 0);
}
