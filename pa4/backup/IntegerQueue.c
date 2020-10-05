//-----------------------------------------------------------------------------
// IntegerQueue.h
// Header file for the Integer Queue ADT in C
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include <assert.h>
#include <string.h>\

#ifndef _Queue_H_INCLUDE_
#define _Queue_H_INCLUDE_

typedef struct NodeObj{
   int job;
   struct NodeObj* next;
} NodeObj;

// Node type
typedef NodeObj* Node;

// newNode()
// constructor for the Node type
Node newNode(int x) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->job = x;
   N->next = NULL;
   return N;
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// freeAllNodes()
// uses recursion to free all the Nodes in list headed by H
void freeAllNodes(Node H){
   if( H!=NULL ){
      freeAllNodes(H->next);
      freeNode(&H);
   }
}

// Exported type --------------------------------------------------------------

// IntegerQueue
// Exported reference type
typedef struct IntegerQueueObj* IntegerQueue;

// IntegerQueueObj
typedef struct IntegerQueueObj{
   int numItems;
   Node front;
   Node back;
} IntegerQueueObj;

// Constructors-Destructors ---------------------------------------------------

// newIntegerQueue()
// Constructor for the IntegerQueue ADT
IntegerQueue newIntegerQueue(){
   IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
   Q->numItems = 0;
   Q->front = NULL;
   Q->back = NULL;
   return Q;
}

// freeIntegerQueue()
// Destructor for the Queue ADT
void freeIntegerQueue(IntegerQueue* pQ){
   if( pQ!=NULL && *pQ!=NULL ){
      free(*pQ);
      *pQ = NULL;
   }
}

// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise.
int isEmpty(IntegerQueue Q){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: isEmpty() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }

   return (Q->numItems == 0);
}

// length()
// Returns the number of elements in Q
int length(IntegerQueue Q){
   return Q->numItems;
}

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: enqueue() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }
   if( (Q->numItems)==0 ){
      Node N = newNode(x);
      Q->front = N;
      Q->back = N;
      (Q->numItems)++;
      return;
   }
   else if(Q->numItems == 1){
      Node N = newNode(x);
      Q->back = N;
      Q->front->next = Q->back;
      (Q->numItems)++;
      return;
   }
   else{
   Node N = newNode(x);
   Q->back->next = N;
   Q->back = N;
   (Q->numItems)++;  
   }
      
}

// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q){
   int x;
   Node N = NULL;
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: dequeue() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }
   if( (Q->numItems)==0 ){
      fprintf(stderr, "IntegerQueue Error: dequeue() called on empty "\
                      "IntegerQueue");
      exit(EXIT_FAILURE);
   }
   if( Q->front==NULL ){
      fprintf(stderr, "IntegerQueue Error: enqueue() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }   

   N = Q->front;
   x = N->job;
   
   if((Q->numItems) ==1 ){
      Q->front = NULL;
      Q->back = NULL;
   }
   else{
      Q->front = Q->front->next;
   }
   (Q->numItems)--;
   
   return x;
}


// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()
int peek(IntegerQueue Q){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: peek() called on NULL "\
                     "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }
   if( (Q->numItems)==0 ){
      fprintf(stderr, "IntegerQueue Error: peek() called on empty "\
                      "IntegerQueue");
      exit(EXIT_FAILURE);
   }

   return Q->front->job;
}

// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: dequeueAll() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }

   Q->numItems = 0;
   Q->front = NULL;
   Q->back = NULL;
}


// Other Operations -----------------------------------------------------------

// IntegerQueueToString()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a 
// char array, allocated from heap memory, containing the integer sequence 
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated 
// by a NUL '\0' character. It is the responsibility of the calling function to 
// free this heap memory.
char* IntegerQueueToString(IntegerQueue Q){
   /*/char* str;
   char* tempString[Q->numItems*2-1];
   
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: printIntegerQueue() called on NULL IntegerQueue reference");
      exit(EXIT_FAILURE);
   }
   int numOfChars = Q->numItems;
   //str = calloc(((Q->numItems)*2-1), sizeof(char));
   Node node = Q->front;
   //itoa(node->job, tempString[0], 10);
   sprintf(tempString[0], "%d", node->job);
   node = node->next;
   for(int i = 1; i < Q->numItems*2-3; i +=2){
      //itoa(node->job, tempString[i+1], 10);
      if(node == NULL) break;
      sprintf(tempString[i+1], "%d", node->job);
      tempString[i] = " ";
      node = node->next;
   }
   while(node != NULL){
      //sprintf(tempString, "%s %s\n", node->key,node->value);
      strcat(str, tempString);
      node = node->next;
   }*/

   Node node = Q->front;
   int total = Q->numItems;
   char* str = calloc(total*2 + 1, sizeof(char));
   char* temp = calloc(2, sizeof(char));
   for(int i = 0; i < total; i ++){
      sprintf(temp, "%d ", node->job);
      strcat(str, temp);
      node = node->next;
   }
   free(temp);
   return str;

}
// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0) 
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R){
   int i, eq=0;
   if( Q==NULL || R==NULL ){
      fprintf(stderr, "IntegerQueue Error: equals() called on NULL IntegerQueue "\
                      "reference");
      exit(EXIT_FAILURE);
   }

   eq = ( (Q->numItems)==(R->numItems) );
   for(i=0; eq && i<(Q->numItems); i++){
      eq = ( (Q->front->job)==(R->front->job) );
   }
   return eq;
}

#endif
