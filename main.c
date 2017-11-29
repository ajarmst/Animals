#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "animals.h"
#include "util.h"

#define SAVEFILE "savefile.txt"

int main(int argc, char** argv)
{
    Node * root = NULL;

    //Test i/o utility functions

    int i = GetInt("Gimme an int: ");
    printf("You said: %d\n",i);

    char sz[50] = "";
    GetString("Say something: ",sz,50);
    printf("You said: %s\n",sz);

    i = GetYorN("Yes or No?");
    printf("%s\n",i?"Oui":"Non");

    //Test data
    root = AnimalsTest();
    //Create a savefile
    Save(AnimalsTest(),SAVEFILE);
    //Release test data
    root = Delete(root);

    //Now, for a real test
    //Load our save file
    root = Load(SAVEFILE);
    PrintTree(root,0);
    root = Delete(root);

    return EXIT_SUCCESS;
}
