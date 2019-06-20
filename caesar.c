#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Constants that are used to determine if the encoded number is 
// within the bounds of the ASCII alphabetic characters.
const int ASCII_LOWER_A = 97;
const int ASCII_UPPER_A = 65;
const int ASCII_LOWER_Z = 122;
const int ASCII_UPPER_Z = 90;
const int UPPER_BOUND = 91;
const int LOWER_BOUND = 123;

// Size of the alphabet.
const int ALPHA_LEN = 26;

int main(int argc, string argv[])
{
    int key;
    string plaintext;
    /* The user must put only one command line argument. */
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    /* Checks if the argument given is a number. 
     * Prints an error otherwise. */
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            printf("%c\n", argv[1][i]);
            return 1;
        }
    }
    
    // Convert the argument into an integer.
    // Normalize the key to be equal to the size of the alphabet.
    key = strtol(argv[1], NULL, 10) % ALPHA_LEN;
    
    // Get the plaintext from the user.
    plaintext = get_string("plaintext: ");
    
    /* Iterates over every character in the plaintext and checks whether or not
     * if the current character is an alphabetic character. */
    for (int i = 0; i < strlen(plaintext); i++)
    {
        /* Ignore characters that are not alphabetic. */
        if (isalpha(plaintext[i]))
        {
            // Used for comparison of ASCII values.
            unsigned char cipher_char = plaintext[i] + key;
            
            /* Statements that cause characters that have values greater than 
             * their alphabetic set to cycle back to the start of their set. */
            if (cipher_char > ASCII_UPPER_Z && cipher_char < ASCII_LOWER_A)
            {
                plaintext[i] = ((cipher_char) % UPPER_BOUND) + ASCII_UPPER_A;
            }
            else if (cipher_char > ASCII_LOWER_Z)
            {
                plaintext[i] = ((cipher_char) % LOWER_BOUND) + ASCII_LOWER_A;
            }
            else
            {
                plaintext[i] = cipher_char;
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}
