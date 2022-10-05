#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

#define MAX 500

int *matrices[MAX];

int main(int argc, char* argv[]) {
	if (argc > 2) {
		printf("Too many arguments supplied.");
	}
	else {
		if (argc == 2) {
			if (strlen(argv[1]) > 4) {
				if (strcmp(argv[1] + strlen(argv[1]) - 4, ".txt") != 0) {
					printf("Error: File is not a .txt file\n");
					return 1;
				}
			}
			else {
				printf("Error: File is not a .txt file\n");
				return 1;
			}


			FILE* input_file = fopen(argv[1], "r");

			if (input_file == NULL) {
				printf("Error opening file\n");
				return 1;
			}
			else {
				char *line = NULL;
				size_t len = 0;
				ssize_t line_length;
				int* matrix_values;
				int in_insert_equation_mode = 0; // false

				while ((line_length = getline(&line, &len, input_file)) != -1) {
					printf("Retrieved line of length %zu:\n", line_length);
    			printf("%s", line);

					if (line_length < 2) {
						in_insert_equation_mode = 0;
						if (matrix_values)
							free(matrix_values);
					}

					if (line_length >= 6 && in_insert_equation_mode != 0) {
						for (int i = 0; i < 5; i++) {
							if (isspace(line[i]) == 0) {
								int value = (int)line[i];
								matrix_values[i] = value;
							}
						}
					}

					if (line_length == 2 && in_insert_equation_mode == 0) {
						int qtd_matrix_rows = (int)line[0];
						matrix_values = (int*)malloc(sizeof(int)*(qtd_matrix_rows*3));
						in_insert_equation_mode = 1; // true
					}
				}

				fclose(input_file);

				if (line)
					free(line);
			}
		}
		else {
		}
	}
	return 0;
}

void make_equation(char *matrix_values) {

}

void solve_equation(int *matrix, int num_of_rows) { }

// https://stackoverflow.com/questions/10874374/passing-a-unknown-size-matrix-reference-to-a-c-function
// https://www.tutorialspoint.com/cprogramming/c_array_of_pointers.htm		