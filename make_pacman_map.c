#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int const N = 100;
int const M = 100;
double const percentblocks = 0.05;
bool permute = true;

void randPerm(int P[], int size);
int main()
{
  int D[N][M];
  int C[N*M][4];
  int P[N*M];
  FILE *fp;
  int i,j,k,p;

  for (i=0;i<N;i++)
    for (j=0;j<M;j++)
      D[i][j] = i*M + j;

  if (permute)
    randPerm(P,N*M);
  else
    for (i=0;i<N*M;i++)
      P[i] = i;

  for (i=0;i<N;i++)
    for (j=0;j<M;j++)
      D[i][j] = P[D[i][j]];
  

  for (i=0;i<N;i++)
    for (j=0;j<M;j++)
      /*      if (drand48()<percentblocks)*/
      if ((double)rand()/RAND_MAX<percentblocks)
	D[i][j] = -1;

  for (i=0;i<N*M;i++)
    for (j=0;j<4;j++)
      C[i][j] = 0.0;

  p = 0;
  for (i=0;i<N;i++)
    for (j=0;j<M;j++)
      {
	k = P[p++];
	if (j==0)
	  C[k][0] = -1;
	else
	  C[k][0] = D[i][j-1];
	if (j==M-1)
	  C[k][1] = -1;
	else
	  C[k][1] = D[i][j+1];
	if (i==0)
	  C[k][2] = -1;
	else
	  C[k][2] = D[i-1][j];
	if (i==N-1)
	  C[k][3] = -1;
	else
	  C[k][3] = D[i+1][j];
      }

  fp = fopen("PacManMap.txt", "w");
  fprintf(fp, "%d\n", N*M);
  for (i=0;i<N*M;i++)
    {
      for (j=0;j<4;j++)
	fprintf(fp, "%d ", C[i][j]);
      fprintf(fp, "\n");
    }

  fclose(fp);
  return 0;
}

void randPerm(int P[], int size)
{
  int i;
  int k;
  int tmp;
  for (i=0;i<size;i++)
    P[i] = i;

  for (i=size-1;i>=0;i--)
    {
      k = floor((double)rand()/RAND_MAX*i);
      tmp = P[k];
      P[k] = P[i];
      P[i] = tmp;
    }
}
  
