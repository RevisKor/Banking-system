// import header file
#include "../include/transactions.h"

void display_balance(Account account) {
    printf("Your balance is %.2f\n", account.balance);
    sleep(ONE_SECOND);
    printf("Press any key to continue\n");
    getchar();
}

// TODO: implement logic where only can withdraw in available currency
void withdraw(Account *account) {
    float withdraw;

    display_balance(*account);

    do {
        printf("How much would you like to withdraw: ");
        if (scanf("%f", &withdraw) != 1) {
            printf("Invaid input\n");
            sleep(ONE_SECOND);
        }

        if (withdraw > account->balance) {
            printf("Withdraw ammount too much please try again\n");
        }
    } while(withdraw > account->balance);

    printf("Processing ...\n");
    sleep(2 * ONE_SECOND);
    
    account->balance -= withdraw;

    display_balance(*account);
}

void deposit(Account *account) {
    float deposit;

    display_balance(*account);

    printf("How much would you like to deposit: ");
    if (scanf("%f", &deposit) != 1) {
        printf("Invaid input\n");
        sleep(ONE_SECOND);
    } 

    printf("Processing ...\n");
    sleep(2 * ONE_SECOND);

    account->balance += deposit;

    display_balance(*account);
}

int change_password(Account *account) { 
    char password[65];
    char *password_ptr = password;
    char hashed[65] = {0};

    int attempts = 3;

    do {
        if (attempts < 3) {
            printf("Try Again! Password incorrect\n");
        }

        attempts--;

        printf("Enter your old password: ");
        scanf("%s", password);

        // hash it to compare with the current pass hash
        hash_password(password_ptr, hashed);

    } while ((strcmp(hashed, account->password) != 0) && (attempts > 0));

    if ((strcmp(hashed, account->password) != 0) && (attempts > 0)) {

        printf("Failed to change password too many incorrect attempts\n");
        sleep(ONE_SECOND);
        printf("Terminating\n");
        return 1;

    } else {
        char new_pass[65];
        char check[65];
        attempts = 3;

        do {
            if (attempts < 3) {
                printf("Try Again!\n");
            }

            attempts--;

            // prompt the user to enter the new password
            printf("Enter The new password: ");
            scanf("%s", new_pass);
            sleep(ONE_SECOND);
            printf("Re-Enter The new password: ");
            scanf("%s", check);
            sleep(ONE_SECOND);
        } while ((strcmp(new_pass, check) != 0) && attempts > 0);
        

        if ((strcmp(new_pass, check) != 0) && attempts > 0) {
            printf("Failed to change password\n");
            sleep(ONE_SECOND);
            printf("Exiting Password changer\n");

            return 0;
        } else {

            hash_password(new_pass, hashed);

            strcpy(account->password, hashed);
            printf("Password Changed Succesfully!\n");
            sleep(ONE_SECOND);

            return 0;
        }    
    }   
}