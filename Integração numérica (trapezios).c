// Lucas Marthe de Almeida RA: 200567

#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>
#include<conio.h>
typedef struct tabela
{
    float x;
    float fx;
}tabela;
typedef struct parametros
{
    float a;
    float b;
    float q_trapezio;
}parametros;
typedef struct funcao
{
    float coef;
    float exp;
}funcao;
void aloca_funcao(funcao **p, int quant);
void aloca_parametros(parametros **p);
void aloca_tabela(tabela **r, float trap);
void monta_tabela(funcao *p, parametros*q, tabela *r, int quant);
void mostra_tabela(tabela *r, parametros *q,int quant);
void recebe_funcao(funcao *p, int quant);
void mostra_funcao(funcao *p, int quant);
void recebe_parametros(parametros *q);
void mostra_parametros(parametros *q);
void calcula(funcao *p, parametros*q, tabela *r, int quant);

int main()
{
    int quant,op;
    int  rep=0;
    funcao *p=NULL;
    parametros *q=NULL;
    tabela *r=NULL;
    do
    { 
        printf("\nInsira o grau do polinomio de 1 a 10?: ");
        scanf("%i", &quant);
        aloca_funcao(&p,quant+1);
        recebe_funcao(p,quant);
        mostra_funcao(p,quant);
        aloca_parametros(&q);
        recebe_parametros(q);
        mostra_parametros(q);
        aloca_tabela(&r, q->q_trapezio);
        monta_tabela(p,q,r,quant);
        mostra_tabela(r,q,quant);
        calcula(p,q,r,quant);
        printf("\n deseja repetir o processo?: Sim(1)-Nao(0)");
        fflush(stdin);
        scanf("%i", &op); 
    } while (op==1);
}
void recebe_funcao(funcao *p, int quant)
{
    int i;
    float valor;
    float expo;
    printf("\n X^[0] = TERMO INDEPENDETE");
    for ( i = quant; i >= 0; i--)
    {
        expo=i;
        printf("\n Digite um valor de coefciente para X^[%i]",i);
        scanf("%f", &valor);
        (p+i)->coef=valor;
        (p+i)->exp=expo;   
    }
}
void recebe_parametros(parametros *q)
{
    float a;
    float b;
    float trap;
    float aux;
    printf("\nDigite o limite inferior a :");
    scanf("%f",&a);
    q->a=a;
    printf("\nDigite o limite superior b :");
    scanf("%f",&b);
    q->b=b;
    printf("\n Insira a quantidade de trapezios desejada: ");
    scanf("%f",&trap);
    if ( q->a > q->b)
    {
       printf(" a ordem correta dos limites e [a]: %.2f e [b]: %.2f", q->a , q->b);
        aux=q->a;
        q->a=q->b;
        q->b=aux;
    }
    q->q_trapezio=trap;  
}
void mostra_funcao(funcao *p, int quant)
{  
    int i;
    printf("\n\no polinomio inserido foi: ");
        for ( i = quant; i >= 0; i--)
        {  
            printf("%.2fX^%.2f  ",(p+i)->coef,(p+i)->exp);   
        }
        
}
void mostra_parametros(parametros *p)
{
    printf("\n Limite a: %f \n Limite b: %f \n Quantidade de trapezios: %f\n", p->a,p->b,p->q_trapezio);
   
}
void monta_tabela(funcao *p, parametros*q , tabela *r, int quant)
{
    float result,intervalo, prog, aux, cont_a=0,cont_b=0, aux2;
    int i,j,num;
    float a=q->a, b=q->b;
    num=q->q_trapezio;
    intervalo = (q->b)-(q->a);
    prog= (intervalo/(q->q_trapezio));      
for ( i = 0; i < quant+1; i++)
{
    cont_a+= (p+i)->coef*pow(a,(p+i)->exp);   
}      
r->fx=cont_a;
r->x=a;  
for ( i = 0; i < quant+1; i++)
{
    cont_b+= (p+i)->coef*pow(b,(p+i)->exp);      
} 
(r+num)->fx=cont_b; 
(r+num)->x=b; 
for ( i = 1; i < num; i++)
{
    aux=0;
    for ( j = 0; j < quant+1; j++)
    {
       aux+= (p+j)->coef*pow(a+(prog*i),(p+j)->exp);
        aux2=a+(prog*i);
    
    }
    (r+i)->fx=aux;
    (r+i)->x=aux2;
   
}
}
void mostra_tabela(tabela *r, parametros *q,int quant)
{
    int i;
    float num=q->q_trapezio;
    printf("   X     F(x)    ");
    for ( i = 0; i < num+1; i++)
    {
    printf("\n%.2f    %.2f",(r+i)->x,(r+i)->fx);
    } 
}
void calcula(funcao *p, parametros*q, tabela *r, int quant)
{
    float soma=0,h=0;
    int i;
    int aux= q->q_trapezio;
    h=((q->b)-(q->a))/(q->q_trapezio);
    for ( i = 1; i < q->q_trapezio; i++)
    {
     soma+=(r+i)->fx;
    }
    printf("\nH: %.2f", h);
    printf("\n\n%.2f", h/2*(((r+aux)->fx)+(r->fx)+(2*soma)));
}
void aloca_funcao(funcao **p, int quant)
{
    if( (*p=(funcao *)realloc(*p,quant*sizeof(funcao)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }   
}
void aloca_parametros(parametros **p)
{
    if( (*p=(parametros *)realloc(*p,1*sizeof(parametros)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }   
}
void aloca_tabela(tabela **r, float trap)
{
        if( (*r=(tabela *)realloc(*r,trap*sizeof(tabela)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }   
}
