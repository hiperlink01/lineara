#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int How_Many_Lines(int** array){

    //to abstract away calculations of array size

    int size = sizeof(array) / sizeof(*array);
    
    return size;

}

int** Create_Matrix(int lines, int collumns){

    //allocating memory for main array (lines), then for each array inside main array (collumns)

    int** matrix = (int**)malloc(sizeof(int*) * lines);
    
    for (int i = 0; i < lines; i++){
    
        matrix[i] = (int*)malloc(sizeof(int) * collumns);
    
    }

    return matrix;

}

void Free_Matrix(int** matrix){

    //freeing memory from arrays of each line, then from the main array

    for (int i = 0; i < How_Many_Lines(matrix); i++){ 
    
        free(matrix[i]);
    
    }

    free(matrix);

}

int** Sum_Subtract_Matrices(int** L_matrix, int sum_or_subtract, int** R_matrix){

    int** result_matrix = Create_Matrix(3, 3);

    if(sum_or_subtract >= 0){

        for (int line = 0; line < 3; line++) {
        for (int collumn = 0; collumn < 3; collumn++){

                result_matrix[line][collumn] = L_matrix[line][collumn] + R_matrix[line][collumn];

            }
        }
    }

    else if(sum_or_subtract < 0) {

        for (int line = 0; line < 3; line++) {
        for (int collumn = 0; collumn < 3; collumn++){

                result_matrix[line][collumn] = L_matrix[line][collumn] - R_matrix[line][collumn];

            }
        }
    }

    Free_Matrix(L_matrix);
    Free_Matrix(R_matrix);

    return result_matrix;

}

int** Multiply_Matrices(int** L_matrix, int** R_matrix){

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
    
                ij_of_result_matrix += L_matrix[i_of_L][iterator] * R_matrix[iterator][j_of_R];
    
            }
            
            result_matrix[i_of_L][j_of_R] = ij_of_result_matrix;

        }
    
    }

    Free_Matrix(L_matrix);
    Free_Matrix(R_matrix);

    return result_matrix;

}

int** Commute_Anticommute_Matrices(int** L_matrix, int commute_or_anticommute, int** R_matrix){

    int** result_matrix = Create_Matrix(3, 3);

    //commutation is arbitrarily represented as < 0 because [A, B] = AB - BA

    if(commute_or_anticommute < 0){

        result_matrix =
        Sum_Subtract_Matrices(
            Multiply_Matrices(L_matrix, R_matrix),
            -1,
            Multiply_Matrices(R_matrix, L_matrix)
        );

    }

    //anticommutation is arbitrarily represented as >= 0 because {A, B} = AB + BA

    else if(commute_or_anticommute >= 0){

        result_matrix = 
        Sum_Subtract_Matrices(
            Multiply_Matrices(L_matrix, R_matrix),
            +1,
            Multiply_Matrices(R_matrix, L_matrix)
        );

    }

    Free_Matrix(L_matrix);
    Free_Matrix(R_matrix);

    return result_matrix;

}


int main(){

    /*
    Declaring matrices
    */

    int matrix_A[3][3], matrix_B[3][3];

    //Auxiliar matrices created for persistance of original data

    int** matrix_A_aux = Create_Matrix(3, 3);
    int** matrix_B_aux = Create_Matrix(3, 3);

    //User inserts data in matrices A and B

    printf("For matrix A:\n\n");

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            printf("Insert number in position a-%d-%d: ", i+1, j+1);
            scanf("%d", &matrix_A[i][j]);
            matrix_A_aux[i][j] = matrix_A[i][j];
        
        }
    }

    printf("\nFor matrix B:\n\n");

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            printf("Insert number in position b-%d-%d: ", i+1, j+1);
            scanf("%d", &matrix_B[i][j]);
            matrix_B_aux[i][j] = matrix_B[i][j];
        
        }
    }

    int select_op = 0;
    int** result_matrix = NULL;

    printf("\nSelect operation:\n\n[1] A+B\n[2] AxB\n[3] BxA\n[4] [A,B]\n([0] to close program)\n\n");
    scanf("%d", &select_op);

    switch (select_op) {
        
        case 0: return 0;
        
        case 1: 
            result_matrix = Sum_Subtract_Matrices(matrix_A_aux, +1, matrix_B_aux);
            break;
        
        case 2:
            result_matrix = Multiply_Matrices(matrix_A_aux, matrix_B_aux);
            break;
        
        case 3:
            result_matrix = Multiply_Matrices(matrix_B_aux, matrix_A_aux);
            break;

        case 4:   
            result_matrix = Commute_Anticommute_Matrices(matrix_A_aux, -1, matrix_B_aux);
            break;
        
        default: return 0;

    }

    printf("\n");

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            printf("%d ", result_matrix[i][j]);
        
        }
        printf("\n");
    }

    return 0;
}