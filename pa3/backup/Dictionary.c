/*
 *  * Suneet Bhandari
 *   * sugbhand
 *    * CSE 15
 *     * 11/16/19
 * Dictionary.c is a program which uses linked lists to show how an online dicti
onary works going from word to word providing definition to definition.
 */

//-----------------------------------------------------------------------------
// Dictionary.c
// Linked List implementation of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"Dictionary.h"

// NodeObj type
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node type
typedef NodeObj* Node;

// DictionaryObj type
typedef struct DictionaryObj{
   Node head;         // pointer to first Node in Dictionary
   int numItems;      // number of items in this Dictionary
} DictionaryObj;

// newNode()
// constructor for the Node type
Node newNode(char* k, char* v) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = k;
   N->value = v;
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

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructor for the Dictionary ADT
Dictionary newDictionary(){
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->head = NULL;
   D->numItems = 0;

   return D;
}

// freeDictionary()
// Destructor for the Dictionary ADT
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      makeEmpty(*pD);
      free(*pD);
      *pD = NULL;
   }
}

// ADT operations -------------------------------------------------------------
// size()
// Returns the number of elements in D
int size(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: size() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }

   return D->numItems;
}

Node findKey(Dictionary D, char* k){
    Node node = D->head;
    Node null = NULL;
     while(node != NULL){         
        if(strcmp(node->key, k)==0){
            return node;
        }
        node = node->next;
    }
    return null;
}
// counts the number of chars in the entire dictionary
int countChars(Dictionary D){
    Node N = D->head;
    int sum = 0;
     for(int i = 0; i < D->numItems; i++){
         sum += strlen(N->key) + strlen(N->value) + 2;
    }
    return sum;
}

// lookup()
// If D contains a pair whose key matches argument k, then return the 
// corresponding value, otherwise return NULL.
char* lookup(Dictionary D, char* k){
   Node N = findKey(D, k);
   Node null = NULL;
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: lookup() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }
   if(N == NULL) {
       return null;
   }
     return N->value;
  
}

// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char* k, char* v){
   Node N = D->head;
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: insert() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }
   if(findKey(D, k) != NULL){
      fprintf(stderr, "Dictionary Error: insert() called on existing key in Dictionary. Key is: %s \n", k);
      exit(EXIT_FAILURE);
   }

   if(N == NULL){
      D->head = newNode(k,v);
   }else{
        while(N->next != NULL){
            N = N->next;
        }
        N->next = newNode(k,v);
   }
   (D->numItems)++;
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, char* k) {
   Node node = NULL;
   Node P = NULL;
   Node head = D->head;
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: delete() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }
   node = findKey(D,k);
   if(node == NULL){
      fprintf(stderr, "Dictionary Error: delete() called on non-existing key in Dictionary. Key is: %s \n", k);
      exit(EXIT_FAILURE);
   }
    for(node = head; node !=NULL; P = node, node = node->next){
        if(strcmp(node->key, k)==0){
            break;
        }
    }
    if (node == D->head) {
        D->head = node->next;
    } 
    else {
        P->next = node->next;
    }

    node->next = NULL;
    freeNode(&node);
    (D->numItems)--;
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D) {

   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: makeEmpty() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }

   freeAllNodes(D->head);
   D->head = NULL;
   D->numItems = 0;
}


// Other Operations -----------------------------------------------------------

// DictionaryToString()
// Determines a text representation of the current state of Dictionary D. Each 
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs 
// occur in the same order they were inserted into D. The function returns a
// pointer to a char array, allocated from heap memory, containing the text  
// representation described above, followed by a terminating null '\0' char. 
// It is the responsibility of the calling function to free this memory.
char* DictionaryToString(Dictionary D) {
   char* str;
   char tempString[150];

   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: printDictionary() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }
   
   int numOfChars = countChars(D);
   str = calloc((numOfChars+1), sizeof(char));
   Node node = D->head;
   
   while(node != NULL){
      sprintf(tempString, "%s %s\n", node->key,node->value);
      strcat(str, tempString);
      node = node->next;
   }
   return str;
}

