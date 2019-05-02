#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIN 1000
typedef struct Nodos{
  //lista de numeros
  int numero;
  int posI;
  int posJ;
  struct Nodos *siguiente;
} Nodo;
typedef struct Listas{
  int tamano;
  Nodo *inicio;
  Nodo *fin; //por comodidad por si piden el el ultimo dato
} Lista;
void agregar(Lista *lista, int valor,int posI,int posJ){
  Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
  nuevo->siguiente = NULL;
  nuevo->numero = valor;
  nuevo->posI = posI;
  nuevo->posJ = posJ;
  //si es el primer elemento a agregar
  if(lista->tamano == 0){
    lista->inicio = nuevo;
    lista->fin = nuevo;
    lista->tamano++;
  }
  else{
    lista->tamano++;
    lista->fin->siguiente = nuevo;
    lista->fin = nuevo;
  }
}
void eliminarLista(Lista *lista){
  Nodo *actual;
  Nodo *aux;
  actual = lista->inicio;
  while(actual!=NULL){
    aux = actual;
    actual = actual->siguiente;
    free(aux);
  }
}
void inicializar(Lista *lista){
  lista->inicio = NULL;
  lista->fin = NULL;
  lista->tamano= 0;
}
void imprimir(Lista *lista){
  Nodo *actual;
  actual = lista->inicio;
  while(actual!=NULL){
    printf("%i \n", actual->numero);
    printf("la posicion I es:%i\n",actual->posI);
    printf("la posicion J es:%i\n",actual->posJ);
    actual = actual->siguiente;
  }
}
int tamano;
void imprimirCM(Lista *lista){
	Nodo *actual;
	actual = lista->inicio;
	printf("el tamano es :%i\n",tamano);
	while(actual != NULL){
		printf("%i ", actual->numero);
		//printf("el posJ %i,tamano -1 = %i \n",actual->posJ,tamano-1);
		if(actual->posJ == tamano - 1){
			printf("\n");
		}
		actual = actual->siguiente;
	}
}
int m,n;
double **leermatriz(){
   //fp es un dato tipo FILE y usando fopen para abrir el archivo de entrada .txt en modo lectura 
   FILE* fp=fopen("matriz1.in","r");
   // linea[MAX_LIN] es un arreglo estatico de tamaño 1000 (MAX_LINE = 1000) donde en el se almacenar cada una de las lineas en el archivo de entrada .txt
   // *p es un puntero que utilizando la funcion strtok va a separar los datos según la separacion que deseamos dar.
   char linea[MAX_LIN], *p;
   // val es la variable que almacenara cada dato de la linea en dato entero para posteriormente guardarla en la matriz
   int val;
   // aqui reservamos memoria para la matriz con la funcion calloc
   double **matriz= (double **) calloc(1000, sizeof(double*)) ;
   //inicializamos m con valor -1
   m=-1;
   while (fgets(linea, MAX_LIN, fp)!=NULL) {
     m=m+1;
     //aqui reservamos memoria para cada uno de los espacios de la matriz
     //printf("La linea es : %s\n", linea);
     matriz[m] = (double *) calloc(MAX_LIN, sizeof(double));
     p = strtok(linea," ");
     n=-1;
     while(p != NULL) {
       n=n+1;
       //con sscanf le damos le asignamos a val el valor que contiene p para posteriormente asigarle val a matriz en la posicion m,n
       sscanf(p,"%d",&val);
       //printf("%d\n",val);
       matriz[m][n] = val;
       p=strtok(NULL," ");
     }
   }
   //imprimirMatriz(matriz);
   //retornamos la matriz con los datos del archivo de entrada.in en ella
   return matriz;
   fclose(fp);
}
//puntero double de dos dimensiones para almacenar las filas y columnas del archivo de entrada.
double **matriz;
int multiplicar(Lista *columna,Lista *fila){
	Nodo *actualFila,*actualColumna;
	actualFila = fila->inicio;
	actualColumna = columna->inicio;
	int resultadoM,resultadoS = 0;
	while(actualFila != NULL){
		actualColumna = columna->inicio;
		resultadoM = 0;
		while(actualColumna != NULL){
			if(actualFila->posI == actualColumna->posJ){
				resultadoM = (actualFila->numero) * (actualColumna->numero);
			}
			actualColumna = actualColumna->siguiente;
		}
		resultadoS = resultadoS + resultadoM;
		actualFila = actualFila->siguiente;
	}
	return resultadoS;
}
int ModPosicion(Lista *lista,Lista *copia,int posI,int posJ){
	Nodo *aux1,*aux2;
	Lista *fila = (Lista *)malloc(sizeof(Lista));
  	Lista *columna = (Lista *)malloc(sizeof(Lista));
  	inicializar(fila);
  	inicializar(columna);
	aux1 = lista->inicio;
	aux2 = copia->inicio;
	while(aux1 != NULL && aux2 != NULL){
		if(aux1->posJ == posJ){
			agregar(columna,aux1->numero,aux1->posI,aux1->posJ);
		}
		if(aux2->posI == posI){
			agregar(fila,aux2->numero,aux2->posI,aux2->posJ);
		}
		aux1 = aux1->siguiente;
		aux2 = aux2->siguiente;
	}
  	int N = multiplicar(fila,columna);
  	free(aux1);
  	free(aux2);
	return N;

}
Lista *multiplicarM(Lista *lista,Lista *copia){
	Lista *L1 = (Lista *)malloc(sizeof(Lista));
	double N;
	double **matriz = (double **) calloc(1000, sizeof(double*));
	for (int i = 0; i < tamano; ++i)
	{
		matriz[i] = (double *) calloc(1000, sizeof(double)) ;
	}
	for (int i = 0; i < tamano; ++i)
  	{
  		for (int j = 0; j < tamano; ++j)
  		{
  			N = ModPosicion(lista,copia,i,j);
  			agregar(L1,N,i,j);
  		}
  	}
  	return L1;
}
Lista *PowMatriz(Lista *lista,int Nexponente){
	Lista *copia = (Lista *)malloc(sizeof(Lista));
	copia = lista;
	//imprimirCM(copia);
	int i = 0;
	if(Nexponente < 2){
		imprimirCM(lista);
	}else{
		while(i < Nexponente - 1){
			lista = multiplicarM(lista,copia);
  			i++;
		}
	}
	//imprimirCM(lista);
	free(copia);
	return lista;
}
int imprimirMatriz(double **matriz){
	int i,j;
	for (int i = 0; i <= tamano; ++i)
	{
		for (int j = 0; j < tamano; ++j)
		{
			printf("%f  ",matriz[i][j]);
		}
		printf("\n");
	}
	return 0;
}
int Npotencia;
int main(){
  matriz = leermatriz();
  tamano = matriz[0][0];
  Npotencia = matriz[0][1];
  printf("el tamano es :%i\n",tamano);
  printf("el numero del exponente es :%i\n",Npotencia);
  imprimirMatriz(matriz);
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  Lista *Mresultante = (Lista *)malloc(sizeof(Lista));
  inicializar(lista);
  for (int i = 1; i <= tamano; ++i)
	for (int j = 0; j < tamano; ++j)
		agregar(lista,matriz[i][j],i-1,j);
  imprimirCM(lista);	
  Mresultante = PowMatriz(lista,Npotencia);
  imprimirCM(Mresultante);
  //free(lista);
  free(Mresultante);
}