#include <stdio.h>

int main() {
    FILE *fp;

    // Open the file in write mode
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    // Write text to the file
    fprintf(fp, "Hello, this is a test.\n");
    fprintf(fp, "Writing some text to a file using a C program.\n");

    // Close the file
    fclose(fp);

    printf("Text has been written to output.txt\n");
    return 0;
}
