#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Produto{
  int codigo;
  char descricao[15];
  int quantidade;
  float preco;
  struct Produto *prox;
}Produto;

void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

Produto* criarListavazia(){
  return NULL;
}

Produto* criarNovaPessoa(){
  Produto *novoProduto = (Produto*)malloc(sizeof(Produto));
  if(novoProduto == NULL){
    printf("\nNão foi possivel alocar memoria");
    exit(EXIT_FAILURE);
  }
  novoProduto->prox = NULL;
  return novoProduto;
}

Produto* Cadastrar(Produto *lista){
  Produto *novoProduto = criarNovaPessoa();
  srand(time(NULL));
  novoProduto->codigo = rand() % 100;
  printf("\nDigite a descrição do produto: ");
  limparBuffer();
  fgets(novoProduto->descricao, sizeof(novoProduto ->descricao), stdin);
  limparBuffer();
  printf("\nDigite a quantidade: ");
  scanf("%d", &novoProduto->quantidade);
  limparBuffer();
  printf("\nDigite o preço: ");
  scanf("%f", &novoProduto->preco);
  if(lista == NULL){
    lista = novoProduto;
  }else{
    Produto *atual = lista;
    while(atual->prox != NULL){
      atual = atual->prox;
    }
    atual->prox = novoProduto;
  }
  return lista;
}

void mostrar(Produto *lista){
  Produto *atual = lista; 
  if(atual == NULL){
    printf("\nLista vazia\n");
    return;
  }else{
    while(atual != NULL){
      printf("\nDescrição: %s", atual->descricao);
      printf("\nCodigo: %d", atual->codigo);
      printf("\nQuantidade: %d", atual->quantidade);
      printf("\nValor: %.2f", atual->preco);
      printf("\n");
      atual = atual->prox;
    }
  }
}

Produto* buscar(Produto *lista, int codigo){
  Produto *atual = lista;
  if(atual == NULL){
    printf("\nLista vazia\n");
    return NULL;
  }else{
    while(atual != NULL){
      if(atual->codigo == codigo){
        printf("\nDescrição: %s", atual->descricao);
        printf("\nCodigo: %d", atual->codigo);
        printf("\nQuantidade: %d", atual->quantidade);
        printf("\nValor: %.2f", atual->preco);
        printf("\n");
        return atual;
      }
      atual = atual->prox;
    }
    printf("\nProduto não encontrado");
    return NULL;
  }
}



Produto* excluir(Produto *lista, int codigo){
  Produto *anterior = NULL;
  Produto *atual = lista;

  while(atual != NULL && atual->codigo != codigo){
    anterior = atual;
    atual = atual->prox;
  }
  if(atual != NULL){
    if(anterior != NULL){
      anterior->prox = atual->prox;
    }else{
      lista = atual->prox;
    }
    free(atual);
    printf("\nProduto excluido");

  }else{
    printf("\nProduto não encontrado");
  }
  return lista;
}

void liberarLista(Produto *lista){
    Produto *atual = lista;
    Produto *prox;
    while(atual != NULL){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

int main() {
  Produto *lista = criarListavazia();
  Produto *encontrada;
  int opcao, codigoBusca;
  do{
    printf("\n1 - cadastrar um produto");
    printf("\n2 - Mostar todos os produtos");
    printf("\n3 - buscar um produto");
    printf("\n4 - excluir um produto");
    printf("\n0 - sair");
    printf("\n\nDigite a opçao: ");
    scanf("%d", &opcao);

    switch(opcao){
      case 1:
        lista = Cadastrar(lista);
      break;
      case 2:
        mostrar(lista);
      break;
      case 3:
        printf("\nDigite o codigo do produto: ");
        scanf("%d", &codigoBusca);
        encontrada = buscar(lista, codigoBusca);
      break;
      case 4:
        printf("\nDigite o codigo do produto: ");
        scanf("%d", &codigoBusca);
        lista = excluir(lista, codigoBusca);
      break;
    }
  }while(opcao != 0);

   liberarLista(lista);

  return 0;
}
