#include "func.h"

void Func1(int c[][TSIZE], int a[][TSIZE], int b[][TSIZE])
{
  int i, j, k, con;
#pragma omp parallel for private (i, j, k, con) shared(a,b,c)
  for (i=0; i<TSIZE; i++) {
    for (k=0; k<TSIZE; k++) {
      con = a[i][k];
      for (j=0; j<TSIZE; j++) {
	c[i][j]+=con*b[k][j];
      }
    }
  }
}

void Func2(int d[][MSIZE], int c[][MSIZE])
{
  int i,j, x, y;
#pragma omp parallel for collapse(1) private(i, j, x, y)
  for(i=0; i<MSIZE; i+=16) { 
    for(j=0; j<MSIZE; j+=16) {
      for(x = i; x < i+16; x++) {
	for (y = j; y < j+ 16; y++) {
       	  d[x][y]=c[y][x];
	}
      }
    }
  }
  
} 

void Func3(int z[][MSIZE], int d[][MSIZE])
{
  int y, x;
  int near = 2;           // The weight of neighbor
  int itself = 84;        // The weight of center
  
  //x==0 and y ==0
  //////////////////////////////
  z[0][0] = near* (d[0][0] +
		   d[0][1] +
		   d[1][0] +
		   d[1][1] +
		   d[0][0] +
		   d[0][1] +
		   d[0][0] +
		   d[1][0]) +
    itself * d[0][0];
  z[MSIZE-1][0] =       near * (d[MSIZE-2][0] +
				d[MSIZE-2][1] +
				d[MSIZE-1][0] +
				d[MSIZE-1][1] +
				d[MSIZE-1][0] +
				d[MSIZE-1][1] +
				d[MSIZE-2][0] +
				d[MSIZE-1][0]) +
    itself * d[MSIZE-1][0];
  z[0][0]/=100;
  z[MSIZE-1][0]/=100;
  //////////////////////////////
  
#pragma omp parallel for private(x)
  for (x=1;x<MSIZE;x++) {
    if (x==MSIZE-1) {
      z[0][x] =       near * (d[0][x-1] +
			      d[0][x] +
			      d[1][x-1] +
			      d[1][x] +
			      d[0][x-1] +
			      d[0][x] +
			      d[0][x] +
			      d[1][x]) +
	itself * d[0][x];
      z[MSIZE-1][x] =       near * (d[MSIZE-2][x-1] +
				    d[MSIZE-2][x] +
				    d[MSIZE-1][x-1] +
				    d[MSIZE-1][x] +
				    d[MSIZE-1][x-1] +
				    d[MSIZE-1][x] +
				    d[MSIZE-2][x] +
				    d[MSIZE-1][x]) +
	itself * d[MSIZE-1][x];
    } else {
      
      z[0][x] =       near * (d[0][x-1] +
			      d[0][x+1] +
			      d[1][x-1] +
			      d[1][x+1] +
			      d[0][x-1] +
			      d[0][x+1] +
			      d[0][x] +
			      d[1][x]) +
	itself * d[0][x];
      z[MSIZE-1][x] =       near * (d[MSIZE-2][x-1] +
				    d[MSIZE-2][x+1] +
				    d[MSIZE-1][x-1] +
				    d[MSIZE-1][x+1] +
				    d[MSIZE-1][x-1] +
				    d[MSIZE-1][x+1] +
				    d[MSIZE-2][x] +
				    d[MSIZE-1][x]) +
	itself * d[MSIZE-1][x];
      
    }
    z[0][x]/=100;
    z[MSIZE-1][x]/=100;
  }

#pragma omp parallel for collapse(1) private(y,x)  
  for (y=1; y<MSIZE-1; y++) {
    for (x=0; x<MSIZE; x++) {
      if (x==0) {
	z[y][0] =       near * (d[y-1][0] +
				d[y-1][1] +
				d[y+1][0] +
				d[y+1][1] +
				d[y][0] +
				d[y][1] +
				d[y-1][0] +
				d[y+1][0]) +
	  itself * d[y][0];
      } else if (x==MSIZE-1) {
	z[y][x] =       near * (d[y-1][x-1] +
				d[y-1][x] +
				d[y+1][x-1] +
				d[y+1][x] +
				d[y][x-1] +
				d[y][x] +
				d[y-1][x] +
				d[y+1][x]) +
	  itself * d[y][x];
      } else {
	z[y][x] =       near * (d[y-1][x-1] +
				d[y-1][x+1] +
				d[y+1][x-1] +
				d[y+1][x+1] +
				d[y][x-1] +
				d[y][x+1] +
				d[y-1][x] +
				d[y+1][x]) +
	  itself * d[y][x];
      }
      z[y][x]/=100;      
    }
  }
}

						
void Func4(int b[], int a[])
{
  int chuck_size=MSIZE;	 
  int array_size=VSIZE/chuck_size;
  int chuck[chuck_size];
  int i, j, cplace = chuck[0];
  #pragma omp parallel
  {
    #pragma omp for private (j, i)
    for(j=0; j<chuck_size; j++) {
      int temp = j*array_size;
      int asdf = b[temp]= a[temp];
      for (i=1; i<array_size; i++) {
	asdf = b[temp + i] = asdf +a[temp + i];
      }
      chuck[j]=asdf;
    }
#pragma omp single
    for(j=1; j<chuck_size; j++) {
      chuck[j] +=cplace;
      cplace=chuck[j];
    }
#pragma omp for private(i, j)
    for(j=1; j<chuck_size; j++) {
      int temp = j*array_size;
      int cval = chuck[j-1]/(j+1);
      for (i=0; i<array_size; i++) {
	b[temp+i]+=cval;
      }
    }
  }
}

void Func5(int b[], int a[])
{
  int i=0, j;
  int temp;
  long log_N=log2(VSIZE);
  #pragma omp parallel for private(j)
  for(j=0; j<VSIZE; j+=2) {
    int temp = a[j];
    b[j]=temp;
    b[j+1] = temp + a[j+1];     
  }
  
  for(i=4; i<VSIZE; i*=2) {
    for(j=0; j<VSIZE; j+=i) {
      b[j+i-1] += b[j+i/2-1];
    }
  }
  
  b[VSIZE-1]=0;
  for(i=(log_N-1); i>=0; i--) {
    int temp1 = (int)pow(2, i+1);
    int temp2 = (int)pow(2, i);
    for(j=0; j<VSIZE; j+=temp1) {
      temp=b[j+temp2-1];
      b[j+temp2-1] = b[j+temp1-1];
      b[j+temp1-1] = temp+b[j+temp1-1];
    }
  }
}
