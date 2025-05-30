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
    Declaring matrices
    */

    int** matrix_A = Create_Matrix(3, 3);
    int** matrix_B = Create_Matrix(3, 3);
    int** result_matrix = NULL;

    //User inserts data in matrices A and B

    printf("For matrix A:\n\n");

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            printf("Insert number in position a-%d-%d: ", i+1, j+1);
            scanf("%d", &matrix_A[i][j]);
        
        }
    }

    printf("\n");

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            printf("%d ", matrix_A[i][j]);
        
        }
        printf("\n");
    }

    printf("\nFor matrix B:\n\n");

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            printf("Insert number in position b-%d-%d: ", i+1, j+1);
            scanf("%d", &matrix_B[i][j]);
            //matrix_B_aux[i][j] = matrix_B[i][j];
        
        }
    }

    printf("\n");

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            printf("%d ", matrix_B[i][j]);
        
        }
        printf("\n");
    }

    int select_op = 0;

    printf("\nSelect operation:\n\n[1] A+B\n[2] AxB\n[3] BxA\n[4] [A,B]\n([0] to close program)\n\n");
    scanf("%d", &select_op);

    switch (select_op) {
        
        case 0:
            Free_Matrix(matrix_A);
            Free_Matrix(matrix_B);
            return 0;
        
        case 1: 
            result_matrix = Sum_Subtract_Matrices(matrix_A, +1, matrix_B);
            break;
        
        case 2:
            result_matrix = Multiply_Matrices(matrix_A, matrix_B);
            break;
        
        case 3:
            result_matrix = Multiply_Matrices(matrix_B, matrix_A);
            break;

        case 4:   
            result_matrix = Commute_Anticommute_Matrices(matrix_A, -1, matrix_B);
            break;
        
        default: 
            Free_Matrix(matrix_A);
            Free_Matrix(matrix_B);
            return 0;

    }

    printf("\n");

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            printf("%d ", result_matrix[i][j]);
        
        }
        printf("\n");
    }

    Free_Matrix(matrix_A);
    Free_Matrix(matrix_B);

    return 0;
}