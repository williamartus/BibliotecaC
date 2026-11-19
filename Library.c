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
  User *userb;
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

void initLists(Sent *s){
  s->firstU=NULL;
  s->lastU=NULL;
  s->firstB=NULL;
  s->lastB=NULL;
  s->qtUsers=0;
  s->qtBooks=0;
}

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
ListB *searchBookID(Sent *s, int id){
  ListB *aux=s->firstB;
  for(;aux!=NULL;aux=aux->next){
    if(aux->book->id==id){
      printf("Livro encontrado!:\n");
      return aux;
    }
  }
  printf("Livro não encontrado!\n");
  return NULL;
}

ListB *searchBookAu(Sent *s, char *au){
  ListB *aux=s->firstB;
  ListB *AuBooks[s->qtBooks];
  int j=0;
  for(;aux!=NULL; aux=aux->next){
    int same=1;
    for(int i=0;aux->book->author[i]!='\0' || au[i]!='\0';i++){
      if(aux->book->author[i]!=au[i]){
        same=0;
        break;
      }
    }
    if(same==1){
      AuBooks[j]=aux;
      j++;
    }
  }
  if(j==0){
    printf("Autor não encontrado!\n");
    return NULL;
  }
  return AuBooks[0];//retorna lista de ponteiros
}

ListU *searchUemail(Sent *s, char *em){
  for(ListU *aux=s->firstU;aux!=NULL;aux=aux->next){
    int same=1;
    for(int i=0;aux->user->email[i]!='\0' || em[i]!='\0';i++){
      if(aux->user->email[i]!=em[i]){
        same=0;
        break;
      }
    }
    if(same==1) return aux;
  }
  printf("Usuário não encontrado!\n");
  return NULL;
}

ListU *searchUname(Sent *s, char *name){
  for(ListU *aux=s->firstU;aux!=NULL;aux=aux->next){
    int same=1;
    for(int i=0;aux->user->uname[i]!='\0' || name[i]!='\0';i++){
      if(aux->user->uname[i]!=name[i]){
        same=0;
        break;
      }
    }
    if(same==1) return aux;
  }
  printf("Usuário não cadastrado!\n");
  return NULL;
}

ListB *searchUemp(Sent *s, char *em){
  ListB *UBooks[s->qtBooks];
  int j=0;
  for(ListB *aux=s->firstB;aux!=NULL;aux=aux->next){
    int same=1;
    for(int i=0;aux->book->userb->email[i]!='\0' || em[i]!='\0';i++){
      if(aux->book->userb->email[i]!=em[i]){
        same=0;
        break;
      }
    }
    if(same==1){
      UBooks[j]=aux;
      j++;
    }
  }
  if(j==0){
    printf("Usuário não emprestou nenhum livro!\n");
    return NULL;
  }
  return UBooks[0];//retorna lista de ponteiros
}

void freeMemory(Sent *s){
  for(ListB *aux=s->firstB;aux!=NULL;){
    ListB *auxprev=aux;
    Book *b=aux->book;
    aux=aux->next;
    free(b);
    free(auxprev);
  }
  for(ListU *aux=s->firstU;aux!=NULL;){
    ListU *auxprev=aux;
    User *u=aux->user;
    aux=aux->next;
    free(u);
    free(auxprev);
  }
  initLists(s);
  free(s);
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
      ListU *u=searchUemail(s, unew->user->email);
      if(u!=NULL){
        printf("Email já existente!\n");
        Sent u={unew,unew, NULL, NULL,1,0};
        freeMemory(&u);
        fail=1;
        break;
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
      int op2;
      printf("Deseja pesquisar por:\n(1)ID\n(2)Autor\n");
      scanf("%d", &op2);
      if(op2==1){//id
        int id;
        ListB *b;
        printf("Digite o ID do livro: ");
        scanf("%d", &id);
        b=searchBookID(s, id);
        if(b==NULL) return;
        printf("Título: %s\n",b->book->title);
        printf("Ano: %d\n",b->book->year);          
        printf("Autor: %s\n",b->book->author);
        printf("ID: %d\n",b->book->id);
        if(b->book->status==1){
          printf("Status: Emprestado\n");
          printf("Emprestado por %s\n",b->book->userb->uname);
        }else printf("Status: Disponível\n");
      }
      if(op2==2){//autor
        char au[SIZEAUTHOR];
        ListB *aubooks;
        printf("Digite o nome do Autor: ");
        scanf("%s", au);
        aubooks=searchBookAu(s, au);
        if(aubooks==NULL) return;
        for(ListB *aux=aubooks;aux!=NULL;aux=aux+(sizeof(ListB))){
          printf("Título: %s\n",aux->book->title);
          printf("Ano: %d\n",aux->book->year);          
          printf("Autor: %s\n",aux->book->author);
          printf("ID: %d\n",aux->book->id);
          if(aux->book->status==1){
            printf("Status: Emprestado\n");
            printf("Emprestado por %s\n",aux->book->userb->uname);
          }else printf("Status: Disponível\n");
        }
      }
      return;
    }
    if(op==2){//usuário
      int op2;
      printf("Deseja pesquisar por:\n(1)Email\n(2)Nome\n");
      scanf("%d", &op2);
      if(op2==1){//email
        char em[SIZEMAIL];
        printf("Digite o Email do usuário: ");
        scanf("%s", em);
        ListU *u=searchUemail(s, em);
        if(u==NULL) return;
        printf("Nome: %s",u->user->uname);
        printf("Email: %s",u->user->email);
      }
      if(op2==2){//nome
        char na[SIZEUNAME];
        printf("Digite o Nome do usuário: ");
        scanf("%s", na);
        ListU *u=searchUname(s, na);
        if(u==NULL) return;
        printf("Nome: %s",u->user->uname);
        printf("Email: %s",u->user->email);
      }
      return;
    }
    if(op==3){//empréstimo
      char em[SIZEMAIL];
        printf("Digite o Email do usuário: ");
        scanf("%s", em);
        ListB *bks=searchUemp(s, em);
        if(bks==NULL) return;
        int i=1;
        for(ListB *aux=bks;aux!=NULL;aux=aux+(sizeof(ListB))){//precisa pular um espaço do vetor
          printf("==Livro %d==\n", i);
          printf("Título: %s\n",aux->book->title);
          printf("Ano: %ds\n",aux->book->year);          
          printf("Autor: %s\n",aux->book->author);
          printf("ID: %d\n",aux->book->id);
          if(aux->book->status==1){
            printf("Status: Emprestado\n");
            printf("Emprestado por %s\n",aux->book->userb->uname);
          }else printf("Status: Disponível\n");
          i++;
        }
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
      int op2, id;
      printf("Digite o ID do livro que deseja alterar: ");
      scanf("%d", &id);
      ListB *b=searchBookID(s, id);
      if(b==NULL) break;
      printf("Selecione o que deseja alterar:\n(1)Título\n(2)Autor\n(3)Ano\n(4)Todos os anteriores\n");
      scanf("%d", &op2);
      if(op2==1){
        char t[SIZETITLE];
        printf("Digite o novo título: ");
        scanf("%s", t);
        for(int i=0;b->book->title[i]!='\0';i++){
          b->book->title[i]=t[i];
          if(t[i]!='\0')b->book->title[i]='\0';
        }
        printf("Título alterado com sucesso!\n");
      }
      if(op2==2){
        char a[SIZEAUTHOR];
        printf("Digite o novo Autor: ");
        scanf("%s", a);
        for(int i=0;b->book->author[i]!='\0';i++){
          b->book->author[i]=a[i];
          if(a[i]!='\0')b->book->author[i]='\0';
        }
        printf("Autor alterado com sucesso!\n");
      }
      if(op2==3){
        int y;
        printf("Digite o novo Ano: ");
        scanf("%d", &y);
        b->book->year=y;
        printf("Ano alterado com sucesso!\n");
      }
      if(op2==4){
        char t[SIZETITLE], a[SIZEAUTHOR];
        int y;
        printf("Digite o novo título: ");
        scanf("%s", t);
        for(int i=0;b->book->title[i]!='\0';i++){
          b->book->title[i]=t[i];
          if(t[i]!='\0')b->book->title[i]='\0';
        }
        printf("Título alterado com sucesso!\n");
        printf("Digite o novo Autor: ");
        scanf("%s", a);
        for(int i=0;b->book->author[i]!='\0';i++){
          b->book->author[i]=a[i];
          if(a[i]!='\0')b->book->author[i]='\0';
        }
        printf("Autor alterado com sucesso!\n");
        printf("Digite o novo Ano: ");
        scanf("%d", &y);
        b->book->year=y;
        printf("Ano alterado com sucesso!\n");
      }
    }
    if(op==2){//usuário
      char e[SIZEMAIL];
      printf("Digite o email do usuário a ser atualizado: ");
      scanf("%s", e);
      ListU *u=searchUemail(s, e);
      if(u==NULL) return;
      char n[SIZEUNAME];
      printf("Digite o novo nome do usuário: ");
      scanf("%s", n);
      for(int i=0;u->user->uname[i]!='\0';i++){
          u->user->uname[i]=n[i];
          if(n[i]!='\0')u->user->uname[i]='\0';
        printf("Nome alterado com sucesso!\n");
      }
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
      int id;
      printf("Digite o id do livro a ser excluído: ");
      scanf("%d", &id);
      ListB *b=searchBookID(s, id);
      if(b==NULL) return;
      ListB *aux=b;
      Book *auxb=b->book;
      if(b==s->firstB && b==s->lastB){
        s->firstB=NULL;
        s->lastB=NULL;
        free(auxb);
        free(aux);
        s->qtBooks--;
      }else{
        if(b==s->firstB){
          s->firstB=b->next;
          b->next->prev=NULL;
          free(auxb);
          free(aux);
          s->qtBooks--;
        }else{
          if(b==s->lastB){
            s->lastB=b->prev;
            b->prev->next=NULL;
            free(auxb);
            free(aux);
            s->qtBooks--;
          }else{
            b->prev->next=b->next;
            b->next->prev=aux->prev;
            free(auxb);
            free(aux);
            s->qtBooks--;
          }
        }
      }
    }
    if(op==2){//usuário
      char em[SIZEMAIL];
      printf("Digite o email do usuário a ser excluído: ");
      scanf("%s", em);
      ListU *u=searchUemail(s, em);
      if(u==NULL) return;
      ListB *bks=searchUemp(s, em);
      if(bks!=NULL){
        for(ListB *aux=bks;aux!=NULL;aux=aux+(sizeof(ListB))){
          bks->book->userb=NULL;
          bks->book->status=0;
        }
      }
      ListU *aux=u;
      User *auxu=u->user;
      if(u==s->firstU && u==s->lastU){
        s->firstU=NULL;
        s->lastU=NULL;
        free(auxu);
        free(aux);
        s->qtUsers--;
      }else{
        if(u==s->firstU){
          s->firstU=u->next;
          u->next->prev=NULL;
          free(auxu);
          free(aux);
          s->qtUsers--;
        }else{
          if(u==s->lastU){
            s->lastU=u->prev;
            u->prev->next=NULL;
            free(auxu);
            free(aux);
            s->qtUsers--;
          }else{
            u->prev->next=u->next;
            u->next->prev=aux->prev;
            free(auxu);
            free(aux);
            s->qtUsers--;
          }
        }
      }
    }
  }
}

void Emp(Sent *s){
  int id;
  printf("Digite o ID do livro a ser emprestado: ");
  scanf("%d", &id);
  ListB *b=searchBookID(s, id);
  if(b==NULL) return;
  if(b->book->status==1){
    printf("Livro já emprestado!\n");
    return;
  }
  char em[SIZEMAIL];
  printf("Digite o email do usuário a emprestar: ");
  scanf("%s", em);
  ListU *u=searchUemail(s, em);
  if(u==NULL) return;
  b->book->userb=u->user;
  b->book->status=1;
  printf("Livro emprestado com sucesso!\n");
}

void Dev(Sent *s){
  int id;
  printf("Digite o ID do livro a ser devolvido: ");
  scanf("%d", &id);
  ListB *b=searchBookID(s, id);
  if(b==NULL) return;
  if(b->book->status==0){
    printf("Livro já disponível!\n");
    return;
  }
  b->book->userb=NULL;
  b->book->status=0;
  printf("Livro devolvido com sucesso!\n");
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