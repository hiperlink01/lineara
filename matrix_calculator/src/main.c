/*  

    The first-level pointer contains elements on a line, represents collumns;
    The second-level pointer contains lines, represents lines.
    "n-level" refers to how many layers of pointers;
    First-level means one layer of pointer, i.e. one pointer, i.e. it points to an actual data;
    Second-level means two layers of pointer, i.e. two pointers, i.e. it points to only one pointer;


*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/mtxmem.h"
#include "../include/mtxmath.h"

int main(){

    /*
    Declaring pointer of pointers that will serve as matrix;
    Declaring int variables that will hold quantity of lines and collumns;
    For matrix A and B
    */

    int** matrix_A;
    int A_lines, A_collumns;
    
    int**  matrix_B;
    int B_lines, B_collumns;

    /*User inputs lines and collumns for A and B*/

    scanf("%d", &A_lines);
    scanf("%d", &A_collumns);
    
    scanf("%d", &B_lines);
    scanf("%d", &B_collumns
    );

    /*
    Allocatting memory for matrix with Create_Matrix() function
    */

    matrix_A = Create_Matrix(A_lines, A_collumns);
    matrix_B = Create_Matrix(B_lines, B_collumns
    );

    //User inserts data in matrices A and B

    printf("For matrix A:\n\n");

    for (int i=0; i<A_lines; i++){
        for (int j=0; j<A_collumns; j++){

            printf("Insert number in position a-%d-%d: ", i+1, j+1);
            scanf("%d", &matrix_A[i][j]);
        
        }
    }

    for (int i=0; i<A_lines; i++){
        for (int j=0; j<A_collumns; j++){

            printf("[%d]", matrix_A[i][j]);
        
        }
        printf("\n");
    }

    printf("\nFor matrix B:\n\n");

    for (int i=0; i<B_lines; i++){
        for (int j=0; j<B_collumns
            ; j++){

            printf("Insert number in position b-%d-%d: ", i+1, j+1);
            scanf("%d", &matrix_B[i][j]);
        
        }
    }

    for (int i=0; i<B_lines; i++){
        for (int j=0; j<B_collumns; j++){

            printf("[%d]", matrix_B[i][j]);
        
        }
        printf("\n");
    }

    //Initiating operation section

    int** result_matrix = NULL;
    int result_matrix_lines, result_matrix_collumns;
    
    int aux_lines, aux_collumns, aux_lines_n_collumns;

    int select_op = 0;

    printf(
        "\nSelect operation:\n\n[1] A+B\n[2] A-B\n[3] AxB\n[4] BxA\n[5] [A,B]\n[6] [B,A]\n[7] {A,B}\n[8] {B,A}\n([0] to close program)\n\n"
    );
    
    scanf("%d", &select_op);

    switch (select_op) {
        
        case 0:
            Free_Matrix(matrix_A, A_lines);
            Free_Matrix(matrix_B, B_lines);
            return 0;
        
        case 1:

            aux_lines = A_lines;
            aux_collumns = B_collumns;
            
            result_matrix =
            
            Sum_Subtract_Matrices(
            
                matrix_A, 
                +1,
                matrix_B, 
            
                aux_lines, aux_collumns
            );
            
            result_matrix_lines = aux_lines;
            result_matrix_collumns = aux_collumns;
            
            break;
        
        case 2:

            aux_lines = A_lines;
            aux_collumns = B_collumns;

            result_matrix =
            Sum_Subtract_Matrices(
            
                matrix_A, 
                -1,
                matrix_B, 
            
                aux_lines, aux_collumns
            );

            result_matrix_lines = aux_lines;
            result_matrix_collumns = aux_collumns;
            
            break;

        case 3:
            result_matrix = Multiply_Matrices(
                
                matrix_A, A_lines, A_collumns,
//              x
                matrix_B, B_lines, B_collumns

            
            );

            result_matrix_lines = A_lines;
            result_matrix_collumns = B_collumns;

            break;
        
        case 4:
            result_matrix = Multiply_Matrices(
                
                matrix_B, B_lines, B_collumns
                ,
//              x
                matrix_A, A_lines, A_collumns
            );

            result_matrix_lines = B_lines;
            result_matrix_collumns = A_collumns;

            break;

        case 5:   

            aux_lines_n_collumns = A_lines;
            
            result_matrix = Commute_Anticommute_Matrices(
                
                matrix_A,
                -1,
                matrix_B,

                aux_lines_n_collumns
            );

            result_matrix_lines = aux_lines_n_collumns;
            result_matrix_collumns = aux_lines_n_collumns;
            
            break;
        
        case 6:   

            aux_lines_n_collumns = A_lines;
            
            result_matrix = Commute_Anticommute_Matrices(
                
                matrix_B,
                -1,
                matrix_A,

                aux_lines_n_collumns
            );

            result_matrix_lines = aux_lines_n_collumns;
            result_matrix_collumns = aux_lines_n_collumns;

            break;

        case 7:   

            aux_lines_n_collumns = A_lines;
            
            result_matrix = Commute_Anticommute_Matrices(
                
                matrix_A,
                +1,
                matrix_B,

                aux_lines_n_collumns
            );

            result_matrix_lines = aux_lines_n_collumns;
            result_matrix_collumns = aux_lines_n_collumns;
            
            break;

        case 8:   

            aux_lines_n_collumns = A_lines;
            
            result_matrix = Commute_Anticommute_Matrices(
                
                matrix_B,
                +1,
                matrix_A,

                aux_lines_n_collumns
            );

            break;
        
        default: 
            Free_Matrix(matrix_A, A_lines);
            Free_Matrix(matrix_B, B_lines);
            return 0;

    }

    printf("\n");

    for (int i=0; i<result_matrix_lines; i++){
        for (int j=0; j<result_matrix_collumns; j++){

            printf("[%d]", result_matrix[i][j]);
        
        }
        printf("\n");
    }

    printf("\n");

    Free_Matrix(matrix_A, A_lines);
    Free_Matrix(matrix_B, B_lines);

    return 0;
}