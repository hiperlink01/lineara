#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/mtxmem.h"
#include "../include/mtxmath.h"

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