#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_LENGTH 32000
#define NUM_LINES 100000
#define MIN_LINE 5

int get_output_name (int file_counter, char output_name[64]) {
	sprintf(output_name, "c://adata/parts/output%d.json", file_counter);
	
	return (file_counter + 1);
}

int main()
{
		FILE * source = NULL, * output = NULL;
		char buf[LINE_LENGTH], output_name[64];
		int line_counter = 0, file_counter = 0;

		source = fopen("c://adata/adata.json", "r");
		
		if (!source) {
			printf("ERROR READING FILE\n");
			return 1;
		}

		while (fgets(buf, LINE_LENGTH, source) != NULL) {
			if (strlen(buf) > MIN_LINE) {
				if ((line_counter % NUM_LINES) == 0) {
					file_counter = get_output_name(file_counter, output_name);
					printf("Creating file: %s\n", output_name);
					output = fopen(output_name, "a+");
					fprintf(output, "[\n");
				}
				
				if ((line_counter % NUM_LINES) == (NUM_LINES - 1)) {
					printf("File completed; %d entries processed.\n\n", (line_counter % NUM_LINES) + 1);
					if(buf[strlen(buf) - 2] == ',') {
						buf[strlen(buf) - 2] = '\0';
					}
					fputs(buf, output);
					fprintf(output, "\n]");
					fclose(output);
					output = NULL;
				} else {
					fputs(buf, output);
				}
				
				line_counter ++;
			}
		}

		if (output) {
			printf("File completed; %d entries processed.\n\n", (line_counter % NUM_LINES));
			fputs(buf, output);
			fclose(output);
			output = NULL;
		}

		source = NULL;
		fclose(source);
		return 0;
}