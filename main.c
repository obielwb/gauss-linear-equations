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
        size_t line_length;
        int *equation_values;
        boolean inserting_equations = false;

        // while ((line_length = getline(&line, &length, file)) != -1) {
        // TODO: read line properly
        while (fgets(line, sizeof(line), file) != NULL)
        {
          printf("Retrieved line of length %zu:\n", strlen(line));
          printf("%s", line);

          if (line_length < 2)
          {
            // store_equation(equation_values);
            for (int i = 0; i < sizeof(equation_values); i++)
            {
              printf("%d", equation_values[i]);
            }

            inserting_equations = 0;
            if (equation_values)
              free(equation_values);
          }

          else if (line_length >= 6 && inserting_equations != 0)
          {
            for (int i = 0; i < 5; i++)
            {
              if (isspace(line[i]) == 0)
              {
                int value = (int)line[i];
                equation_values[i] = value;
              }
            }
          }

          else if (line_length == 2 && inserting_equations == 0)
          {
            int qtd_matrix_rows = (int)line[0];
            equation_values = (int *)malloc(sizeof(int) * (qtd_matrix_rows * 3));
            inserting_equations = true;
          }
        }

        fclose(file);

        if (line)
          free(line);
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
            const int remaining_equations = qtd_equations;

            const size_t buffer_size = 32;
            size_t characters;
            char *buffer = (char *)malloc(buffer_size * sizeof(char));

            char **equations = malloc(sizeof(char *) * qtd_equations);
            v[0] = malloc(sizeof(char) * buffer_size * qtd_equations);
            for (int i = 0; i < qtd_equations; i++)
              equations[i] = v[0] + i * buffer_size;

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
                v[qtd_equations - remaining_equations] = buffer;
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

void store_equation(int *equation_values) {}

// https://stackoverflow.com/questions/10874374/passing-a-unknown-size-matrix-reference-to-a-c-function
// https://www.tutorialspoint.com/cprogramming/c_array_of_pointers.htm
