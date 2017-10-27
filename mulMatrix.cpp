/******************************************************************************
        author: LeLeXia
          date: 22:38:15 10/26/2017
        e-mail: lishuxiang@cug.edu.cn
   description: to calculate the result of two matrixs's(A and B) product(A*B).
******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 20

inline void
Input (int p[MAX_SIZE][MAX_SIZE], int *n, int *m)
{
  //Input Matrix
  char *line;
  size_t len = 0;
  int tmp_m = 0;
  *n = 0;
  *m = 0;
  while (getline (&line, &len, stdin) > 0)
    {
      while (~sscanf (line, "%d", &p[*n][tmp_m]))
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

int
main ()
{
  printf ("This program is used to figure out A*B.\n");
  while (true)
    {
      //Input Matrix
      int A[MAX_SIZE][MAX_SZIE] = { {0} }, B[MAX_SIZE][MAX_SIZE] =
      {
	{
      0}};
      int an = 0, am = 0, bn = 0, bm = 0;
      printf ("Please input matrix A:\n");
      Input (A, &an, &am);
      printf ("Please input matrix B:\n");
      Input (B, &bn, &bm);
      //can they multiply?
      if (am != bn)
	{
	  printf
	    ("Please check your input.It is meaningless that A times B\n");
	  continue;
	}
      //calculate
      int R[an][bm];
      printf ("result matrix R(%d,%d):\n", an, bm);
      for (int n = 0; n < an; n++)
	{
	  for (int m = 0; m < bm; m++)
	    {
	      int r = 0;
	      for (int i = 0; i < am; i++)
		{
		  r += A[n][i] * B[i][m];
		}
	      R[n][m] = r;
	      printf ("%d ", R[n][m]);	//output
	    }
	  printf ("\n");
	}
    }
  return 0;
}
