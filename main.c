#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*#include<malloc.h>*/
#include"matrix.h"

/* strcmp not identifying capitals or lower-case */
int strcmpcl(const char* p1, const char* p2){
	while(*p1&&*p2){
		char c1 = *p1;
		char c2 = *p2;
		if(c1>='A'&&c1<='Z') c1+= 'a'-'A';
		if(c2>='A'&&c1<='Z') c2+= 'a'-'A';
		if(c1!=c2)return c1-c2;
		p1++;
		p2++;
		}	
	return *p1-*p2;
	}

int main(int argc, char* argv[]){
	int m,n,i,j;
	/*
	matrix a,b,c;
	scanf("%d",&n);
	printf("n = %d\n",n);
	mat_zero(&a, n, n);
	mat_zero(&b, n, n);
	for(i=0;i<n;i++)a.mat[i][i]=b.mat[i][i] = i+1;
	mat_line_swap(&a, 2, 1);
	mat_print(&a);
	mat_print(&b);
	mat_product(&a,&b,&c);
	mat_print(&c);
	mat_destroy(&c);
	mat_transpos(&a,&c);
	mat_print(&c);
	mat_destroy(&a);
	mat_copy(&c,&a);
	mat_print(&c);
	*/
	/*
	printf("%d\n",argc);
	for(i=0;i<argc;i++)printf("%s\n",argv[i]);
	*/
	FILE *_in;
	matrix *a,*b,*c,*d;
	char cmd[64];
	_in = fopen(argv[1],"r");
	while(fscanf(_in,"%s",cmd)!=EOF){
		if(!strcmpcl(cmd,"reverse")){
			fscanf(_in,"%d %d",&n,&m);
			a = mat_init(n,m);
			for(i=0;i<n;i++)
				for(j=0;j<m;j++)
					fscanf(_in,"%f",&a->mat[i][j]);
			b = mat_reverse(a);
			printf("Reverse of the given matrix:\n");
			mat_print(b);
			mat_destroy(a);
			mat_destroy(b);
			printf("...\n");
			}
		if(!strcmpcl(cmd,"determinant")||!strcmpcl(cmd,"det")){
			fscanf(_in,"%d %d",&n,&m);
			a = mat_init(n,m);
			for(i=0;i<n;i++)
				for(j=0;j<m;j++)
					fscanf(_in,"%f",&a->mat[i][j]);
			printf("Determinant of given matrix: %10.3f\n", mat_det(a));
			mat_destroy(a);
			printf("...\n");
			}
		if(!strcmpcl(cmd,"rank")){
			fscanf(_in,"%d %d",&n,&m);
			a = mat_init(n,m);
			for(i=0;i<n;i++)
				for(j=0;j<m;j++)
					fscanf(_in,"%f",&a->mat[i][j]);
			printf("Rank of given matrix: %d\n", mat_rank(a));
			mat_destroy(a);
			printf("...\n");
			}
		if(!strcmpcl(cmd,"solve")){
			fscanf(_in,"%d %d",&n,&m);
			a = mat_init(n,m);
			for(i=0;i<n;i++)
				for(j=0;j<m;j++)
					fscanf(_in,"%f",&a->mat[i][j]);
			fscanf(_in,"%d %d",&n,&m);
			b = mat_init(n,m);
			for(i=0;i<n;i++)
				for(j=0;j<m;j++)
					fscanf(_in,"%f",&b->mat[i][j]);
			/*
			if(a->n!=a->m){}
			*/
			c = mat_reverse(a);
			d = mat_product(c,b);
			printf("Solution of given linear system:\n");
			mat_print(d);
			mat_destroy(a);
			mat_destroy(b);
			mat_destroy(c);
			mat_destroy(d);
			printf("...\n");
			}
		}
	printf("END.\n");
	return 0;
	}
