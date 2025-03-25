#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/mtxmem.h"
#include "../include/mtxmath.h"

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