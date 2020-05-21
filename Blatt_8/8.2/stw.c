#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define N 40 //passagiere
#define M 12 //kapazität
#define SEATS M / 3

int capacity = M;
int free_seats = SEATS;

pthread_mutex_t mutex;
pthread_cond_t enter;
pthread_cond_t sit;

typedef struct
{
    int id;
    int waiting; // 0 == not waiting    1 == waiting
    int seat; // 0 == standing      1 == sitting
} Person;

void* visitor(void* visitor);
void einsteigen(Person* person);
void aussteigen(Person* person);
void sitz_platz(Person* person);

int main(int argc, char const* argv[])
{
    srand(time(NULL));

    Person personen[N];
    pthread_t threads[N];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&enter, NULL);
    pthread_cond_init(&sit, NULL);

    for (int i = 0; i < N; i++) {
        personen[i].id = i;
        pthread_create(&threads[i], NULL, visitor, (void*)&personen[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&enter);
    pthread_cond_destroy(&sit);

    return 0;
}

void* visitor(void* visitor)
{
    visitor = (Person*)visitor;
    int r = rand() % 3 + 1;

    einsteigen(visitor);
    sitz_platz(visitor);

    //simulate random activity over time
    sleep(r);

    aussteigen(visitor);

    pthread_exit(NULL);
}

void einsteigen(Person* person)
{

    pthread_mutex_lock(&mutex);

    while (capacity == 0) {

        printf("---- Person %d tries to enter bus ----\n", person->id);
        //printf("\tPeople --> on bus: %d --> sitting: %d\n", M - capacity, SEATS - free_seats);

        pthread_cond_wait(&enter, &mutex);
    }
    sleep(2);
    capacity--;
    person->seat = 0;
    printf("Person %d has entered the bus", person->id);
    printf("\tPeople --> on bus: %d --> sitting: %d\n", M - capacity, SEATS - free_seats);

    pthread_mutex_unlock(&mutex);
}

void aussteigen(Person* person)
{

    pthread_mutex_lock(&mutex);
    person->waiting = 1;
    capacity++;
    free_seats++;
    sleep(1);

    printf("Person %d has left the bus", person->id);
    printf("\tPeople --> on bus: %d --> sitting: %d\n", M - capacity, SEATS - free_seats);

    pthread_cond_signal(&sit);
    pthread_cond_signal(&enter);
    pthread_mutex_unlock(&mutex);
}

void sitz_platz(Person* person)
{
    pthread_mutex_lock(&mutex);

    while (free_seats == 0) {
        sleep(1);
        printf("Person %d is standing\t", person->id);
        printf("\tPeople --> on bus: %d --> sitting: %d\n", M - capacity, SEATS - free_seats);
        pthread_cond_wait(&sit, &mutex);
    }
    sleep(1);
    free_seats--;
    person->seat = 1;
    printf("Person %d is sitting\t", person->id);
    printf("\tPeople --> on bus: %d --> sitting: %d\n", M - capacity, SEATS - free_seats);

    person->seat = 1;
    pthread_mutex_unlock(&mutex);
}
