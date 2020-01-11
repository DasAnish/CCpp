#include "matrix.h"
#include <stdbool.h>

matrix_t matrix_create(int rows, int cols) { 
  matrix_t m = {rows, cols, NULL};
  double *val = malloc(rows*cols*sizeof(double));
  
  m.elts = val;

  return m;
}

double matrix_get(matrix_t m, int r, int c) {
  assert(r >= 0 && r < m.rows && c >= 0 && c < m.cols);
  return m.elts[m.cols * r + c];
}

void matrix_set(matrix_t m, int r, int c, double d) { 
  assert(r < m.rows && c < m.cols);
  m.elts[m.cols * r + c] = d;
}


void matrix_free(matrix_t m) { 
  free(m.elts);
}

double matrix_calc(matrix_t m1, matrix_t m2, int r, int c) {
  double s = 0;
  for (int i = 0; i<m1.cols; i++) {
    s += matrix_get(m1, r, i) * matrix_get(m2, i, c);
  }

  return s;
}

matrix_t matrix_multiply(matrix_t m1, matrix_t m2) {
  assert(m1.cols == m2.rows);
  matrix_t m = {m1.rows, m2.cols, NULL};
  m.elts = malloc(m.rows * m.cols * sizeof(double));

  for (int r = 0; r < m.rows; r++) {
    for (int c = 0; c < m.cols; c++) {
      m.elts[r * m.rows + c] = matrix_calc(m1, m2, r, c);
    }
  }

  return m;
}

matrix_t matrix_transpose(matrix_t m) { 
  matrix_t mt = {m.cols, m.rows, NULL};
  mt.elts = malloc(m.rows * m.cols * sizeof(double));

  for (int r = 0; r < m.rows; r++) {
    for (int c = 0; c < m.cols; c++) {
      matrix_set(mt, c, r, matrix_get(m, r, c));
    }
  }

  return mt;
}

matrix_t matrix_multiply_transposed(matrix_t m1, matrix_t m2) { 
  assert(m1.cols == m2.cols);

  matrix_t mt = matrix_transpose(m2);
  matrix_t prod =  matrix_multiply(m1, mt);
  matrix_free(mt);
  return prod;
}

double matrix_calc2(matrix_t m1, matrix_t m2, int r, int c) {
  double s = 0;
  for (int i = 0; i < m1.cols; i++) {
    s += matrix_get(m1, r, i) * matrix_get(m2, c, i);
  }

  return s;
}

matrix_t matrix_multiply_fast(matrix_t m1, matrix_t m2) { 
  matrix_t mt = matrix_transpose(m2);
  matrix_t prod = {m1.rows, m2.cols, NULL};
  prod.elts = malloc(prod.rows * prod.cols * sizeof(double));
  
  for (int r = 0; r < prod.rows; r++) {
    for (int c = 0; c < prod.cols; c++) {
      matrix_set(prod, r, c, matrix_calc2(m1, mt, r, c));
    }
  }
  matrix_free(mt);
  return prod;
}

void matrix_print(matrix_t m) { 
  for (int i = 0; i < m.rows; i++) { 
    for (int j = 0; j < m.cols; j++) { 
      printf("%g\t", matrix_get(m, i, j));
    }
    printf("\n");
  }
  printf("\n");
}


