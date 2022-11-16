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
 *  gcc mergeLists.c -o mergeLists
 * 
 * para usar invoque
 * ./mergeLists 
 * 
 * Digite na entrada padrão a lista desejada
 * 
 * A saída será impressa na saída padrão
*/

struct ListNode 
{
    int data;
    struct ListNode* next;
};

#define MAX_LIST_LENGTH 256
#define MAX_NUMBER_LENGTH 10

void printList(struct ListNode* node)
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
    printf("]");
}

	
struct ListNode* sortedMerge(struct ListNode* a, struct ListNode* b)
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
		result->next = sortedMerge(a->next, b);
	}
	else 
    {
		result = b;
		result->next = sortedMerge(a, b->next);
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
			lists[i] = sortedMerge(lists[i], lists[j]);

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

// function to create a new node.
struct ListNode* createNewNode(int data)
{
	struct ListNode* temp = (struct ListNode*)malloc(sizeof(struct ListNode));
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void appendNewNodeToList(int newValue, struct ListNode** newList)
{
    if(*newList == NULL)
    {
        *newList = createNewNode(newValue);
        return;
    }
    else
    {
        struct ListNode* lastNode = *newList;
        while(lastNode != NULL && lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = createNewNode(newValue);
    }

}

void appendNewListToUnmergedList(struct ListNode* newListHead, struct ListNode* unmergedList[], int k)
{   
    unmergedList[k]->data = newListHead->data;
    unmergedList[k]->next = newListHead->next;
}

void createListOfListNodes(struct ListNode* list[], int size)
{
    for(int i=0; i<size; i++)
    {
        // create new dummy nodes
        list[i] = createNewNode(0);
    }
}

void getListFromString(char strList[], struct ListNode* unmergedList[])
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

                appendNewNodeToList(number, &head);
                
                while(k < strlen(strList) && !isdigit(strList[k]) && strList[k] != ']')
                {
                    k++;
                }
                j = k;
            }

            // new list ended, must append it to unmergedList
            appendNewListToUnmergedList(head, unmergedList, listIndex);
            i = j;
            listIndex++;
        }
    }
}

int getNumberOfLinkedLists(char strList[])
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

int main()
{
    char strList[MAX_LIST_LENGTH] = {0};
    fgets(strList, MAX_LIST_LENGTH, stdin);
    
    //k is for Number of linked lists and n for Number of elements in each list
	int k = getNumberOfLinkedLists(strList); 
    
    struct ListNode* unmergedLists[k];
    createListOfListNodes(unmergedLists, k);

    getListFromString(strList, unmergedLists);

	// Merge all lists
	struct ListNode* head = mergeKLists(unmergedLists, k - 1);

	printList(head);

	return 0;
}