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
 *  gcc -g -o redGradient redGradient.c 
 * 
 * para usar invoque
 * ./redGradient cor_inicial cor_final nro_steps
 * 
 * A resposta será impressa na saída padrão
*/

#define RED     0XFF0000


__uint32_t convert_string_to_uint32(char str[])
{
    __uint32_t converted_color = strtoul(str, NULL, 16);
    return converted_color;
}

int isolate_red_from_color(int color)
{
    return color & RED;
}

void print_red_gradient(char initial_color[], char final_color[], int steps)
{
    __uint32_t initial_color_code = convert_string_to_uint32(initial_color);
    __uint32_t initial_red = isolate_red_from_color(initial_color_code);

    __uint32_t final_color_code = convert_string_to_uint32(final_color);
    __uint32_t final_red = isolate_red_from_color(final_color_code);

    __uint32_t increment = (final_red - initial_red) / steps;

    for(int i=0; i<steps; i++)
    {
        initial_color_code = initial_color_code + increment;
        printf("Color[%d] = 0x%X\n", i, initial_color_code);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        perror("Parameters error! Usage: redGradient initial_color final_color number_of_steps");
        exit(-1);
    }

    char initial_color[10] = {0};
    strcpy(initial_color, argv[1]);

    char final_color[10] = {0};
    strcpy(final_color, argv[2]);

    int steps = atoi(argv[3]);
    
    print_red_gradient(initial_color, final_color, steps);
}