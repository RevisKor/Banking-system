// import the header file
#include "../../include/prototypes/auth/date.h"
#include "../../include/prototypes/io.h"

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void get_date(const char *prompt, char *dest_birthdate) {
    flush_stdin();

    printf("%s (DD/MM/YYYY): ", prompt);
    fflush(stdout);

    if (fgets(dest_birthdate, 11, stdin) != NULL) {
        
        dest_birthdate[strcspn(dest_birthdate, "\n")] = '\0';
    }
}

void get_time(const char* prompt, char* dest_time) {
    char input_buffer[6];

    do {

        printf("%s (HH:MM): ", prompt);
        scanf("%s", input_buffer);
        flush_stdin();

    } while (validate_time(input_buffer));

    strcpy(input_buffer, dest_time); 
}

int validate_date(char* date) {
    unsigned int day, month, year;
    unsigned int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    sscanf(date, "%u/%u/%u", &day, &month, &year);

    if (year < 1900 || year > 2100) {
        return 1;
    } 

    if (month < 1 || month > 12) {
        return 1;
    } 
    
    if (month == 2 && is_leap_year(year)) {
        days_in_month[1] = 29;
    }

    return !(day <= days_in_month[month - 1]);
}

int validate_time(char* time) {
    unsigned int minutes, hours;

    sscanf(time, "%u:%u", &hours, &minutes);

    if (hours > 23) {
        return 1;
    }

    if (minutes > 59) {
        return 1;
    }

    return 0;
}

int validate_opening_hours(char* times, char* opening_hours, char* closing_hours) {
    unsigned int time[2], open[2], close[2];

    // break each time string to hours [0] and minutes [1]
    sscanf(times        , "%u:%u", &time [0], &time [1]);
    sscanf(opening_hours, "%u:%u", &open [0], &open [1]);
    sscanf(closing_hours, "%u:%u", &close[0], &close[1]);

    unsigned int time_minutes, open_minutes, close_minutes;

    time_minutes = time[0] * 60 + time[1];
    open_minutes = open[0] * 60 + open[1];
    close_minutes = close[0] * 60 + close[1];

    if (time_minutes < open_minutes || time_minutes > close_minutes) {
        return 1;
    }

    return 0;
}
