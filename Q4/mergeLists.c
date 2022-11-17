#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Questão 04
 * Dada uma array de k , lista lincada “listas”, cada lista esta em ordem ascendente. 
 * Mergear as listas lincadas em uma única lista em ordem ascendente.
 * 
 * Input:
 * listas = [[1,3,8],[1,3,6],[8,9]] 
 * 
 * Output:
 * [1,1,3,3,6,8,8,9]
 * 
 * 
 * Referência:
 * listas = [ ] 
 * output = [ ]
 * listas = [ [ ] ] 
 * output = [ ]
 * struct ListaNode* mergeKListas(struct ListNode** listas, int listasSize){}
 * 
 * o programa foi compilado com a linha de comando
 *  gcc -g -o mergeLists mergeLists.c 
 * 
 * para usar invoque
 * ./mergeLists 
 * 
 * Digite na entrada padrão a lista desejada
 * 
 * A resposta será impressa na saída padrão
*/

struct ListNode 
{
    int data;
    struct ListNode* next;
};

#define MAX_LIST_LENGTH 256
#define MAX_NUMBER_LENGTH 10

void print_list(struct ListNode* node)
{
    printf("[");
    while(node != NULL)
    {
        if(node->next)
        {
            printf("%d,", node->data);
        }
        else
        {
            printf("%d", node->data);
        }
        node = node->next;
    }
    printf("]\n");
}

	
struct ListNode* sorted_merge(struct ListNode* a, struct ListNode* b)
{
	struct ListNode* result = NULL;

	//Base case to end search  
	if (a == NULL)
    {
        	return (b);
    }
	else 
    {
        if (b == NULL)
		{
            return (a);
        }
    }

	// Choose either a or b, and start recursion
	if (a->data <= b->data) 
    {
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else 
    {
		result = b;
		result->next = sorted_merge(a, b->next);
	}

	return result;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listSize)
{
    // repeat until only one list is left
	while (listSize != 0) 
    {
		int i = 0;
        int j = listSize;
		
		while (i < j) {
			// merge List i with List j and store it in List i
			lists[i] = sorted_merge(lists[i], lists[j]);

			// consider next pair
			i++;
            j--;

			// If all pairs are merged, update last
			if (i >= j)
            {
                listSize = j;
            }
		}
	}

	return lists[0];
}

struct ListNode* create_new_node(int data)
{
	struct ListNode* temp = (struct ListNode*)malloc(sizeof(struct ListNode));
	temp->data = data;
	temp->next = NULL;
	return temp;
}


void append_new_node_to_list(int newValue, struct ListNode** newList)
{
    if(*newList == NULL)
    {
        *newList = create_new_node(newValue);
        return;
    }
    else
    {
        struct ListNode* lastNode = *newList;
        while(lastNode != NULL && lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = create_new_node(newValue);
    }

}

void append_new_list_to_unmerged_list(struct ListNode* newListHead, struct ListNode* unmergedList[], int k)
{   
    unmergedList[k]->data = newListHead->data;
    unmergedList[k]->next = newListHead->next;
}

void create_list_of_list_nodes(struct ListNode* list[], int size)
{
    for(int i=0; i<size; i++)
    {
        // create new dummy nodes
        list[i] = create_new_node(0);
    }
}

void get_list_from_string(char strList[], struct ListNode* unmergedList[])
{
    int listIndex = 0;
    int j = 0;
    for(int i = 1; i<strlen(strList);i++)
    {
        int k = 0;
        // beginning of a new list 
        if(strList[i] == '[')
        {
            struct ListNode* head = NULL;

            i++;
            
            for(j = i ; strList[j] != ']' && j < strlen(strList);)
            {
                int number = 0;
                char numberStr[MAX_NUMBER_LENGTH] = {0};
                int strIndex = 0;

                for(k = j; isdigit(strList[k]) && k < strlen(strList); k++)
                {
                    numberStr[strIndex] = strList[k];
                    strIndex++;
                }
                number = atoi(numberStr);

                append_new_node_to_list(number, &head);
                
                while(k < strlen(strList) && !isdigit(strList[k]) && strList[k] != ']')
                {
                    k++;
                }
                j = k;
            }

            // new list ended, must append it to unmergedList
            append_new_list_to_unmerged_list(head, unmergedList, listIndex);
            i = j;
            listIndex++;
        }
    }
}

int get_number_of_linked_lists(char strList[])
{
    int k = 0;
    int size = strlen(strList);

    for(int i=0; i<size; i++)
    {
        if(strList[i] == '[')
        {
            k++;
        }
    }

    // remove outer [ 
    return k-1;
}

void freeAll(struct ListNode** list, int size)
{
    for(int i=0; i<size; i++)
    {
        free(list[i]);
    }
}

int main()
{
    char strList[MAX_LIST_LENGTH] = {0};
    fgets(strList, MAX_LIST_LENGTH, stdin);
    
    //k is for Number of linked lists and n for Number of elements in each list
	int k = get_number_of_linked_lists(strList); 
    
    struct ListNode* unmergedLists[k];
    create_list_of_list_nodes(unmergedLists, k);

    get_list_from_string(strList, unmergedLists);

	// Merge all lists
	struct ListNode* head = mergeKLists(unmergedLists, k - 1);

	print_list(head);

    freeAll(unmergedLists, k);

	return 0;
}