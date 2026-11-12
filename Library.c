#include <stdio.h>
#include <stdlib.h>

#define SIZEMAIL 50
#define SIZEUNAME 50
#define SIZETITLE 50
#define SIZEAUTHOR 50

typedef struct tuser{
  char email[SIZEMAIL];
  char uname[SIZEUNAME];
}User;

typedef struct tbook{
  char title[SIZETITLE];
  char author[SIZEAUTHOR];
  int year;
  int id;
  int status;
  User* userb;
}Book;

typedef struct tlistU{
  User *user;
  struct tlistU *next, *prev;
}ListU;

typedef struct tlistB{
  Book *book;
  struct tlistB *next, *prev;
}ListB;

typedef struct tsent{
  ListU *firstU, *lastU;
  ListB *firstB, *lastB;
  int qtUsers, qtBooks;
}Sent;

int printLUVMenu(){
  int op;
  printf("1. Livros\n");
  printf("2. Usuários\n");
  printf("0. Voltar\n");
  scanf("%d", &op);
  if (op>2 || op<0){
    printf("Opção inexistente!\n");
    return 0;
  }
  return op;
}

void freeMemory(Sent *s){

}

void Cad(Sent *s){
  int op;
  while(1){
    printf("Selecione a opção de cadastro:\n");
    op=printLUVMenu();
    if(op==0) return;
    if(op==1){//livro
      ListB *bnew;
      bnew=(ListB *)malloc(sizeof(ListB));
      bnew->book=(Book *)malloc(sizeof(Book));//coreção de erro que o programa fechava sozinho

      printf("Digite as seguintes informações:\n");
      printf("Título: ");
      scanf("%s", bnew->book->title);
      printf("Autor: ");
      scanf("%s", bnew->book->author);
      printf("Ano de publicação: ");
      scanf("%d", &bnew->book->year);
      bnew->book->status=0;
      bnew->book->userb=NULL;

      if(s->firstB==NULL){
        s->firstB=bnew;
        s->lastB=bnew;
        bnew->next=NULL;
        bnew->prev=NULL;
        bnew->book->id=1;
      }else{
        s->lastB->next=bnew;
        bnew->prev=s->lastB;
        bnew->next=NULL;
        bnew->book->id=s->lastB->book->id+1;
        s->lastB=bnew;
      }
      printf("Livro Cadastrado com Sucesso! (ID:%d)\n", bnew->book->id);
      s->qtBooks++;
    }
    if(op==2){//usuário
      ListU *unew;
      int fail=0;
      unew=(ListU *)malloc(sizeof(ListU));
      unew->user=(User *)malloc(sizeof(User));

      printf("Digite as seguintes informações:\n");
      printf("Email: ");
      scanf("%s", unew->user->email);
      for(ListU *aux=s->firstU;aux!=NULL;aux=aux->next){//vai precisar da biblioteca string.h
        if(unew->user->email==aux->user->email){
          printf("Email já existente!\n");
          Sent u={unew,unew, NULL, NULL,1,0};
          freeMemory(&u);
          fail=1;
          break;
        }
      }
      if(fail==1)break;
      printf("Nome (sem espaços): ");
      scanf("%s", unew->user->uname);

      if(s->firstU==NULL){
        s->firstU=unew;
        s->lastU=unew;
        unew->next=NULL;
        unew->prev=NULL;
      }else{
        s->lastU->next=unew;
        unew->prev=s->lastU;
        unew->next=NULL;
        s->lastU=unew;
      }
      printf("Usuário cadastrado com sucesso!\n");
      s->qtUsers++;
    }
  }
}

int printLUEVMenu(){
  int op;
  printf("1. Livros\n");
  printf("2. Usuários\n");
  printf("3. Empréstimos\n");
  printf("0. Voltar\n");
  scanf("%d", &op);
  if (op>3 || op<0){
    printf("Opção inexistente!\n");
    return 0;
  }
  return op;
}

void Con(Sent *s){
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

void Atu(Sent *s){
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

void Exc(Sent *s){
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

void Emp(Sent *s){

}

void Dev(Sent *s){

}

void initLists(Sent *s){
  s->firstU=NULL;
  s->lastU=NULL;
  s->firstB=NULL;
  s->lastB=NULL;
  s->qtUsers=0;
  s->qtBooks=0;
}

void printMainMenu(){
  printf("DIGITE A OPERAÇÃO:\n");
  printf("1. Cadastro\n2. Consulta\n3. Atualização\n4. Exclusão\n5. Empréstimo\n6. Devolução\n0. Sair\n");
}

int main(){
  int op;
  printf("INICIANDO BIBLIOTECA...\n");
  Sent s;
  initLists(&s);
  while(1){
    printMainMenu();
    scanf("%d", &op);
    if(op==0){
      freeMemory(&s);
      break;
    }
    if(op==1){
      Cad(&s);
    }else{
      if(op==2){
        Con(&s);
      }else{
        if(op==3){
          Atu(&s);
        }else{
          if(op==4){
            Exc(&s);
          }else{
            if(op==5){
              Emp(&s);
            }else{
              if(op==6){
                Dev(&s);
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