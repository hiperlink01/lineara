#ifndef MTXMATH_H
#define MTXMATH_H

int** Sum_Subtract_Matrices(
    int** L_matrix, 
    int sum_or_subtract, 
    int** R_matrix, 
    int lines, int collumns
);

int** Multiply_Matrices(
    int** L_matrix, int L_lines, int L_collumns,
    int** R_matrix, int R_lines, int R_collumns
);

int** Commute_Anticommute_Matrices(
    int** L_matrix, 
    int commute_or_anticommute, 
    int** R_matrix, 
    int lines_n_collumns
);

#endif