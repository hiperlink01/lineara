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

int** Create_Matrix(int lines, int collumns){

    //allocating memory for main array (lines), then for each array inside main array (collumns)

    int** matrix = (int**)malloc(sizeof(int*) * lines);
    
    for (int i = 0; i < lines; i++){
    
        matrix[i] = (int*)malloc(sizeof(int) * collumns);
    
    }

    return matrix;

}

int** Create_Aux_Matrix(int** original_matrix){

    int** aux_matrix = Create_Matrix(3, 3);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            aux_matrix[i][j] = original_matrix[i][j];

        }
    }

    return aux_matrix;

}

void Free_Matrix(int** matrix){

    //freeing memory from arrays of each i, then from the main array

    for (int i = 0; i < 3; i++){ 
    
        free(matrix[i]);
    
    }

    free(matrix);

}

int** Sum_Subtract_Matrices(int** L_matrix, int sum_or_subtract, int** R_matrix){
    
  
    int** L_matrix_aux = Create_Aux_Matrix(L_matrix);
    int** R_matrix_aux = Create_Aux_Matrix(R_matrix);

    int** result_matrix = Create_Matrix(3, 3);

    if(sum_or_subtract >= 0){

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++){

                result_matrix[i][j] = L_matrix_aux[i][j] + R_matrix_aux[i][j];

            }
        }
    }

    else if(sum_or_subtract < 0) {

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++){

                result_matrix[i][j] = L_matrix_aux[i][j] - R_matrix_aux[i][j];

            }
        }
    }

    Free_Matrix(L_matrix_aux);
    Free_Matrix(R_matrix_aux);

    return result_matrix;

}

int** Multiply_Matrices(int** L_matrix, int** R_matrix){

    int** L_matrix_aux = Create_Aux_Matrix(L_matrix);
    int** R_matrix_aux = Create_Aux_Matrix(R_matrix);

    int** result_matrix = Create_Matrix(3, 3);


    for (
        int i_of_L = 0;
        i_of_L < 3;
        i_of_L++
    ){
        for (
            int j_of_R = 0;
            j_of_R < 3;
            j_of_R++
        ){
          
          int ij_of_result_matrix = 0;
    
            for (
                int iterator = 0;
                iterator < 3;
                iterator++
            ){
    
                ij_of_result_matrix += L_matrix_aux[i_of_L][iterator] * R_matrix_aux[iterator][j_of_R];
    
            }
            
            result_matrix[i_of_L][j_of_R] = ij_of_result_matrix;

        }
    }

    Free_Matrix(L_matrix_aux);
    Free_Matrix(R_matrix_aux);

    return result_matrix;

}

int** Commute_Anticommute_Matrices(int** L_matrix, int commute_or_anticommute, int** R_matrix){

    int** L_matrix_aux = Create_Aux_Matrix(L_matrix);
    int** R_matrix_aux = Create_Aux_Matrix(R_matrix);

    int** result_matrix = Create_Matrix(3, 3);

    //commutation is arbitrarily represented as < 0 (negatives) because [A, B] = AB - BA

    if(commute_or_anticommute < 0){

        result_matrix =
        Sum_Subtract_Matrices(
            Multiply_Matrices(L_matrix_aux, R_matrix_aux),
            -1,
            Multiply_Matrices(R_matrix_aux, L_matrix_aux)
        );

    }

    //anticommutation is arbitrarily represented as >= 0 (non-negatives) because {A, B} = AB + BA

    else if(commute_or_anticommute >= 0){

        result_matrix = 
        Sum_Subtract_Matrices(
            Multiply_Matrices(L_matrix_aux, R_matrix_aux),
            +1,
            Multiply_Matrices(R_matrix_aux, L_matrix_aux)
        );

    }

    Free_Matrix(L_matrix_aux);
    Free_Matrix(R_matrix_aux);

    return result_matrix;

}

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