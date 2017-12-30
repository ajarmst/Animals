#ifndef UTILH
#define UTILH
#pragma once

//Some utility functions of general value.

//Size of general purpose buffer for user input.
#define INPUTBUFFSIZE 255

//strip trailing whitespace and ctrl characters
char * CleanStringTR(char * sz);

//Remove padding, carriage returns and control
char * CleanStringCR(char * sz);

//Remove padding, internal spaces, convert to lower case DESTRUCTIVE
char * CleanStringLC(char * sz);

//Get an int from user
int GetInt(char * prompt);

//Get a y or n response from user.  Y returns 1, else 0
int GetYorN(char * prompt);

//Get a string from the user after a prompt
char * GetString(char * prompt, char * buffer, int buffersize);

#endif
