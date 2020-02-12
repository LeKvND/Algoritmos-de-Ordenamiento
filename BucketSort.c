#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define NUM_HILOS 5
pthread_mutex_t lock; 
//Compilar con gcc BucketSort.c -lpthread

int I=0;
int numerocubetas;
int tamanios[100];
int contador=0;


void swap(int* a, int* b){ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  

void bubbleSort(int arr[], int n){ 
   int i, j; 
   for (i = 0; i < n-1; i++){       
    
       for (j = 0; j < n-i-1; j++){
           if (arr[j] > arr[j+1]){
              swap(&arr[j], &arr[j+1]); 
            }
        }
   }
} 
  

void *codigo_del_hilo(void *arreglo){
    
    int size=0;

    pthread_mutex_lock(&lock);
    printf("\n\nHilo %d iniciado",contador);
    printf("\n\nNumero de elementos que tiene la canasta %d: %d",contador,tamanios[contador]);
    size = tamanios[contador];
    contador++;
    pthread_mutex_unlock(&lock);
 
    bubbleSort(arreglo, size);
    pthread_exit(arreglo);

}







     

void main(int argc, char *argv[]){
    
    int h;
    pthread_t hilos[NUM_HILOS];
    int error;
    int *salida;
    int arreglogrande[3500];
    int hora = time(NULL);  
    int tamanioarreglomini;

    for(int contador2 = 0; contador2<3500; contador2++){ //Generar numeros  
  
        arreglogrande[contador2] = rand()%999;  
                 
    }  


    printf("Cuantas cubetas desea: ");
    scanf("%d",&numerocubetas);

    tamanioarreglomini=999/numerocubetas;
    int arreglosmini[numerocubetas][3500];
    int posicion[numerocubetas];

    for(int t=0;t<numerocubetas;t++){           //rellena con 0's el arreglo posicion
        posicion[t]=0;
    }

    for(int j=0;j<3500;j++){//recorre todo el arreglo grande y clasifica

        for(int k=0;k<numerocubetas;k++){

        if((arreglogrande[j]>tamanioarreglomini*k) && (arreglogrande[j]<tamanioarreglomini*(k+1))){
            arreglosmini[k][posicion[k]]=arreglogrande[j];
            posicion[k]+=1;
        }


        }


    }


    
printf("Estos son los numeros que se generaron:\n\n");            //imprime absolutamente todo el arreglo grande
for(int o=0;o<3500;o++){
    printf("%d, ",arreglogrande[o]);
}

for(int g=0;g<numerocubetas;g++){                               //mete a un arreglo global el arreglo que dice la cantidad que hay en cada uno
    tamanios[g]=posicion[g];
}

for(int o=0;o<numerocubetas;o++){
    printf("\n\nEstos son los numeros que se guardaron en la cubeta %d :\n",o);
    for(int m=0;m<tamanios[o];m++){
    printf("%d,",arreglosmini[o][m]);}
}


contador=0;
for(h=0;h<numerocubetas;h++){
    error=pthread_create(&hilos[h],NULL,codigo_del_hilo,arreglosmini[h]);
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
    //printf("\n\nHilo %d terminado\n",*salida);
}
    




    for(int d=0;d<numerocubetas;d++){
        printf("\n\nnumeros ordenados que estan en la cubeta %d: \n\n",d);
        
        for(int n=0;n<tamanios[d];n++){
            if(arreglosmini[d][n]!=0)printf("%d, ",arreglosmini[d][n]);
        }
    }
        printf("\n\nNumeros ordenados: \n\n");
        for(int d=0;d<numerocubetas;d++){
       
        for(int n=0;n<tamanios[d];n++){
            if(arreglosmini[d][n]!=0)printf("%d, ",arreglosmini[d][n]);
        }
    }
}