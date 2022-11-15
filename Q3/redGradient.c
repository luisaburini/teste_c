#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Questão 03
 * Considerando que o espaço de cor RGB pode ser representada por um uint32, 
 * onde os 8 primeiros bits menos significantes representam o canal azul, 
 * seguidos por 8 bits que representam a claridade de verde, que por sua vez 
 * são seguidos de 8 bits que nos dizem a intensidade do vermelho. 
 * Os 8 bits mais significantes são interpretados como o canal Alpha, 
 * ou seja, a transparência.
 * Podemos, portanto, representar cada canal de cor por um par hexadecimal, 
 * de 00 a FF. Conseguimos definir então que:
 * 
 *  0x0 é equivalente a preto, já que a luminosidade de todos os canais está em 0;
 *  0xFF (255) nos daria o azul mais brilhante;
 *  0xFF00 (65280) nos daria o máximo de verde possivel;
 *  0xFF0000 (16711680) nos daria o vermelho mais vivo;
 * 
 * Crie com base nisto uma função que gradativamente mude e printe a cor vermelha
 *  de r_inicial para r_final em um certo numero de passos;
 * 
 * Referência de saída:
 * cor_inicial = 0x00001A; 
 * cor_final = 0xFF001A; 
 * steps = 3;
 * output_esperado: 0x55001A\n 0xAA001A\n 0XFF001A\n
 * 
 * o programa foi compilado com a linha de comando
 *  gcc redGradient.c -o redGradient
 * 
 * para usar invoque
 * ./redGradient cor_inicial cor_final nro_steps
 * 
 * A saída será impressa na saída padrão
*/

#define RED     0XFF0000


__uint32_t convertStringToUint32(char str[])
{
    __uint32_t convertedColor = strtoul(str, NULL, 16);
    return convertedColor;
}

int isolateRedFromColor(int color)
{
    return color & RED;
}

void printRedGradient(char initialColor[], char finalColor[], int steps)
{
    __uint32_t initialColorCode = convertStringToUint32(initialColor);
    __uint32_t initialRed = isolateRedFromColor(initialColorCode);

    __uint32_t finalColorCode = convertStringToUint32(finalColor);
    __uint32_t finalRed = isolateRedFromColor(finalColorCode);

    __uint32_t increment = (finalRed - initialRed) / steps;

    for(int i=0; i<steps; i++)
    {
        initialColorCode = initialColorCode + increment;
        printf("Color[%d] = 0x%X\n", i, initialColorCode);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        perror("Parameters error! Usage: redGradient initial_color final_color number_of_steps");
        exit(-1);
    }

    char initialColor[10] = {0};
    strcpy(initialColor, argv[1]);

    char finalColor[10] = {0};
    strcpy(finalColor, argv[2]);

    int steps = atoi(argv[3]);
    
    printRedGradient(initialColor, finalColor, steps);
}