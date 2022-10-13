#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXIMUM 512

typedef enum
{
  false,
  true
} boolean;

float *matrices[MAXIMUM];
int matrices_current_position = 0;

int order_and_matrix[MAXIMUM * 2] = {};
// float solutions[MAXIMUM] = {};

void menu()
{
  system("clear");
  printf(
      "_______\n"
      "|     __|.---.-.--.--.-----.-----.\n"
      "|    |  ||  _  |  |  |__ --|__ --|\n"
      "|_______||___._|_____|_____|_____|\n\n");
  printf("0 - Exit\n");
  printf("1 - Type in equations system\n\n");
}

void pause()
{
  printf("Press enter to continue...");
  while ((getchar()) != '\n')
    ;
  getchar();
}

float *sanitize_input_equation(char *equation, int qtd_equations)
{
}

boolean equal_results_between_pairs_of_lines(float *matrix, int matrix_order)
{
  float *lines_division = (float *)malloc(sizeof(float) * (matrix_order * matrix_order));
  int lines_division_position = 0;

  // i - first line of couple
  // j - second line of couple
  // k - interator to divide each element
  for (int i = 0; i < matrix_order; i++)
  {
    for (int j = i + 1; j < matrix_order; j++)
    {
      for (int k = 0; k < matrix_order; k++)
      {
        float result = matrix[i * (matrix_order + 1) + k] / matrix[j * (matrix_order + 1) + k];
        lines_division[lines_division_position] = result;
        lines_division_position++;
      }
    }
  }

  int qtd_appears_same_number = 0;
  for (int i = 0; i < (matrix_order * matrix_order) - 1; i++)
  {
    if (lines_division[i] == lines_division[i + 1])
    {
      qtd_appears_same_number++;
      if (qtd_appears_same_number == matrix_order)
      {
        return true;
      }
    }
    else
    {
      qtd_appears_same_number = 0;
    }
  }
  return false;
}

boolean can_have_no_zeros_in_main_diagonal(float *matrix) {}

// matrix_order + 1 because the matrix has the results in the last column
void turn_diagonal_element_into_one(float *matrix, int number_column_position, int number_line_position, int matrix_order)
{
  float number = matrix[number_line_position * (matrix_order + 1) + number_column_position];
  for (int i = 0; i < matrix_order + 1; i++)
  {
    matrix[number_column_position * (matrix_order + 1) + i] = matrix[number_column_position * (matrix_order + 1) + i] / number;
  }
}

void turn_element_into_zero(float *matrix, int matrix_order, int line_that_just_implemented_one, int current_line, float number_to_multiply)
{
  for (int i = 0; i < matrix_order + 1; i++)
  {
    float multiplied_number = matrix[line_that_just_implemented_one * (matrix_order + 1) + i] * number_to_multiply;
    matrix[current_line * (matrix_order + 1) + i] = matrix[current_line * (matrix_order + 1) + i] + multiplied_number;
  }
}

// TODO: implement logic to store solutions
void solve_equation_by_make_column_elements_zero()
{
  for (int k = 0; k < sizeof(order_and_matrix); k += 2)
  {
    int matrix_order = order_and_matrix[k];
    float *matrix = matrices[order_and_matrix[k + 1]];

    turn_diagonal_element_into_one(matrix, 0, 0, matrix_order);
    int line_that_just_implemented_one = 0;

    for (int column = 0; column < matrix_order; column++)
    {
      for (int line = 0; line < matrix_order; line++)
      {
        if (line != column)
        {
          float current_number = matrix[line * (matrix_order + 1) + column];
          if (current_number != 0.0)
          {
            turn_element_into_zero(matrix, matrix_order, line_that_just_implemented_one, line, (current_number * -1.0));
            if (matrix[line * (matrix_order + 1) + line] != 1.0)
            {
              // if we make the element of row N zero, the diagonal NxN becomes one
              turn_diagonal_element_into_one(matrix, line, line, matrix_order);
              line_that_just_implemented_one = line;
            }
          }
        }
      }
    }
  }
}

int main(int argument_count, char *argument_values[])
{
  if (argument_count > 2)
  {
    printf("Error: Too many arguments given");
  }
  else
  {
    if (argument_count == 2)
    {
      if (strlen(argument_values[1]) > 4)
      {
        if (strcmp(argument_values[1] + strlen(argument_values[1]) - 4, ".txt") != 0)
        {
          printf("Error: File is not a .txt file\n");
          return 1;
        }
      }
      else
      {
        printf("Error: Invalid file given\n");
        return 1;
      }

      FILE *file = fopen(argument_values[1], "r");

      if (file == NULL)
      {
        printf("Error: File could not be opened\n");
        return 1;
      }
      else
      {
        char line[256];
        size_t length = 0;
        float *matrix_values;
        int matrix_values_atual_position = 0;
        boolean inserting_equations = false; // false
        int matrix_size;

        while (fgets(line, sizeof(line), file) != NULL)
        {
          printf("> Retrieved line of length %zu:\n", strlen(line));
          printf("> %s", line);

          int qtd_line_elements = 0;

          char *token = strtok(line, " ");

          while (token != NULL)
          {
            if (isspace(*token) == 0)
              qtd_line_elements++;
            token = strtok(NULL, " ");
          }

          printf("elements %d\n", qtd_line_elements);

          if (qtd_line_elements < 1)
          {
            // debug
            printf("size : %d\n", matrix_size);
            printf("values : %d\n", matrix_values_atual_position);
            printf("first: %f\n", matrix_values[0]);
            for (int i = 0; i < (matrix_size); i++)
            {
              printf("%f ", matrix_values[i]);
            }

            /*
            if (can_have_no_zeros_in_main_diagonal(matrix_values) == true)
              if (equal_results_between_pairs_of_lines(matrix_values, matrix_size) == false) {
                matrices[matrices_current_position] = matrix_values;
                matrices_current_position++;

                // vector of pairs -> order and matrix position in matrices array
                order_and_matrix[matrices_current_position] = matrix_size;
                order_and_matrix[matrices_current_position + 1] = matrices_current_position;
              }
            */

            matrix_size = 0;
            inserting_equations = 0;
            // if (matrix_values)
            //   free(matrix_values);

            printf("\nReset operation\n");
          }
          else if (matrix_size > 0)
          {
            if (qtd_line_elements != matrix_size + 1)
            {
              printf("Error: Invalid matrix size.");
              return 1;
            }
          }

          if (inserting_equations == true)
          {
            char *equation_element = strtok(line, " ");

            while (equation_element != NULL)
            {
              if (isspace(*equation_element) == 0)
              {
                if (isdigit(*equation_element) != 0)
                {
                  float value = atof(equation_element);
                  matrix_values[matrix_values_atual_position] = value;
                  matrix_values_atual_position++;
                  printf("Value: %f\n", value);
                }
              }
              equation_element = strtok(NULL, " ");
            }
          }
          else if (qtd_line_elements == 1 && inserting_equations == false)
          {
            char *first_element = strtok(line, " ");
            sscanf(first_element, "%d", &matrix_size);
            matrix_values = (float *)malloc(sizeof(float) * (matrix_size * matrix_size + 1));
            inserting_equations = true;

            printf("Qtd matrix rows: %d\n", matrix_size);
            printf("inserting equations %d\n", inserting_equations);
          }
        }

        fclose(file);
      }
    }
    else
    {
      while (true)
      {
        menu();

        char option;

        printf("> Chose an option: ");
        scanf("%c", &option);

        if (option == '0')
          break;

        else if (option == '1')
        {
          boolean solve_current_equations_systems = false;
          int equations_system_stored = 0;

          while (solve_current_equations_systems == false)
          {
            system("clear");
            int qtd_equations;

            printf("[systems of equations already entered - %d]\n", equations_system_stored);
            printf("> Type in the number of equations of the system: ");
            scanf("%d", &qtd_equations);

            if (qtd_equations < 2)
            {
              printf("Error: Invalid number of equations\n");
              printf("> Type in the number of equations: ");
              scanf("%d", &qtd_equations);
            }
            else
            {
              int remaining_equations = qtd_equations;

              size_t buffer_size = 32;
              size_t characters;
              char *buffer = (char *)malloc(buffer_size * sizeof(char));

              if (buffer == NULL)
              {
                printf("Error: Could not allocate memory to the read buffer. Run the program again.\n");
                exit(1);
              }

              float *matrix_values = (float *)malloc(sizeof(float) * (qtd_equations * qtd_equations + 1));

              if (matrix_values == NULL)
              {
                printf("Error: Could not allocate memory to the matrix values. Run the program again.\n");
                exit(1);
              }

              while (remaining_equations > 0)
              {
                printf("> Type the %d° equation: ", remaining_equations);
                characters = getline(&buffer, &buffer_size, stdin);
                if (isspace(buffer[0]) != 0)
                {
                  buffer[characters - 1] = '\0';
                }
                else
                {
                  if (characters == -1)
                  {
                    printf("Error: Could not read the equation. Run the program again.\n");
                    exit(1);
                  }
                  else
                  {
                    printf("Retrieved line of length %zu:\n", characters);
                    printf("%s", buffer);

                    int qtd_buffer_elements = 0;

                    char *token = strtok(buffer, " ");

                    while (token != NULL)
                    {
                      if (isspace(*token) == 0)
                        qtd_buffer_elements++;
                      token = strtok(NULL, " ");
                    }

                    if (qtd_buffer_elements > qtd_equations + 1 && qtd_buffer_elements < 1)
                    {
                      printf("Error: Invalid number of elements in the equation.\n");
                      remaining_equations++;
                    }
                    else
                    {
                    }

                    remaining_equations--;
                  }
                }
              }

              printf("\n\nWant to add more equations or see the result of the current ones?\n");
              printf("1 - Add more equations\n");
              printf("2 - See the result of the current equations\n");
              printf("0 - Exit\n");

              char option;

              while (true)
              {
                printf("> Chose an option: ");
                scanf("%c", &option);

                if (option == '0')
                  exit(0);

                else if (option == '1')
                {
                  equations_system_stored++;
                  break;
                }

                else if (option == '2')
                {
                  solve_current_equations_systems = true;
                  break;
                }

                else
                {
                  printf("Error: Invalid option.\n");
                }
              }
            }
          }
        }

        else
        {
          printf("\n> Invalid option!\n");
          pause();
        }
      }

      return 0;
    }
  }

  return 0;
}

// https://stackoverflow.com/questions/10874374/passing-a-unknown-size-matrix-reference-to-a-c-function
// https://www.tutorialspoint.com/cprogramming/c_array_of_pointers.htm
// https://www.geeksforgeeks.org/find-all-pairs-possible-from-the-given-array/

// ------------- exist_zeros_in_main_diagonal() -------------
// https://cs.stackexchange.com/questions/58096/permutation-on-matrix-to-fill-main-diagonal-with-non-zero-values
// https://www.geeksforgeeks.org/maximum-bipartite-matching/
