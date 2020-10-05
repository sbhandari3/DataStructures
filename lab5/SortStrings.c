//-----------------------------------------------------------------------------
// SortStrings.c
// Suneet Bhandari
// sugbhand
// 12/04/19
// SortStrings.c is a lab that takes strings from a file and sorts them alphabetically.


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#include <assert.h>
#define MAX_STRING_LENGTH 100
void printArray(FILE* out,char** A, int n){
   int i;
   for(i=0; i<n; i++){
      fprintf(out, "%s\n", A[i]);
   }
}

void swap(char** A, int i, int j){
   char* temp;
   temp = A[i];
   A[i] = A[j];
   A[j] = temp;
}
int Partition(char** A, int p, int r){
   int j,i;
   i = p-1;
   for(j=p; j<r; j++){

      if(strcmp(A[j],A[r]) <= 0){
         i++;
         swap(A, i, j);
      }
   }
   swap(A, i+1, r);
   return(i+1);
}

void QuickSort(char** A, int p, int r){
   int q;
   if(p < r){
      q = Partition(A, p, r);
      QuickSort(A, p, q-1);
      QuickSort(A, q+1, r);
   }
}
int main(int argc, char * argv[]){
   FILE *in;         // input file pointer
   FILE *out;        // output file pointer 
   char word[200];   // stores one string from the input file 
   int status, n;
   char ch;
   char** A;
   int i = 0;
   // Check command line for correct number of arguments.
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // Open input file for reading. 
   in = fopen(argv[1], "r");
   if( in==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // Open output file for writing. 
   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // Read words from the input file and parse them as int, double or string.
   while(fscanf(in, " %s", word)!=EOF){ 
      // the space in the format string says to skip any number of leading
      // white space characters. We end when EOF (end-of-file) is reached. 
      // This operation will fail if the string has more than 200 characters, 
      // since that is the length of array word[].
      
      // try to parse word as int
      status = sscanf(word, "%d%c", &n, &ch);  // why is ch needed?
      if(status==1){
         //fprintf(out, "%s is an int\n", word);
          A = calloc(atoi(word),sizeof(char*));
          assert(A != NULL);
         continue; // skip rest of this iteration
      }
      size_t len = strlen(word);
      A[i] = (char *)calloc(len+1,sizeof(char));
      strcpy(A[i], word);
      i++;
      
      // word must be a non-numeric string
      //fprintf(out, "%s is a non-numeric string\n", word);
 
   }
   
   //for(int z = 0; z < sizeof(A); z++){
      //fprintf(out,"%s", A[z]);
   //}
   QuickSort(A, 0,i-1);
   printArray(out,A, i);
   for(int z = 0; z < i; z++){
      free(A[z]);
   }
   free(A);
   // close input and output files 
   fclose(in);
   fclose(out);

   return(EXIT_SUCCESS);
}
