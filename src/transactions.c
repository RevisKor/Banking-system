// import header file
#include "../include/transactions.h"

void display_balance(Account account) {
    printf("Your balance is %.2f\n", account.balance);
    sleep(ONE_SECOND);
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