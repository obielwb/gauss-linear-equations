#include<stdio.h>
#include<string.h>

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

				while ((c = fgetc(input_file)) != EOF) {
					printf("%c", c);
				}
				fclose(input_file);
			}
		}
		else {
		}
	}
	return 0;
}


// method - make method to store equation in array