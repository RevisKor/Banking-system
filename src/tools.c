// import the header file
#include "../include/tools.h"

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
    while(fscanf(data, "%d %49s %19s %f", &tmp_account.ID, tmp_account.username, tmp_account.password, &tmp_account.balance) == 4) {

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
    bank->capacity *= 2;            // double the space 
    
    // reallocate new memory from the bigger array
    Account *tmp_arr = realloc(bank->accounts, bank-> capacity * sizeof(Account));

    // if there is no memory available then terminate
    if (tmp_arr == NULL) {
        printf("Memory Allocation failed ...\n");
        sleep(ONE_SECOND);
        printf("Terminating");

        free (bank->accounts);      // free to avoid problems

        return 1;                   // memmory alloc issue
    }

    // space was found assign the new location to Accounts array
    bank->accounts = tmp_arr;
    return 0;

        
}