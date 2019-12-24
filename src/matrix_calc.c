#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "matrix_calc.h"

/* Creates a matrix_t and returns a pointer to the struct */
matrix_t* create_matrix_2d(int rows, int cols) {

    /* Allocate memory for the matrix struct */
     matrix_t* matrix = malloc(sizeof( matrix_t));
    if (matrix != NULL)
    {
        matrix->rows = rows;
        matrix->cols = cols;

        /* Allocate enough memory for all the rows in the first matrix */
        matrix->array = calloc(rows, sizeof(TYPE*));
        if (matrix->array != NULL)
        {
            /* Enough memory for all the columns */
            for (int i = 0; i < rows; i++) {
                matrix->array[i] = calloc(cols, sizeof(TYPE));
            }
        }
    }

    return matrix;
}

/* Creates a matrix from a stack based array and returns a pointer to the struct */
 matrix_t*  create_matrix_2d_from_array(int rows, int cols, TYPE* m)
{
    /* Allocate memory for the  matrix_t struct */
     matrix_t* matrix = ( matrix_t*)malloc(sizeof( matrix_t));
    if (matrix == NULL)
    {
        printf("allocate memery for array failed!\n");
        return NULL;
    }
    else
    {
        matrix->rows = rows;
        matrix->cols = cols;

        /* Allocate memory for the matrix */
        matrix->array = (TYPE**)malloc(sizeof(TYPE*) * rows);
        if (matrix->array != NULL)
        {
            /* Allocate memory for each array inside the matrix */
            for (int i = 0; i < rows; i++)
            {
                matrix->array[i] = (TYPE*)malloc(sizeof(TYPE) * cols);
            }
            /* Populate the matrix with m's values */
            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                {
                     //*(*(array->array+row*cols)+col) = *(m + row * cols + col);
                    matrix->array[row][col] = *(m + row * cols + col);
                }
            }
        }
    }
    return matrix;
}


/* free the matrix memery */
void  free_matrix( matrix_t* m)
{
    if (m != NULL)
    {
        if (m->array != NULL )
        {
            for (int i = 0; i < m->rows; i++)
            {
                free(m->array[i]);
            }
            free(m->array);
        }
        free(m);
    }
}

/*copy a region matrix value to a new matrix*/
void  matrix_copy_block( matrix_t* msrc, point_t begin, point_t end,  matrix_t* mdst)
{
    int i, j;
    int tempx;
    int tempy;
    for (i = 0, tempx = begin.x; i <= (end.x - begin.x); i++, tempx++)
    {
        for (j = 0, tempy = begin.y; j <= (end.y - begin.y); j++, tempy++)
        {
            mdst->array[i][j] = msrc->array[tempx][tempy];
        }

    }
}

/* Copies a matrix column from msrc at column col1 to mdst at column col2 */
void  matrix_copy_column( matrix_t* msrc, int col1,  matrix_t* mdst, int col2)
{
    for (int i = 0; i < msrc->rows; i++) {
        mdst->array[i][col2] = msrc->array[i][col1];
    }
}

/* Subtracts m2's column c2 from m1's column c1 */
 matrix_t*  matrix_column_subtract( matrix_t* m1, int c1,  matrix_t* m2, int c2)
{
    for (int i = 0; i < m1->rows; i++) {
        m1->array[i][c1] -= m2->array[i][c2];
    }
    return m1;
}

/* Returns the length of the vector column in m */
double  vector_length( matrix_t* m, int column)
{
    double length = 0;
    for (int row = 0; row < m->rows; row++) {
        length += m->array[row][column] * m->array[row][column];
    }
    return sqrt(length);
}

/* Divides the matrix column c in m by k */
 matrix_t*  matrix_column_divide( matrix_t* m, int c, TYPE k)
{
    for (int i = 0; i < m->rows; i++) {
        m->array[i][c] /= k;
    }
    return m;
}

/* Multiplies the matrix column c in m by k */
 matrix_t*  matrix_column_multiply( matrix_t* m, int c, TYPE k)
{
    for (int i = 0; i < m->rows; i++) {
        m->array[i][c] *= k;
    }
    return m;
}

 matrix_t*  matrix_multiply( matrix_t* m,  matrix_t* n)
{
    int i, j, k;
     matrix_t* reslt =  create_matrix_2d(m->rows, n->cols);

    if (m->cols != n->rows)
    {
        printf("left matrix's cols not equal to right matrix's rows \n matrix can not multiply!");
         free_matrix(reslt);
        return NULL;
    }
    else
    {
        for (i = 0; i < m->rows; i++)
        {
            for (j = 0; j < m->cols; j++)
            {
                for (k = 0; k < n->cols; k++)
                {
                    reslt->array[i][k] += m->array[i][j] * n->array[j][k];
                }
            }
        }
        return reslt;
    }
}

 matrix_t*  matrix_transpose( matrix_t* m)
{
    int i, j;
     matrix_t* dst_trans;
    dst_trans =  create_matrix_2d(m->cols, m->rows);

    for (i = 0; i < m->rows; i++)
    {
        for (j = 0; j < m->cols; j++)
        {
            dst_trans->array[j][i] = m->array[i][j];
        }
    }

    return dst_trans;
}

/* cofactor matrix: calc new matrix D without row p and column q
tam represent rows or cols of matrix A*/
void  matrix_cofactor( matrix_t* A,  matrix_t* D, int p, int q, int tam)
{
    int i, j, k = 0, w = 0;

    for (i = 0; i < tam; ++i)
    {
        for (j = 0; j < tam; ++j)
        {
            if (i != p && j != q)
            {
                D->array[k][w++] = A->array[i][j];
                if (w == (tam - 1))
                {
                    w = 0;
                    k++;
                }
            }
        }
    }
}

/* calc  matrix_t Determinant*/
double  matrix_deter( matrix_t* A, int tam)
{
    int i, signo = 1;
    double determ = 0.0;
     matrix_t* D = NULL;

    if (A->rows == A->cols)
    {
        if (tam == 1)
            return A->array[0][0];
        if (tam == 2)
            return (A->array[0][0] * A->array[1][1] - A->array[0][1] * A->array[1][0]);
        else
        {
            D =  create_matrix_2d(A->rows, A->cols);
            for (i = 0; i < tam; ++i)
            {
                 matrix_cofactor(A, D, 0, i, tam);
                determ += signo * A->array[0][i] *  matrix_deter(D, (tam - 1));
                signo = -signo;
            }
             free_matrix(D);
        }
        return determ;
    }
    else
    {
        printf("determinate invalid!");
        return -1;
    }
}

/* calc adjugate matrix*/
void  matrix_adjugate( matrix_t* A,  matrix_t* Adj, int tam)
{
    int i, j, signo2 = 1;
     matrix_t* temp_m;

    if (A != NULL)
    {
        temp_m =  create_matrix_2d(A->rows, A->cols);
    }

    if (tam == 1)
        Adj->array[0][0] = 1;

    for (i = 0; i < tam; ++i)
    {
        for (j = 0; j < tam; ++j)
        {
            //E =  create_matrix_2d(A->rows, A->cols);
             matrix_cofactor(A, temp_m, i, j, tam);
            signo2 = ((i + j) % 2 == 0) ? 1 : -1;
            Adj->array[j][i] = (signo2) * ( matrix_deter(temp_m, (tam - 1)));
        }
    }
     free_matrix(temp_m);
}

/*calcuate inverse matrix */
void  matrix_inverse( matrix_t* m,  matrix_t* mdst)
{
    double determ = 0.0;
    int i, j;
     matrix_t* adj;

    if (m->rows != m->cols)
    {
        printf("inverse matrix must be a square matrix!\n");
    }
    else
    {
        determ =  matrix_deter(m, m->rows);
        if (determ == 0)
            printf("the matrix not exists inversa\n");
        else
        {
            adj =  create_matrix_2d(m->rows, m->cols);
             matrix_adjugate(m, adj, m->rows);
            for (i = 0; i < m->rows; ++i)
                for (j = 0; j < m->rows; ++j)
                    mdst->array[i][j] = adj->array[i][j] / determ;
            printf("\nthe matriz inversa as: \n");
            // print_matrix(mdst);
             free_matrix(adj);
        }
    }
}

/* Debugging only */
void  print_matrix( matrix_t* m) {
    for (int row = 0; row < m->rows; row++) {
        printf("[");
        for (int col = 0; col < m->cols - 1; col++) {
            printf("%7.6f, ", m->array[row][col]);
        }
        printf("%7.6f", m->array[row][m->cols - 1]);
        printf("]\n");
    }
    printf("\n");
}

/* Decomposes the matrix A into QR */
void QR_decompose(matrix_t* A, matrix_t* Q, matrix_t* R) {

    /* Using the Gram-Schmidt process */
    /* Temporary vector T and S used in calculations */
    matrix_t* T = create_matrix_2d(A->rows, 1);
    matrix_t* S = create_matrix_2d(A->rows, 1);

    for (int i = 0; i < A->cols; i++) {
        //Qi = Ui
        matrix_copy_column(A, i, Q, i);

        for (int j = 0; j < i; j++) {

            //r[j,i] = Qj^T * Ui
            matrix_copy_column(Q, j, T, 0);
            matrix_copy_column(A, i, S, 0);
            TYPE r = 0;
            for (int k = 0; k < A->rows; k++) {
                r += T->array[k][0] * S->array[k][0];
            }

            R->array[j][i] = r;
            matrix_column_subtract(Q, i, matrix_column_multiply(T, 0, r), 0);
        }

        //r[i,i] = ||Qi||
        R->array[i][i] = vector_length(Q, i);
        //Qi = Qi/r[i,i]
        matrix_column_divide(Q, i, R->array[i][i]);
    }

    free_matrix(T);
    free_matrix(S);
}
