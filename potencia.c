//includimos libreria de la biblioteca estandar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
//definimos una variable para poder almacenar los datos en un arreglo bidimensional
#define MAX_LIN 1000
/******* variables globales ********/
//puntero double de dos dimensiones para almacenar las filas y columnas del archivo de entrada.
int main(){
  //igualamos la variable global matriz , al llamado de leermatriz
  matriz = leermatriz();
  //igualamos la variable global matriz al numero de la posicicion 0,0 de matriz para obtener el tamaño
  tamano = matriz[0][0];
  //igualamos el Npotencia al numero de la posicion 0,1 de la matriz para obtener el exponente de la potencia
  Npotencia = matriz[0][1];
  //imprimimos el tamaño y el numero del exponen para ver si estan de manera correcta
  printf("\n\n\nel tamano es :%i\n",tamano);
  printf("el numero del exponente es :%i\n",Npotencia);
  printf("*******************************************\n\n\n");
  //creamos 3 listas (lista,Mresultante y MDispersa) de tipo Lista
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  Lista *Mresultante = (Lista *)malloc(sizeof(Lista));
  Lista *MDispersa = (Lista *)malloc(sizeof(Lista));
  //inicializamos la lista
  inicializar(lista);
  //hacemos dos ciclos para recorrer la matriz
  for (int i = 1; i <= tamano; ++i)
	for (int j = 0; j < tamano; ++j)
    //agregamos el dato , las posiciones i y j del dato de la matriz a la lista
		agregar(lista,matriz[i][j],i-1,j);
  //igualamos Mresultante al llamado de la funcion PowMatriz
  Mresultante = PowMatriz(lista,Npotencia);
  //imprimimos la matriz resultante
  imprimirCM(Mresultante);
  printf("\n\n\n\n");
  //declaramos dos variables tipo float para obtener el tamano en memoria de las matrices resultante y dispersa
  float TamanoDispersa,TamanoMatrizNormal;
  //igualamos el tamanomatriznormal al llamado de la funcion calcularbytes
  TamanoMatrizNormal = CalcularBytes(Mresultante);
  //igualamos la lista Mdispersa al llamado de la funcion matrizdispersa
  MDispersa = MatrizDispersa(Mresultante);
  //igualamos el tamanodispersa al llamado de la funcion calcularbytes
  TamanoDispersa = CalcularBytes(MDispersa);
  //imprimimos ambos valores para ser mostrados por pantallas 
  printf("tamano en memoria de la matriz dispersa = %f bytes \n",TamanoDispersa);
  printf("tamano en memoria de la matriz completa habria sido = %f bytes \n",TamanoMatrizNormal);
  //eliminamos ambas matrices
  eliminarLista(Mresultante);
  eliminarLista(MDispersa);
}