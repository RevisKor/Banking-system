// import the header file
#include "tools.h"

int load_data(const char *file, Bank *bank) {
    // load in the file in read mode
    FILE *data = fopen(file, "r");

    // check if there is an account file if not then terminate the program
    if (!data) {
        printf("No existing file found\n");
        return 1;
    }

    // tmp account we will store the data in till we make sure it is valid 
    Account tmp_account;

    // scan the file till we hit the end of the file
    while(fscanf(data, "%d %49s %64s %f", &tmp_account.ID, tmp_account.username, tmp_account.password, &tmp_account.balance) == 4) {

        // check if our Account array in the bank can hold the data
        if (bank->count >= bank->capacity) {
            if (reallocate_accounts(bank)) {
                fclose(data);
                return 2;           // TODO: issue error status ex. MEMMORY_ALLOCATION_ISSUE
            }
        }
        
        // put the newly acquired data from the file in the new index
        bank->accounts[bank->count] = tmp_account;

        // increment the count for the next iteration
        bank->count++;

    }

    return 0;
}

int reallocate_accounts(Bank *bank) {
    bank->capacity *= 2;

    Account *tmp_arr = realloc(bank->accounts, bank->capacity * sizeof(Account));

    if (tmp_arr == NULL) {
        printf("Memory Allocation failed ...\n");
        sleep(ONE_SECOND);
        printf("Terminating\n");

        free(bank->accounts);

        return 1;
    }

    bank->accounts = tmp_arr;
    return 0;
}

int add_account_to_database(const char *file, const Account *account) {
    FILE *data = fopen(file, "a");

    if (data == NULL) {
        printf("Loading file failed ...\n");
        sleep(ONE_SECOND);
        printf("Terminating\n");
        return 1;
    }

    if (fprintf(data, "%d %s %s %.2f\n", 
        account->ID, 
        account->username, 
        account->password, 
        account->balance) < 0) {

        printf("Failed to write account to database\n");
        fclose(data);
        return 1;
    }

    fclose(data);
    return 0;
}

void update_data(Bank *bank, const char *file) {

    // open the file and load it in write mode
    FILE *data = fopen(file, "w");

    // check that the file exists
    if (data == NULL) {
        printf("could not update the database file\n");
        sleep(ONE_SECOND);
        printf("Terminating");
        return;
    }

    // write the new data
    for (int index = 0; index < bank->count; index++) {
        fprintf(data, "%d %s %s %.2f\n", 
            bank->accounts[index].ID,
            bank->accounts[index].username,
            bank->accounts[index].password,
            bank->accounts[index].balance);
    }

    fclose(data);

}