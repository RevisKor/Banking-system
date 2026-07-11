// import the header file
#include "ui.h"

void display_menu_login(int count) {
    if (count <= 1) {
        printf("Hello and welcome to our Bank\n");
    }
    sleep(ONE_SECOND);
    printf("===== Account MANAGEMENT =====\n");
    printf("1. Log in\n");
    printf("2. Create account\n");
    printf("3. Exit\n");
    printf("=============================");
    printf("\n");
}

void display_menu_account(char *username) {
    printf("\n===== Account: %s =====\n", username);
    printf("1. Display balance\n");
    printf("2. Withdraw\n");
    printf("3. Deposit\n");
    printf("4. Exit\n");
    printf("=============================" );
    printf("\n");
}
