#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define TAM 4

void clear () 
{    
  while ( getchar() != '\n' );
}

typedef struct
{
    int topo;
    int item[TAM];
}TPilha;

void InicializaPilha(TPilha *p)
{
    p -> topo=-1;
}

bool PilhaVazia(TPilha *p)
{
    if( p -> topo == -1)
    {
        return true;
    }
  else
    {
        return false;
    }
}

bool PilhaCheia(TPilha *p)
{
    if (p -> topo == TAM-1)
    {
        return true;
    }
  else
    {
        return false;
    }
}

void Empilha(TPilha *p, int x)
{
    if(PilhaCheia(p)==false)
    {
        p->topo++;
        p->item[p->topo]=x;
    }
}

void Desempilha(TPilha *p, int x)
{
    if(PilhaVazia(p)==false)
    {
        x=p->item[p->topo];
        p->topo--;
    }
}

int ElementoDoTopo(TPilha *p, int x)
{
    if(PilhaVazia(p)==false)
    {
        x=p->item[p->topo];
        return x;
    }
}

void InicializaJogo(TPilha *Pilha[], int n)
{
    for(int i=0; i<n+2; i++)
    {
        InicializaPilha(Pilha[i]);
    }
}

void RandomizaJogo(TPilha *Pilha[], int n)
{
    int x;
    srand(time(0));
    for(int i=0;i<100;i++)
    {
        (rand()%100);
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<TAM; j++)
        {
            x = (rand() %n);
            if(PilhaCheia(Pilha[x]))
            {
                j--;
            }
            else
            {
                Empilha(Pilha[x],i+1);
            }
        }
    }
}

void ImprimePilha(TPilha *Pilha[], int n)
{
    for(int j=TAM-1; j>-1;j--)
    {
        for(int i=0; i<n; i++)
        {
            if(Pilha[i]->topo>=j)
            {
                printf("|%d| ", Pilha[i]->item[j]);
            }
            else
            printf("| | ");
        }
        printf("\n");
    }

    for(int i=0; i<n; i++)
    {
        printf("¯¯¯ ");
    }

    printf("\n");

    for(int i=0; i<n; i++)
    {
        printf(" %d  ",i);
    }
}

void ManipulaPilha(TPilha *Pilha[], int n)
{
    int a,b,x;
    printf("\n\nSelecione a Pilha que deseja desempilhar: ");
    scanf("%d",&a);
    printf("Selecione a Pilha que deseja empilhar: ");
    scanf("%d",&b);
    printf("\n");
    clear();
    if(((0<=a&&a<n)&&(0<=b&&b<n)) && (PilhaVazia(Pilha[a])==false) && ((ElementoDoTopo(Pilha[a],x) == ElementoDoTopo(Pilha[b],x)) || PilhaVazia(Pilha[b])) && (PilhaCheia(Pilha[b])==false))
    {
        x=ElementoDoTopo(Pilha[a],x);
        Desempilha(Pilha[a],x);
        Empilha(Pilha[b],x);
    }
    else
    {
        printf("\n**Operacao INVALIDA. Tente Novamente**\n\n");
    }
}

bool EncerraJogo(TPilha *Pilha[], int n)
{
    int h=0;
    for(int i=0;i<n;i++)
    {
        if (PilhaCheia(Pilha[i])||PilhaVazia(Pilha[i]))
        {
            if((Pilha[i]->item[0]==Pilha[i]->item[1] && Pilha[i]->item[0]==Pilha[i]->item[2] && Pilha[i]->item[0]==Pilha[i]->item[3]) || PilhaVazia(Pilha[i]))
            {
                h++;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        if (h==n)
        {
            printf("\n============| O Jogo Terminou |============\n");
            printf("          -=+xx VOCE VENCEU xx+=-           \n");
            return true;
        }
    }
}

int main(void)
{
    TPilha *p = (TPilha*)malloc(sizeof(TPilha));

    int n;
    char aux;

    printf("\n============| Trabalho 1 - ED |============\n");
    printf("\nPor: Amanda Viscovini e Lucas Pinheiro\n");
    do
    {
        printf("\n=============================================\n");
        printf("==================*INICIO*===================\n");
        do
        {
            printf("\nDigite com quantos numeros diferentes voce quer jogar entre 3 e 9: ");
            scanf("%d",&n);
            printf("\n");
            clear();
        }while(n<3 || n>9);

        TPilha objetos[n+2];
        TPilha *Pilha[n+2];

        for(int i = 0;i<n+2; i++)
        {
            Pilha[i] = &objetos[i];
        }

        InicializaJogo(Pilha,n);
        RandomizaJogo(Pilha,n);
        ImprimePilha(Pilha,n+2);

        while(EncerraJogo(Pilha,n+2)==false)
        {
            ManipulaPilha(Pilha,n+2);
            ImprimePilha(Pilha,n+2);
        }

        printf("\nDeseja Jogar outra vez? s/n\n");
        scanf("%s",&aux);
        clear();
    } while (aux=='s');
}