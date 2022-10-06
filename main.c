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

int *matrices[MAXIMUM];

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
        int *matrix_values;
        int matrix_values_atual_position = 0;
        int inserting_equations = 0; // false
        int matrix_size;


        while (fgets(line, sizeof(line), file) != NULL)
        {
          printf("> Retrieved line of length %zu:\n", strlen(line));
          printf("> %s", line);

          int qtd_line_elements = 0;

          char* token = strtok(line, " ");
          char *values;
          
          while (token != NULL)
          {
            qtd_line_elements++;
            token = strtok(NULL, " ");
          }
          
          if (qtd_line_elements < 2)
          {
            // store_equation(matrix_values);
            for (int i = 0; i < sizeof(matrix_values); i++)
            {
              printf("%d", matrix_values[i]);
            }

            inserting_equations = 0;
            if (matrix_values)
              free(matrix_values);

            printf("Reset operation\n");
          }

          else if (qtd_line_elements == 2 && inserting_equations == 0)
          {
            token = strtok(line, " "); // get the first element again
            sscanf(token, "%d", &matrix_size);
            matrix_values = (int *)malloc(sizeof(int) * (matrix_size * matrix_size));
            inserting_equations = 1;

            printf("Qtd matrix rows: %d\n", matrix_size);
          }

          else if (inserting_equations != 0)
          {
            int equation_values[matrix_size];

            char* equation_element = strtok(line, " ");

            while (equation_element != NULL) {
              if (isspace(*equation_element) == 0) { 
                int value;
                sscanf(equation_element, "%d", &value);
                matrix_values[matrix_values_atual_position] = value;
                equation_element = strtok(NULL, " ");
                matrix_values_atual_position++;
                printf("Value: %d\n", value);
              }
            }
          }

          
        }

        fclose(file);
      }
    }
    else
    {
      printf(
          "_______\n"
          "|     __|.---.-.--.--.-----.-----.\n"
          "|    |  ||  _  |  |  |__ --|__ --|\n"
          "|_______||___._|_____|_____|_____|\n\n");

      while (true)
      {
        printf("0 - Exit\n");
        printf("1 - Type in equations system\n\n");

        char option;

        printf("> Chose an option: ");
        scanf("%c", &option);

        if (option == '0')
          break;

        else if (option == '1')
        {
          int qtd_equations;

          printf("> Type in the number of equations: ");
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
              return 1;
            }

            char **equations = malloc(sizeof(char *) * qtd_equations);
            equations[0] = malloc(sizeof(char) * buffer_size * qtd_equations);
            for (int i = 0; i < qtd_equations; i++)
              equations[i] = equations[0] + i * buffer_size;

            while (remaining_equations > 0)
            {
              printf("> Type the %d° equation: ", remaining_equations);
              characters = getline(&buffer, &buffer_size, stdin);

              if (characters == -1)
              {
                printf("Error: Invalid equation, type again\n");
                remaining_equations++;
              }
              else
              {
                printf("Retrieved line of length %zu:\n", characters);
                printf("%s", buffer);
                equations[qtd_equations - remaining_equations] = buffer;
              }

              qtd_equations--;
            }
          }
        }

        else
          printf("\n> Invalid option!\n\n");
      }

      return 0;
    }
  }

  return 0;
}

void extract_coefficients() {}

void store_equation(int *matrix_values) {}

// https://stackoverflow.com/questions/10874374/passing-a-unknown-size-matrix-reference-to-a-c-function
// https://www.tutorialspoint.com/cprogramming/c_array_of_pointers.htm
