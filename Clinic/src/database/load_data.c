// import the header files
#include "../../include/prototypes/database/load_data.h"

void handle_allocation_failure(void* database_ptr, Database_type type) {

    printf("Memory Allocation failed ...\n");
    sleep(ONE_SECOND);
    printf("Terminating\n");

    if (database_ptr != NULL) {

        if (type == PATIENT_TYPE) {

            // convert the void pointer to a database pointer
            Patient_database* database = (Patient_database*) database_ptr;
            free(database->patients);

        } else if (type == APPOINTMENT_TYPE) {

            // convert the void pointer to a database pointer
            Appointment_database* database = (Appointment_database*) database_ptr;
            free(database->appointments);
        }
    }
    
    exit(MEMMORY_ALLOCATION_ERROR);
}

void reallocate_data(void* database_ptr, Database_type type) {

    // check for the database type
    if (type == PATIENT_TYPE) {

        // convert the void pointer to a database pointer
        Patient_database* database = (Patient_database*) database_ptr;

        database->capacity *= 2;        // multiply the capacity by 2

        Patient *tmp = realloc(database->patients, database->capacity * sizeof(Patient));

        if (tmp == NULL) {
            handle_allocation_failure(database, PATIENT_TYPE);
        }

        database->patients = tmp;
        return;

    } else if (type == APPOINTMENT_TYPE) {

        // convert the void pointer to a database pointer
        Appointment_database* database = (Appointment_database*) database_ptr;

        database->capacity *= 2;        // multiply the capacity by 2

        Appointment *tmp = realloc(database->appointments, database->capacity * sizeof(Appointment));

        if (tmp == NULL) {
            handle_allocation_failure(database, APPOINTMENT_TYPE);
        }

        database->appointments = tmp;
        return;
    }

    
    printf("Internal Error wrong type entered please check the code\n");
    exit(INTERNAL_ERROR);
    
}

// function to load the data from the datafile at the start
void load_data(const char* file, void* database_ptr, Database_type type) {

    // load in the file in read mode
    FILE *data = fopen(file, "r");

    // check if there is a file if not then terminate the program
    if (!data) {
        printf("No existing data file found\n");
        sleep(ONE_SECOND);
        printf("Terminating ...\n");
        exit(FILE_NOT_FOUND_ERROR);
    }

    // check what the database entered is
    if (type == PATIENT_TYPE) {

        // convert the void pointer to a database pointer
        Patient_database* database = (Patient_database*) database_ptr;

        // tmp patient we will store the data in till we make sure it is valid 
        Patient tmp_patient;

        // scan the file till we hit the end of the file
        while(fscanf(data, "%64s %d %64s %10s %c ",
            tmp_patient.username,           
            &tmp_patient.patient_id, 
            tmp_patient.password_hash, 
            tmp_patient.birth_date,
            &tmp_patient.gender ) == 5) 
        {

            // check if our array can hold the data
            if (database->count >= database->capacity) {
                reallocate_data(database, PATIENT_TYPE);
            }
            
            // put the newly acquired data from the file in the new index
            database->patients[database->count] = tmp_patient;

            // increment the count for the next iteration
            database->count++;
        }

    } else if (type == APPOINTMENT_TYPE) {

        // convert the void pointer to a database pointer
        Appointment_database* database = (Appointment_database*) database_ptr;

        // tmp appointment we will store the data in till we make sure it is valid 
        Appointment tmp_appointment;

        // scan the file till we hit the end of the file
        while(fscanf(data, "%d %10s %5s",
            &tmp_appointment.patient_id,           
            tmp_appointment.date, 
            tmp_appointment.time) == 3) 
        {

            // check if our array in the can hold the data
            if (database->count >= database->capacity) {
                reallocate_data(database, APPOINTMENT_TYPE);
            }
            
            // put the newly acquired data from the file in the new index
            database->appointments[database->count] = tmp_appointment;

            // increment the count for the next iteration
            database->count++;

        } 

    } else {

        printf("Internal Error wrong type entered please check the code\n");
        exit(INTERNAL_ERROR);
    }

    fclose(data);
}



