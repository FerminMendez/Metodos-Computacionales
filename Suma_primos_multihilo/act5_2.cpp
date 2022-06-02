/*************************************************************
* Implementación de métodos computacionales (Gpo 601)
*
* Actividad 5.2 Programación paralela y concurrente
* 
* Jordana Betancourt Menchaca A01707434
* Fermín Méndez García A01703366
* 
* Para compilar g++ act5_2.cpp -pthread
*
*
*************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "utils.h"

using namespace std;


const int END = 5000000;
// const int END = 1000000;
const int THREADS = 8;

/*************************************************************
 * Implementación secuencial
 *************************************************************/
int isprime(int num){
   if (num < 2)
      return 0;
   for (int i = 2; i <= sqrt(num); i++){
      if (num % i == 0)
         { return 0; }
   }
   return 1; //Si los dos casos de arriba fallan es true
}

double sumPrimes(int end){
   double sum=0;
   for(int i=1;i<=end;i++){
      if(isprime(i)==1)
         { sum += i ; }
   }
   return sum;
}

/*************************************************************
 * Implementación concurrente
 *************************************************************/
typedef struct {
  int start, end; // [start, end)
  int *arr;
  double acum;
} Block;

void* partialSum(void* param) {
  Block *block;
  double acum;

  block = (Block*) param;
  acum = 0;
  
   for(int i= block->start ;i< block->end;i++){
      if(isprime(i)==1)
         { acum += i ; }
   }


  block->acum = acum;
  pthread_exit(0);
}



/*************************************************************
 * Main
 *************************************************************/
int main(int argc, char* argv[]) {
  
   // int END=5000000;
   // int END = 100;
   // cout <<endl<<"Suma números primos hasta 5 millones "<<sumPrimes(END);

  int *data, blockSize;
  double ms, result;
  pthread_t tids[THREADS];
  Block blocks[THREADS];

  data = new int[END];
  fill_array(data, END);
//   display_array("data = ", data);

  /*--------------------- MONO THREAD ---------------------*/
  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();
    result = sumPrimes(END);
    ms += stop_timer();
  }
  cout << "---- Serial ----\n";
  cout << "Resultado = " << result << "\n";
  cout << "Tiempo = " << (ms / N) << "ms\n";

  float T1 = (ms / N);

  /*--------------------- MULTI THREAD ---------------------*/

  blockSize = (END + 1) / THREADS;
  for (int i = 0; i < THREADS; i++) {
    blocks[i].start = i * blockSize;
    blocks[i].end = (i != (THREADS - 1))? ((i + 1) * blockSize) : (END + 1);
    blocks[i].arr = data;
    blocks[i].acum = 0;
  }

  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();

    for (int j = 0; j < THREADS; j++) {
      pthread_create(&tids[j], NULL, partialSum, (void*) &blocks[j]);
    }

    result = 0;
    for (int j = 0; j < THREADS; j++) {
      pthread_join(tids[j], NULL);
      result += blocks[j].acum;
    }

    ms += stop_timer();
  }
  cout << "\n---- Multithread ----\n";
  cout << "Resultado = " << result << "\n";
  cout << "Tiempo = " << (ms / N) << "ms\n";

  float TP = (ms / N);

 /*--------------------- SPEED UP---------------------*/
    cout << "\n---- Speedup  ----\n";
    float speedup = T1/ TP;
    cout << "El speedup es de: " << speedup << "\n";
    

  delete [] data;
  

return 0;

}