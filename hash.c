#include <stdio.h>
#include <stdlib.h>

typedef struct table
{
  int valor;
  struct table *prox;
  struct table *ant;
} Table;

//função de hashing
int h(int k)
{
  return k % 4;
}

int main()
{
  int op = 0, num;
  char tratamento;
  Table *table[4], *aux;

  //setando posições como vazias
  for (int i = 0; i < 4; i++)
  {
    table[i] = NULL;
  }

  while (op != 4)
  {
    printf("1 - Inserir\n2 - Remover\n3 - Buscar\n4 - Sair\n- : ");
    scanf("%d", &op);
    switch (op)
    {
    //insere na tabela
      case 1:
      {
        printf("Digite o numero a ser inserido na tabela: ");
        scanf("%d", &num);
        //se houver colisão
        if (table[h(num)] != NULL)
        {
          printf("Colisão. Deseja fazer o tratamento por encadeamento?(S/N): ");
          setbuf(stdin, NULL);
          scanf("%c", &tratamento);
          //insere no inicio da lista
          if (tratamento == 's' || tratamento == 'S')
          {
            Table *novo = malloc(sizeof(Table));
            novo->valor = num;
            novo->ant = NULL;
            novo->prox = table[h(num)];
            table[h(num)]->ant = novo;
            table[h(num)] = novo;

            printf("Inserido na posição %d.\n\n", h(num));
          }
          else
            break;
        }
        //se não, insere normalmente.
        else
        {
          Table *novo = malloc(sizeof(Table));
          novo->valor = num;
          novo->prox = novo->ant = NULL;
          table[h(num)] = novo;
          printf("Inserido posicao %d\n\n", h(num));
        }
        break;
      }
      //Encontra posição do valor na tabela.
      case 3:
      {
        int found = 0;
        printf("Digite o valor a ser encontrado: ");
        scanf("%d", &num);
        //se posição estiver vazia
        if (table[h(num)] == NULL)
        {
          printf("Valor não encontrado.\n\n");
          break;
        }
        //se primeiro elemento da posição for o procurado
        else if (table[h(num)]->valor == num)
        {
          printf("Valor encontrado na posição %d.\n\n", h(num));
          break;
        }
        //se primeiro elemento não for o procurado
        else
        {
          aux = table[h(num)];
          do
          {
            if (aux->valor == num)
            {
              printf("Valor encontrado na posição %d.\n\n", h(num));
              found = 1;
              break;
            }
            aux = aux->prox;
          } while (aux != NULL);
        }
        //se procurou e não encontrou
        if (!found)
          printf("Valor não encontrado.\n\n");
        break;
      }
    }
  }

  return 0;
}