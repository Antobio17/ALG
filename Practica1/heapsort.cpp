#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void insertarEnPos(double *apo, int pos){
  int idx = pos-1;
  int padre;

  //cout << "       idx: " << idx;


  if(idx > 0){
    if(idx%2==0) {
      padre=(idx-2)/2;
    }
    else{
      padre=(idx-1)/2;
    }
    //cout << "\n       padre: " << padre << "\n";

    if(apo[padre] > apo[idx]){
      double tmp=apo[idx];
      apo[idx]=apo[padre];
      apo[padre]=tmp;
      //cout << "APO: ";
      //for(int j=0; j<pos; j++)
      //  cout << apo[j] << " ";
      //cout << "\n";
      insertarEnPos(apo, padre+1);
    }
  }
}

void reestructurarRaiz(double *apo, int pos, int tamapo){
  int minhijo;

  if(2*pos+1 < tamapo){
    minhijo=2*pos+1;
    //cout << "       minhijo: " << minhijo << "\n";
    if((minhijo+1 < tamapo) && (apo[minhijo]>apo[minhijo+1])) minhijo++;
    if(apo[pos]>apo[minhijo]){
      double tmp = apo[pos];
      apo[pos]=apo[minhijo];
      apo[minhijo]=tmp;

      //cout << "APO: ";
      //for(int j=0; j<tamapo; j++)
      //  cout << apo[j] << " ";
      //cout << "\n";
      reestructurarRaiz(apo, minhijo, tamapo);
    }
  }
}

void HeapSort(int *v, int n){
  double *apo=new double[n];
  int tamapo=0;

  for(int i=0; i<n; i++){
    apo[tamapo]=v[i];
    tamapo++;

    //cout << "i: " << i << "\n";
    //cout << "APO: ";
    //for(int j=0; j<tamapo; j++)
    //  cout << apo[j] << " ";
    //cout << "\ntamapo: " << tamapo << "\n";
    insertarEnPos(apo,tamapo);
  }

  for(int i=0; i<n; i++){
    v[i]=apo[0];
    tamapo--;
    apo[0]=apo[tamapo];
    reestructurarRaiz(apo,0,tamapo);
  }

  delete [] apo;
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
    HeapSort(vec, n);
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
