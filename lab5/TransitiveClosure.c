/*

Author  : E/16/086
compile : gcc TransitiveClosure.c -o TransitiveClosure
run     : TransitiveClosure


*/

#include <stdio.h>
#define S 7

//Initially the matrix size has defined to 7x7
//print a Matrix
void printMatrix(int graph[S][S]){

    for (int i = 0 ; i < S ; i++){

        for ( int j = 0 ; j < S ; j++){
           printf("%d ",graph[i][j]);
        }
        printf("\n");
    }

}

//Calculate transitive closure using warshall's algorithm
void transitiveClosure(int graph[S][S]){

    int reachMatrix[S][S];

    //copying the current matrix to the Transitive closure
    for (int i = 0; i < S; i++)
        for ( int j = 0; j < S; j++)
            reachMatrix[i][j] = graph[i][j];

    for (int m = 0 ; m < S ; m++){
        for (int i = 0 ; i < S ; i++){
            for ( int j = 0 ; j < S ; j++){
                if(i==j){
                   reachMatrix[i][j] = 1; //diagonal elements are set to one
                }
                else{
                    //set reachMatrix[i][j] =1 if i to j has a directed path,0 otherwise.
                   reachMatrix[i][j] = (reachMatrix[i][m] && reachMatrix[m][j]) || reachMatrix[i][j];
                }
            }
        }
    }
    printf("Transitive closure for the given graph:\n");
    printMatrix(reachMatrix);
}



int main(){

int graph[S][S] = { {0, 1, 1, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 0},
                    {0, 0, 0, 0, 0, 1, 0},
                    {0, 1, 0, 0, 1, 0, 1},
                    {0, 0, 0, 0, 0, 0, 1},
                    {0, 0, 0, 1, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0, 0}
                   };
    printf("given graph:\n");
    printMatrix(graph);  //print given matrix
    transitiveClosure(graph); //get the trasitive closure




return 0;
}
