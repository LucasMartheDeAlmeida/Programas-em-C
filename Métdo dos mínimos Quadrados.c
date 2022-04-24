//Lucas Marthe de Almeida       |  RA: 200567

#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>
#include<conio.h>

//funçõoes referentes a alocação de ponteiros que armazenarão os valores inseridos pelo usuário
void aloca_x(float **var, int num);
void aloca_fx(float **fun, int num);
// função referente a entrada dos valores
void recebe_valores(float *var, float *fun, int num);
//funçôoes que realizam os calculos
void sistema_vetores(float *var, float *fun, int num);
void sistema_linear(float *vet,float *vetFx,int num,int tam,int op);

//alocação dos vetores auxiliares
void aloca_L(float **l, int num);
void aloca_vet(float **vet, int tam);
void aloca_vet_Fx(float **vetFx, int num);



int main()
{   
    float *var=NULL, *fun=NULL;
    int num;
    int op=0;
    do{
    op=1;
    printf("\n\n\nDigite o numero de termos da tabela de X e F(x): ");
    scanf("%i", &num);
    aloca_x(&var,num);
    aloca_fx(&fun,num);
    recebe_valores(var,fun,num);
    sistema_vetores(var,fun,num);
    do
    {
    printf("\n Deseja realizar mais uma execucao ?\n(1)-sim  (2)-nao");
    scanf("%i",&op);
    } while (op!=2 && op!=1);
    }while (op==1);
    
}
void recebe_valores(float *var, float *fun, int num)
{
    int i;
    printf("\nDigite os valores de X[0] ate X[%i]\n", num-1);
    fflush(stdin);

    for (i = 0; i < num; i++)
    {
        printf("X[%i] = ", i);
        scanf("%f", var+i);   //entrada dos valores para X
    }

    printf("\nDigite os valores de Fx[0] ate Fx[%i]\n", num-1);
    for (i = 0; i < num; i++)
    {
        printf("F(x)[%i] = ", i);
        scanf("\n %f", fun+i);   //entrada dos valores para Fx
    }
}

void sistema_vetores(float *var, float *fun, int num)
{
    int soma;
    int i;
    int j;
    int op;
    int tam= num*num;
    float aux;
    float aux1;
    float aux3;    
    float *vet=NULL;
    float *vetFx=NULL;
    aloca_vet(&vet,tam);
    aloca_vet_Fx(&vetFx,num);

    do
    { 
        printf("\nDigite uma opcao (1) Reta (2) Parabola : ");
        fflush(stdin);
        scanf("%i", &op);    // laço que determinnará se o calculo será referente a uma reta ou parábola 1==reta 2==parabola
        fflush(stdin);

    }while(op != 2 && op !=1 && op !=3);
    
    printf ("\n----Vetores----\n");
   



    if (op == 1 )  // "vetorização" dos valoroes inseridos para o formato Reta
    {
        for ( i = 0; i < num; i++)
        {
            *(vetFx+i)=*(fun+i);
            printf("%.2f ", *(vetFx+i));

            for ( j = 0; j < 2; j++)
            {
                *(vet+i*num+j)=pow(*(var+i),j);
                printf("%.2f ", *(vet+i*num+j));
            }
        printf("\n");
        }
    }

    if (op== 2) // "vetorização" dos valoroes inseridos para o formato Parabola
    {
        for ( i = 0; i < num; i++)
        {
            *(vetFx+i)=*(fun+i);
            printf("%.2f ", *(vetFx+i));
            for ( j = 0; j<3;j++)
            {
                *(vet+i*num+j)=pow(*(var+i),j);
                printf("%.2f ", *(vet+i*num+j));
            }
        printf("\n");
     }
 }

    sistema_linear(vet,vetFx,num,tam,op); // chamada da função que realizará os proximoos calculos, sistema linear e eliminação de gauss
}

void sistema_linear(float *vet,float *vetFx,int num,int tam,int op)
{
    float somX=0,somX2=0,somY=0,somX3=0,somX4=0,somX5=0,somX6=0,somXY=0,somX2Y,b=0,a=0,a1=0,a2=0,medy,medx,n=num;
    float piv=num,M21,M31,M32,piv2;
    int i,j,k;
    float *L1=NULL;
    float *L2=NULL;
    float *L3=NULL;
    float inv=-1;

//alocação dos vvetores que serão usados para fazer a eliminação de gauss

    aloca_L(&L1,num+1); 
    aloca_L(&L2,num+1);
    aloca_L(&L3,num+1);

    if (op==1) // realização dos calculos para reta
    {
        for ( i = 0; i < num; i++)   //laço que retornará os elementos do sistema linear
        {
            somX += *(vet+i*num+1);   
            somY += *(vetFx+i);
            somX2+=*(vet+i*num+1) * *(vet+i*num+1);
            somXY+=*(vet+i*num+1) * *(vetFx+i);
        }
        b= (((num*somXY)-(somX * somY))/((num * somX2)- (somX * somX)));  //calculo de b para termo idependente
    printf("\n %.2f \n", somX);
    printf("\n %.2f \n", somY);
    printf("\n %.2f \n", somX2); 
    printf("\n %.2f \n", somXY);
    printf("\n %.2f \n", b);

    printf("Sistema Linear: \n %i.00 %.2f %.2f \n %.2f %.2f %.2f\n\n\n",num,somX,somY,somX,somX2,somXY);
       
    //medias de X e Y que serão usadas para calcular o coef de X

       medx= somX/num;
       medy= somY/num;
       a= (medy-(b*medx)); //calculo do coef de X
       
    
    printf("a reta que melhor descreve o conjunto inserido e  %.2f + %.2fx\n\n", b,a);
    }
    

    else if (op==2) // estrutura que será responsavel por calcular a parabola
    {
         for ( i = 0; i < num; i++) //definição dos elementos de uma matriz quadrada para calculo da parabaloa
        {
        somX += *(vet+i*num)* *(vet+i*num+1);
        somX2+= *(vet+i*num+1)* *(vet+i*num+1);
        somX3+= *(vet+i*num+2)* *(vet+i*num+1);
        somX4+= *(vet+i*num+2)* *(vet+i*num+2);
        somY += *(vetFx+i);
        somXY += *(vetFx+i)* *(vet+i*num+1);
        somX2Y += *(vetFx+i)* *(vet+i*num+2);

        }
        M21=somX/num; 
        M31=somX2/num;

    *(L1)=num;  //posicionamennto dos elemenntos da matriz em um ponteiro que representara a linha 1
    *(L1+1)=somX; 
    *(L1+2)=somX2;
    *(L1+3)=somY;

    *(L2)=somX;//posicionamennto dos elemenntos da matriz em um ponteiro que representara a linha 2
    *(L2+1)=somX2;
    *(L2+2)=somX3;
    *(L2+3)=somXY;   

    *(L3)=somX2; //posicionamennto dos elemenntos da matriz em um ponteiro que representara a linha 3
    *(L3+1)=somX3;
    *(L3+2)=somX4;
    *(L3+3)=somX2Y;



        for ( i = 0; i < num+1; i++)  //alterações nas linhas para fazer a primeira eliminação com o uso de M21 e M31 relacionados ao primeiro pivo usado
        {
            *(L2+i)-=*(L1+i)*M21;
        }
        for ( i = 0; i < num+1; i++)
        {
            *(L3+i)-=*(L1+i)*M31;
        }
        
        printf("\n\n\n\n SIstema Linear : \n   %i.00  %.2f   %.2f   %.2f\n   %.2f   %.2f   %.2f   %.2f\n   %.2f   %.2f   %.2f   %.2f\n ", num,somX,somX2,somY,somX,somX2,somX3,somXY,somX2,somX3,somX4,somX2Y);
    piv2=*(L2+1); //pivo do segunndo passo e M32
M32=*(L3+1)/piv2;
printf("\n Pivo : %.2f ", piv);
printf("\n Pivo2: %.2f ", piv2);
printf("\n M21: %.2f ", M21);
printf("\n M31: %.2f ", M31);
printf("\n M32: %.2f ", M32);


        for ( i = 0; i < num+1; i++) //alteração da ultima linha para realizar eliminnação de gauss
        {
            *(L3+i)-=*(L2+i)*M32;
        }



printf("\n\n\n Eliminacao de Gauss\n");  //exibição do novo sistema afim de calcular o coef de cada termo
for ( i = 0; i < num+1; i++)
{
   printf("%.2f  ", *(L1+i));
}
printf("\n");
for ( i = 0; i < num+1; i++)
{
   printf("%.2f  ", *(L2+i));
}
printf("\n");
for ( i = 0; i < num+1; i++)
{
   printf("%.2f  ", *(L3+i));
}

a2 = (*(L3+3)/ *(L3+2));  // calculo de cada  coeficiente
a1 = (*(L2+3)-(*(L2+2)*a2))/ *(L2+1);
a = (*(L1+3)-((*(L1+1)*a1)+(*(L1+2)*a2)))/ *(L1);

printf("\n\n A parabola que melhor descreve o conjunto e :  %.2f + %.2f x +%.2f x^2",a,a1,a2);

    }



}

// daqui para baixo exitem soamente funções de alocação
void aloca_fx(float **fun, int num)
{
    if( (*fun=(float *)realloc(*fun,num*sizeof(float)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }
    
}    
void aloca_x(float **var, int num)
{
    if( (*var=(float *)realloc(*var,num*sizeof(float)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }
    
}
void aloca_vet(float **vet, int tam)
{
    if( (*vet=(float *)realloc(*vet,tam*sizeof(float)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }
    
}  
void aloca_L(float **lin, int tam)
{
        if( (*lin=(float *)realloc(*lin,tam*sizeof(float)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }
}
void aloca_vet_Fx(float **vetFx, int num)
{
    if( (*vetFx=(float *)realloc(*vetFx,num*sizeof(float)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }   
}