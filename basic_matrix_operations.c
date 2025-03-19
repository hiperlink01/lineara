#include <stdio.h>
#include <math.h>

int Size_of_Array(int*array){

    return int size = sizeof(array) / sizeof(*array);

}

int** Multiply_Matrices(int**l_side_matrix, int**r_side_matrix, int**result_matrix){

    int count_l_lines = Size_of_Array(l_side_matrix);     //The first-level pointer contains elements on a line, represents collumns; 
    int count_r_collumns = Size_of_Array(*r_side_matrix); //the second-level pointer contains lines, represents lines.

    if (count_l_lines!=count_r_collumns){ return result_matrix; }

    

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


int main(){



    return 0;
}