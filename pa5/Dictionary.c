/*
 *  * Suneet Bhandari
 *   * sugbhand
 *    * CSE 15
 *     * 12/6/19
 * Dictionary.c is a program which uses hash tables with linked lists to show how an online dictionary works going from word to word providing definition to definition.
 */


//-----------------------------------------------------------------------------
// Dictionary.c
// Hash Table implementation of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include "Dictionary.h"

const int tableSize = 199;

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);   // same as: shift = shift%sizeInBits
   if ( shift == 0 )
      return value;
   else
      return (value << shift) | (value >> (sizeInBits - shift)); // perform rotation
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {  // input points to first char in string
   unsigned int result = 0xBAE86554;  // = 10111010111010000110010101010100, begin with a random looking bit pattern
   while (*input) {                   // while *input is not '\0' (not end of string)
      result ^= *input++;                // result = result ^ *input (current char alters result) 
                                         // input++  (go to next char)
      result = rotate_left(result, 5);   // rotate result by fixed amount
   }
                   // after the preceding loop, each char of input has altered result, which
   return result;  // is now a random looking bit pattern depending on the input string
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
   return pre_hash(key)%tableSize;
}

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
   Node *hTable;         // pointer to hashTable in Dictionary
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


// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructor for the Dictionary ADT
Dictionary newDictionary(){
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D != NULL);
   D->hTable = calloc(tableSize, sizeof(Node));
   assert(D->hTable != NULL);
   D->numItems = 0;

   return D;
}

// freeDictionary()
// Destructor for the Dictionary ADT
void freeDictionary(Dictionary* pD){
if( pD!=NULL && *pD!=NULL ){
      makeEmpty(*pD);
      free((*pD)->hTable);
      free(*pD);
      *pD = NULL;
   }
}

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
    Node node = D->hTable[hash(k)];
    Node null = NULL;
     while(node != NULL){
        if(strcmp(node->key, k)==0){
            return node;
        }
        node = node->next;
    }
    return null;
}
int countChars(Dictionary D){
    int sum = 0;
    for(int i = 0; i < tableSize; i++) {
        Node N = D->hTable[i];
        //while(N != NULL){
        for(Node P = N; P !=NULL;P = P->next){
            sum += strlen(P->key) + strlen(P->value) + 2;
        }
    }
    return sum;
}
/*int countChars(Dictionary D){
    Node N = D->head;
    int sum = 0;
     for(int i = 0; i < D->numItems; i++){
         sum += strlen(N->key) + strlen(N->value) + 2;
    }
    return sum;
}*/
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
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: insert() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }
   if(findKey(D, k) != NULL){
      fprintf(stderr, "Dictionary Error: insert() called on existing key in Dictionary. Key is: %s \n", k);
      exit(EXIT_FAILURE);
   }
    Node N = newNode(k, v);
    
 if(D->hTable[hash(k)] != NULL){
      N->next = D->hTable[hash(k)];
      D->hTable[hash(k)] = N;
      (D->numItems)++;
   }else{
      D->hTable[hash(k)] = N;
      (D->numItems)++;
   }
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, char* k) {
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: delete() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }
   Node P = findKey(D,k);
   if(P == NULL){
      fprintf(stderr, "Dictionary Error: delete() called on non-existing key in Dictionary. Key is: %s \n", k);
      exit(EXIT_FAILURE);
   }
   P = D->hTable[hash(k)];

   if (P->key == k) {
        D->hTable[hash(k)] = P->next;
    } else{
        while(P->next->key != k) {
            P = P->next;
        }
        Node t = P->next;
        P->next = t->next;
    }
    freeNode(&P);
    (D->numItems)--;
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D) {
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: makeEmpty() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }
    //int j = 0;
    //while(j < tableSize){ 
    for(int j = 0; j < tableSize; j++){
        while (D->hTable[j] != NULL) {
            Node P = D->hTable[j];
            D->hTable[j]=P->next;
            freeNode(&P);
            P = NULL;
            //j++;
        }
    }
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
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: printDictionary() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }
   char* str;
   char tS[256];
   int count = countChars(D);
   str = calloc((count+1), sizeof(char));

   for(int i = 0; i < tableSize; i++){
       for(Node P = D->hTable[i]; P !=NULL;P = P->next){      
            sprintf(tS, "%s %s\n", P->key,P->value);
            strcat(str, tS);
       }
   }
   return str;
}

