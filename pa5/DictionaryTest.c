//-----------------------------------------------------------------------------
// DictionaryClient1.java
// A rather weak test of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"


int main(){
   int i;
   Dictionary B;
   char* str;
   char* v;
   char* k = calloc(100, sizeof(char));

   // create a Dictionary and some pairs into it
   B = newDictionary();
   //insert(A, "1","a");
   //insert(A, "2","b");
   //insert(A, "3","c");
   //insert(A, "4","d");
   //insert(A, "5","e");
   //insert(A, "6","f");
   //insert(A, "7","g");
   
   // print out the Dictionary
   str = DictionaryToString(B);
   printf("%s\n", str);
   free(str);

   // test lookup()
   for(i=5; i<=15; i++){
      sprintf(k, "%d", i);
      v = lookup(B, k);
      printf("k=%s, value=%s\n", k, v);
   }
   printf("\n");

   // insert(A, "2","f");  // causes duplicate key error

   // delete some pairs
   delete(B, "2");
   delete(B, "4");
   delete(B, "6");

   // print out the Dictionary
   //str = DictionaryToString(A);
   //printf("%s\n", str);
   //free(str);

   // delete(A, "7");  // causes key not found error

   // check size
   printf("size(B) = %d\n", size(B));

   // make A empty, check size, print it out
   makeEmpty(B);
   printf("size(B) = %d\n", size(B));
   str = DictionaryToString(B);
   printf("%s\n", str);
   free(str);

   // free everything
   free(k);
   freeDictionary(&B);

   return EXIT_SUCCESS;
}

