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

void printLUVMenu(){
  printf("1. Livros\n");
  printf("2. Usuários\n");
  printf("0. Voltar\n");
}

void Cad(){
  int op;
  while(1){
    printf("Selecione a opção de cadastro:\n");
    printLUVMenu();
    scanf("%d, &op");
    if(op==0) return;
    if(op==1){

    }else{
      if(op==2){

      }else{
        printf("Opção inexistente!\n");
      }
    }
  }
}

void Con(){

}

void Atu(){

}

void Exc(){

}

void Emp(){

}

void Dev(){

}

void printMainMenu(){
  printf("DIGITE A OPERAÇÃO:\n");
  printf("1. Cadastro\n2. Consulta\n3. Atualização\n4. Exclusão\n5. Empréstimo\n6. Devolução\n0. Sair\n");
}

int main(){
  int op;
  printf("INICIANDO BIBLIOTECA...\n");
  while(1){
    printMenu();
    scanf("%d", &op);
    if(op==0)break;
    if(op==1){
      Cad();
    }else{
      if(op==2){
        Con();
      }else{
        if(op==3){
          Atu();
        }else{
          if(op==4){
            Exc();
          }else{
            if(op==5){
              Emp();
            }else{
              if(op==6){
                Dev();
              }else{
                printf("Opção inexistente!\n\n");
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
