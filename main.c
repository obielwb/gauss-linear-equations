#define _GNU_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM 512

typedef enum { false, true } boolean;

float **matrices = malloc(MAXIMUM * sizeof(float *));
int matrices_current_position = 0;

int order_and_matrix[MAXIMUM * 2] = {};

void menu() {
  system("clear");
  printf("|-------------------------------------------------|\n"
         "|       _______                                   |\n"
         "|       |     __|.---.-.--.--.-----.-----.        |\n"
         "|       |    |  ||  _  |  |  |__ --|__ --|        |\n"
         "|       |_______||___._|_____|_____|_____|        |\n"
         "|                                                 |\n"
         "|-------------------------------------------------|\n\n");
}

boolean equal_results_between_pairs_of_lines(float *matrix, int matrix_order) {
  float *lines_division =
      (float *)malloc(sizeof(float) * (matrix_order * matrix_order));
  int lines_division_position = 0;

  // i - first line of couple
  // j - second line of couple
  // k - interator to divide each element
  for (int i = 0; i < matrix_order; i++) {
    for (int j = i + 1; j < matrix_order; j++) {
      for (int k = 0; k < matrix_order; k++) {
        float result = matrix[i * (matrix_order + 1) + k] /
                       matrix[j * (matrix_order + 1) + k];
        lines_division[lines_division_position] = result;
        lines_division_position++;
      }
    }
  }

  int appears_same_number_count = 0;
  for (int i = 0; i < (matrix_order * matrix_order) - 1; i++) {
    if (lines_division[i] == lines_division[i + 1]) {
      appears_same_number_count++;
      if (appears_same_number_count == matrix_order) {
        return true;
      }
    } else {
      appears_same_number_count = 0;
    }
  }

  return false;
}

boolean main_diagonal_has_zeros(float *matrix) {
  for (int i = 0; i < order_and_matrix[matrices_current_position]; i++) {
    if (matrix[i * (order_and_matrix[matrices_current_position] + 1)] == 0) {
      return true;
    }
  }

  return false;
}

// matrix_order + 1 because the matrix has the results in the last column
void turn_diagonal_element_into_one(float *matrix, int number_column_position,
                                    int number_line_position,
                                    int matrix_order) {
  float number = matrix[number_line_position * (matrix_order + 1) +
                        number_column_position];
  for (int i = 0; i < matrix_order + 1; i++) {
    matrix[number_column_position * (matrix_order + 1) + i] =
        matrix[number_column_position * (matrix_order + 1) + i] / number;
  }
}

void turn_element_into_zero(float *matrix, int matrix_order,
                            int line_that_just_implemented_one,
                            int current_line, float number_to_multiply) {
  for (int i = 0; i < matrix_order + 1; i++) {
    float multiplied_number =
        matrix[line_that_just_implemented_one * (matrix_order + 1) + i] *
        number_to_multiply;
    matrix[current_line * (matrix_order + 1) + i] =
        matrix[current_line * (matrix_order + 1) + i] + multiplied_number;
  }
}

float *solve_equation_by_making_column_elements_zero(float *matrix,
                                                     int matrix_order) {
  float *solutions = (float *)malloc(sizeof(float) * matrix_order);

  turn_diagonal_element_into_one(matrix, 0, 0, matrix_order);
  int line_that_just_implemented_one = 0;

  for (int column = 0; column < matrix_order; column++) {
    for (int line = 0; line < matrix_order; line++) {
      if (line != column) {
        float current_number = matrix[line * (matrix_order + 1) + column];
        if (current_number != 0.0) {
          turn_element_into_zero(matrix, matrix_order,
                                 line_that_just_implemented_one, line,
                                 (current_number * -1.0));
          if (matrix[line * (matrix_order + 1) + line] != 1.0) {
            // if we make the element of row N zero, the diagonal NxN becomes
            // one
            turn_diagonal_element_into_one(matrix, line, line, matrix_order);
            line_that_just_implemented_one = line;
          }
        }
      }
    }
  }

  for (int i = 0; i < matrix_order; i++) {
    solutions[i] = matrix[i * (matrix_order + 1) + matrix_order];
  }

  return solutions;
}

void free_pointers_array(float **pointers_array, int size) {
  for (int i = 0; i < size; i++) {
    free(pointers_array[i]);
  }

  free(pointers_array);
}

int main(int argument_count, char *argument_values[]) {
  if (argument_count > 2) {
    printf("Error: Too many arguments");
  } else {
    if (argument_count == 2) {
      if (strlen(argument_values[1]) > 4) {
        if (strcmp(argument_values[1] + strlen(argument_values[1]) - 4,
                   ".txt") != 0) {
          printf("Error: Not a .txt file\n");
          return 1;
        }
      } else {
        printf("Error: Invalid file\n");
        return 1;
      }

      FILE *file = fopen(argument_values[1], "r");

      if (file == NULL) {
        printf("Error: File could not be opened\n");
        return 1;
      } else {
        menu();

        char line[256];

        float *matrix_values;
        int matrix_values_current_position = 0;
        int matrix_size;

        boolean inserting_equations = false;

        while (fgets(line, sizeof(line), file) != NULL) {
          printf("> Retrieved line of length %zu:\n", strlen(line));
          printf("> %s", line);

          int line_elements_count = 0;

          char *element = strtok(line, " ");

          while (element != NULL) {
            if (isspace(*element) == 0)
              line_elements_count++;
            element = strtok(NULL, " ");
          }

          printf("elements %d\n", line_elements_count);

          if (line_elements_count < 1) {
            // debug
            printf("size : %d\n", matrix_size);
            printf("values : %d\n", matrix_values_current_position);
            printf("first: %f\n", matrix_values[0]);
            for (int i = 0; i < (matrix_size); i++) {
              printf("%f ", matrix_values[i]);
            }

            /*
            if (main_diagonal_has_zeros(matrix_values))
              if (equal_results_between_pairs_of_lines(matrix_values,
            matrix_size) == false) { matrices[matrices_current_position] =
            matrix_values; matrices_current_position++;

                // vector of pairs -> order and matrix position in matrices
            array order_and_matrix[matrices_current_position] = matrix_size;
                order_and_matrix[matrices_current_position + 1] =
            matrices_current_position;
              }
            */

            matrix_size = 0;
            inserting_equations = 0;

            printf("\nReset operation\n");
          } else if (matrix_size > 0) {
            if (line_elements_count != matrix_size + 1) {
              printf("Error: Invalid matrix size");
              return 1;
            }
          }

          if (inserting_equations == true) {
            char *equation_element = strtok(line, " ");

            while (equation_element != NULL) {
              if (isspace(*equation_element) == 0) {
                if (isdigit(*equation_element) != 0) {
                  float value = atof(equation_element);
                  matrix_values[matrix_values_current_position] = value;
                  matrix_values_current_position++;
                  printf("Value: %f\n", value);
                }
              }
              equation_element = strtok(NULL, " ");
            }
          } else if (line_elements_count == 1 && inserting_equations == false) {
            char *first_element = strtok(line, " ");
            sscanf(first_element, "%d", &matrix_size);
            matrix_values = (float *)malloc(sizeof(float) *
                                            (matrix_size * matrix_size + 1));
            inserting_equations = true;

            printf("Matrix size: %d\n", matrix_size);
            printf("Inserting equations? %d\n", inserting_equations);
          }
        }

        /*for (int k = 0; k < sizeof(order_and_matrix); k += 2)
        {
          int matrix_order = order_and_matrix[k];
          float *matrix = matrices[order_and_matrix[k + 1]];

          print_matrix(matrix, matrix_order);
          float *solutions =
        solve_equation_by_making_column_elements_zero(matrix, matrix_order);

          printf("Solutions: ");
          for (int i = 0; i < matrix_order; i++)
          {
            printf("%f ", solutions[i]);
          }
        }*/

        fclose(file);

        free_pointers_array(matrices, MAXIMUM);
      }
    } else {
      printf("Error: No file given\n");
      return 1;
    }
  }

  return 0;
}
