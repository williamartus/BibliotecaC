#include <stdio.h>
#include <stdlib.h>

typedef struct tuser{
  char* email;
  char* uname;
}User;

typedef struct tbook{
  char* title;
  char* author;
  int year;
  int id;
  int status;
  User* userb;
}Book;

typedef struct tlistU{
  User *user;
  struct tlistU *next, *prev;
}ListU;

typedef struct tsent{
  User *firstU, *lastU;
  Book *firstB, *lastB;
  int qtUsers, qtBooks;
}Sent;

typedef struct tlistB{
  Book *book;
  struct tlistB *next, *prev;
}ListB;

int printLUVMenu(){
  int op;
  printf("1. Livros\n");
  printf("2. Usuários\n");
  printf("0. Voltar\n");
  scanf("%d, &op");
  if (op>2 || op<0){
    printf("Opção inexistente!\n");
    return 0;
  }
  return op;
}

void Cad(Sent s){
  int op;
  while(1){
    printf("Selecione a opção de cadastro:\n");
    op=printLUVMenu();
    if(op==0) return;
    if(op==1){//livro

    }
    if(op==2){//usuário

    }
  }
}

int printLUEVMenu(){
  int op;
  printf("1. Livros\n");
  printf("2. Usuários\n");
  printf("3. Empréstimos\n");
  printf("0. Voltar\n");
  scanf("%d, &op");
  if (op>3 || op<0){
    printf("Opção inexistente!\n");
    return 0;
  }
  return op;
}

void Con(Sent s){
  int op;
  while(1){
    printf("Selecione a opção de consulta:\n");
    op=printLUEVMenu();
    if(op==0) return;
    if(op==1){//livro

    }
    if(op==2){//usuário

    }
    if(op==3){//empréstimo

    }
  }
}

void Atu(Sent s){
  int op;
  while(1){
    printf("Selecione a opção de Atualização:\n");
    op=printLUVMenu();
    if(op==0) return;
    if(op==1){//livro
      /*Titulo 
      Autor  
      Ano */
    }
    if(op==2){//usuário
      //nome
    }
  }
}

void Exc(Sent s){
  int op;
  while(1){
    printf("Selecione a opção de Exclusão:\n");
    op=printLUVMenu();
    if(op==0) return;
    if(op==1){//livro

    }
    if(op==2){//usuário

    }
  }
}

void Emp(Sent s){

}

void Dev(Sent s){

}

void freeMemory(Sent s){

}

void initLists(Sent s){
  s.firstU=NULL;
  s.lastU=NULL;
  s.firstB=NULL;
  s.lastB=NULL;
  s.qtUsers=0;
  s.qtBooks=0;
}

void printMainMenu(){
  printf("DIGITE A OPERAÇÃO:\n");
  printf("1. Cadastro\n2. Consulta\n3. Atualização\n4. Exclusão\n5. Empréstimo\n6. Devolução\n0. Sair\n");
}

int main(){
  int op;
  printf("INICIANDO BIBLIOTECA...\n");
  Sent s;
  initLists(s);
  while(1){
    printMenu();
    scanf("%d", &op);
    if(op==0){
      freeMemory(s);
      break;
    }
    if(op==1){
      Cad(s);
    }else{
      if(op==2){
        Con();
      }else{
        if(op==3){
          Atu(s);
        }else{
          if(op==4){
            Exc(s);
          }else{
            if(op==5){
              Emp(s);
            }else{
              if(op==6){
                Dev(s);
              }else{
                printf("Opção inexistente!\n\n");
              }
            }
          }
        }
      }
    }
  }
  printf("ENCERRANDO BIBLIOTECA...\n");
  return 0;
}