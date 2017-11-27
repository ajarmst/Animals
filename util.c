#include <stdlib>
#include <stdio>
#include <ctype>

//Remove padding, convert to lower case DESTRUCTIVE
char * CleanString(char * sz)
{
    //This modifies the input string by removing any
    //leading or trailing whitespace and converting
    //all uppercase characters to lowercase
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
        exit(EXIT_FAILURE);
#ifdef _DEBUG
        fflush(stdin); //Make sure there's nothing lurking in the buffer.
        printf("Press Enter to Exit");
        fgetc(stdin);
#endif
    }

    do
    {
        printf("%s",prompt);
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
int GetYorN(char * prompt)
{
    int gotResponse = 0;
    int retval = 0;
    char * pos = NULL; //Pointer to location in buffer
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
        printf("%s",prompt);
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
        if(!strcmp(buffer,"y") && !strcmp(buffer,"yes"))
        {
            gotresponse = 1;
            retval = 1'
        }
        else if(!strcmp(buff,"n") && !strcmp(buffer,"no"))
        {
            gotresponse = 1;
            retval = 0;
        }
        else gotresponse = 0;
    } while (!gotresponse);
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

    do
    {
        printf("%s",prompt);
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
        return buffer;
}
