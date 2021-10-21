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

            printf("Valor %d inserido na posição %d.\n\n",num, h(num));
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
          printf("Valor %d inserido posicao %d\n\n",num, h(num));
        }
        break;
      }

      //remove da tabela
      case 2:
      {
        int found=0;
        printf("Digite o valor a ser removido: ");
        scanf("%d",&num);
        //se posição estiver vazia
        if (table[h(num)] == NULL)
        {
          printf("Valor não encontrado.\n\n");
          break;
        }
        //se primeiro valor da posição for o desejado
        else if (table[h(num)]->valor == num)
        {
          printf("valor %d na posicao %d removido.\n\n",num,h(num));
          //se for o único da posiçãp
          if(table[h(num)]->prox==NULL)
          {
            free(table[h(num)]);
            table[h(num)]=NULL;
          }
          //se não for o único
          else
          {
            table[h(num)]=table[h(num)]->prox;
            free(table[h(num)]->ant);
            table[h(num)]->ant=NULL;
          }
          break;
        }
        //procura valor na posição
        else
        {
          aux = table[h(num)];
          do
          { //se encontrou
            if (aux->valor == num)
            {
              printf("Valor %d na posição %d removido.\n\n",num, h(num));
              //se for o último
              if(aux->prox==NULL){
                aux->ant->prox=NULL;
                free(aux);
              }
              //se não for o último
              else{
                aux->ant->prox=aux->prox;
                aux->prox->ant=aux->ant;
                free(aux);
              }
              found = 1;
              break;
            }
            aux = aux->prox;
          } while (aux != NULL);
        }
        //se o valor não foi encontrado
        if (!found)
          printf("Valor não encontrado.\n\n");
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
          printf("Valor %d encontrado na posição %d.\n\n",num, h(num));
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
              printf("Valor %d encontrado na posição %d.\n\n",num, h(num));
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