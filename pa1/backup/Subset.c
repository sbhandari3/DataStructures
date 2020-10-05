/* 
 * Suneet Bhandari
 * sugbhand
 * CSE 15
 * 10/11/19
 * Subset.c is a program which prints all the binomial coefficients of the user chosen inputs
 * Subset.c  
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_SIZE 100
/* This function prints out the specific set makes sure the proper amount of commas in place
 *
 */
void printSet (int B[], int n) {

    printf("{");
    int addComma = 0;
     for (int j=1; j<n; j++) {
        if (B[j] == 1) {
            if (addComma==0) {
                printf("%d", j);
                addComma = 1;
            }
            else {
                printf(", %d", j);
            }
        }
    }
    printf("}\n");
}
/* creates all the subsets
 */
void printSubsets(int B[], int n, int k, int i){
    if (k==0) {
        printSet(B, n);
        return;
    }
    if (i > n - 1){
        return;
    }

    B[i]=1;
    printSubsets (B, n, k-1, i+1);

    B[i]=0;
    printSubsets (B, n, k, i+1);
}
/* function to check whether the arguments entered are positive integers.
 */
int checkInteger (char * c) {
    int check = 0;
    int counter = 1;
    while(check < strlen(c)){
        if (!isdigit(c[check])){
                counter = 0;
                break;
            }
            check++;
        }
    return counter;

}


int main(int argc, char *argv[]) {
    int B[MAX_SIZE + 1];
    int i = 1;

/* creates space and memory
 */     
    for(int i = 0; i < MAX_SIZE + 1; i++){
        B[i] = 0;
    }

/* checks if there are more or less than 3 arguments and whether they integers or not
 */
    if(argc < 3 || argc > 3 || !checkInteger(argv[1]) || !checkInteger(argv[2])){   
        printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)\n");       
        exit(EXIT_FAILURE);
    }   
/* creates integers from the string values the user inputted
 */
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

/* check for whether k is greater than n and if n is over 100
 */
    if(k > n || n > 100){
        printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)\n");       
        exit(EXIT_FAILURE);
    }   
        printSubsets(B, n+1, k, i);
}       
