#include "include/common.h"
#include "include/prototypes/database/load_data.h"
#include "include/prototypes/create_account.h"

void print_patient_database(const Patient_database* db);
void print_appointment_database(const Appointment_database* db);

int main() {
    Patient_database patients;
    
    patients.count = 0;
    patients.capacity = 10;
    patients.patients = malloc(patients.capacity * sizeof(Patient));


    Appointment_database appointments;

    appointments.count = 0;
    appointments.capacity = 10;
    appointments.appointments = malloc(appointments.capacity * sizeof(Appointment));

    load_data("data/Patients.txt", &patients, PATIENT_TYPE);
    load_data("data/Appointments.txt", &appointments, APPOINTMENT_TYPE);

    print_patient_database(&patients);
    print_appointment_database(&appointments);

    create_account(&patients);

   // Change -> to . since 'patients' is a local struct variable
    Patient* new_patient = &patients.patients[patients.count - 1];

    // This call is perfectly correct!
    add_to_database("data/Patients.txt", new_patient, PATIENT_TYPE);

    free(patients.patients);
    free(appointments.appointments);

    return 0;
}

// helpers
void print_patient_database(const Patient_database* db) {
    if (db == NULL || db->count == 0) {
        printf("\n=== Patient Database is empty ===\n");
        return;
    }

    printf("\n=================================== PATIENT DATABASE ===================================\n");
    // %-20s means left-aligned, 20 characters wide. %-10d means left-aligned integer, 10 wide.
    printf("%-10s | %-20s | %-12s | %-6s | %s\n", "ID", "Username", "Birth Date", "Gender", "Password Hash (First 10 chars)");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < db->count; i++) {
        Patient p = db->patients[i];
        
        // Truncate hash just for printing so it doesn't blow up the terminal screen width
        char short_hash[11];
        snprintf(short_hash, sizeof(short_hash), "%s", p.password_hash);

        printf("%-10d | %-20s | %-12s | %-6c | %s...\n", 
               p.patient_id, 
               p.username, 
               p.birth_date, 
               p.gender, 
               short_hash);
    }
    printf("========================================================================================\n");
    printf("Total Patients: %d / Capacity: %d\n", db->count, db->capacity);
}

void print_appointment_database(const Appointment_database* db) {
    if (db == NULL || db->count == 0) {
        printf("\n=== Appointment Database is empty ===\n");
        return;
    }

    printf("\n=================== APPOINTMENT DATABASE ===================\n");
    printf("%-15s | %-15s | %-10s\n", "Patient ID", "Date", "Time");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < db->count; i++) {
        Appointment a = db->appointments[i];
        printf("%-15d | %-15s | %-10s\n", 
               a.patient_id, 
               a.date, 
               a.time);
    }
    printf("============================================================\n");
    printf("Total Appointments: %d / Capacity: %d\n", db->count, db->capacity);
}