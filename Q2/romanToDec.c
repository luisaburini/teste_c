#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Questão 02
 * Desenvolver um programa que receba via teclado um número romano, 
 * converta o mesmo em número decimal e apresente em tela o resultado.
 * Considerar como números validos:
 *  I = 1, V = 5 , X = 10, L = 50, C = 100, D = 500, M = 1000
 * 
 * Exemplos de referência de saída :
 *  IV = 4 , VI = 6 , XII = 12 , IX =9 , VIII = 8, MDCDLXXIV = 1974.
 * 
 * o programa foi compilado com a linha de comando
 *  gcc -g -o romanToDec romanToDec.c 
 * 
 * para usar invoque
 * ./romanToDec
 * 
 * Digite na entrada padrão o número romano para ser convertido em decimal
 * 
 * A resposta será impressa na saída padrão
*/

int get_decimal_value(char roman)
{
    int decimal = 0;

    switch (roman)
    {
    case 'I':
        decimal = 1;
        break;
    case 'V':
        decimal = 5;
        break;
    case 'X':
        decimal = 10;
        break;
    case 'L':
        decimal = 50;
        break;
    case 'C':
        decimal = 100;
        break;
    case 'D':
        decimal = 500;
        break;
    case 'M':
        decimal = 1000;
        break;
    default:
        printf("Not a roman\n");
        exit(-1);
        break;
    }

    return decimal;
}

int convert_roman_to_decimal(char roman[])
{
    int decimal = 0;

    for(int i=0; i<strlen(roman); i++)
    {
        int current_decimal_value = get_decimal_value(roman[i]);

        // make sure rightDecimalValue is within bounds
        if(i+1 < strlen(roman))
        {
            int right_decimal_value = get_decimal_value(roman[i+1]);

            if(current_decimal_value >= right_decimal_value)
            {
                decimal = decimal + current_decimal_value;
            }
            else
            {
                decimal = decimal + right_decimal_value - current_decimal_value;
                i++;
            }
        }
        else
        {
            decimal = decimal + current_decimal_value;
        }
    }

    return decimal;
}


int main()
{
    char roman[128] = {0};

    scanf("%s", roman);

    printf("Decimal: %d\n", convert_roman_to_decimal(roman));

}