#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int* ptr, int inicio,int fim){
    int pivot = ptr[fim];
    int i = inicio-1;
    for(int j = inicio; j < fim; j++){
        if(ptr[j] <= pivot){
          i++;
          swap(&ptr[i],&ptr[j]);
        }
    }
    swap(&ptr[i+1],&ptr[fim]);
    return (i+1);
}
/*função do QuickSort */
void quickSort(int* ptr,int inicio,int fim){
    if(inicio < fim) {
       int p = partition(ptr,inicio,fim);
        quickSort(ptr,inicio,p-1);
        quickSort(ptr,p+1,fim);
    }
}
void merge(int* ptr, int esquerda, int centro, int direita) {
    int tamanho = direita - esquerda + 1;
    int fim1 = 0, fim2 = 0;
    int *ptTemp,ptLeft,ptRight,i,j,k;
    ptLeft = esquerda;
    ptRight = centro+1;

    ptTemp =(int*)malloc(tamanho*sizeof(int));
    if(ptTemp!=NULL){
        for(i=0;i<tamanho;i++){
            if(!fim1 && !fim2){
                if(ptr[ptLeft] < ptr[ptRight]){
                    ptTemp[i]= ptr[ptLeft++];
                }
                else{
                    ptTemp[i] = ptr[ptRight++];
                }
                if(ptLeft > centro) fim1=1;
                if(ptRight > direita) fim2 = 1; 
            }
            else{
                if(!fim1) ptTemp[i] = ptr[ptLeft++];
                else ptTemp[i] = ptr[ptRight++];
            }
        }
            for(j=0, k=esquerda;j<tamanho;j++,k++){
                ptr[k] = ptTemp[j];
            }
    }
    free(ptTemp);
}
/*função da MergeSort */
void mergeSort(int* ptr,int esquerda,int direita){
    if(esquerda <  direita){
        int centro = (esquerda+direita)/2;
        mergeSort(ptr,esquerda,centro);
        mergeSort(ptr,centro+1,direita);
        merge(ptr,esquerda,centro,direita);
    }
   
}
/*função do BubbleSort */
void bubblesort(int* ptr, int fim){
    int i, j;
    for(i = 0; i < fim-1; i++){
        for(j = 0; j < fim - i - 1; j++ ){
            if(ptr[j]>ptr[j+1]){
                swap(ptr[j],ptr[j+1]);
            }
        }
    }
}

int main(int argc, char * argv[]){
    int tam; // tamanho do vetor
    char* Tsort; // tipo de ordenação

    if(argc > 1){
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i],"-n")){
            tam = stoi(argv[i+1]);
        }
        if(argv[argc-1] != to_string(tam)){
        Tsort = argv[argc-1];
        }
    }
    }else{
        cout << "Nao foram passados parametros!" << "\n";
    }

int *ptVetor = (int*)malloc(sizeof(int)*tam); 

for(int i = 0; i < tam; i++){
        cin >>  ptVetor[i];  // preencher o ptVetor com os valores dados
    }

if(!strcmp(Tsort,"-m")){       //se -m, vai rodar o mergesort
    mergeSort(ptVetor,0,tam-1);
}
else if (!strcmp(Tsort,"-q")){ //se -q, vai srodar o quicksort
    quickSort(ptVetor,0,tam-1);
}
else{
    bubblesort(ptVetor,tam);  //caso não tenha nada, vai rodar o bubblesort
}
   cout << "\n";
    for (int i = 0; i < tam; i++){
        cout <<  ptVetor[i] << " ";
    }
}