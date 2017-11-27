#ifndef ANIMALSH
#define ANIMALSH
#pragma once

#define ANITEXTSIZE 512 //Number of chars in node text
#define NULLSTRING "###" //Symbol in file to indicate NULL
//Forward declaration so that "Node *" makes sense
struct node;

typedef struct node
{   char text[ANITEXTSIZE];
    struct node * yes;
    struct node * no;
}Node;

//Display the contents of a tree
void PrintTree(Node * root, int indent);

//Release memory
Node * Delete(Node * tree);

//Open a file and call SaveTree to
//save tree to it.
void Save(Node * tree, char * filename);

//Recursively save tree to text file
void SaveTree(Node * tree, FILE * fp);

//Open a file and call loadtree to
//retrieve a tree
Node * Load(char * filename);

//Recursively Load tree from a text file
Node * LoadTree(FILE * fp);

//Create some test data
Node * AnimalsTest();

#endif
