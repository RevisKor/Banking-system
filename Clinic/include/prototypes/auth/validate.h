#ifndef VALIDATE_H
#define VALIDATE_H

// imports
#include "../../common.h"

// prototypes
void check_input_length(const char *display_prompt, const char *field_identifier, char **destination_buffer, int minimum_allowed_length, int maximum_allowed_length);
int validate_password(const char *password);

#endif