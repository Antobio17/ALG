//g++ metodo-basico.cpp -o metodo-basico
//./metodo-basico salida-basico.txt 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000
#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

int numInversiones(int *vec, int n){
  int inversiones = 0, aux;

  for(int i = 0; i < n-1; i++){
    for(int j = i+1; j < n; j++){
      if(vec[i] > vec[j]){
        aux = vec[i];
        vec[i] = vec[j];
        vec[j] = aux;
        inversiones++;
      }
    }
  }

  return inversiones;
}

int main(int argc, char *argv[]){
  chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
  int n, argumento, inversiones;
  double tejecucion;
  int *vec;
  ofstream fsalida;

  if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}

	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}

  // Pasamos por cada tamaÒo de caso
	for (argumento= 2; argumento<argc; argumento++) {
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);

    // Reservamos memoria para el vector
		vec= new int[n];

    for(int i = 0; i < n; i++){
      vec[i]=rand()%n;
    }

    t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
    inversiones = numInversiones(vec, n);
    tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

    unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n <<endl;

		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida << n << " " << tejecucion<< "\n";

    // Mostramos la solución
    cout << "                             El vector tiene " << inversiones << " inversiones." << endl << endl;

		// Liberamos memoria del vector
		delete [] vec;
  }

  // Cerramos fichero de salida
	fsalida.close();

	return 0;
}
