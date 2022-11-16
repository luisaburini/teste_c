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
 *  gcc -g -o palindrome palindrome.c 
 * 
 * para usar invoque
 * ./palindrome nome-do-arquivo.txt
 * 
 * A resposta será impressa na saída padrão
*/

#define MAX_LINE_LENGTH 256

void revert_string(char str[], char reverse[], int size)
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
int get_palindrome_length(char* str, int start, int size)
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
    
    revert_string(string, stringReverse, size);
    
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
void check_palindromes_in_line(char line[])
{
    int i = strlen(line);
    int size = strlen(line);
    int longest_palindrome = 0;
    
    if(size < 2)
    {
        printf("1\n");
    }


    for(; i > 0 ; i--)
    {
        for(int start = 0; start < size ; start++)
        {
            int palindrome_length = get_palindrome_length(line, start, i);

            if(palindrome_length > longest_palindrome)
            {
                longest_palindrome = palindrome_length;
            }
        }
    }

    printf("Longest Palindrome: %d\n", longest_palindrome);

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
        check_palindromes_in_line(line);
    }

    fclose(file);
}

