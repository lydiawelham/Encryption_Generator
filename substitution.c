//#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef char string[4096];

int DuplicateCheck(string key);
int LetterCheck(string key);
void Encrypt(string plaintext, string key);

int main(int argc, char* argv[])
{
    //Checks whether key has been entered at command-line

    if (argc != 2)
    {
        printf("Enter key\n");
        return 1;
    }

    //Runs functions to check for key length, presence of duplicates and presence of non-letters

    int key_length = strlen(argv[1]);
    int duplicate = DuplicateCheck(argv[1]);
    int nonletter = LetterCheck(argv[1]);

    //Prints error message if key is not 26 characters long

    if (key_length != 26)
    {
        printf("Key must be 26 characters\n");
        return 1;
    }

    //Prints error message if key contains duplicate characters

    else if (duplicate > 0)
    {
        printf("Key must not contain duplicate characters\n");
        return 1;
    }

    //Prints error message if key contains non-alphabetical characters

    else if (nonletter > 0)
    {
        printf("Key must contain letters only\n");
        return 1;
    }

    //If key has none of the above errors, runs encryption

    else
    {
        //Collects plaintext from user to be encrypted

        string plaintext = "";
        printf("Plaintext: \n");
        fgets(plaintext,4096,stdin);

        //Runs encryption function using plaintext and key collected at command-line

        Encrypt(plaintext, argv[1]);

        //Prints a new line and closes programme

        printf("\n");
        return 0;

    }
}

int DuplicateCheck(string key)
{
    //Initialises value to be returned to main - 0 indicates no duplicates

    int duplicate = 0;

    for (int i = 0, key_length = strlen(key); i < key_length; i++)
    {
        //Loops for each character in key

        for (int j = i; j < key_length; j++)
        {
            if (key[i] == key[i + 1])
            {
                duplicate += 1;
            }
        }
    }
    return duplicate;
}

int LetterCheck(string key)
{
    //Initialises value to be returned to main - 0 indicates no non-alphabetical characters

    int nonletter = 0;

    //Loops through characters in key

    for (int i = 0, key_length = strlen(key); i < key_length; i++)
    {
        //Checks if alphabetical

        if (! isalpha(key[i]))
        {
            nonletter += 1;
        }

    }

    return nonletter;
}

void Encrypt(string plaintext, string key)
{
    int text_length = strlen(plaintext);

    char ciphertext[text_length + 1];

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                int n = plaintext[i] - 65;
                ciphertext[i] = toupper(key[n]);
            }
            else if (islower(plaintext[i]))
            {
                int m = plaintext[i] - 97;
                ciphertext[i] = tolower(key[m]);
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: %s", ciphertext);
}