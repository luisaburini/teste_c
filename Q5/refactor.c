#include <stdio.h>
#include <stdlib.h>

/**
 * Questão 5
 * 
 * Refatorar o código-fonte contido no arquivo questao_05.c deste repositório.
 * Serão considerados fatores como melhoria na eficiência, identação, e simplicidade.
 * O código deverá fazer um sorteio e a comparação com o “premio”. 
 * Se houver match , deverá ser exibida a saída da string “ganhou”.
 * 
*/

#define LINES  3
#define COLUMNS 5

int **create_slot(int **slot)
{
    int col = 0;
    int line = 0;

    slot = malloc (sizeof(int *) * COLUMNS);
    
    
    for(col = 0; col < COLUMNS; col++)
    {
        slot[col] =  malloc (sizeof (int) * LINES);
    }



    for (line = 0; line < LINES; line++)
    {
        printf("Insira os valores da linha %d:\n", (line + 1));
        for (col = 0; col < COLUMNS; col++)
        {
            scanf("%d", &slot[line][col]);
        }
    }

    return (slot);
}
  
int main (void)
{
    int prize[LINES][COLUMNS] =  {{1,0,0,0,1}, {0,1,0,1,0}, {0,0,1,0,0}};
    int **slot = 0;
    int lines = 0;
    int cols = 0;

    slot = create_slot(slot);
    int comp = slot[0][0];
    int count_prize = 0;
    while (lines < LINES && count_prize != COLUMNS)
    {
        while (cols < COLUMNS)
        {
            if (comp == slot[lines][cols] && prize[lines][cols])
            { 
                count_prize++;
            }
            cols++; 
        }
        cols = 0;
        lines ++;
        if (lines == LINES && count_prize != COLUMNS)
        {
            lines = 0;
            while (lines < LINES)
            {
                free (slot[lines++]);
            }
            free(slot);
            lines = 0;
            cols = 0;
            count_prize = 0;
            slot = create_slot(slot);
            comp = slot[0][0];
        }
    }
    
    printf ("Ganhou!\n");
    return (0);
}