#ifndef COMMON_H
#define COMMON_H

// standard imports header
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Single structs 
typedef struct {
    char username[65];
    int patient_id;

    char password_hash[65];

    char birth_date[11];    // DD/MM//YYYY
    char gender;            // M / F

} Patient;

typedef struct {
    int patient_id;

    char date[11];          // DD/MM//YYYY
    char time[6];           // HH:MM

} Appointment;

// Database structs
typedef struct {
    Patient* patients;
    int count;
    int capacity;

} Patient_database;

typedef struct {
    Appointment* appointments;
    int count;
    int capacity;
    
} Appointment_database;

// enums
typedef enum {
    PATIENT_TYPE,
    APPOINTMENT_TYPE,

} Database_type;

// common error enum
typedef enum {
    MEMMORY_ALLOCATION_ERROR = 1,
    FILE_NOT_FOUND_ERROR,
    INTERNAL_ERROR

} ERROR_STATUS;

#define ONE_SECOND 1

#endif