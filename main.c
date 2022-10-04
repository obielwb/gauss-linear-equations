#include<stdio.h>
#include<string.h>

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
				char c;

				int matrix_rows = 0;
				int row[3] = {};
				int cnt = -1;
				int qtd_added_rows = 0;

				while ((c = fgetc(input_file)) != EOF) {
					int value = (int)c;

					if (matrix_rows > 0) {
						if (cnt < 3) 
							row[++cnt] = (int)c;
						else {
							qtd_added_rows++;

							if (qtd_added_rows == matrix_rows) {
								// reset matrix rows size to read the next
								matrix_rows = 0;
							}
						}
					}
				}
				fclose(input_file);
			}
		}
		else {
		}
	}
	return 0;
}



void solve_equation(int *matrix, int num_of_rows) { }

// https://stackoverflow.com/questions/10874374/passing-a-unknown-size-matrix-reference-to-a-c-function
// https://www.tutorialspoint.com/cprogramming/c_array_of_pointers.htm		