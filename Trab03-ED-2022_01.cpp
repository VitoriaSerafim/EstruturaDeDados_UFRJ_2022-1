#include<stdio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

typedef struct _tno{
int chave;
_tno *prox;
}tno;

void Insere(tno **ptlista, int v){

    /*verifica se o vertice já está inserido na lista*/
    if ( (*ptlista != NULL) && ((*ptlista)->chave == v) ) printf("Achei!");
    tno *novo = (tno*)malloc(sizeof(tno));
    /*verifica se existe espaço na lista*/
    if (novo == NULL){ 
        printf("ERRO!Acabou memória!");
        return;
    }
    novo-> prox = *(ptlista);
    novo-> chave = v;
    (*ptlista) = novo;
}

int main(){
  /*Utilizei algumas partes do 'sample code' disponibilizado no classroom de 2021.1*/
  char *linha = NULL;
  size_t tamLinha = 0;
  int vertices, arestas, pos, *grau,*ord;
  int numLido = 0,numChars;
  tno **adj,*ptlista;

  scanf("%d %d\n", &vertices, &arestas);

/*Inicializa todas as listas que serão usadas. 
obs.: o tamanho das lista é vertices +1 para podermos começar do index 1. */
    ord = (int*) malloc( (vertices+1) * (sizeof(int)));
    grau = (int*) malloc( (vertices+1) * (sizeof(int)));
    adj = (tno**) malloc( (vertices+1) * (sizeof(tno*)));

/*Leitura dos vertices e arestas (obtido através do 'sample code')*/
    for(int i = 1; i <= vertices; i++){

    getline(&linha,&tamLinha,stdin);
    pos = 0;
    numLido = 0;

    while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0) {
      pos += numChars;
      if(strlen(linha) != 0){
      Insere(&adj[i], numLido);   
      grau[numLido]++;
      }
    }
}

/*Adiciona os vertices de grau 0 na lista de acordo com suas respectivas posições */
pos = 1;
    for(int i = 1; i <= vertices; i++){
        if (grau[i] == 0){
            ord[pos++] = i;
        }
    }
/*Ordena os vertices de acordo com o grau de entrada*/
    for(int i = 1; i <= vertices; i++){
        ptlista = adj[ord[i]];
        while(ptlista != NULL){ /*enquanto houver elementos ...*/
            grau[ptlista->chave]--; /*desconta do grau de entrada as arestas que saem de v, onde v = ptlista->chave */
            if(grau[ptlista->chave] == 0){
                ord[pos++] = ptlista->chave;
            }
            ptlista = ptlista->prox; /*passa para o prox v*/
        }
    }
/*Imprime a lista ordenada*/
     for(int i = 1; i <= vertices; i++){
        printf("%d ", ord[i]);
    }
}