// by : Lucas Marthe de Almeida
#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>

//Fun��es
void recebeParametros(float *p);
void alocaParametros(float **p, int tam);
float calculoMed(float *p);
float calculoFx(float *p, float m);
float media_cont(float a, float b);

int main()
{
float media=0;
float *vet=NULL;
alocaParametros(&vet,7);
recebeParametros(vet);
media=calculoMed(vet);
calculoFx(vet,media);
}

//Aloca��o de par�metros
void alocaParametros(float **p, int tam)
{
    tam=4;
    if( (*p=(float *)realloc(*p,tam*sizeof(float)) )==NULL)
    {
        printf("Erro na alocao!");
        exit(1);   
    }
    printf("\n Espaco alocado com sucesso");
}

//Utiliza��o de Matriz de Ponteiros
void recebeParametros(float *p)
{
    printf("\n\n Digite os valores coefcientes de\n x, x^2, x^3 e o termo idependente: ");
    scanf(" %f%f%f%f", p+0,p+1,p+2, p+6);

    printf("\n insira o valor do erro: ");    
    scanf("%f", p+3);

    printf("\n Insira o valor de A: ");
    scanf("%f", p+4);

    printf("\n Insira o valor de B: ");
    scanf("%f", p+5);
}

//Calcula a m�dia entre A e B => (A+B)/2 = M	
float calculoMed(float *p)
{
	float m=0;
	m=(*(p+5)+*(p+4))/2;
	return  m;
}

float calculoFx (float *p, float m)
{   float modm;
    float a=*(p+4);
    float b=*(p+5);
    float conta_a=0;
    float conta_b=0;
    float conta_m=0;
 	
 	//Estrutua de repeti��o para achar o m < erro
    do
    {	//F�rmula fornecida pelo usu�rio
    	conta_a = *(p+2)*pow(a,3)+*(p+1)*pow(a,2)+*(p+0)*a+*(p+6);
   		conta_b = *(p+2)*pow(b,3)+*(p+1)*pow(b,2)+*(p+0)*b+*(p+6);
   		conta_m = *(p+2)*pow(m,3)+*(p+1)*pow(m,2)+*(p+0)*m+*(p+6);
        
		a=*(p+4);
        b=*(p+5);
        
		printf("\n m = %.3f \n a = %.3f \n b = %.3f \n F(a) = %.3f \n F(m) = %.3f \n F(b) = %.3f\n\n",m, *(p+4),*(p+5),conta_a, conta_m , conta_b );
       
       //Condi��o para "escorregar" o M para A ou B
       if (conta_m<0 && conta_a>0)
       {
        *(p+5)=m; //*(p+5)=b    *(p+4)=a   *(p+3)= erro  m= media entre a e b     conta_a= F(a) conta_b=F(b)  conta_m= f(m)
       }
       else if(conta_m<0 && conta_b>0)
       {
        *(p+4)=m;
       }
       else if(conta_m>0 && conta_a<0)
       {
        *(p+5)=m;
       }
        else if(conta_m>0 && conta_b<0)
       {
        *(p+4)=m;
       }
        
        m = (a+b)/2;
        modm= fabs(conta_m); //Deixa na compara��o o valor de f(x) em m�dulo, possibilitando a estrutura de deci��o acima
		
    }while(modm>*(p+3));
    
    system("cls");
    printf("\nA raiz da funcao eh %.3f", m);
    printf("\n*Importante: O resultado eh apenas arredondado no final, ou seja, pode variar milesimos depois da virgula\n\n");
}
