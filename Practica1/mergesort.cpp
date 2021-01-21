#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void combina(int* v, int ini, int med, int fin){
    int vtam= fin - ini + 1;
    int *aux = new int[vtam];
    int i = ini, j = med + 1, k = 0;

    while(i <= med && j <= fin){
      if(v[i] < v[j]) { aux[k] = v[i]; i++; }
      else { aux[k] = v[j]; j++; }
      k++;
    }

    while(i <= med) { aux[k] = v[i]; i++; k++; }

    while(j <= fin) { aux[k] = v[j]; j++; k++; }

    for (int n = 0; n < vtam; ++n) v[ini+n] = aux[n];
    delete [] aux;
}

void MergeSort(int* v, int ini, int fin){
  if(ini < fin){
    int med = (ini + fin)/2;
    MergeSort(v, ini, med);
    MergeSort(v, med + 1, fin);
    combina(v, ini, med, fin);
  }
}

int main(int argc, char *argv[]){
  chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
  int n, argumento;
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
    MergeSort(vec, 0, n-1);
    tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

    unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n <<endl;

		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida << n << " " << tejecucion<< "\n";


		// Liberamos memoria del vector
		delete [] vec;
  }

  // Cerramos fichero de salida
	fsalida.close();

	return 0;
}
