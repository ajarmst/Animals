#ifndef UTILH
#define UTILH
#pragma once

//Some utility functions of general value.

//Size of general purpose buffer for user input.
define INPUTBUFFSIZE 255

//Remove padding, convert to lower case DESTRUCTIVE
char * CleanString(char * sz);

//Get an int from user
int GetInt(char * prompt);

//Get a y or n response from user.  Y returns 1, else 0
int GetYorN(char * prompt);

//Get a string from the user after a prompt
char * GetString(char * prompt, char * buffer, int buffersize);

#endif
