#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct solucion{
  int *A, *B, tamA, tamB;
};

bool EsFactible(int k, int *X, int *A, int *B, int n, int tamA, int tamB, int decision){
  int sumatoriaA = 0, sumatoriaB = 0, sumatoriaRestoX = 0;
  bool factible = false;

  for(int i = k; i < n; i++){
    sumatoriaRestoX = + sumatoriaRestoX + X[i];
    if(X[i] < 0)
      factible = true;
  }

  if(!factible){
    for(int i = 0; i < tamA; i++)
      sumatoriaA += A[i];
    for(int i = 0; i < tamB; i++)
      sumatoriaB += B[i];

    if(decision == 0){
      if((sumatoriaA+sumatoriaRestoX) >= sumatoriaB)
          factible = true;
    }else{
      if((sumatoriaB+sumatoriaRestoX) >= sumatoriaA)
          factible = true;
    }
  }

  return factible;
}

bool solucionAniadida(solucion sol, solucion *soluciones, int numSoluciones){
  bool solucionAniadida = true, esta = false;

  if(numSoluciones == 0)
    solucionAniadida = false;
  else
    for(int i = 0; i < numSoluciones; i++){
      solucionAniadida = true;
      if(sol.tamA != soluciones[i].tamA || sol.tamB != soluciones[i].tamB)
        solucionAniadida = false;
      else{
        for(int j = 0; j < sol.tamA && solucionAniadida; j++){
          esta = false;
          for(int k = 0; k < sol.tamA && !esta; k++){
            if(sol.A[j] == soluciones[i].A[k])
              esta = true;
          }
          if(!esta)
            solucionAniadida = false;
        }
      }
    }

  return solucionAniadida;
}

void EsSolucion(int *A, int *B, int tamA, int tamB, solucion* soluciones, int &numSoluciones){
  int sumatoriaA = 0, sumatoriaB = 0;
  solucion sol;

  for(int i = 0; i < tamA; i++)
    sumatoriaA += A[i];
  for(int i = 0; i < tamB; i++)
    sumatoriaB += B[i];

  if((sumatoriaA-sumatoriaB) == 0){
    sol.A = new int[tamA];
    sol.B = new int[tamB];
    sol.tamA = tamA;
    sol.tamB = tamB;

    for(int i = 0; i < tamA; i++)
      sol.A[i] = A[i];
    for(int i = 0; i < tamB; i++)
      sol.B[i] = B[i];

    if(!solucionAniadida(sol, soluciones, numSoluciones)){
      soluciones[numSoluciones] = sol;
      numSoluciones++;
    }
  }
}

void Subconjuntos(int *X, int *decisiones, int *A, int *B, int n, int &tamA, int &tamB, solucion* soluciones, int &numSoluciones){
  int i = 0;

  A[tamA] = X[i];
  tamA++;
  decisiones[i] = 0;
  i++;
  decisiones[i] = 2;

  while( i >= 0 ){
    decisiones[i] -= 1;
    //¿Ha explorado ya todos los descencientes del nodo?
    if( decisiones[i] == -1 ){
      tamA--;
      i--;
    }else{
      if( decisiones[i] == 1 ){
        //¿Es factible explorar la rama?
        if( EsFactible(i, X, A, B, n, tamA, tamB, decisiones[i]) ){
          B[tamB] = X[i];
          tamB++;
          //¿Ha llegado al nodo hoja?
          if( i == n-1 ){
            EsSolucion(A, B, tamA, tamB, soluciones, numSoluciones);
          }else{
            i++;
            decisiones[i] = 2;
          }
        }else{
          tamB++;
        }
      }
      if( decisiones[i] == 0 ){
        tamB--;
        //¿Es factible explorar la rama?
        if( EsFactible(i, X, A, B, n, tamA, tamB, decisiones[i]) ){
          A[tamA] = X[i];
          tamA++;
          //¿Ha llegado al nodo hoja?
          if( i == n-1 ){
            EsSolucion(A, B, tamA, tamB, soluciones, numSoluciones);
          }else{
            i++;
            decisiones[i] = 2;
          }
        }else{
          tamA++;
        }
      }
    }
  }
}

int main(int argc, char *argv[]){
  int *X, *A, *B, *decisiones, n, tamA = 0, tamB = 0, numSoluciones = 0, memoriaSoluciones;
  solucion* soluciones;
  bool random = false, ejemplo = false;
  time_t t;
  string tipo_ejecucion;

  // Inicializamos generador de numeros aleatorios
  srand((unsigned) time(&t));

  if (argc < 3) {
    tipo_ejecucion = argv[1];
    if(argc == 2 && tipo_ejecucion == "ejemplo"){
      ejemplo = true;
    }else{
      if(argc == 2 && tipo_ejecucion == "aleatorio"){
        random = true;
      }else{
        cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
    		cerr << argv[0] <<" n x0 x1 x2 ... xn-1 ó " << argv[0] << " aleatorio ó" << argv[0] << " ejemplo (Para ejecutar el ejemplo de la documentacion)\n\n";
    		return 0;
      }
    }
	}

  if(ejemplo){
    n = 4;
    // Reservamos memoria para los vectores
    X = new int[n];
    A = new int[n];
    B = new int[n];
    decisiones = new int[n];

    X[0] = 2;
    X[1] = -1;
    X[2] = 5;
    X[3] = 2;
  }else if(random){
    n = 2 + rand()%13;

    // Reservamos memoria para los vectores
    X = new int[n];
    A = new int[n];
    B = new int[n];
    decisiones = new int[n];

    for(int i = 0; i < n; i++)
      X[i] = (rand()%80) - 40;
  }else{
    n = atoi(argv[1]);

    // Reservamos memoria para los vectores
    X = new int[n];
    A = new int[n];
    B = new int[n];
    decisiones = new int[n];

    for(int i = 0; i < n; i++)
      X[i] = atof(argv[i+2]);
  }

  memoriaSoluciones = pow(2,n-1);
  soluciones = new solucion[memoriaSoluciones];

  //Mostramos los valores de los alumnos, de los esquies y de la matriz
  if(ejemplo)
    cout << "<<<<<<<<< Ejecucion del Problema 9 con los datos del ejemplo de la documentacion >>>>>>>>>" << endl << endl;
  else if(random)
    cout << "<<<<<<<<< Ejecucion del Problema 9 con conjunto X de tamaño " << n << " con valores aleatorios >>>>>>>>>" << endl << endl;
  else
    cout << "<<<<<<<<< Ejecucion del Problema 9 con conjunto X de tamaño " << n << " con los datos introducidos >>>>>>>>>" << endl << endl;

  cout << "Conjunto X = {";
  for(int i = 0; i < n-1; i++)
    cout << X[i] << ", ";
  cout <<  X[n-1] << "}" << endl << endl;

  Subconjuntos(X, decisiones, A, B, n, tamA, tamB, soluciones, numSoluciones);

  //Mostrar soluciones
  for(int i = 0; i < numSoluciones; i++){
    cout << "Solucion " << i+1 << ":" << endl;
    cout << "Conjunto A = {";
    for(int j = 0; j < soluciones[i].tamA-1; j++)
      cout << soluciones[i].A[j] << ", ";
    cout <<  soluciones[i].A[soluciones[i].tamA-1] << "}" << endl;

    cout << "Conjunto B = {";
    for(int j = 0; j < soluciones[i].tamB-1; j++)
      cout << soluciones[i].B[j] << ", ";
    cout <<  soluciones[i].B[soluciones[i].tamB-1] << "}" << endl;
  }
  cout << endl << "Hay " << numSoluciones << " soluciones." << endl << endl;

  delete[] X;
  delete[] A;
  delete[] B;
  delete[] soluciones;

  return 0;
}
