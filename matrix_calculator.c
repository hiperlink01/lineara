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

int** Create_Aux_Matrix(int** original_matrix, int lines, int collumns){

    int** aux_matrix = Create_Matrix(lines, collumns);
    
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < collumns; j++) {
            
            aux_matrix[i][j] = original_matrix[i][j];

        }
    }

    return aux_matrix;

}

void Free_Matrix(int** matrix, int lines){

    //freeing memory from arrays of each i, then from the main array

    for (int i = 0; i < lines; i++){ 
    
        free(matrix[i]);
    
    }

    free(matrix);

}

int** Sum_Subtract_Matrices(int** L_matrix, int sum_or_subtract, int** R_matrix, int lines, int collumns){
    
    int** L_matrix_aux = Create_Aux_Matrix(L_matrix, lines, collumns);
    int** R_matrix_aux = Create_Aux_Matrix(R_matrix, lines, collumns);

    int** result_matrix = Create_Matrix(lines, collumns);

    if(sum_or_subtract >= 0){

        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < collumns; j++){

                result_matrix[i][j] = L_matrix_aux[i][j] + R_matrix_aux[i][j];

            }
        }
    }

    else if(sum_or_subtract < 0) {

        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < collumns; j++){

                result_matrix[i][j] = L_matrix_aux[i][j] - R_matrix_aux[i][j];

            }
        }
    }

    Free_Matrix(L_matrix_aux, lines);
    Free_Matrix(R_matrix_aux, lines);

    return result_matrix;

}

int** Multiply_Matrices(int** L_matrix, int L_lines, int L_collumns, int** R_matrix, int R_lines, int R_collumns){

    int** L_matrix_aux = Create_Aux_Matrix(L_matrix, L_lines, L_collumns);
    int** R_matrix_aux = Create_Aux_Matrix(R_matrix, R_lines, R_collumns);

    int** result_matrix = Create_Matrix(L_lines, R_collumns);


    for (
        int i_of_L = 0;
        i_of_L < L_lines;
        i_of_L++
    ){
        for (
            int j_of_R = 0;
            j_of_R < R_collumns;
            j_of_R++
        ){
          
          int ij_of_result_matrix = 0;
    
            for (
                int iterator = 0;
                iterator < L_collumns;
                iterator++
            ){
    
                ij_of_result_matrix += L_matrix_aux[i_of_L][iterator] * R_matrix_aux[iterator][j_of_R];
    
            }
            
            result_matrix[i_of_L][j_of_R] = ij_of_result_matrix;

        }
    }

    Free_Matrix(L_matrix_aux, L_lines);
    Free_Matrix(R_matrix_aux, R_lines);

    return result_matrix;

}

int** Commute_Anticommute_Matrices(int** L_matrix, int commute_or_anticommute, int** R_matrix, int lines_n_collumns){

    int** L_matrix_aux = Create_Aux_Matrix(L_matrix, lines_n_collumns, lines_n_collumns);
    int** R_matrix_aux = Create_Aux_Matrix(R_matrix, lines_n_collumns, lines_n_collumns);

    int** result_matrix = Create_Matrix(3, 3);

    //commutation is arbitrarily represented as < 0 (negatives) because [A, B] = AB - BA

    if(commute_or_anticommute < 0){

        result_matrix =

        Sum_Subtract_Matrices(

            Multiply_Matrices(
                L_matrix_aux, lines_n_collumns, lines_n_collumns,
                R_matrix_aux, lines_n_collumns, lines_n_collumns
            ),

            -1,

            Multiply_Matrices(
                R_matrix_aux, lines_n_collumns, lines_n_collumns,
                L_matrix_aux, lines_n_collumns, lines_n_collumns
            ),

            lines_n_collumns, lines_n_collumns
        
        );

    }

    //anticommutation is arbitrarily represented as >= 0 (non-negatives) because {A, B} = AB + BA

    else if(commute_or_anticommute >= 0){

        Sum_Subtract_Matrices(

            Multiply_Matrices(
                L_matrix_aux, lines_n_collumns, lines_n_collumns,
                R_matrix_aux, lines_n_collumns, lines_n_collumns
            ),

            +1,

            Multiply_Matrices(
                R_matrix_aux, lines_n_collumns, lines_n_collumns,
                L_matrix_aux, lines_n_collumns, lines_n_collumns
            ),

            lines_n_collumns, lines_n_collumns
        
        );

    }

    Free_Matrix(L_matrix_aux, lines_n_collumns);
    Free_Matrix(R_matrix_aux, lines_n_collumns);

    return result_matrix;

}

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

    int select_op = 0;
    int** result_matrix = NULL;
    int result_matrix_lines, result_matrix_collumns;
    int aux_lines, aux_collumns, aux_lines_n_collumns;

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