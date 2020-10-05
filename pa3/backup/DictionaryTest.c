/*
 *  *  * Suneet Bhandari
 *   *   * sugbhand
 *    *    * CSE 15
 *     *     * 11/16/19
 *      * Dictionary.c is a program which uses linked lists to show how an online dictionary works going from word to word providing definition to definition.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

int main(){
   Dictionary A;
   char* str;
   char* k = calloc(50, sizeof(char));

   // create a Dictionary and some pairs into it
   //A = newDictionary();
   //insert(A, "1","app");
   //insert(A, "2","or");
   //insert(A, "3","ban");
   //insert(A, "4","cheese");
   //insert(A, "5","straw");
   //printf("size(A) = %d\n", size(A));


   //print out the Dictionary
   str = DictionaryToString(A);
   printf("%s\n", str);

   free(str);

   // test lookup()
   //sprintf(k,"10");
   //printf("Value of key: %s is %s \n", k, lookup(A,k));
   //sprintf(k,"30");
   //printf("Value of key: %s is %s \n", k, lookup(A,k));
   //sprintf(k,"70");   
   //printf("Value of key: %s is %s \n", k, lookup(A,k));


   //insert(A, "10","blueberries");  // causes duplicate key error

   // delete some pairs
   delete(A, "10");
   delete(A, "30");
   delete(A, "50");

   // print out the Dictionary
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);

   //delete(A, "50");  // causes key not found error

   // check size
   //printf("size(A) = %d\n", size(A));

   // make A empty, check size, print it out
   //makeEmpty(A);
   //printf("size(A) = %d\n", size(A));
   //str = DictionaryToString(A);
   //printf("%s\n", str);
   //free(str);

   // free everything
   free(k);
   freeDictionary(&A);

   return EXIT_SUCCESS;
}

