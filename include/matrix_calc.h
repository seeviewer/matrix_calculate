#ifndef MATRIX_CALC_H_
#define MATRIX_CALC_H_
#define TYPE float

typedef struct
{
  int x;
  int y;
}point_t;

typedef struct {
    int rows;       /* Number of rows */
    int cols;       /* Number of columns */
    TYPE** array;   /* Pointer to an array of type TYPE */
} matrix_t;

/* Creates a matrix and returns a pointer to the struct */
matrix_t* create_matrix_2d(int rows, int cols);

/* Creates a matrix from a stack based array and returns a pointer to the struct */
matrix_t* create_matrix_2d_from_array(int rows, int cols, TYPE* m);

/* free the matrix memery */
void free_matrix(matrix_t* m);

/*copy matrix block data to a new matrix*/
void matrix_copy_block(matrix_t* msrc, point_t start, point_t end, matrix_t* mdst);

/* Copies a matrix column from msrc at column col1 to mdst at column col2 */
void matrix_copy_column(matrix_t* msrc, int col1, matrix_t* mdst, int col2);

/* Subtracts m2's column c2 from m1's column c1 */
matrix_t* matrix_column_subtract(matrix_t* m1, int c1, matrix_t* m2, int c2);

/* Returns the length of the vector column in m */
double vector_length(matrix_t* m, int column);

/* Divides the matrix column c in m by k */
matrix_t* matrix_column_divide(matrix_t* m, int c, TYPE k);

/* Multiplies the matrix column c in m by k */
matrix_t* matrix_column_multiply(matrix_t* m, int c, TYPE k);

/* Multiplies the matrix*/
matrix_t* matrix_multiply(matrix_t* m, matrix_t* n);

/*matrix transpose*/
matrix_t* matrix_transpose(matrix_t* m);

/* cofactor matrix: calc new matrix D without row p and column q
tam represent rows or cols of matrix A*/
void matrix_cofactor(matrix_t* A, matrix_t* D, int p, int q, int tam);

/* calc matrix Determinant*/
double matrix_deter(matrix_t* A, int tam);

/* calc matrix adjugate */
void matrix_adjugate(matrix_t* A, matrix_t* Adj, int tam);

/*calcuate inverse matrix */
void matrix_inverse(matrix_t* m, matrix_t* mdst);

/*print matrix*/
void print_matrix(matrix_t* m);

void QR_decompose(matrix_t* A, matrix_t* Q, matrix_t* R);

#endif
