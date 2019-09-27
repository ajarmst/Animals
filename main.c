#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h> //For getting information about files
#include "animals.h"
#include "util.h"

#define SAVEFILE "savefile.txt"

int main(int argc, char** argv)
{
    Node * root = NULL;
    //Do I have a savefile to load from?
    struct stat statb;
    if(stat(SAVEFILE,&statb))
    {
        //No save file.  Let's create one.
        Save(AnimalsTest(),SAVEFILE);
    }

    //Load my data
    root = Load(SAVEFILE);

    //Play the game for a round
    do
    PlayRound(root);
    while(GetYorN("Play Again?"));
#ifdef _DEBUG //Print state of tree if we're in debug mode
    PrintTree(root,0);
#endif
    //Save current state, clean up and leave
    Save(root, SAVEFILE);
    root = Delete(root);

    return EXIT_SUCCESS;
}
