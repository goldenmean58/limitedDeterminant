/***********************************************

  Copyright: lelexia

     Author: lelexia

       Date: 2017-10-17

Description: to calculate a limited determinant

     e-mail: lishuxiang@cug.edu.cn

***********************************************/
#include <stdio.h>
#include <cmath>
#define MAX_SIZE 16		//16 rows*16cols

/*
	    name: calculate
	function: call back to calculate
	   input: array and n
	  output: result
	optimize: no
*/

inline int
calculate (int a[MAX_SIZE][MAX_SIZE], int n)
{
  int result = 0;
  if (n == 2)
    {				//directly calculate
      result = a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
  else
    {
      for (int i = 0; i < n; i++)
	{
	  int tmp[MAX_SIZE][MAX_SIZE] = { {0} };
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
	    result + pow (-1, i + 2) * a[0][i] * calculate (tmp, n - 1);
	}
    }
  return result;
}

int
main (void)
{
  while (true)
    {
      printf
	("Please input your limited determinant,and split the numbers by space:\n");
      int n = 0;
      int input = 0;
      int tmp[MAX_SIZE][MAX_SIZE] = { {0} };
      while (~scanf ("%d", &input))
	{
	  tmp[n / MAX_SIZE][n % MAX_SIZE] = input;
	  n++;
	}
      int x;
      x = (int) sqrt (n);
      int a[16][16] = { {0} };
      for (int i = 0; i < n; i++)
	{
	  a[i / x][i % x] = tmp[i / MAX_SIZE][i % MAX_SIZE];
	}
      int result = calculate (a, x);
      printf ("result=%d\n\n", result);
    }
  return 0;
}
