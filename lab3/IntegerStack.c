/*
 * Suneet Bhandari
 * sugbhand
 * CSE 15
 * 11/06/19
 *
 * IntegerStack.c is a program in C which takes a file an uses ADT in C. There are a series of functions used to show how a ADT is used seen when an input file is inputted.
 */


#include<stdlib.h>
#include<stdio.h>
#include"IntegerStack.h"
#define MAX_LENGTH 25 

// Private Types and Functions ----------------------------
// IntegerStackObj
typedef struct IntegerStackObj{
 int* item; //array of IntegerStack items
 int numItems; // number of items in this IntegerStack
 int physicalSize;  // current length of underlying array
} IntegerStackObj;

// arrayIndex()
// transforms an IntegerStack index to an Array index
int arrayIndex(int stackIndex){
 return stackIndex-1;
}

// doubleItemArray
// Doubles the physical size of the underlying array S->item.
void doubleItemArray(IntegerStack S){
   int i;
   int* newArray;
   int* oldArray = S->item;
   S->physicalSize *= 2;
   newArray = calloc(S->physicalSize, sizeof(int));
   for( i=0; i<(S->numItems); i++){
      newArray[i] = oldArray[i];
   }
   S->item = newArray;
   free(oldArray);
}
// Constructors-Destructors --------------------------------
// newIntegerStack()
// Constructor for the IntegerStack ADT
IntegerStack newIntegerStack(){
 IntegerStack S = malloc(sizeof(IntegerStackObj));
 S->item = calloc(MAX_LENGTH, sizeof(int));
 S->numItems = 0;
 S->physicalSize = MAX_LENGTH;
 return S;
}

// freeIntegerStack()
// Destructor for the Stack ADT
void freeIntegerStack(IntegerStack* pS){
 if( pS!=NULL && *pS!=NULL ){
 free((*pS)->item);
 free(*pS);
 *pS = NULL;
 }
}

// ADT operations
// isEmpty()
int isEmpty(IntegerStack S){
    if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   return (S->numItems == 0);
}

// push()
// Pushes x on top of S.
void push(IntegerStack S, int x){
    if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: push() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
// increase physical size of array if necessary
   if( (S->numItems)==(S->physicalSize) ){
      doubleItemArray(S);
   }
   S->item[S->numItems] = x;
   S->numItems++;
}
// pop()
// Deletes and returns integer at top of S.
// Pre: !isEmpty(S)
int pop(IntegerStack S){
    if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: pop() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
    S->numItems--;
    return S->item[S->numItems];
}

// peek()
// Returns integer at top of S.
// Pre: !isEmpty(S)
int peek(IntegerStack S){
    if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: peek() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   return S->item[S->numItems-1];
}

// popAll()
// Resets S to the empty state.
void popAll(IntegerStack S){
    if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: popAll() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   S->numItems = 0;
}

// printIntegerStack()
// Prints a space separated list of integers in S, from top to bottom, to the
// filestream out.
void printIntegerStack(FILE* out, IntegerStack S){
    if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: printIntegerStack() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   for(int i=S->numItems-1; i >=0; i--){
      fprintf(out, "%d ", S->item[i] );
   }
   fprintf(out, "\n");
}
// equals()
// Returns true (1) if S and T are matching sequences of integers, false (0) 
// otherwise.
int equals(IntegerStack S, IntegerStack T){
    if( S==NULL || T==NULL ){
      fprintf(stderr, "IntegerStack Error: equals() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   int i, eq;
   eq = ( (S->numItems)==(T->numItems) );
   for( i=0; eq && i< (S->numItems); i++){
      eq = ( (S->item[i])==(T->item[i]) );
   }
   return eq;
}
