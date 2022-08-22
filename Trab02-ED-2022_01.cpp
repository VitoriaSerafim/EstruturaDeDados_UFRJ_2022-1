// Calculo do valor de uma expressao numerica
// VITORIA DE SOUZA SERAFIM  120035369 2022/1
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;  

//DEFINIÇÃO DA PILHA
struct Pilha {
	int topo;
	char *pElem;
	float *Num;
};

//  ************************* FUNÇÕES DA PILHA ***********************
// ESTÃO DUPLICADAS POIS O TRABALHO POSSUI PILHAS DE TIPOS DIFERENTES
// UMA FARÁ O CÁLCULO DA EXPRESSÃO E A OUTRA TRATARÁ A ENTRADA 
void criarpilha( struct Pilha *p, int c ){
  p->topo = -1;
  p->pElem = (char*) malloc(c);

}
void criarpilhaNum( struct Pilha *p, int c ){
  p->topo = -1;
  p->Num = (float*) malloc(c*sizeof(float));

}

int retornatopo ( struct Pilha *p ){
  return p->pElem [p->topo];
}
float retTopoNum( struct Pilha *p ){
  return p->Num[p->topo];
}

void push( struct Pilha *p, char v){
    p->topo++;
    p->pElem [p->topo] = v;
}
void pushNum( struct Pilha *p, float v){
    p->topo++;
    p-> Num[p->topo] = v;
}

char pop( struct Pilha *p ){
  p->pElem [p->topo] = '\0';
  p->topo--;
  return p->pElem [p->topo];
}
float popNum( struct Pilha *p ){
  p->Num[p->topo] = '\0';
  p->topo--;
  return p->Num[p->topo];
}

bool pilhavazia(struct Pilha *p){
  bool r;
  if (p->topo == -1) r = true;
  else r = false;
  return r;  
}
//  ********************* TERMINO FUNÇÕES DA PILHA **********************

//  *** FUNÇÃO PARA CALCULAR PRIORIDADE DOS ELEMENTOS DA EXPRESSÃO ******
int Prioridade(int c){
  int pc = 0;
  if(c == 42 || c == 47)
    pc = 2;
  else if(c == 43 || c == 45)
    pc = 1;
  return pc;
}

//  **** FUNÇÃO PARA EXECUTAR A CONTA DE ACORDO COM O OPERADOR **********
float Operacao(float op1, float op2, int opr){
  float result = 0;
  switch (opr)
  {
  case(43):  // 43 É '+'
      result = op2 + op1;
      break;
  case(45): // 45 É '-'
      result = op2 - op1;
      break;
  case(42): // 42 É '*'
      result = op2 * op1;
      break;
  case(47): // 47 É '/'
      result = op2 / op1;
      break;
  default:
  cout << "ERROR: OPERADOR NÃO RECONHECIDO" << '\n';
    break;
  }

return result;
}
//  **** FUNÇÃO PARA CONVERTER A ENTRADA PARA NOTAÇÃO POSFIXA ******
Pilha infixaParaPosfixa (char *exp) {
  int n = strlen (exp);
  Pilha saida,operadores;
  criarpilha(&operadores,n);
  criarpilha(&saida,n);
 
  for(int i = 0; i < strlen(exp); i++){ 
    if(exp[i] >= '0' && exp[i] <= '9' ){
      push(&saida, (int)exp[i]); 
      continue;
    }
    else{
      if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/'){
        if(pilhavazia(&operadores)) push(&operadores,(int)exp[i]);
        else{
            if(Prioridade(retornatopo(&operadores)) <= Prioridade((int)exp[i])) push(&operadores,(int)exp[i]);
            while(Prioridade(retornatopo(&operadores)) > Prioridade((int)exp[i]) ){
                push(&saida,retornatopo(&operadores));
                pop(&operadores);
                push(&operadores,(int)exp[i]);
            }
        }
        continue;
      }
      else if (exp[i] == '('){
        push(&operadores,(int)exp[i]);
        continue;
      }
      else if(exp[i] == ')'){
        while (retornatopo(&operadores) != '('){
          push(&saida,retornatopo(&operadores));
          pop(&operadores);
        }
        pop(&operadores); // para remover o '('
        continue;
      }
    }
  }
  while(!pilhavazia(&operadores)){
    push(&saida,retornatopo(&operadores));
    pop(&operadores);
  }

  return saida;
}  

int main(){
cout<<"Obs.: a expressão deve ser composta de elementos de 1 dígito. Ex.: 9,1 etc\nEntre com uma expressão :\n";
char expr[100]; // TAM_MAX DE 100 CARACTERES
cin.getline(expr, sizeof(expr)); // LEITURA DA EXPRESSÃO

Pilha ptexpressao = infixaParaPosfixa(expr); // CONVERSÃO PARA POSFIXA
char *e = (ptexpressao.pElem); // PARA PODER EXECUTAR A ITERAÇÃO DOS ELEMENTOS
Pilha resultado;

criarpilhaNum(&resultado,strlen(expr)); 

for(int i = 0; i < strlen(e); i ++){
    if(e[i] != 42 && e[i] != 43 && e[i] != 45 && e[i] != 47){
      pushNum(&resultado, (e[i]-'0') ); // COLOCA OS OPERANDOS NA PILHA RESULTADO
    }
    else{ // SE FOR UM OPERADOR ... 
        pushNum(&resultado,' ');
        float op1 = popNum(&resultado); // PEGA O PRIMEIRO OPERANDO
        float op2 = popNum(&resultado); // PEGA O SEGUNDO OPERANDO
        popNum(&resultado);
        pushNum(&resultado,Operacao(op1,op2,e[i])); // COLOCA NO LUGAR DOS OPERANDOS O RESULTADO DA OPERAÇÃO
        
    }
}
cout << retTopoNum(&resultado); //IMPRIME O RESULTADO DA EXPRESSÃO (QUE ESTÁ NO TOPO DA PILHA)
 
}
