/* o algoritmo de arvore geradora minima de Kruskal,
 utilizando union-find, com compressao de caminhos e criterio de rank , altura ou tamanho.*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int *pai;
int *peso;

// Estrutura para guardar as arestas
typedef struct _Aresta{
    int peso;
    int v1,v2;
}Aresta;

// a árvore é t_min
Aresta *t_min,*aresta;

// Achar a raiz de k
int Find(int k){
	//Se o node é raiz, return k
	if(pai[k] == k) {
		return k;
	}
    //Find com compressao de caminhos, atualizaremos a raiz com a recursão
	return Find(pai[k]);
}

// unir os conjuntos
void Union(int a, int b){
	a = Find(a);
	b = Find(b);
	if(a == b){
		printf("%s\n","Erro!");
	}
	else{
		if(peso[a] > peso[b]) pai[b] = a;
		else if(peso[b] > peso[a]) pai[a] = b;
		else{
			pai[b] = pai[a];
			peso[a]++;
		}
	}
}
 
 // para ordenar as arestas por peso, utilizarei o bubblesort
void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void bubblesort(Aresta* ptr, int fim){
    int i, j;
    for(i = 0; i < fim-1; i++){
        for(j = 0; j < fim - i - 1; j++ ){
            if(ptr[j].peso > ptr[j+1].peso){
                swap(ptr[j],ptr[j+1]);
            }
        }
    }
}

int main(){
    int n, m; // número de vértices e arestas
	int sum_peso = 0, size = 0;; // peso da arvore

    cin >> n >> m;
    aresta = (Aresta*)malloc(m * sizeof(Aresta) );
	t_min = (Aresta*)malloc(m * sizeof(Aresta) );
	pai = (int*)malloc(n * sizeof(int) );
	peso = (int*)malloc(m * sizeof(int) );
	

    for(int i = 1; i <= m; i++)
        cin >> aresta[i].v1 >> aresta[i].v2 >> aresta[i].peso;

    // inicializar os pais e os pesos
    for(int i = 1; i <= n; i++) pai[i] = i;
    for(int i = 1; i <= m; i++) peso[i] = 0;

    // ordenar as arestas pelo peso
    bubblesort(aresta, m);
  
    for(int i = 1;i <= m;i++){
        
        if( Find(aresta[i].v1) != Find(aresta[i].v2) ){ // se não for o mesmo vertice...
            Union(aresta[i].v1, aresta[i].v2);  // faz o union
            t_min[++size] = aresta[i]; // coloca na arvore
        }
        
    }

    // imprimir o peso de t_min
    for(int i = 1; i <= m; i++){ 
		sum_peso += t_min[i].peso;
	}
    cout << sum_peso << "\n";
    return 0;
}