#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;

void mostrarMatriz(int **matriz, int n, int m){
  cout << "             ";
  for(int i = 0; i < n; i++){
    cout << "alumno " << i+1;
    if(i+1 < 10)
      cout << "   ";
    else if(i+1 < 100)
      cout << "  ";
    else if(i+1 < 1000)
      cout << " ";
  }
  cout << endl;

  for(int i = 0; i < m; i++){
    if(i+1 < 10)
      cout << "  esqui " << i+1 << "    ";
    else if(i+1 < 100)
      cout << "  esqui " << i+1 << "   ";
    else if(i+1 < 1000)
      cout << "  esqui " << i+1 << "  ";

    for(int j = 0; j < n; j++){
      cout << matriz[i][j];
      if(matriz[i][j] < 10)
        cout << "          ";
      else if(matriz[i][j] < 100)
        cout << "         ";
      else if(matriz[i][j] < 1000)
        cout << "        ";
      else if(matriz[i][j] < 10000)
        cout << "       ";
    }
    cout << endl;
  }
}

bool elegido(int *eleccion, int n, int esqui){
  bool result = false;

  for(int i = 0; i < n; i++)
    if(esqui == eleccion[i])
      result = true;

  return result;
}

void asignacionEsquies(int **matriz, int n, int m, int *eleccion){
  int min, tam = 0;

  for(int i = 0; i < n; i++){
    min = -1;
    for(int j = 0; j < m; j++){
      if(min == -1 || min > matriz[j][i]){
        if(!elegido(eleccion, tam, j)){
          eleccion[i] = j;
          tam = i + 1;
          min = matriz[j][i];
        }
      }
    }
  }
}

int main(int argc, char *argv[]){
  int n, m;
  string ejem;
  double error = 0;
  int *alumnos, *esquies, *solucion;
  int **matriz;
  time_t t;
  bool ejemplo = false;

  // Inicializamos generador de numeros aleatorios
  srand((unsigned) time(&t));

  if (argc != 3) {
    ejem = argv[1];
    if(argc == 2 && ejem == "ejemplo"){
      ejemplo = true;
    }else{
      cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
  		cerr<<argv[0]<<" NumeroAlumnos NumeroEsquies (NumeroAlumnos <= NumeroEsquies) o " <<argv[0]<< " ejemplo (Para ejecutar el ejemplo de la documentacion)\n\n";
  		return 0;
    }
	}

  if(ejemplo){
    n = 7;
    m = 9;

    solucion = new int[n];
    alumnos = new int[n];
    alumnos[0] = 170;
    alumnos[1] = 168;
    alumnos[2] = 181;
    alumnos[3] = 175;
    alumnos[4] = 163;
    alumnos[5] = 185;
    alumnos[6] = 173;

    esquies = new int[m];
    esquies[0] = 160;
    esquies[1] = 160;
    esquies[2] = 165;
    esquies[3] = 165;
    esquies[4] = 170;
    esquies[5] = 170;
    esquies[6] = 170;
    esquies[7] = 180;
    esquies[8] = 190;

  }else{
    n = atoi(argv[1]);
    m = atoi(argv[2]);


    // Reservamos memoria para los vectores
    alumnos = new int[n];
    for(int i = 0; i < n; i++)
      alumnos[i] = 150 + rand()%40;

    esquies = new int[m];
    for(int i = 0; i < m; i++)
      esquies[i] = 150 + rand()%40;

    solucion = new int[n];
  }

  //Contrucción de la matriz de error cuadrático
  matriz = new int*[m];
  for(int i = 0; i < m; i++)
    matriz[i] = new int[n];

  for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++)
      matriz[i][j] = pow(alumnos[j]-esquies[i],2);

  //Mostramos los valores de los alumnos, de los esquies y de la matriz
  if(ejemplo)
    cout << endl << "<<<<<<<<< Ejecucion del Problema 3 con los datos del ejemplo de la documentacion >>>>>>>>>" << endl << endl;
  else
    cout << endl << "<<<<<<<<< Ejecucion del Problema 3 con " << n << " alumnos y " << m << " esquies aleatorios >>>>>>>>>" << endl << endl;

  cout << "El conjunto de alumnos: {";
  for(int i = 0; i < n-1; i++)
    cout << alumnos[i] + 1 << ", ";
  cout <<  alumnos[n-1] + 1 << "}" << endl;

  cout << "El conjunto de esquies: {";
  for(int i = 0; i < m-1; i++)
    cout << esquies[i] + 1 << ", ";
  cout <<  esquies[m-1] + 1 << "}" << endl;

  if(n < 10){
    cout << "La matriz de error cuadratico es:" << endl << endl;
    mostrarMatriz(matriz, n, m);
    cout << endl;
  }else{
    cout << endl << "La matriz de error cuadratico solo se puede mostrar bien si el numero de alumnos es menos que 10 (también depende del tamaño de la pantalla)" << endl << endl;
  }


  //Resolución del problema
  asignacionEsquies(matriz, n, m, solucion);

  //Calculo del error cuadraticos medio
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
      if(solucion[i] == j)
        error += matriz[j][i];

  //Mostrar solución
  cout << "Los esquies elegidos para cada alumno son {";
  for(int i = 0; i < n-1; i++)
    cout << solucion[i] + 1 << ", ";
  cout <<  solucion[n-1] + 1 << "} y su error cuadratico medio es de " << error/n << endl << endl;

  return 0;
}
