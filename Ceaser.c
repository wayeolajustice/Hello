#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool only_digits(char* string);

int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (argc == 1)
    {
        return 2;
    }
    else if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    char string[10];
    printf("Plaintext: ");
    scanf("%s", string);
    printf("Ciphertext: ");

    for (int j = 0; j < strlen(string); j++){
        printf("%c", (string[j]+key)%26);
    }
    printf("\n");

    return 0;
}

bool only_digits(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (!isdigit(string[i]))
        {
            return false;
        }
    }
    return true;
}