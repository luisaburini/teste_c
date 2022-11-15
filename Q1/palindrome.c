#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Questão 01
 * Desenvolver um algoritmo para encontrar o maior palíndromo
 * (trecho que lido da esquerda pra direita e vice-versa mantém 
 * sequência em ambos os lados)
 * A sequência deve ser lida a partir de um arquivo de texto.
 * O código deve apresentar a quantidade de letras do maior palíndomo 
 * dentro de cada string e zero caso não encontre.
 * 
 * o programa foi compilado com a linha de comando
 *  gcc palindrome.c -o palindrome
 * 
 * para usar invoque
 * ./palindrome nome-do-arquivo.txt
 * 
 * A saída será impressa 
*/

#define MAX_LINE_LENGTH 256

void revertString(char str[], char reverse[], int size)
{
    for(int i=0; i < size; i++)
    {
        reverse[i] = str[size-i-1];
    }
}

/**
 * Get Palindrome Length
 *  returns the string length if palindrome, otherwise 0
*/
int getPalindromeLength(char* str, int start, int size)
{
    char* string = malloc(strlen(str) - start);
    memset(string, 0x00, size);
    strcpy(string, str + start);
    string[size] = '\0';

    char* stringReverse = malloc(size);
    memset(stringReverse, 0x00, size);
    // if cannot find any palindrome,
    // must return 0
    __uint8_t sizeToReturn = 0;
    
    revertString(string, stringReverse, size);
    
    if(strcmp(string, stringReverse) == 0)
    {
        sizeToReturn = size;
    }

    free(stringReverse);
    free(string);

    return sizeToReturn;
}

/**
 * Search for palindromes in the line
*/
void checkPalindromesInLine(char line[])
{
    int i = strlen(line);
    int size = strlen(line);
    int start = 0;
    int longestPalindrome = 0;
    
    if(size < 2)
    {
        printf("1\n");
    }


    for(; i > 0 ; i--)
    {
        for(start = 0; start < size && i > 0 ; start++)
        {
            int palindromeLength = getPalindromeLength(line, start, i);

            if(palindromeLength > longestPalindrome)
            {
                longestPalindrome = palindromeLength;
            }
        }
    }

    printf("Longest Palindrome: %d\n", longestPalindrome);

}


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        perror("Parameters error! Usage: palindrome filename");
        exit(-1);
    }

    FILE* file = fopen(argv[1], "r");

    if(file == NULL)
    {
        perror("Unable to open file.");
        exit(-1);
    }

    char line[MAX_LINE_LENGTH];

    while(fgets(line, sizeof(line), file))
    {
        checkPalindromesInLine(line);
    }

    fclose(file);
}

