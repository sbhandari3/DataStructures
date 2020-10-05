#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include <stdbool.h>

    void placeQueen(int** B, int n, int i, int j) {
        B[i][j] = 1;
        B[i][0] = j;
        int letters, numbers;
        for(letters = i+1; letters <= n; letters++)
            B[letters][j]+= -1;

        letters = i + 1;
        numbers = j - 1;
        
        while(letters < n + 1 && numbers > 0){
            B[letters++][numbers--] += -1;
        }
        
        letters = i + 1;
        numbers = j + 1;
        
        while(letters< n + 1 && numbers< n + 1){
            B[letters++][numbers++] += -1;
        }
    }

    void removeQueen(int** B, int n, int i, int j) {
        B[i][j] = 0;
        B[i][0] = 0;
        int letters, numbers;
        for(letters = i+1; letters <= n; letters++)
            B[letters][j]+= 1;

        letters = i + 1;
        numbers = j - 1;
        
        while(letters < n + 1 && numbers > 0){
            B[letters++][numbers--] += 1;
        }
        
        letters = i + 1;
        numbers = j + 1;
        
        while(letters < n + 1 && numbers < n + 1){
            B[letters++][numbers++] += 1;
        }
    }
    int checkforSpace(int** B, int n, int i, int j) {
        int letters;
        int numbers;

        for(letters = 1; letters < i; letters++){
            if(B[letters][j]==1){
                return -1;
            }
        }

        letters = i - 1;
        numbers = j - 1;
        
        while(letters >= 1 && numbers >= 1){
            if(B[letters--][numbers--]==1){ 
                return -1;
            }
        }
        
        letters = i - 1;
        numbers = j + 1;

        while(letters >= 1 && numbers < n + 1){
            if(B[letters--][numbers++]==1){
                return -1;
            }
        }
        return 0;
    }
    void printBoard(int** B, int n){
        int count = 1;
        printf("(");
        while(count < n + 1){
            if (count == n) {
                printf("%d)", B[count][0] );
            }
            else{
                printf("%d, ", B[count][0]);
            }
            count++;
        }
        printf("\n");
    }

    int findSolutions(int** B, int n, int i, char* mode) {
        int sol = 0;
        int x = strcmp(mode, "verbose");
        
        if (i == n+1) {
            if (x == 0) {
                printBoard(B, n);
            }
            return 1;
        }
        
        for (int numbers = 1; numbers < n + 1; numbers++) {
            if (checkforSpace(B, n, i, numbers)==0){
                placeQueen(B, n, i, numbers);
                sol += findSolutions(B, n, i + 1, mode);
                removeQueen(B, n, i, numbers);
            }
        }

        return sol;
    }
    int intCheck (char * s) {
        int retVal = 1;
        int i = 0;
        while(i < strlen(s)){
            if (!isdigit(s[i])){
                retVal = 0;
                break;
            }
            i++;
        }
        return retVal;
    }

int main(int argc, char* argv[]){
        int n;
        int x = strcmp(argv[1], "-v");
        char* verbose;
        int sol;


        if (argc< 1) {
            printf("Usage: Queens [-v] number \n");
            printf("Option: -v verbose output, print all solutions \n");
        } 
        else {
            while (true) {
                    if (argc == 3) {
                        if (x == 0) {
                            verbose = "verbose";
                        } else {
                            printf("Usage: Queens [-v] number \n");
                            printf("Option: -v verbose output, print all solutions \n");
                            break;
                        }
                        if(!intCheck(argv[2])){
                            printf("Usage: Queens [-v] number \n");
                            printf("Option: -v verbose output, print all solutions \n");
                            break;
                        }
                        n = atoi(argv[2]);
                    } 
                    else if(argc == 2){
                        if(!intCheck(argv[1])){
                            printf("Usage: Queens [-v] number \n");
                            printf("Option: -v verbose output, print all solutions \n");
                            break;
                        }
                        n = atoi(argv[1]);
                    }
                    else{
                        printf("Usage: Queens [-v] number \n");
                        printf("Option: -v verbose output, print all solutions \n");
                        break;
                    }

                      int **B = calloc((n+1), sizeof(int*));
                      for (int i=0; i<=n; i++) {
                          B[i] = (int*)calloc((n+1), sizeof(int));
                        for (int j=0; j<=n; j++) {
                             B[i][j] = 0;
                        }
                    }
                    sol = findSolutions(B, n, 1, verbose);
                    printf("%d-Queens has %d solutions", n, sol);
                    for(int i = 0; i <=n; i++){
                        free(B[i]);
                        }
                    free(B);
                    break;
            }
        }
    }

