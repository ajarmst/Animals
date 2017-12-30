#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "util.h"


//strip trailing whitespace and ctrl characters
char * CleanStringTR(char * sz)
{
  //Easy. Just start at the end, and work back to first printing character.
    char * p = sz;
    //find the null
    while(*p)++p;
    //work backwards
    while(p > sz)
    {
        if(!isgraph(*p)) *(p--) = 0;
        else break;
    }
    return sz;
}


//Remove padding, CR, DESTRUCTIVE
char * CleanStringCR(char * sz)
{
    //This modifies the input string by removing any
    //leading or trailing whitespace, CR
    char * p = sz; //Pointer to first char
    char * q = sz; //Insertion point
    int leadspace = 1; // Am I in leading whitepace?
    while(*p)// While I haven't reached the null
    {
      if(!isgraph(*p)) //non-printing
      {
          if(isspace(*p))
          {
              if(leadspace)
                  p++; //drop leading whitespace
              else
              {
                  //Replace all whitepsace with spaces
                  *q=' ';
                  ++q;
                  ++p;
              }
          }
      }
      else
      {
          //Done with any lead space
          leadspace = 0;
          *q = *p;
          ++p;
          ++q;
      }
    }
    *q = *p;//Copy final null.

    //Get rid of trailing whitespace
    sz = CleanStringTR(sz);
    return sz; // Return modified string
}

//Remove padding, convert to lower case DESTRUCTIVE
char * CleanStringLC(char * sz)
{
    //This modifies the input string by removing any
    //leading or trailing whitespace and converting
    //all uppercase characters to lowercase
    sz = CleanStringCR(sz);
    char * p = sz; //Pointer to first char
    char * q = sz; //Insertion point
    while(*p)// While I haven't reached the null
    {
        if(isspace(*p) || iscntrl(*p)) //whitespace
        {
            p++; //Ignore
        }
        else
        {//tolower doesn't change non-uppercase
            *q = tolower(*p);
            ++p;
            ++q;
        }
    }
    *q = *p;//Copy final null.
    return sz; // Return modified string
}

//Get an int from user
int GetInt(char * prompt)
{
    int gotanint = 0;
    int value = 0;
    char * pos = NULL; //Pointer to location in buffer
    char * buffer = (char *)malloc(INPUTBUFFSIZE);
    if (!buffer)// DMA Failure
    {
        fprintf(stderr, "Error: DMA Failure.\n");
#ifdef _DEBUG
        fflush(stdin); //Make sure there's nothing lurking in the buffer.
        printf("Press Enter to Exit");
        fgetc(stdin);
#endif
        exit(EXIT_FAILURE);
    }

    do
    {
        printf("%s ",prompt);
        fflush(stdout);
        fflush(stdin);
        if (!fgets(buffer, INPUTBUFFSIZE, stdin)) // Error talking to user
        {
            fprintf(stderr, "Error: Unable to get value from user.\n");
            exit(EXIT_FAILURE);
#ifdef _DEBUG
            fflush(stdin); //Make sure there's nothing lurking in the buffer.
            printf("Press Enter to Exit");
            fgetc(stdin);
#endif
        }
        value = strtol(buffer, &pos, 10); // Expect base 10.  pos at final
        //Was what we got an integer?
        if (buffer[0] != '\n' && (*pos == '\n' || *pos == '\0'))
            gotanint = 1; //looks good
    } while (!gotanint);
    //Free the memory
    free(buffer);
    return value;
}


//Get a y or n response from user.  Y returns 1, else 0
//Will keep asking until it gets something intelligible.
int GetYorN(char * prompt)
{
    int gotResponse = 0;
    int retval = 0;
    char * buffer = (char *)malloc(INPUTBUFFSIZE);
    if (!buffer)// DMA Failure
    {
        fprintf(stderr, "Error: DMA Failure.\n");
#ifdef _DEBUG
        fflush(stdin); //Make sure there's nothing lurking in the buffer.
        printf("Press Enter to Exit");
        fgetc(stdin);
        exit(EXIT_FAILURE);
#endif
    }

    do
    {
        printf("%s ",prompt);
        fflush(stdout);
        fflush(stdin);
        if (!fgets(buffer, INPUTBUFFSIZE, stdin)) // Error talking to user
        {
            fprintf(stderr, "Error: Unable to get value from user.\n");
#ifdef _DEBUG
            fflush(stdin); //Make sure there's nothing lurking in the buffer.
            printf("Press Enter to Exit");
            fgetc(stdin);
            exit(EXIT_FAILURE);
#endif
        }
        //We now have a response from the user.  Is it what we're looking for?
        buffer = CleanStringLC(buffer); //Convert to lcase, strip whitespace

        if(!strcmp(buffer,"y") || !strcmp(buffer,"yes"))
        {
            gotResponse = 1;
            retval = 1;
        }
        else if(!strcmp(buffer,"n") || !strcmp(buffer,"no"))
        {
            gotResponse = 1;
            retval = 0;
        }
        else gotResponse = 0;
    } while (!gotResponse);
    //Free the memory
    free(buffer);
    return retval;
}


//Get a string from the user after a prompt
char * GetString(char * prompt, char * buffer, int buffersize)
{
    //In this case, we will not acquire our own temporary buffer
    //but use the one passed to us by the calling scope.
    if (!buffer)// bad buffer location
    {
        fprintf(stderr, "Error: Buffer is a Null Pointer.\n");
#ifdef _DEBUG
        fflush(stdin); //Make sure there's nothing lurking in the buffer.
        printf("Press Enter to Exit");
        fgetc(stdin);
        exit(EXIT_FAILURE);
#endif
    }

    printf("%s ",prompt);
    fflush(stdout);
    fflush(stdin);
    if (!fgets(buffer, buffersize, stdin)) // Error talking to user
    {
        fprintf(stderr, "Error: Unable to get value from user.\n");
#ifdef _DEBUG
        fflush(stdin); //Make sure there's nothing lurking in the buffer.
        printf("Press Enter to Exit");
        fgetc(stdin);
        exit(EXIT_FAILURE);
#endif
    }
    return CleanStringCR(buffer);
}
