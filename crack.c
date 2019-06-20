#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Stores the key for crypt().
    char key[2];
    
    // Contains all upper/lower case alphabetic characters.
    char alphabet[53] = {'\0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    
    /* Return an error if there is not only one command line argument. */
    if (argc != 2) 
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    // Grab the key from the hash. Used as the key from crypt()
    key[0] = argv[1][0];
    key[1] = argv[1][1];
    
    /* Initialize all characters to null so that when a match is found, 
    the compiler will end at the first null character it detects. */
    char password[6] = "\0\0\0\0\0\0"; 
    
    // Hash from argument. Used for comparing.
    char *hash = argv[1];

    /* Iterate through all of the permutaions of a 5 character string. */
    for (int a = 0; a < sizeof(alphabet); a++)
    {
        password[4] = alphabet[a];
        for (int b = 0; b < sizeof(alphabet); b++)
        {
            password[3] = alphabet[b];
            for (int c = 0; c < sizeof(alphabet); c++)
            {
                password[2] = alphabet[c];
                for (int d = 0; d < sizeof(alphabet); d++)
                {
                    password[1] = alphabet[d];
                    for (int e = 0; e < sizeof(alphabet); e++)
                    {
                        password[0] = alphabet[e];
                        
                        // Brute hash used to compare with the user hash.
                        if (strcmp(hash, crypt(password, key)) == 0)
                        {
                            printf("%s\n", password);
                            return 0;
                        }
                    }
                }
            }
        }        
    }
}
