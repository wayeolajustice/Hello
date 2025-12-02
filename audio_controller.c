#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 44;

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL) {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL) {
        printf("Could not open output file.\n");
        fclose(input);
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Process audio samples
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input)) {
        // Adjust volume of each sample
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
