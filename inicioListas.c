#include <stdio.h>
#include <stdlib.h>             // para malloc

// intervenção(Daniel)
#include <time.h>

struct novaLista {
    int matricula;
    int idade;
    double salario;
    struct novaLista *ant;
    struct novaLista *prox;
};
struct NovaListaHeader {
    int qtd;                    // quantos elementos tem
    double totSal;              // total de salário
    int maior18anos;
    struct novaLista *inicio;
    struct novaLista *fim;
};

struct NovaListaHeader *arrumaheader(struct novaLista *lista) {

  // Intervenção (Daniel) toda função
  struct novaLista *aux = NULL, *aux2 = NULL;
  struct NovaListaHeader *h;
  int i = 0, maior = 0;
  double somaSalario = 0;
  h = (struct NovaListaHeader *) malloc(sizeof(struct NovaListaHeader));

  // Se não alocar na memória
  if (h != NULL) {
    if (lista == NULL) {
        h = NULL;
        return h;
    }

    aux = lista;
    aux2 = aux->prox;
    
    while (aux2 != NULL) {
        // Corrige o campo anterior
        aux2->ant = aux;

        // Contagem da quantidade de itens da lista
        i++;

        // Verifica se é maior de idade
        if (aux->idade >= 18) {
            maior++;
        }
        
        // Soma total de salarios
        somaSalario = somaSalario + aux->salario;

        // Incremento
        aux = aux->prox;
        aux2 = aux2->prox;
    }

    // Para acrescentar o do último item
    // Contagem da quantidade de itens da lista
    i++;
    
    // Verifica se é maior de idade
    if (aux->idade >= 18) {
        maior++;
    }

    // Soma total de salarios
    somaSalario = somaSalario + aux->salario;

    // Seta parâmetros do header
    h->inicio = lista;
    h->fim = aux;
    h->totSal = somaSalario;
    h->maior18anos = maior;
    h->qtd = i;
    return h;

  } else {
    // Se não conseguir alocar
    h = NULL;
    return h;
  }
}

struct novaLista *cadastraLista()
{
    struct novaLista *novo;

    novo = malloc(sizeof(struct novaLista));
    if (novo == NULL) {
        printf("ERRO no malloc\n");
        return (NULL);
    }

    novo->matricula = random();
    novo->idade = random() % 100;       // até 99 anos
    novo->salario = (random() % 30000) + ((random() % 100) / (double) 100);     // salario em reais com centavos
    novo->prox = NULL;
    return (novo);
}

int insereNofim(struct novaLista *lista, struct novaLista *novo)
{
    struct novaLista *aux;

    aux = lista;
    /* Indo ao fim */
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;           // inserido no fim
}

int impLista(struct novaLista *lista)
{
    struct novaLista *aux;
    int i;

    aux = lista;
    i = 0;
    while (aux) {
        printf("[%04d] %10d %3d %10.2lf\n", i++, aux->matricula, aux->idade, aux->salario);
        aux = aux->prox;
    }
}

int desalocaNos(struct novaLista *lista)
{
    struct novaLista *vit;

    while (lista) {
        vit = lista;
        lista = lista->prox;
        free(vit);
    }
}

int main()
{
    struct NovaListaHeader *h;
    struct novaLista *lista, *novo, *aux;

    int total;                  // quantos gerar
    int i;

    srand(time(NULL));          // para gerar números aleatórios

    total = 1000;               // irá gerar 1000 elementos

    lista = novo = aux = NULL;
    h = NULL;

    for (i = 0; i < total; i++) {
        /* Como dito o programador não ajustou o ant. Deixou com lixo */
        novo = cadastraLista();
        if (novo == NULL) {
            return (1);
        }
        if (lista == NULL) {
            lista = novo;
            continue;
        }
        insereNofim(lista, novo);
    }

    /* Invocacao da tua função que deve ser feita */
    h = arrumaheader(lista);
    if (h == NULL) {
        printf("Erro na funcao arrumaheader\n");
        return (2);
    }

    impLista(lista);
    printf("\n");
    
    printf("Informacoes do header:\n");
    printf("\tTotal de elementos: %d\n", h->qtd);
    printf("\tTotal maiores de 18 anos: %d\n", h->maior18anos);
    printf("\tTotal de todos os salários: %.2lf\n", h->totSal);
    printf("\tMatricula do primeiro elemento: %d\n", h->inicio->matricula);
    printf("\tMatricula do último elemento: %d\n", h->fim->matricula);

    desalocaNos(lista);         // removendo todos os nos
    if (h) {                    // removendo o header
        free(h);
    }

}