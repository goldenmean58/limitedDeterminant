/*****************************************************************************

    author: LeLeXia
      date: 11:30 10/29/2017
    e-mail: lishuxiang@cug.edu.cn
  function: to calculate rank of matrix A
    theory: use Main-element elimination(col) to turn A into a Row_Echelonize,and have improved it for some disadvantages:
  * * * *
  0 * * *
  0 0 0 * <- pay attention to the third zero,sometimes use Main-element-
  0 0 0 *    elimination(col) may cause the case. I've fixed it in line 110-118

     refer: https://baike.baidu.com/item/%E5%88%97%E4%B8%BB%E5%85%83%E6%B6%88%E5%8E%BB%E6%B3%95

******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MAX_SIZE 20
#define ACCURACY 1e-5

void
Input (float p[MAX_SIZE][MAX_SIZE], int *n, int *m)
{
  //Input Matrix
  char *line;
  size_t len = 0;
  int tmp_m = 0;
  *n = 0;
  *m = 0;
  while (getline (&line, &len, stdin) > 0)
    {
      while (~sscanf (line, "%f", &p[*n][tmp_m]))
	{
	  int i = 0;
	  while (true)
	    {
	      if (*(line + i) == ' ' || *(line + i) == '\n'
		  || *(line + i) == '\0' || *(line + i) == EOF)
		{
		  line += (i + 1);
		  break;
		}
	      i++;
	    }
	  tmp_m++;
	}
      (*n)++;
      *m = tmp_m;
      tmp_m = 0;
    }
}

void exchangeRow(float A[MAX_SIZE][MAX_SIZE],int r1,int r2,int m){ //r1<->r2
	float tmp=0;
	for(int i=0;i<m;i++){
		tmp=A[r1-1][i];
		A[r1-1][i]=A[r2-1][i];
		A[r2-1][i]=tmp;
	}
}

void Eliminate(float A[MAX_SIZE][MAX_SIZE],int r1,int r2,float k,int m){ //r1+k*r2
	for(int i=0;i<m;i++){
		A[r1-1][i]=A[r1-1][i]+k*A[r2-1][i];
	}
}

int max(float A[MAX_SIZE][MAX_SIZE],int n,int m){
	int result=0;
	float tmp=fabs(A[m-1][m-1]);
	for(int i=m-1;i<n;i++){
		if(fabs(A[i][m-1])>tmp){
			tmp=fabs(A[i][m-1]);
			result=i+1;
		}
	}
	return result;
}

int nonZero(float A[MAX_SIZE][MAX_SIZE],int r,int m){
	int result=0;
	for(int i=0;i<m;i++){
		if(fabs(A[r-1][i])<ACCURACY){ //XXX:Accuracy
			result=i+1;
		}
		else{	
			break;
		}
	}
	result++;
	return result;
}

void Row_Echelonize(float A[MAX_SIZE][MAX_SIZE],int n,int m){
	int min;
	min=(n>m)?m:n;
	float k=0;
	int maxResult=0;
	for(int i=0;i<min-1;i++){ 
		maxResult=max(A,n,i+1);
		if(maxResult!=0)
			exchangeRow(A,maxResult,i+1,m); 
		for(int j=i+1;j<n;j++){
			if(A[i][i]==0)
				break;
			k=-(A[j][i]/A[i][i]);
			Eliminate(A,j+1,i+1,k,m);
		}
	}
	for(int i=0;i<min;i++){
		int n1,n2;
		n1=nonZero(A,i+1,m);
		n2=nonZero(A,i+2,m);
		if(n1==n2 && n1<=m){
			k=-(A[i+1][n2-1]/A[i][n1-1]);
			Eliminate(A,i+2,i+1,k,m);
		}
	}
}

int rankMatrix(float A[MAX_SIZE][MAX_SIZE],int n,int m){
	int rank=0;
	//turn the matrix to a Row-Echelon matrix
	Row_Echelonize(A,n,m);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(fabs(A[i][j])>ACCURACY){ //XXX: Accuracy
				rank++;
				break;
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			printf("%f ",A[i][j]);
		}
		printf("\n");
	}
	return rank;
}

int main(void){
	while(true){
		float A[MAX_SIZE][MAX_SIZE]={{0}};
		int n=0,m=0;
		int rank=0;
		printf("Please input matrix A:\n");
		Input(A,&n,&m);
		rank=rankMatrix(A,n,m);
		printf("The rank of matrix A is: %d\n",rank);
	}
	return 0;
}
