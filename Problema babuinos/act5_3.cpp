/ =================================================================
//
// File: act5_3.cpp
// Authors: Jordana Betancourt Menchaca A01707434
//          Fermín Méndez García A01703366
//
// To compile: g++ act5_3.cpp -lpthread
//
//  Tecnológico de Monterrey Campus Querétaro
//  Lunes 13 de junio de 2022
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

//Capacidad de la cuerda
const int CAPACITY = 3;
//Babuinos en la izquierda
const int LEFT_BABOONS_INITIAL = 10;
//Babuinos en la derecha
const int RIGHT_BABOONS_INITIAL = 10;

//Máximo número de hilos
const int MAXLEFT = 5;
const int MAXRIGHT = 5;

//Mutex controlador
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Semáforo cuerda
sem_t rope;

//Babuinos que cruzaron de derecha a izquierda
int left_babboons_arrived = 0;
//Babuinos que cruzaron de izquierda a derecha
int right_babboons_arrived = 0;

//Contadores para controlar el acceso a la cuerda
int left_babboons_counter = 0;
int right_babboons_counter = 0;

//Mover babuinos de izquierda a derecha
void *move_left_to_right(void *arg)
{
    //Mientras que haya babuinos iniciales izquierdos
	while (LEFT_BABOONS_INITIAL - right_babboons_arrived > 0)
	{
		//Dejamos formar a un babuino en la fila
		pthread_mutex_lock(&mutex);
		printf("Se forma un babuinito en el lado izquierdo...\n");
        //Aumentamos el contador en uno
		left_babboons_counter += 1;
		printf("Hay %i babuino(s) en la fila izquierda\n", left_babboons_counter);

        //Si ya hay tres babuinos en la fila dejamos que pasen o si ya solo quedan menos de tres babuinos
		if (left_babboons_counter == CAPACITY || left_babboons_counter == LEFT_BABOONS_INITIAL - right_babboons_arrived)
		{
            //Cerramos la cuerda para que pasen los babuinos
			sem_wait(&rope);
            //Sumamos los babuinos que cruzaron de izquierda a derecha
			right_babboons_arrived += left_babboons_counter;
            printf("Cruzan %i babuinos al lado derecho\n", left_babboons_counter);
             //Limpiamos la fila
			left_babboons_counter = 0;
			printf("En total %i babuinos han llegado a salvo al lado derecho\n\n", right_babboons_arrived);
            //Abrimos la cuerda
			sem_post(&rope);
		}
		pthread_mutex_unlock(&mutex);
        //Dejamos "dormir" para ver si los del lado derecho pueden pasar
		sleep(1);
	}
	pthread_exit(NULL);
}

//Mover babuinos de derecha a izquierda 
void *move_right_to_left(void *arg)
{
     //Mientras que haya babuinos iniciales derechos
	while (RIGHT_BABOONS_INITIAL - left_babboons_arrived > 0)
	{
		//Dejamos formar a un babuino en la fila
		printf("Se forma un babuinito en el lado derecho...\n");
		pthread_mutex_lock(&mutex);
        //Aumentamos el contador en uno
		right_babboons_counter += 1;
		printf("Hay %i babuino(s) en la fila derecha\n", right_babboons_counter);

        //Si ya hay tres babuinos en la fila dejamos que pasen o si ya solo quedan menos de tres babuinos
		if (right_babboons_counter == CAPACITY || right_babboons_counter == RIGHT_BABOONS_INITIAL - left_babboons_arrived)
		{
            //Cerramos la cuerda para que pasen los babuinos
			sem_wait(&rope);
            //Sumamos los babuinos que cruzaron de derecha a izquierda
			left_babboons_arrived += right_babboons_counter;
            printf("Cruzan %i babuinos al lado izquierdo\n", right_babboons_counter);
            //Limpiamos la fila
			right_babboons_counter = 0;
			printf("En total  %i babuinos han llegado a salvo al lado izquierdo\n\n", left_babboons_arrived);
            //Abrimos la cuerda
			sem_post(&rope);
		}
		pthread_mutex_unlock(&mutex);
        //Dejamos "dormir" para ver si los del lado izquierdo pueden pasar
		sleep(1);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    //Creamos variables iniciales de hilo y semáforo
	pthread_t left_thread[MAXLEFT];
	pthread_t right_thread[MAXRIGHT];
	sem_init(&rope, 0, 1);

	for (int i = 0; i < MAXLEFT; i++)
	{
		pthread_create(&left_thread[i], NULL, move_left_to_right, NULL);
	}
	for (int i = 0; i < MAXRIGHT; i++)
	{
		pthread_create(&right_thread[i], NULL, move_right_to_left, NULL);
	}
	for (int i = 0; i < MAXLEFT; i++)
	{
		pthread_join(left_thread[i], NULL);
	}
	
	printf("RESULTADOOO...\n");
	printf("%i Babuinos que cruzaron al lado izquierdo...\n", left_babboons_arrived);
	printf("%i Babuinos que cruzaron al lado derecho...\n", right_babboons_arrived);
	return 0;
}