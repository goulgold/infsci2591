#include "util.h"
int **allocMatrix(int size) {
  int **matrix;
  matrix = (int **)malloc(size * sizeof(int *));
  for (int row = 0; row < size; row++) {
    matrix[row] = (int *)malloc(size * sizeof(int));
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

int readMatrixFile(int **matrix, int N, char *filename){

  FILE *ifp, *ofp;
  ifp = fopen(filename, "r");

  if (ifp == NULL) {
    fprintf(stderr, "Can't open input file in.list!\n");
    return 1;
  }

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      if (!fscanf(ifp, "%d", &matrix[i][j])) {
	fprintf(stderr, "Unable to read!\n");
	return 1;
      }
    }
  }
  return 0;
}

int **randomMatrix(int n) {
    srand (time(NULL));
     int **matrix = allocMatrix(n);
     for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
             if (i == 0 || j == 0) {
                 matrix[i][j] = 0;
             }
             else if (i != j) {
                  matrix[i][j] = rand() % 50;
             } else {
                  matrix[i][j] = 0;
             }
         }
     }
     return matrix;
}
