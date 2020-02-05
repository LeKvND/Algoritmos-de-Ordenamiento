#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define NUM_HILOS 5
//Compilar con gcc BucketSort.c -lpthread

int I=0;
int numerocubetas;

void swap(int *xp, int *yp){ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void bubbleSort(int arr[], int n){ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 
  
void printArray(int arr[], int size){ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

void *codigo_del_hilo(void *arreglo[]){
    //int i= 0; //posicion de esta cubeta
    int n = sizeof(arreglo)/sizeof(arreglo[0]); 
    bubbleSort(arreglo, n);
    printArray(arreglo,n);
    printf("Entraste al hilo bro");
    pthread_exit(arreglo);
}







     

void main(int argc, char *argv[]){
    int h;
    pthread_t hilos[NUM_HILOS];
    //int id[NUM_HILOS]={1,2,3,4,5};
    int error;
    int *salida;
    int arreglogrande[3500];
    int hora = time(NULL);  
    int tamanioarreglomini;

    for(int contador = 0; contador<3500; contador++){ //Generar numeros  
  
        arreglogrande[contador] = rand()%999;  
                 
    }  


    printf("Cuantas cubetas desea");
    scanf("%d",&numerocubetas);

    tamanioarreglomini=999/numerocubetas;
    int arreglosmini[numerocubetas][3500];
    
    for(int j=0;j<3500;j++){//recorre todo el arreglo grande

        for(int k=0;k<numerocubetas;k++){

        if(arreglogrande[j]<tamanioarreglomini*k){
            arreglosmini[k][/*la posicion*/]=arreglogrande[j]
        }


        }


    }





    for(h=0;h<numerocubetas;h++){
        error=pthread_create(&hilos[h],NULL,codigo_del_hilo,arreglosmini[/*mandar arreglo bidimensional de acuerdo a h*/]);
        if(error){
            fprintf(stderr,"Error %d; %s\n",error,strerror(error));
            exit(-1);
        }
    }
    for(h=0;h<numerocubetas;h++){
        error=pthread_join(hilos[h],(void**)&salida);
    }
    if(error)
        fprintf(stderr, "error %d: %s\n",error,strerror(error));
    else
    {
        printf("Hilo %d terminado\n",*salida);
    }
    

}