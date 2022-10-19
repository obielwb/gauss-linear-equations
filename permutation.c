#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef
  enum
  {
    false, true
  } boolean;


void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

boolean has_zeros_in_diagonal(int *matrix, int matrix_order) {
  for (int i = 0; i < matrix_order; i++) {
    if (matrix[i * matrix_order + i] == 0) {
      return true;
    }
  }

  return false;
}

int *arrange_matrix_from_permutation(int *matrix, int *permutation, int matrix_order) {
  int *arranged_matrix = (int *)malloc(matrix_order * matrix_order * sizeof(int));

  // rows arrangement
  for (int i = 0; i < matrix_order; i++) {
    for (int j = 0; j < matrix_order; j++) {
      arranged_matrix[i * matrix_order + j] =
          matrix[permutation[i] * matrix_order + j];
    }
  }

  if (has_zeros_in_diagonal(arranged_matrix, matrix_order) == false) {
    return arranged_matrix;
  }

  // columns arrangement
  for (int i = 0; i < matrix_order; i++) {
    for (int j = 0; j < matrix_order; j++) {
      arranged_matrix[i * matrix_order + j] =
          matrix[i * matrix_order + permutation[j]];
    }
  }

  if (has_zeros_in_diagonal(arranged_matrix, matrix_order) == false) {
    return arranged_matrix;
  }

  return 0;
}

void permutate(int indexes[], int start, int end, int matrix_order,
               int matrix[matrix_order][matrix_order]) {
  if (start == end) {
    int *arranged_matrix =
        arrange_matrix_from_permutation((int *)matrix, indexes, matrix_order);

    if (arranged_matrix != 0) {
      for (int i = 0; i < matrix_order; i++) {
        for (int j = 0; j < matrix_order; j++) {
          matrix[i][j] = arranged_matrix[i * matrix_order + j];
        }
      }
      return;
    }
  }

  for (int i = start; i <= end; i++) {
    swap((indexes + i), (indexes + start));
    permutate(indexes, start + 1, end, matrix_order, matrix);
    swap((indexes + i), (indexes + start));
  }
}

int *find_matrix_without_zeros_in_diagonal(int *matrix, int matrix_order) {
  int *indexes = (int *)malloc(matrix_order * sizeof(int));
  for (int i = 0; i < matrix_order; i++) {
    indexes[i] = i;
  }

  int *matrix_without_zeros = (int *)malloc(matrix_order * matrix_order * sizeof(int));

  for (int i = 0; i < matrix_order; i++) {
    for (int j = 0; j < matrix_order; j++) {
      matrix_without_zeros[i * matrix_order + j] = matrix[i * matrix_order + j];
    }
  }

  permutate(indexes, 0, matrix_order - 1, matrix_order, matrix_without_zeros);

  int equal_elements = 0;
  for (int i = 0; i < matrix_order; i++) {
    for (int j = 0; j < matrix_order; j++) {
      if (matrix_without_zeros[i * matrix_order + j] == matrix[i * matrix_order + j]) {
        equal_elements++;
      }
    }
  }

  if (equal_elements == matrix_order * matrix_order) {
    return 0;
  }

  return matrix_without_zeros;
}

int main() {
  printf("K: ");

  int matrix_order;
  scanf("%d", &matrix_order);

  int matrix[matrix_order][matrix_order];

  for (int i = 0; i < matrix_order; i++) {
    for (int j = 0; j < matrix_order; j++) {
      matrix[i][j] = j - i;
      printf("%d ", matrix[i][j]);
    }

    printf("\n");
  }

  int *matrix_without_zeros =
      find_matrix_without_zeros_in_diagonal(matrix, matrix_order);

  printf("\n--------------\n");

  if (matrix_without_zeros != 0) {
    for (int i = 0; i < matrix_order; i++) {
      for (int j = 0; j < matrix_order; j++) {
        printf("%d ", matrix_without_zeros[i * matrix_order + j]);
      }

      printf("\n");
    }
  } else {
    printf("No solution");
  }

  return 0;
}
