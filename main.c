#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "animals.h"

#define SAVEFILE "savefile.txt"

int main(int argc, char** argv)
{
    Node * root = NULL;

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
