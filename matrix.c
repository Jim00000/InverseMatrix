#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

void Matrix_Init(Mat** matrix,const size_t row,const size_t col)
{
    (*matrix) = (Mat*)malloc(sizeof(Mat));
    Mat* m_p = (*matrix);
    m_p->row = row;
    m_p->col = col;
    m_p->data = (double**)calloc(row,sizeof(double*));
    for(size_t i=0;i<row;i++)
        m_p->data[i] = (double*)calloc(col,sizeof(double));
}

void Matrix_Init_Identity(Mat** matrix,const size_t size)
{
    Matrix_Init(matrix,size,size);
    for(size_t i = 0; i < size ; i++ ){
        (*matrix)->data[i][i] = 1.0;
    }
}

void Matrix_Copy(Mat** src,Mat** dst)
{
    Mat* src_p = (*src);
    Mat* dst_p = (*dst);

    ///TODO: Check validation
    for(size_t i=0;i<src_p->row;i++)
        for(size_t j=0;j<src_p->col;j++)
            dst_p->data[i][j] = src_p->data[i][j];
}

void Matrix_Print(Mat** matrix)
{
    Mat* m_p = (*matrix);
    if(m_p == NULL || matrix == NULL){
        fprintf(stderr,"Matrix pointer is NULL \n");
        return;
    }

    size_t row = m_p->row;
    size_t col = m_p->col;
    for(size_t r=0;r<row;r++){
        printf("[");
        for(size_t c=0;c<col;c++){
            printf("%05.2lf,",m_p->data[r][c]);
        }
        printf("\b]\n");
    }


}

void Matrix_Free(Mat** matrix)
{
    if(matrix != NULL && *matrix != NULL){
        Mat* m_p = (*matrix);
        if(m_p->data != NULL){
            for(size_t i=0;i<m_p->row;i++){
                free(m_p->data[i]);
                m_p->data[i] = NULL;
            }
            m_p->data = NULL;
        }

        free(*matrix);
        *matrix = NULL;
    }
}

void Matrix_Minor(Mat** src,Mat** dst,size_t row,size_t col)
{
    size_t size = (*src)->row;
    Matrix_Init(dst,size - 1,size - 1);

    for(size_t r = 0,dr = 0;r < size;r++){
        if(r == row) continue;
        for(size_t c = 0,dc = 0;c < size;c++){
            if(c == col) continue;
            (*dst)->data[dr][dc] = (*src)->data[r][c];
            dc++;
        }
        dr++;
    }
}

const double Matrix_Cofactor(Mat** mat,size_t row,size_t col)
{
    double sign = ((row + col) & 0x1 == 0x1) ? -1.0 : 1.0;
    Mat* minor = NULL;
    Matrix_Minor(mat,&minor,col,row);
    const double det = Matrix_Determinant(&minor);
    Matrix_Free(&minor);
    return sign * det;
}

void Matrix_Inverse(Mat** src,Mat** dst)
{
    size_t size = (*src)->row;
    Matrix_Init(dst,size,size);
    
    for(size_t r = 0; r < size; r++){
        for(size_t c = 0; c < size; c++){
            const double cofactor = Matrix_Cofactor(src,r,c);
            const double det = Matrix_Determinant(src);
            (*dst)->data[r][c] = cofactor / det;
        }
    }
}

void Matrix_LU_Decomposition(Mat** matrix,Mat** lower,Mat** upper)
{
    size_t size = (*matrix)->row;
    Matrix_Init_Identity(lower,size);
    Matrix_Init(upper,size,size);
    Matrix_Copy(matrix,upper);
    Mat* l_p = (*lower);
    Mat* u_p = (*upper);
    
    for(size_t i = 0 ; i < size - 1 ; i++){
        double pivot = u_p->data[i][i];
        for(size_t j = i + 1 ; j < size ; j++){
            l_p->data[j][i] = u_p->data[j][i] / pivot;
            for(size_t k = 0 ; k < size ; k++){
                u_p->data[j][k] -= (u_p->data[i][k] * l_p->data[j][i]); 
            }
        }
    }
}

const double Matrix_Determinant(Mat** matrix)
{
    double det = 1.0;
    size_t size = (*matrix)->row;
    Mat *L = NULL,*R = NULL;
    Matrix_LU_Decomposition(matrix,&L,&R);
    
    for(size_t t = 0; t < size;t++)
        det *= (L->data[t][t] * R->data[t][t]);

    Matrix_Free(&L);
    Matrix_Free(&R);
    return det;
}
