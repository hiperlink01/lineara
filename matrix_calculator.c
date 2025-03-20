/*  

    The first-level pointer contains elements on a line, represents collumns;
    The second-level pointer contains lines, represents lines.
    "n-level" refers to how many layers of pointers;
    First-level means one layer of pointer, i.e. one pointer, i.e. it points to an actual data;
    Second-level means two layers of pointer, i.e. two pointers, i.e. it points to only one pointer;


*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int Size_of_Line(int** array){

    //to abstract away calculations of array size

    int size = sizeof(array) / sizeof(*array);
    
    return size;

}

int Size_of_Collumn(int*array){

    //to abstract away calculations of array size

    int size = sizeof(array) / sizeof(*array);
    
    return size;

}
/*
int** Sum_Matrices(int** L_matrix, int** matrix_B){

    int** result_matrix;

    {
        int count_L_lines = Size_of_Line(L_matrix);
        int count_L_collumns = Size_of_Collumn(*L_matrix);
        int count_R_lines = Size_of_Line(matrix_B);
        int count_R_collumns = Size_of_Collumn(*matrix_B);

        if (count_L_lines != count_R_lines || count_L_collumns != count_R_collumns){
        
            return result_matrix;
        
        }

    }

    int count_lines = Size_of_Lines(L_matrix);
    int count_collumns = Size_of_Collumn(*L_matrix);

    for (int line = 0; line < count_lines; line++) {

        for (int collumn = 0; collumn<count_collumns; collumn++){

            result_matrix[line][collumn] = L_matrix[line][collumn] + matrix_B[line][collumn];

        }
    
    }

    return result_matrix

}

int** Multiply_Matrices(int** L_matrix, int** matrix_B, int** result_matrix){

    int count_L_lines = Size_of_Line(L_matrix);      
    int count_R_collumns = Size_of_Collumn(*matrix_B); //the second-level pointer contains lines, represents lines.

    if (count_L_lines!=count_R_collumns){ return result_matrix; }

    

    for (
        int i_of_A = 0;
        i_of_A<2;
        i_of_A++
    ){
        for (
            int j_of_B = 0;
            j_of_B < qtd_colunas;
            j_of_B++
        ){
          
          int ij_result = 0;
    
            for (
                int iterator = 0;
                iterator<2;
                iterator++
            ){
    
                ij_result += A[i_of_A][iterator] * B[iterator][j_of_B];
    
            }
    
        }
    
    }

}
*/

int main(){

    /*
    Declaring pointer of pointers that will serve as matrix;
    Declaring int variables that will hold quantity of lines and collumns;
    For matrix A and B
    */

    int** matrix_A;
    int A_line_qtt, A_collumn_qtt;
    
    int**  matrix_B;
    int B_line_qtt, B_collumn_qtt;

    /*User inputs lines and collumns for A and B*/

    scanf("%d", &A_line_qtt);
    scanf("%d", &A_collumn_qtt);
    
    scanf("%d", &B_line_qtt);
    scanf("%d", &B_collumn_qtt);

    /*
    Allocatting memory for the pointer of pointers;
    i.e. creating array of pointers;
    for matrix A and B
    */

    matrix_A = (int**)malloc( sizeof(int*) * A_line_qtt );

    matrix_B = (int**)malloc( sizeof(int*) * B_line_qtt );

    /*
    Allocatting memory for each pointer inside the array of pointers;
    i.e. creating arrays inside the array;
    i.e. properly creating the matrix;
    for matrix A and B
    */
    
    for (int i=0; i<A_line_qtt; i++){
    
        matrix_A[i] = malloc(sizeof(int) * A_collumn_qtt);

    }

    
    for (int i=0; i<B_line_qtt; i++){
    
        matrix_B[i] = malloc(sizeof(int) * B_collumn_qtt);
    
    }

    //User inserts data in matrices A and B

    printf("For matrix A:\n\n");

    for (int i=0; i<A_line_qtt; i++){
        for (int j=0; j<A_collumn_qtt; j++){

            printf("Insert number in position a-%d-%d: ", i+1, j+1);
            scanf("%d", &matrix_A[i][j]);
        
        }
    }

    printf("\nFor matrix B:\n\n");

    for (int i=0; i<B_line_qtt; i++){
        for (int j=0; j<B_collumn_qtt; j++){

            printf("Insert number in position b-%d-%d: ", i+1, j+1);
            scanf("%d", &matrix_B[i][j]);
        
        }
    }

    return 0;
}