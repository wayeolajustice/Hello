#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    if (score1 == score2){

        printf("Tie! \n");
    }

    else if (score1 > score2){

        printf("Player1 win \n");
    }

    else
    {
        printf("Player2 win \n");
    }


    return (0);
}

int compute_score(string word)
{
    int j = 0;
    int count = 0;

    while (word[j] != '\0')
    {
        for (int i = 0; i < 26; i++)
        {
            char letter = alphabet[i];

            int point = POINTS[i];



            if (toupper(word[j]) == letter)
            {

                count+=point;
                }
            }
            
        j++;
    }

    return count;
}
    