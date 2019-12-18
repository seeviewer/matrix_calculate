#include <stdio.h>
#include "../include/mixo_image_linear_cal.h"

int main(int argc, const char **argv) 
{
    TYPE a[5][3] = { { 12, -51, 33 }, { 6, 167, 21 }, { -4, 24, 87 } ,{23, 14, 17},{21, 35, 41} };

    matrix *A = create_matrix_from_array(5,3,(TYPE**)a);
    matrix *Q = create_matrix(5,5);
    print_matrix(Q);
    matrix *R = create_matrix(5,3);
    print_matrix(R);
    
    mixo_QR_decompose(A,Q,R);

    print_matrix(A);
    print_matrix(Q);
    print_matrix(R);

    TYPE b[3][3] = { { 12, -51, 33 }, { 6, 167, 21 }, { -4, 24, 87 } };
    matrix* B = create_matrix_from_array(3, 3, (TYPE**)b);

    printf("matrix det\n");
    matrix_deter(B, B->cols);
    print_matrix(B);
    
    matrix* b_invers = create_matrix(B->rows, B->cols);
    printf("b before inverse\n");
    print_matrix(b_invers);
    
    matrix_inverse(B, b_invers);
    printf("b after inverse\n");
    print_matrix(b_invers);

    return 0;

}