#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Matrix{
    size_t row,col;
    double **data;
};

typedef struct Matrix Mat;

void Matrix_Init(Mat** matrix,const size_t row,const size_t col);
void Matrix_Init_Identity(Mat** matrix,const size_t size);
void Matrix_Copy(Mat** src,Mat** dst);
void Matrix_Print(Mat** matrix);
void Matrix_Free(Mat** matrix);

void Matrix_Minor(Mat** src,Mat** dst,size_t row,size_t col);
const double Matrix_Cofactor(Mat** mat,size_t row,size_t col);
void Matrix_Inverse(Mat** src,Mat** dst);

void Matrix_LU_Decomposition(Mat** matrix,Mat** lower,Mat** upper);
const double Matrix_Determinant(Mat** matrix);

#ifdef __cplusplus
}
#endif

#endif