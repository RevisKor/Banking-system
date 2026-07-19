// import the header file
#include "../../include/prototypes/database/update_data.h"

void add_to_database(const char *file, void* entry, Database_type type) {
    
    // open the file
    FILE *data = fopen(file, "a");

    if (data == NULL) {
        printf("Loading file failed ...\n");
        sleep(ONE_SECOND);
        printf("Terminating\n");
        exit(MEMMORY_ALLOCATION_ERROR);
    }

    if (type == PATIENT_TYPE) {
        
        // assign the gerneric pointer back to the database pointer
        Patient* patient = (Patient*) entry;

        // attempt to add data to the file
        if (fprintf(data, "%s %d %64s %s %c \n",
            patient->username,           
            patient->patient_id, 
            patient->password_hash, 
            patient->birth_date,
            patient->gender) < 0) {

                printf("Failed to write account to database\n");
                fclose(data);
                exit(MEMMORY_ALLOCATION_ERROR);
        }

        fclose(data);

    } else if (type == APPOINTMENT_TYPE) {

        // assign the gerneric pointer back to the database pointer
        Appointment* patient = (Appointment*) entry;

        // attempt to add data to the file
        if (fprintf(data, "%d %10s %5s\n",
            patient->patient_id,           
            patient->date, 
            patient->time) < 0) {

                printf("Failed to write account to database\n");
                fclose(data);
                exit(MEMMORY_ALLOCATION_ERROR);
        }

        fclose(data);
    }
}

void update_data(const char* file, void* database_ptr, Database_type type) {

    // open the file and load it in write mode
    FILE *data = fopen(file, "w");

    if (type == PATIENT_TYPE) {

        // assign the gerneric pointer back to the database pointer
        Patient_database* database = (Patient_database*) database_ptr;

        for (int index = 0; index < database->count; index++) {
            fprintf(data, "%s %d %64s %s %c \n",
                database->patients[index].username,           
                database->patients[index].patient_id, 
                database->patients[index].password_hash, 
                database->patients[index].birth_date,
                database->patients[index].gender);
        }
        
        fclose(data);

    } else if (type == APPOINTMENT_TYPE) {

        // assign the gerneric pointer back to the database pointer
        Appointment_database* database = (Appointment_database*) database_ptr;

        for (int index = 0; index < database->count; index++) {
            fprintf(data, "%d %s %5s\n",
                database->appointments[index].patient_id,           
                database->appointments[index].date, 
                database->appointments[index].time);
        }
        
        fclose(data);
    }
}