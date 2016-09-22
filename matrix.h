/******************************************************************
Matrix and basic matrix operations
based on the lessons of matrix by Alexis Gryson and Alexander Gewirtz at IFCEN, SYSU.
******************************************************************/

#ifndef MAT__
#define MAT__

typedef struct{
	float **mat;
	int m, n;	
	} matrix;
	
/* Basic initialization */
matrix* mat_init(int m, int n);

/* Initialization into zero matrix */
matrix* mat_zero(int m, int n);

/* Matrix destruction */
void mat_destroy(matrix *T);

/* Matrix product c = a * b, return 0 if success */
matrix* mat_product(matrix *a, matrix *b);

/* Print a matrix */
void mat_print(matrix *a);

/* Swap line i and line j in matrix a */
void mat_line_swap(matrix *a, int i, int j);

/* multiply line i by ll in matrix a */
void mat_line_mult(matrix *a, int i, float lb);

/* Line substraction: line i = line i - line j * ll in matrix a */
void mat_line_subs(matrix *a, int i, int j, float lb);

/* Calculate the rank of matrix a */
int mat_rank(matrix *a);

/* Copy matrix a to matrix b */
matrix* mat_copy(matrix *a);

/* Matrix transposition: b = a^T, a read only */
matrix* mat_transpos(matrix *a);

/* Calculate a matrix's reverse with basic operations */
matrix* mat_reverse(matrix *a);

/* Calculate the determinant of a square matrix. */
float mat_det(matrix *a);



#endif
