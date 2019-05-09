/**
autor : Diego Bustamante Núñez
rut : 20.067.251-8






**/
//includimos libreria de la biblioteca estandar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//definimos una variable para poder almacenar los datos en un arreglo bidimensional
#define MAX_LIN 1000
/******* variables globales ********/
//puntero double de dos dimensiones para almacenar las filas y columnas del archivo de entrada.
double **matriz;
int Npotencia;
int tamano;
int m,n;
//declaramos un struct para hacer nuestros nodos , donde se incluira el numero junto con las posiciones i y j.
typedef struct Nodos{
  //el numero es una variable tipo double.
  double numero;
  //los numeros de las posiciones son variables tipo int 
  int posI;
  int posJ;
  //declaramos el apuntador para el nodo siguiente ya que usaremos una lista simplemente enlazada.
  struct Nodos *siguiente;
} Nodo;
//declaramos una struct lista para la cabecera de la lista simplemente enlazada.
typedef struct Listas{
  //declaramos el tamano del arreglo 
  int tamano;
  //nodo inicio y nodo fin
  Nodo *inicio;
  Nodo *fin; //por comodidad por si piden el el ultimo dato
} Lista;
/*
void agregar(lista,valor,posI,posJ)
entradas:
-una lista tipo struct Lista
-un valor tipo double
-dos valores posiciones tipo int 
salidas: nada.
agregar lo que hace es crear un nodo y asignandole cada elemento del nodo respectivamente a lo que entra
para finalizar lo que hace es aumentar el tamaño de este.
*/
void agregar(Lista *lista, double valor,int posI,int posJ){
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
/*
eliminar lista:
entradas:una lista simplemente enlazada.
salidas: nada
funcion que elimina una lista utilizando un free en cada uno de los nodos.
*/
void eliminarLista(Lista *lista){
  //creamos dos variables tipo nodo
  Nodo *actual,*aux;
  //inicializamos el nodo actual en el inicio de la cabecera de la lista
  actual = lista->inicio;
  //iteramos para recorrer la lista
  while(actual!=NULL){
    //igualamos el aux a actual para que liberemos el nodo con la funcion free
    aux = actual;
    //actual lo cambias al siguiente de actual
    actual = actual->siguiente;
    //liberamos aux
    free(aux);
  }
}
/*
inicializar:
entradas:una lista simplemente enlazada
salidas:nada
funcion que se encarga de darle valores iniciales a una lista

*/
void inicializar(Lista *lista){
  // a la lista que ingresa le apuntaremos a inicio y fin un NULL y al tamano = 0;
  lista->inicio = NULL;
  lista->fin = NULL;
  lista->tamano= 0;
}
/*
imprimirCM:
entradas:una lista simplemente enlazada.
salidas:nada
funcion que se encarga de imprimir los elementos numero de la lista en forma de matriz.
*/
void imprimirCM(Lista *lista){
  //creamos una variable tipo nodo
  Nodo *actual;
  //inicializamos el nodo en la cabecera de la lista
  actual = lista->inicio;
  //iteramos para recorrer la lista
  while(actual != NULL){
    //imprimimos el numero del nodo actual
    printf("%.f ", actual->numero);
    //si la posicion j es igual al limite , imprime un salto de linea
    if(actual->posJ == tamano - 1){
      printf("\n");
    }
    //igualamos el actual apuntandolo al actual siguiente
    actual = actual->siguiente;
  }
}
/*
leermatriz():
entradas:nada
salidas:nada
funcion que se encarga de leer el archivo matriz.in y crea un arreglo bidimensional para almacenar todos los datos que hay 
en nuestro archivo de entrada

*/
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
       sscanf(p,"%i",&val);
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

/*
multiplicar():
entradas:dos listas simplemente enlazadas , fila y columna
salidas:resultado de la suma de multiplicaciones de numeros en fila y columna
funcion que realiza la multiplicacion entre el numeros que hay dentro de las listas fila y columna para posteriormente
sumar los resultados y retornarlo en un solo resultado.




*/
int multiplicar(Lista *columna,Lista *fila){
  //creamos dos nodos fila y columna
  Nodo *actualFila,*actualColumna;
  //inicializamos ambos nodos en inicio de cada lista
  actualFila = fila->inicio;
  actualColumna = columna->inicio;
  //variables enteras en las que se almacenaran el resultados de las multiplicaciones y la suma final
  int resultadoM,resultadoS = 0;
  //recorremos la lista de las filas 
  while(actualFila != NULL){
    //actualcolumna lo inicializamos en el inicio de la lista columna
    actualColumna = columna->inicio;
    //el resultado de la multiplicacion la hacemos 0;
    resultadoM = 0;
    //recorremos la lista de las filas
    while(actualColumna != NULL){
      //si el numero de la  la posicion en la fila es igual al numero de la posicion en las columna,se multiplican
      if(actualFila->posI == actualColumna->posJ){
        resultadoM = (actualFila->numero) * (actualColumna->numero);
      }
      //cambiamos el actualcolumna apuntandolo al siguiente de este.
      actualColumna = actualColumna->siguiente;
    }
    //el resultado de las sumas lo vamos aumentando en el resultado de las multiplicaciones
    resultadoS = resultadoS + resultadoM;
    //cambias el actualfila apuntandolo al siguiente de este.
    actualFila = actualFila->siguiente;
  }
  //retornamos el resultadoS que tiene almacenado el resultado de la sumas de todas las multiplicaciones hechas.
  return resultadoS;
}
/*
ModPosicion:
entradas:dos listas simplemente enlazadas,dos enteros que indican la posicion
salidas: un Numero entero
funcion que se encarga de obtener el valor especifico de una matriz dandole como entradas las posiciones del resultado que queremos obtener
*/
int ModPosicion(Lista *lista,Lista *copia,int posI,int posJ){
  //creamos 2 nodos para recorrer las listas por separados
  Nodo *aux1,*aux2;
  //creamos dos listas para las filas y las columnas.
  //dandole el memoria con el tipo de dato que queremos , en este caso sera de tipo lista
  Lista *fila = (Lista *)malloc(sizeof(Lista));
  Lista *columna = (Lista *)malloc(sizeof(Lista));
  //inicializamos ambas listas con la funcion inicializar
  inicializar(fila);
  inicializar(columna);
  //inicializamos los nodos aux en el inicio de ambas listas que entran a la matriz
  aux1 = lista->inicio;
  aux2 = copia->inicio;
  //recorremos ambas listas con un solo while
  while(aux1 != NULL && aux2 != NULL){
    //comprobamos si la posicion j del aux1 es igual al j que entra como parametro de la funcion
    if(aux1->posJ == posJ){
      //si este es correcto , lo que hacemos es con la funcion agregar , agregar el dato y su posicion a la lista columnas
      agregar(columna,aux1->numero,aux1->posI,aux1->posJ);
    }
    //comprobamos si la posicion i del aux2 es igual al i que entra como parametro de la funcion
    if(aux2->posI == posI){
      //si este es correco , lo que hacemos es con la funcion agregar, agregar el dato y su posicion a la lista fila
      agregar(fila,aux2->numero,aux2->posI,aux2->posJ);
    }
    //ambos nodos auxiliares los apuntamos al siguiente nodo de este
    aux1 = aux1->siguiente;
    aux2 = aux2->siguiente;
  }
  //declaramos una variable int N , la cual la igualamos a la llamada de la funcion multiplicar entre las listas fila y columna
  int N = multiplicar(fila,columna);
  //liberamos ambos auxiliares
  free(aux1);
  free(aux2);
  //eliminamos ambas listas.
  eliminarLista(fila);
  eliminarLista(columna);
  //retornamos el valor de N
  return N;

}
/*
multiplicarM:
entradas:una lista simplemente enlazada y la copia de esta lista.
salidas:un lista simplemente enlazada
funcion que almacena todos los resultados segun la posicion en una nueva lista para poder modificar la lista resultado

*/
Lista *multiplicarM(Lista *lista,Lista *copia){
  //creamos un dato tipo lista para almacenar todos los resultados.
  Lista *L1 = (Lista *)malloc(sizeof(Lista));
  //creamos una variable tipo double
  double N;
  //un iterador desde i hasta el tamaño
  for (int i = 0; i < tamano; ++i)
    {
      //iteramos desde  hasta el tamano
      for (int j = 0; j < tamano; ++j)
      {
        //igualamos N al llamado de la funcion ModPosicion
        N = ModPosicion(lista,copia,i,j);
        //agregamos N y sus respectivas posiciones a la Listas L1 con la funcion agregar 
        agregar(L1,N,i,j);
      }
    }
    //retornamos L1;
    return L1;
}
/*
powMatriz:
entradas:una lista simplemente enlazada y el numero de la potencia que se quiere obtener
salida:la lista con los resultados obtenidos
funcion que se encarga de realizar la potencia de la matriz usando la lista enlaza.
*/
Lista *PowMatriz(Lista *lista,int Nexponente){
  //creamos un dato tipo lista el cual sera la copia de la lista de entrada de la funcion
  Lista *copia = (Lista *)malloc(sizeof(Lista));
  //igualamos la lista copia con la lista de entrada
  copia = lista;
  //incializamos i = 0;
  int i = 0;
  //si el numero del exponene es inferior a dos lo que se hara es retornar la lista.
  if(Nexponente == 1 || Nexponente < 2){
    return lista;
  //si no , hacemos la potencia
  }else{
    //iteramos desde i hasta el exponete - 1
    while(i < Nexponente - 1){
      //igualamos la lista al llamado de la funcion multiplicarM(lista,copia)
      lista = multiplicarM(lista,copia);
      //i++
      i++;
    }
  }
  //liberamos la copia
  free(copia);
  //retornamos la listas
  return lista;
}
/*
CalcularBytes():
entradas:una listas simplemente enlazada
salidas:un double 
funcion que se encarga de calcular el tamano en memoria de la matriz en bytes
*/
double CalcularBytes(Lista *lista){
  //creamos un nodo
  Nodo *actual;
  //inicializamos el nodo en la cabecera de la lista
  actual = lista->inicio;
  //creamos un double llamado bytes
  double Bytes = 0;
  //iteramos para recorrer la lista
  while(actual != NULL){
    //vamos sumando los tamano de los nodo.
    Bytes = Bytes + sizeof(actual);
    //cambias el actual , al siguiente de este
    actual = actual->siguiente;
  }
  //retornamos bytes
  return Bytes;
}
/*
MatrizDispersa():
entradas:una lista simplemente enlazada
salidas:una lista simplemente enlazada
funcion que se encarga de realizar una matriz dispersa en la cual se crea una lista y en ella se almacenas los datos distintos de 0.
*/
Lista *MatrizDispersa(Lista *lista){
  //creamos una nueva lista
  Lista *mDispersa = (Lista *)malloc(sizeof(Lista));
  //creamos un nodo
  Nodo *nuevo;
  //igualamos el nodo al inicio de la cabecera de la lista
  nuevo = lista->inicio;
  //iteramos hasta que el nuevo se haga null
  while(nuevo != NULL){
    //si el numero de nuevo es distinto de 0 , se agrega a la nueva lisat
    if(nuevo->numero != 0){
      agregar(mDispersa,nuevo->numero,nuevo->posI,nuevo->posJ);
    }
    //nuevo sera igual al siguiente de este.
    nuevo = nuevo->siguiente;
  }
  //retornamos la lista dipersa
  return mDispersa;
}