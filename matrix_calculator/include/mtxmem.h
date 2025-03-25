#ifndef MTXMEM_H
#define MTXMEM_H

int** Create_Matrix(int lines, int collumns);
int** Create_Aux_Matrix(int** original_matrix, int lines, int collumns);
void Free_Matrix(int** matrix, int lines);

#endif