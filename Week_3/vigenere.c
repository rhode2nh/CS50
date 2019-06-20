#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int shift(char c);

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
    // Stores the unencrypted text given by the user
    string plaintext;
    
    /* The user must put only one command line argument. */
    if (argc != 2)
    {
        printf("Usage: ./vigenere key\n");
        return 1;
    }
    
    /* Checks if the argument given is a number. 
     * Prints an error otherwise. */
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./vigenere key\n");
            return 1;
        }
    }

    // Get the plaintext from the user.
    plaintext = get_string("plaintext: ");
    
    // Store the user's key into a variable to use as a cipher.
    char *key = argv[1];
    
    // Used to store the current character to enciphere with.
    int encipher;
    
    /* Used to keep track of enciphering characters to ensure they do not
     * increment to the next number unless the plaintext character is an alphabetic
     *  character. */
    int j = 0;

    /* Iterates over every character in the plaintext and checks whether or not
     * if the current character is an alphabetic character. */
    for (int i = 0; i < strlen(plaintext); i++)
    {
        /* Ignore characters that are not alphabetic. */
        if (isalpha(plaintext[i]))
        {   
            /* Store the current character to use as a cipher. We mod the length
             * of the user's key with j to ensure that we can cycle back to the first
             * character in the user's key. */
            encipher = shift(*(key + (j % strlen(key))));
            
            // Used for comparison of ASCII values.
            unsigned char cipher_char = plaintext[i] + encipher;

            /* Checks if the current character is uppercase. */
            if (plaintext[i] >= ASCII_UPPER_A && plaintext[i] <= ASCII_UPPER_Z)
            {
                /* Checks if the character added to the encipher is a uppercase character. */
                if (plaintext[i] + encipher < ASCII_UPPER_A || plaintext[i] + encipher > ASCII_UPPER_Z)
                {
                    // Normalize the character by cyling back through the set of uppercase characters.
                    cipher_char = ((plaintext[i] + encipher) % UPPER_BOUND) + ASCII_UPPER_A;                    
                }
            }
            /* Checks if the current character is lowercase. */
            else if (plaintext[i] >= ASCII_LOWER_A && plaintext[i] <= ASCII_LOWER_Z)
            {
                /* Checks if the character added to the encipher is a lowercase character. */
                if (plaintext[i] + encipher < ASCII_LOWER_A || plaintext[i] + encipher > ASCII_LOWER_Z)
                {
                    // Normalize the character by cyling back through the set of lowecase characters.
                    cipher_char = ((plaintext[i] + encipher) % LOWER_BOUND) + ASCII_LOWER_A;
                }
            }
            plaintext[i] = cipher_char;
            j++;
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}

/* This function normalizes characters and returns its corresponding
 * index in the ASCII alphabet */
int shift(char c)
{
    /* For uppercase characters. */
    if (c >= ASCII_UPPER_A && c <= ASCII_UPPER_Z)
    {
        c = c - ASCII_UPPER_A;
    }
    
    /* For lowercase characters. */
    else if (c >= ASCII_LOWER_A && c <= ASCII_LOWER_Z)
    {
        c = c - ASCII_LOWER_A;
    }
    return (int) c;
}
