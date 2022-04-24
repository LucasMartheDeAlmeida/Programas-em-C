#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>
#include<conio.h>
//-----------------------------------------------------------------------Declaração------------------------------------------------------------

void aloca_x(float **p, int quant);
void aloca_fx(float **p, int quant);
void recebe_x(float *p, int quant);
void recebe_fx(float *p, int quant);
void interpolacao(float *p_x,float *p_fx, int quant);


int main()
{
    float *var=NULL, *fun=NULL;
    int quant;
    valor:
    printf("\nDigite o numero de valores de x e F(x): ");
    scanf("%i", &quant);
    if (quant<0 || quant==0)
    {
        printf("\nDigite um valor valido\n");
        goto valor;
    }
    
//--------------------------------------------------------------------Chamada de Funções-------------------------------------------------------

    aloca_x(&var,quant);
    aloca_fx(&fun,quant);
    recebe_x(var,quant);
    recebe_fx(fun,quant);
    interpolacao(var,fun,quant);
}

//--------------------------------------------------------------------------Funções------------------------------------------------------------

void aloca_x(float **p, int quant)
{
    if( (*p=(float *)realloc(*p,quant*sizeof(float)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }
}

void aloca_fx(float **p, int quant)
{
    if( (*p=(float *)realloc(*p,quant*sizeof(float)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }
}

void recebe_x (float *p, int quant)
{
    int i;
        printf("\nDigite os valores de cada ponto de x : ");
        for ( i = 0; i < quant; i++)
        {
            printf("\nx[%i]: ", i);
            scanf("%f", p+i);
        }
}

void recebe_fx (float *p, int quant)
{
    int i;
        printf("\nDigite o valor de cada ponto de F(x): ");
        for ( i = 0; i < quant; i++)
        {
            printf("\nF(%i): ", i);
            scanf("%f", p+i);
        }

}

void interpolacao (float *p_x,float *p_fx, int quant)
{
    float in, resp=0;;
    float L=1, L2=1;
    int aux = quant - 1;
    int i, j;
    int op;
    do{
    entrada:
    printf("\nDigite o valor a ser interpolado: ");
    scanf("%f", &in);
    if (in>*(p_x+aux) ||in< *(p_x))
    {
        printf("\nO valor a ser digitado deve estar entre X[0] e X[%i]\n ", aux);
        goto entrada;
    }
       
    printf("\n\n");
    printf("----------Calculo de Lagrange----------");
    printf("\n");

    printf("\nLn calculados:\n");

    for(i=0;i<quant;i++)
    {
        L=1.0;
        L2=1.0;

        for(j=0;j<quant;j++)
        {
            if(i!=j)
            {
                L=L * (in - *(p_x + j));
                L2=L2 * (*(p_x + i) - *(p_x + j));
            }
        
        }

        printf("\nL[%i] = %.3f ", i, L/L2);
        printf("\n");

        resp=resp + ((L / L2) * *(p_fx + i));
    }

    printf("\nO ponto %.3f em F(x) = %.3f",in ,resp);
    printf("\n\n\n");

    resp=0;
    opcao:

    printf("\nDeseja interpolar outro valor?\n(1)-sim\n(2)-nao ");
    scanf("%i", &op);
    
    if (op!= 1 && op!= 2)
    {
        printf("\n digite uma opcao valida");
        goto opcao;
    }
    else if(op == 2)
    {
        exit(1);
    }
    
    }while (op==1);

}