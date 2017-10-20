#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS     7
#define TAMANO          8

int tablero[8][8];
int reinasListas[NUM_THREADS];
int threadsEjecutados = 0;



void *imprimirTablero(void *t) {


    while (!todasListas())
    {
        //system("clear");
        printf("\033[H\033[J");
        usleep(1000 * 16);//~60 fps ;)
        for (int i = 0; i < TAMANO; ++i) {

            for (int j = 0; j < TAMANO; ++j) {

                printf("%d", tablero[i][j]);

            }
            printf("\n");

        }

    }

}

void initTablero(void) {
    int i,j;
    for (i = 0; i < TAMANO; ++i) {

        for (j = 0; j < TAMANO; ++j) {

            tablero[i][j] = 0;

        }

    }
}

void *posicionarReina(void *threadid) {
    long tid;
    tid = (long) threadid;

    printf("Se ha movido la reina #%ld\n", tid);
    threadsEjecutados++;
    printf("Se han ejecutado %d threads\n", threadsEjecutados);

    while (seLaCome())//a una reina :x
    {
        reinasListas[(int) threadid] = 1;
    }



    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    pthread_t screen;
    int error;
    long trheadId;

    initTablero();

    for (trheadId = 0; trheadId < NUM_THREADS; trheadId++) {
        //printf("In main: creating thread %ld\n", t);
        error = pthread_create(&threads[trheadId], NULL, posicionarReina, (void *) trheadId);
        pthread_create(&screen, NULL, imprimirTablero, (void *) trheadId);
        (void) pthread_join(threads[trheadId], NULL);
        (void) pthread_join(screen, NULL);


        if (error) {
            printf("ERROR; return code from pthread_create() is %d\n", error);
            exit(-1);
        }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
}