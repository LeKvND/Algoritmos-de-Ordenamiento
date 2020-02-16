#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define NUM_HILOS 5
pthread_mutex_t lock; 
//Compilar con gcc cubetas.c -lpthread

struct Node { 
    int data; 
    struct Node* next; 
    struct Node* prev; 
}; 
        
    int id[10000];
void push(struct Node** head_ref, int new_data){ 
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
  
    new_node->data = new_data; 
  
    new_node->next = (*head_ref); 
    new_node->prev = NULL; 
  
    if ((*head_ref) != NULL) 
        (*head_ref)->prev = new_node; 

    (*head_ref) = new_node; 
} 
  
void insertAfter(struct Node* prev_node, int new_data) 
{ 

    if (prev_node == NULL) { 
        printf("the given previous node cannot be NULL"); 
        return; 
    } 
  
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
  
    new_node->data = new_data; 
    new_node->next = prev_node->next; 
    prev_node->next = new_node; 
    new_node->prev = prev_node; 
  
    if (new_node->next != NULL) 
        new_node->next->prev = new_node; 
} 
  
void append(struct Node** head_ref, int new_data) 
{ 
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
  
    struct Node* last = *head_ref;
  
    new_node->data = new_data; 
  
    new_node->next = NULL; 

    if (*head_ref == NULL) { 
        new_node->prev = NULL; 
        *head_ref = new_node; 
        return; 
    } 
  
    while (last->next != NULL) 
        last = last->next; 
  
    last->next = new_node; 
  
    new_node->prev = last; 
  
    return; 
} 
  
void printList(struct Node* node) 
{ 
    struct Node* last; 
    while (node != NULL) { 
        printf(" %d ", node->data); 
        last = node; 
        node = node->next; 
    } 
  

} 

int I=0;

/* function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b) 
{ 
    int temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
} 

void bubbleSort(struct Node *start) 
{ 
    int swapped, i; 
    struct Node *ptr1; 
    struct Node *lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            if (ptr1->data > ptr1->next->data) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 
  




void *codigo_del_hilo(struct Node* arreglo){


    bubbleSort(arreglo); 
    pthread_exit(arreglo);
}







     

void main(int argc, char *argv[]){
    
    int h;


    int error;
    int *salida;
    time_t t;
    srand((unsigned) time(&t));
    struct Node* principal = NULL; 
    int numero=0;

    for( int i = 0 ; i < 3500 ; i++ ) {     //Generacion de numeros aleatorios
        numero=rand() % 1000;
        //printf("%d, ", numero);
        append(&principal, numero);
    }
    int numerocubetas=0;
    printf("¿Cuantas cubetas desea? ");
    scanf("%d",&numerocubetas);
    struct Node* arreglo[numerocubetas];
    
    printf("\n\n\t\t\t\t\t-----------Estos son los numeros que se generaron----------\n\n");
    printList(principal);
    printf("\n\n\t\t\t\t\t---------------------------------------------------Soy un separador---------------------------------------------------\n\n");
    for(int i=0;i<numerocubetas;i++)
        id[i]=i;

    pthread_t hilos[numerocubetas];

    for(int i=0;i<numerocubetas;i++) //Declaramos vacio el arreglo de listas
        arreglo[i]=NULL;

    int division=1000/numerocubetas;

    int restante=1000-(division*numerocubetas);


    struct Node* last; 
    
    while (principal != NULL) {                      //recorremos toda la lista
        for(int i=1;i<=numerocubetas;i++){
            if(i==numerocubetas){
                if(principal->data >= ((division*(i-1))+1) && principal->data <= (division*i)+restante){
                    append(&arreglo[i-1],principal->data);
                }
            }
            else{            
                if(principal->data >= ((division*(i-1))+1) && principal->data <= division*i){
                    append(&arreglo[i-1],principal->data);
                }
            }

        }
        last = principal; 
        principal = principal->next; 
    } 


    printf("\n\n\t\t\t\t\t-------------------------------------------------Estos son los numeros que hay en cada cubeta---------------------------------------------------\n\n");

    for(int i=0;i<numerocubetas;i++){
        printf("\n\nEn la cubeta %d, hay estos numeros:\n\n",i);
        printList(arreglo[i]);
    }










for(h=0;h<numerocubetas;h++){
    error=pthread_create(&hilos[h],NULL,codigo_del_hilo,arreglo[h]);
    if(error){
        fprintf(stderr,"Error %d; %s\n",error,strerror(error));
        exit(-1);
    }
}

for(h=0;h<numerocubetas;h++){
    error=pthread_join(hilos[h],(void**)&salida);

if(error)
    fprintf(stderr, "error %d: %s\n",error,strerror(error));

}
    
    printf("\n\n\t\t\t\t\t---------------------------------------------Estos son los numeros ya ordenados por cubeta---------------------------------------------------\n\n");
for(int i=0;i<numerocubetas;i++){
    printf("\n\nEstos son los numeros de la cubeta %d\n\n",i);
    printList(arreglo[i]);
}
printf("\n\n\n\n\t\t\t\t\t---------------------------------------------Estos son los numeros ya ordenados---------------------------------------------------\n\n");

for(int i=0;i<numerocubetas;i++){
    printList(arreglo[i]);
}

}


