#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(void)
{
    printf("===== Test START ===== \n");
    Mat *mat = NULL;
    Matrix_Init(&mat,3,3);
    mat->data[0][0] = 2;
    mat->data[0][1] = 1;
    mat->data[0][2] = 2;
    mat->data[1][0] = 3;
    mat->data[1][1] = 2;
    mat->data[1][2] = 2;
    mat->data[2][0] = 1;
    mat->data[2][1] = 2;
    mat->data[2][2] = 3;
    printf("Original Matrix : \n\n");
    Matrix_Print(&mat);
    printf("======================\n");
    Mat* inv = NULL;
    Matrix_Inverse(&mat,&inv);
    printf("Inversed Matrix : \n\n");
    Matrix_Print(&inv);

    Matrix_Free(&mat);
    Matrix_Free(&inv);
    printf("===== Test  END  ===== \n");
    return 0;
}