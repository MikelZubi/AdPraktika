#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "lag.h"

extern Node lista[];
extern Node2* lista_kruskal;
extern struct Node2* Emaitza;

int searchElement(struct Node* head, int item)
{
    struct Node* current = head;  // Initialize current
    int index = 0;
    // traverse till then end of the linked list
    while (current != NULL)
    {
        if (current->data == item){
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

float mysearchElement(int item1, int item2)
{
    Node * current;
    int item;
    if(item1 > item2){
        current = &lista[item2];
        item = item1;
    }else{
        current = &lista[item1];
        item = item2;
    }
    
    int index = 0;
    // traverse till then end of the linked list
    while (current != NULL)
    {   
        if (current->data < item){
            current = current->next;
            index++;
            continue;
        }
        else if (current->data == item){
            return current->weight;
        }
        else if (current->data > item)
        {
            return __FLT_MIN__;
        }
        
    }


    
    return __FLT_MIN__;
}

void insert(struct Node** head, int data){

    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = *head;

    //changing the new head to this freshly entered node
    *head = newNode;
}

void push(struct Node2** head_ref, int A, int B, float weight)
{
    /* 1. allocate node */
    struct Node2* new_node = (struct Node2*) malloc(sizeof(struct Node2));
  
    /* 2. put in the data  */
    new_node->A  = A;
    new_node->B  = B;
    new_node->weight  = weight;
  
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);
  
    /* 4. move the head to point to the new node */
    (*head_ref)    = new_node;
}

void display(){
    //as linked list will end when Node is Null
    while(Emaitza!=NULL)
    {
        printf("%d %d %f \n",Emaitza->A,Emaitza->B,Emaitza->weight);
        Emaitza = Emaitza->next;
    }
}

void display2(){

    //as linked list will end when Node is Null
    while(lista_kruskal!=NULL)
    {
        printf("%d-tik %d-ra: %f-ko pisuarekin \n",lista_kruskal->A,lista_kruskal->B,lista_kruskal->weight);
        lista_kruskal = lista_kruskal->next;
    }
}

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct Node2** headRef)
{
    struct Node2* head = *headRef;
    struct Node2* a;
    struct Node2* b;
 
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}
 
/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
struct Node2* SortedMerge(struct Node2* a, struct Node2* b)
{
    struct Node2* result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
 
    /* Pick either a or b, and recur */
    if (a->weight >= b->weight) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}
 
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct Node2* source, struct Node2** frontRef, struct Node2** backRef)
{
    struct Node2* fast;
    struct Node2* slow;
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}



 
