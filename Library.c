#include <stdio.h>
#include <stdlib.h>

void printMenu(){
  printf("DIGITE A OPERAÇÃO:\n");
  printf("1. Cadastro\n2. Consulta\n3. Atualização\n4. Exclusão\n5. Empréstimo\n6. Devolução\n0. Sair\n");
}

int main(){
  int op;
  printf("INICIANDO BIBLIOTECA...\n");
  while(1){
    printMenu();
    scanf("%d", &op);
    
  }
  return 0;
}
