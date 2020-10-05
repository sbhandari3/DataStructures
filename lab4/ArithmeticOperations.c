//-----------------------------------------------------------------------------
// Suneet Bhandari
// sugbhand
// 11/22/19
// ArithmeticOperations.c is a program that evaluates some arithmetic operations encoded in an input file through using basic functions, such as pointers
// ArithmeticOperations.c
// Stubs for required functions.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#define MAX_STRING_LENGTH 100

// Define fptr_t type using typedef statement
typedef int (*fptr_t)(int, int);

// Define functions
int sum(int x, int y){
   return x+y;
}
 
int diff(int x, int y){
   return x-y;
}

int prod(int x, int y){
   return x*y;
}

int quot(int x, int y){
   return x/y;
}

int rem(int x, int y){
   return x%y;
}

int apply( fptr_t fp, int x, int y){
   return fp(x,y);
}

int compute(fptr_t fcn[5], int* A, int* idx, int n){
   int first;
   first = A[0];
   for(int i = 0; i < n; i++){
      first = apply(fcn[idx[i]], first, A[i + 1]);
   }
   return first;
}
int main(int argc, char * argv[]){
   
   fptr_t op[]  = {sum, diff, prod, quot, rem};
   FILE *in, *out;   // handles for input and output files 
   char word[256];   // char array to store words from input file 
   int number[256];
   int i = 0;
   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open input file for reading 
   in = fopen(argv[1], "r");
   if( in==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing 
   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }
   //opCode = calloc(MAX_STRING_LENGTH+1,sizeof(int));
   //A = calloc(MAX_STRING_LENGTH+1,sizeof(int));
   
   //assert(A != NULL && opCode != NULL);
   //int n = sizeof(opCode);
   // read words from input file, print on separate lines to output file 
   while(fscanf(in, " %s", word)!=EOF){
       //fprintf(out, "%s\n", word);
       number[i] = atoi(word);
       i++;
   }
   int* opCode = calloc(number[0],sizeof(int));
   int* A = calloc(number[0]+1,sizeof(int));

   assert(A != NULL && opCode != NULL);

   int z = number[0]+1;
   for(int j = 0; j < number[0]; j++){
      opCode[j] = number[j+1];
   }
   for(int s = 0; s < number[0] + 1; s++){
      A[s] = number[z];
      z++;
   }
   fprintf(stdout,"%d\n", compute(op, A, opCode, number[0]));
   //for(int j = 0; j < i; j++){
      //printf("%d\n", number[j]);
   //}
   free(A);
   free(opCode); 
   // close input and output files 
   fclose(in);
   fclose(out);
   
   return(EXIT_SUCCESS);
}

