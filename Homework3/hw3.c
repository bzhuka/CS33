void transpose (int *dst, int *src, int dim)
{
  int i,j;
  int x,y;
  int xdim;
  for (i = 0; i < dim; i+=64) {
    for (j = 0; j < dim; j+=64) {
      for (x = i; x < (i+64,dim); x++) {
	xdim = x * dim;
	for (y = j; y < (j + 64, dim); y++) {
	  dst[y*dim + x] = src[xdim + y];
	}
      }
    }
  }
}
