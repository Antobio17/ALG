#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

double minimo(double a, double b, double c){
  double min = a;

  if(b < min)
    min = b;
  if(c < min)
    min = c;

  return min;
}

void actualizarIndices(int &k, int &l, int a, int b, int c){
  double min = a;
  int aux_k = k-1, aux_l = l;

  if(b < min){
    min = b;
    aux_k = k;
    aux_l = l-1;
  }
  if(c < min){
    aux_k = k-1;
    aux_l = l-1;
  }

  k = aux_k;
  l = aux_l;
}

void   DynamicTimeWarping(double **DTW, double *senialX, double *senialY, int n, int m, double &distanciaMinima, int **emparejamientos, int &nEmparejamientos){
  int **aux_emparejamientos;
  int k = n, l = m, h = 0;   //Contadores
  nEmparejamientos = 0;

  //Inicializamos la matriz
  for(int i = 0; i <= n; i++)
    for(int j = 0; j <= m; j++)
      DTW[i][j] = 100000;  //Infinito

  DTW[0][0] = 0;

  //Contruimos la matriz
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      DTW[i][j] = abs(senialX[i-1]-senialY[j-1]) + minimo(DTW[i-1][j], DTW[i][j-1], DTW[i-1][j-1]);

  //Soluciones
  distanciaMinima = DTW[k][l];

  aux_emparejamientos = new int*[2];        //Para evitar tener que estar destruyendo y reservando memoria cada vez que metemos
  aux_emparejamientos[0] = new int[n*m];    //un nuevo emparejamiento vamos a reservar para un tamaño n*m en una matriz auxiliar
  aux_emparejamientos[1] = new int[n*m];

  while(k > 0 && l > 0){
    aux_emparejamientos[0][nEmparejamientos] = l;
    aux_emparejamientos[1][nEmparejamientos] = k;
    nEmparejamientos++;

    actualizarIndices(k, l, DTW[k-1][l], DTW[k][l-1], DTW[k-1][l-1]);
  }

  //Contruimos correctamente la matriz de emparejamientos ya que estan ordenados del último al primero y muy probablemente con memoria sobrante
  emparejamientos[0] = new int[nEmparejamientos];
  emparejamientos[1] = new int[nEmparejamientos];

  for(int i = 0; i < 2; i++){
    for(int j = nEmparejamientos; j > 0; j--){
      emparejamientos[i][h] = aux_emparejamientos[i][j-1];
      h++;
    }
    h=0;
  }

  delete[] aux_emparejamientos[0];
  delete[] aux_emparejamientos[1];
  delete[] aux_emparejamientos;
}

int main(int argc, char *argv[]){
  int n, m, nEmparejamientos;
  double **DTW;
  int **emparejamientos;
  double *senialX, *senialY;
  double distanciaMinima = 0;
  time_t t;
  string tipo_ejecucion;
  bool ejemplo = false, random = false;

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
    		cerr << argv[0] <<" n (tamaño señal 1) m (tamaño señal 2) o " << argv[0] << " aleatorio o" << argv[0] << " ejemplo (Para ejecutar el ejemplo de la documentacion)\n\n";
    		return 0;
      }
    }
	}

  if(ejemplo){
    n = 10;
    m = 10;
    senialX = new double[n];
    senialX[0] = 1;
    senialX[1] = 3;
    senialX[2] = 4;
    senialX[3] = 9;
    senialX[4] = 8;
    senialX[5] = 2;
    senialX[6] = 1;
    senialX[7] = 5;
    senialX[8] = 7;
    senialX[9] = 3;

    senialY = new double[m];
    senialY[0] = 1;
    senialY[1] = 6;
    senialY[2] = 2;
    senialY[3] = 3;
    senialY[4] = 0;
    senialY[5] = 9;
    senialY[6] = 4;
    senialY[7] = 3;
    senialY[8] = 6;
    senialY[9] = 3;
  }else{
    if(random){
      n = rand()%20;
      m = rand()%20;


      // Reservamos memoria para los vectores
      senialX = new double[n];
      for(int i = 0; i < n; i++)
        senialX[i] = rand()%80;

      senialY = new double[m];
      for(int i = 0; i < m; i++)
        senialY[i] = rand()%80;
    }else{
      n = atoi(argv[1]);
      m = atoi(argv[n+2]);

      // Reservamos memoria para los vectores
      senialX = new double[n];
      senialY = new double[m];

      for(int i = 0; i < n; i++)
        senialX[i] = atof(argv[i+2]);

      for(int i = 0; i < m; i++)
        senialY[i] = atof(argv[i+n+3]);
    }
  }

  //Contrucción de la matriz de error cuadrático
  DTW = new double*[n+1];
  for(int i = 0; i <= n; i++)
    DTW[i] = new double[m+1];

  //Mostramos los valores de los alumnos, de los esquies y de la matriz
  if(ejemplo)
    cout << "<<<<<<<<< Ejecucion del Problema 4 con los datos del ejemplo de la documentacion >>>>>>>>>" << endl << endl;
  else if(random)
    cout << "<<<<<<<<< Ejecucion del Problema 4 con una señal X de tamaño " << n << " y una señal Y de tamaño " << m << " aleatorias >>>>>>>>>" << endl << endl;
  else
    cout << "<<<<<<<<< Ejecucion del Problema 4 con una señal X de tamaño " << n << " y una señal Y de tamaño " << m << " con los datos introducidos >>>>>>>>>" << endl << endl;

  cout << "La señal X = {";
  for(int i = 0; i < n-1; i++)
    cout << senialX[i] << ", ";
  cout <<  senialX[n-1] << "}" << endl;

  cout << "La señal Y = {";
  for(int i = 0; i < m-1; i++)
    cout << senialY[i] << ", ";
  cout <<  senialY[m-1] << "}" << endl;

  //Resolución del problema
  emparejamientos = new int*[2];
  DynamicTimeWarping(DTW, senialX, senialY, n, m, distanciaMinima, emparejamientos, nEmparejamientos);

  //Mostrar solución
  cout << "La distancia mínima entre las dos señales es de " << distanciaMinima << endl;
  cout << "Los emparejamientos son de la forma {Xi,Yj}: ";
  for(int i = 0; i < nEmparejamientos; i++){
    cout << "{";
    for(int j = 0; j < 2; j++){
      cout << emparejamientos[j][i];
      if(j < 1)
        cout << ", ";
    }
    cout << "}   ";
  }
  cout << endl << endl;

  delete[] senialX;
  delete[] senialY;
  for(int i = 0; i <= n; i++)
    delete[] DTW[i];
  delete[] DTW;
  delete[] emparejamientos[0];
  delete[] emparejamientos[1];
  delete[] emparejamientos;

  return 0;
}
