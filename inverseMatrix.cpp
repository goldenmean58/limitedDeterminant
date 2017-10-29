/******************************************************************************

   author: LeLeXia
     date: 08:56:47 10/27/2017
   e-mail: lishuxiang@cug.edu.cn
 function: To figure out matrix A's |A|,A*,and A^(-1)

******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#define MAX_SIZE 20

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

float
calculateDeterminant (float a[MAX_SIZE][MAX_SIZE], int n)
{
  int result = 0;
  if (n == 1)
    {
      result = a[0][0];
    }
  if (n == 2)
    {				//directly calculate
      result = a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
  else
    {
      for (int i = 0; i < n; i++)
	{
	  float tmp[MAX_SIZE][MAX_SIZE] = { {0} };
	  //merge cofactor to a new array
	  for (int j = 0; j < n - 1; j++)
	    {
	      for (int z = 0; z < n; z++)
		{
		  if (z <= i)
		    {
		      tmp[j][z] = a[j + 1][z];
		    }
		  else
		    {
		      tmp[j][z - 1] = a[j + 1][z];
		    }
		}
	    }
	  result =
	    result + pow (-1, i + 2) * a[0][i] * calculateDeterminant (tmp,
								       n - 1);
	}
    }
  return result;
}

float
calCompanionMatrix (float a[MAX_SIZE][MAX_SIZE], int n, int x, int y)
{
  float result = 0;
  float tmp[MAX_SIZE][MAX_SIZE] = { {0} };
  //merge cofactor to a new array
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  if (i < x && j < y)
	    {
	      tmp[i][j] = a[i][j];
	    }
	  if (i < x && j > y)
	    {
	      tmp[i][j - 1] = a[i][j];
	    }
	  if (i > x && j < y)
	    {
	      tmp[i - 1][j] = a[i][j];
	    }
	  if (i > x && j > y)
	    {
	      tmp[i - 1][j - 1] = a[i][j];
	    }
	}
    }
  result = pow (-1, x + y + 2) * calculateDeterminant (tmp, n - 1);

  return result;
}

int
main (void)
{
  while (true)
    {
      float A[MAX_SIZE][MAX_SIZE] = { {0} };
      int n = 0, m = 0;
      printf ("Please input the matrix A:\n");
      Input (A, &n, &m);
      float value = 0;		// |A|
      //Can it be inverted?
      if (n != m || (value = calculateDeterminant (A, n)) == 0)
	{
	  printf
	    ("The matrix A cann't be inverted.Please check your input.\n");
	  continue;
	}
      printf ("|A|=%f\n", value);
      //firstly figure out A*
      float tmp_A[MAX_SIZE][MAX_SIZE] = { {0} };
      float companionA[MAX_SIZE][MAX_SIZE] = { {0} };	// A*
      for (int i = 0; i < n; i++)
	{
	  for (int j = 0; j < m; j++)
	    {
	      companionA[j][i] = calCompanionMatrix (A, n, i, j);
	    }
	}
      printf ("A*=\n");
      for (int i = 0; i < n; i++)
	{
	  for (int j = 0; j < m; j++)
	    {
	      printf ("%f ", companionA[i][j]);
	    }
	  printf ("\n");
	}
      //secondly figure out A^(-1)
      float inverseA[MAX_SIZE][MAX_SIZE] = { {0} };
      printf ("A^(-1)=\n");
      for (int i = 0; i < n; i++)
	{
	  for (int j = 0; j < m; j++)
	    {
	      inverseA[i][j] = companionA[i][j];
	      inverseA[i][j] /= value;
	      printf ("%f ", inverseA[i][j]);
	    }
	  printf ("\n");
	}
    }
  return 0;
}
