#include<stdio.h>
/*#include<malloc.h>*/
#include<stdlib.h>
#include<math.h>
#include"matrix.h"


/*
typedef struct{
	float **mat;
	int m, n;	
	} matrix;
*/	

/* Basic initialization, O(m) */
matrix* mat_init(int m, int n){
	int i;
	matrix *T;
	T=(matrix*)malloc(sizeof(matrix));
	T->mat = (float**)malloc(m*sizeof(float*));
	for(i=0;i<m;i++){
		T->mat[i] = (float*)malloc(n*sizeof(float));
		}
	T->m = m;
	T->n = n;
	return T;
	}

/* Initialization into zero matrix, O(mn)*/
matrix* mat_zero(int m, int n){
	int i, j;
	matrix *T;
	T=mat_init(m, n);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			T->mat[i][j] = 0;
	return T;
	}

/* Matrix destruction, O(m) */
void mat_destroy(matrix *T){
	int i;
	for(i=0;i<T->m;i++)
		free(T->mat[i]);
	free(T->mat);
	free(T);
	}

/* Matrix product c = a * b, return 0 if success */
matrix* mat_product(matrix *a, matrix *b){
	int i,j,k;
	matrix *c;
	if(a->n != b->m){
		/* product of a and b not defined */
		printf("Error: matrix product not defined!\n");
		return c;
		}
	c = mat_zero(a->m, b->n);
	for(k=0;k<a->n;k++)
		for(i=0;i<a->m;i++)
			for(j=0;j<b->n;j++)
				c->mat[i][j] += a->mat[i][k] * b->mat[k][j];
	return c;
	}



/* Print a matrix */
void mat_print(matrix *a){
	int i,j;
	if(a->m == 0 || a->n == 0){
		printf("Matrix %d * %d not defined.\n",a->m,a->n);
		return;
		}
	printf("Matrix %d * %d:\n", a->m, a->n);
	for(i=0;i<a->m;i++){
		for(j=0;j<a->n;j++) printf("%8.3f", a->mat[i][j]);
		printf("\n");
		}
	}

void mat_line_swap(matrix *a, int i, int j){
	int k;
	float tmp;
	if(i==j)return;
	for(k=0;k<a->n;k++){
		tmp = a->mat[i][k];
		a->mat[i][k] = a->mat[j][k];
		a->mat[j][k] = tmp;
		}
	}

void mat_line_mult(matrix *a, int i, float lb){
	int k;
	for(k=0;k<a->n;k++) a->mat[i][k] *= lb;
	}

void mat_line_subs(matrix *a, int i, int j, float lb){
	int k;
	if(i==j){
		printf("Error: substracting a line from itself!\n");
		return;
		}
	for(k=0;k<a->n;k++) a->mat[i][k] -= a->mat[j][k] * lb;
	}
	
/*
void mat_copy(matrix *a, matrix *b){
	int i,j;
	mat_init(b, a->m, a->n);
	for(i=0;i<a->m;i++)
		for(j=0;j<a->n;j++)
			b->mat[i][j] = a->mat[i][j];
	}
*/

/* Calculate the rank of matrix a */
int mat_rank(matrix *a){
	matrix *b;
	int i,j,k,rank;
	if(a->m < a->n) b = mat_copy(a);
	else b = mat_transpos(a);
	rank = 0;
	for(i=j=0; i<b->m; i++,j++){
		/*
		printf("From ");
		mat_print(b);
		*/
		/* Operation to ith line on jth coordinate */
		k=b->m;
		while(k>=b->m && j<b->n){
			for(k=i; k<b->m && fabs(b->mat[k][j])<1e-5 ; k++);
			if(k>=b->m)j++;
			}/* Search for a non zero value */
		if(j>=b->n)break;
		mat_line_swap(b,i,k);
		for(k=i+1;k<b->m;k++) 
			mat_line_subs(b, k, i, b->mat[k][j]/b->mat[i][j]);
		/*
		printf("With key %d %d\n", i,j);
		printf("To ");
		mat_print(b);
		*/
		}
	/*
	printf("Rank: %d?\n",i);
	*/	
	mat_destroy(b);
	return i;
	/* We have constructed i independant lines */
	}

/* Copy matrix a to matrix b */
matrix* mat_copy(matrix *a){
	int i,j;
	matrix *b;
	b = mat_init(a->m, a->n);
	for(i=0;i<a->m;i++)
		for(j=0;j<a->n;j++)
			b->mat[i][j] = a->mat[i][j];
	return b;
	}
	
/* Matrix transposition */
matrix* mat_transpos(matrix *a){
	int i,j;
	matrix *b;
	b = mat_init(a->n, a->m);
	for(i=0;i<a->n;i++)
		for(j=0;j<a->m;j++)
			b->mat[i][j] = a->mat[j][i];
	return b;
	}

/* Calculate a matrix's reverse with Gauss-Jordan algorithm */
matrix* mat_reverse(matrix *a){
	matrix *b, *c;
	int n,i,k;
	float lb;
	if(a->m != a->n){
		printf("Error: reversing a non square matrix!\n");
		return c;
		}
	n = a->n;
	b = mat_copy(a);
	c = mat_zero(n,n);
	for(i=0;i<n;i++) c->mat[i][i] = 1.;

	for(i=0; i<b->m; i++){
		/*
		printf("\nBefore:\n");
		printf("b: ");
		mat_print(b);
		printf("c: ");
		mat_print(c);
		*/
		/* Operation to ith line */
		for(k=i; k<n && fabs(b->mat[k][i])<1e-5 ; k++);
		/* Search for a non zero value */
		if(k>=n){
			mat_destroy(b);
			mat_destroy(c);
			printf("Error: square matrix not reversible!\n");
			return NULL;
			}
		mat_line_swap(b,i,k);
		mat_line_swap(c,i,k);
		/*
		printf("After swap:\n");
		printf("b: ");
		mat_print(b);
		printf("c: ");
		mat_print(c);
		*/
		lb = 1. / b->mat[i][i];
		mat_line_mult(b,i,lb);
		mat_line_mult(c,i,lb);
		/*
		printf("After unification:\n");
		printf("b: ");
		mat_print(b);
		printf("c: ");
		mat_print(c);
		*/
		for(k=0;k<n;k++)if(k!=i){ 
			lb = b->mat[k][i];
			mat_line_subs(b, k, i, lb);
			mat_line_subs(c, k, i, lb);
			}
		/*
		printf("With key %d %d\n", i,j);
		printf("To ");
		mat_print(b);
		*/
		/*
		printf("After substraction:\n");
		printf("b: ");
		mat_print(b);
		printf("c: ");
		mat_print(c);
		*/
		}
	mat_destroy(b);
	return c;
	}	

/* Calculate the determinant of a square matrix. */
float mat_recurs_det(matrix *a){
	if(a->m != a->n){
		printf("Error: calculating the determinant of a non square matrix!\n");
		return 0;
		}
	
	int *next_col, *prev_col, *memo;
	/* next_col, prev_col: link table, mem: stack */
	/* n = 'origin' point */
	/* insertion of a node based on the properties of the stack! */
	int n,i,j;
	float det,trm;
	n = a->n;
	
	next_col = (int*)malloc(sizeof(int)*(n+1));
	prev_col = (int*)malloc(sizeof(int)*(n+1));
	for(i=0;i<n-1;i++){
		next_col[i] = i+1;
		prev_col[i+1] = i;
		}
	next_col[n-1] = n;
	prev_col[0] = n;
	
	next_col[n] = 0;
	prev_col[n] = n-1;
	/* Note the first and the last node. */
	
	memo = (int*)malloc(sizeof(int)*n);
	
 	for(det=0,trm=1.,i=0; i>=0;){
		/* Establish a new complete state */
		while(i<n){ 
			j = next_col[n];
			/* j is the first available element. */
			/* Note that such an element always exists. */
			next_col[prev_col[j]] = next_col[j];
			/* Short circuit the front link to pushed element. */
			prev_col[next_col[j]] = prev_col[j];
			/* Short circuit the back link to pushed element. */
			trm *= a->mat[i][j];
			/* Refresh the value of the term. */
			memo[i++] = j;
			/* Push j into stack. */
			} 
 		
 		for(j=0;j<i;j++) printf("%d ",memo[j]);
 		printf(":%8.3f\n",trm);
		
		/* Now we have established a complete state. */
		/* It's time to add up the term to det. */
		det += trm;
		/* Now the state is used. */
		/* Move on the next state. */
		while(i>=0){
			if(!i) {i--; break;}
			j = memo[--i];
			next_col[prev_col[j]] = j;
			prev_col[next_col[j]] = j;
			trm /= a->mat[i][j];
			
			if(next_col[j]<n){
				j = next_col[j];
				next_col[prev_col[j]] = next_col[j];
				prev_col[next_col[j]] = prev_col[j];
				trm *= -a->mat[i][j];
				/* Horizontal move: change the sign */
				memo[i++] = j;
				break;
				/* short circuit the recurse sign change */
				}
			if((n-i)%2==0) trm *= -1.;
			/* Tricky point: check the sign of the last combination by line development. */
			}
		
		}
	free(next_col);
	free(prev_col);
	free(memo);
	return det;
	}



/* Calculate the determinant of a square matrix. */
float mat_det(matrix *a){
	matrix *b;
	int n,i,k;
	float lb,det;
	if(a->m != a->n){
		printf("Error: calculating the determinant of a non square matrix!\n");
		return 0.;
		}
	n = a->n;
	b = mat_copy(a);
	det = 1.;

	for(i=0; i<b->m; i++){
		/*
		printf("\nBefore:\n");
		printf("b: ");
		mat_print(b);
		printf("c: ");
		mat_print(c);
		*/
		/* Operation to ith line */
		for(k=i; k<n && fabs(b->mat[k][i])<1e-5 ; k++);
		/* Search for a non zero value */
		if(k>=n){
			mat_destroy(b);
			/* printf("Error: square matrix not reversible!\n"); */
			return 0.;
			}
		mat_line_swap(b,i,k);
		if(k!=i) det *= -1;
		det *= b->mat[i][i];
		/*
		printf("After swap:\n");
		printf("b: ");
		mat_print(b);
		printf("c: ");
		mat_print(c);
		*/
		for(k=i+1;k<n;k++){ 
			lb = b->mat[k][i];
			mat_line_subs(b, k, i, lb);
			}
		/*
		printf("With key %d %d\n", i,j);
		printf("To ");
		mat_print(b);
		*/
		/*
		printf("After substraction:\n");
		printf("b: ");
		mat_print(b);
		printf("c: ");
		mat_print(c);
		*/
		}
	mat_destroy(b);
	return det;
	}


/*
int main(int argc, char* argv[]){
	matrix a,b,c;
	printf("%d %d\n", a.m, a.n);
	mat_init(&a, 2, 3);
	mat_print(&a);
	return 0;
	}
*/
