/*
 * Suneet Bhandari
 * sugbhand
 * CSE 15
 * 10/20/19
 *
 * charType.c is a program in C which takes letters and punctuation and whitespaces and sorts them into each own category in the output letting the user know how much of what is in the given file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

// function prototype
void extract_chars(char* s, char* a, char* d, char* p, char* w) ;

// function main which takes command line arguments
int main(int argc, char* argv[]){
FILE* in;
FILE* out;
char* line;
char* alpha;
char* digits;
char* punct;
char* spaces;
int   lines = 1;

// check command line for correct number of arguments
if( argc != 3 ){
      printf("Usage: %s input-file output-file\n", argv[0]);
      exit(EXIT_FAILURE);
   }

// open input file for reading
 if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

// open output file for writing
  if ((out=fopen(argv[2], "w")) == NULL) {
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
  }

// allocate strings line and alphabets, digits, punctuation, spaces on the heap
 line  = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
 alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
 digits = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
 punct = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
 spaces = calloc(MAX_STRING_LENGTH+1, sizeof(char) );

 assert( line!=NULL && alpha!=NULL && digits!=NULL && punct!=NULL && spaces!=NULL );

// read each line in input file, extract alphabets, digitss, punctuation, spaces  characters
while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
      extract_chars(line, alpha, digits, punct, spaces);
      fprintf(out, "line %d contains:\n", lines++);
      fprintf(out, "%d alphabetic %s: %s\n",(int)strlen(alpha), strlen(alpha) > 1 || strlen(alpha) == 0 ? "characters" : "character", alpha );
      fprintf(out, "%d numeric %s: %s\n",(int)strlen(digits), strlen(digits) > 1 || strlen(digits) == 0 ? "characters" : "character", digits );
      fprintf(out, "%d punctuation %s: %s\n",(int)strlen(punct), strlen(punct) > 1 || strlen(punct) == 0 ? "characters" : "character", punct );
      fprintf(out, "%d whitespace %s: %s\n",(int)strlen(spaces), strlen(spaces) > 1 || strlen(spaces) == 0 ? "characters" : "character", spaces );
   }

// free heap memory
free(line);
free(alpha);
free(digits);
free(punct);
free(spaces);

// close input and output files
fclose(in);
fclose(out);

return EXIT_SUCCESS;
}

// function definition
 void extract_chars(char* s, char* a, char* d, char* p, char* w ){
	int i=0;
	int j=0;
	int k=0;
	int l=0;
	int m=0;
       while(s[i]!='\0' && i<MAX_STRING_LENGTH){
             if( isalpha( (int) s[i]) ) a[j++] = s[i];
             if( isdigit( (int) s[i]) ) d[k++] = s[i];
             if( ispunct( (int) s[i]) ) p[l++] = s[i];
             if( isspace( (int) s[i]) ) w[m++] = s[i];
                   i++;
                      }
                         a[j] = '\0';
                         d[k] = '\0';
                         p[l] = '\0';
                         w[m] = '\0';
 }
