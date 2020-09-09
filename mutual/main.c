#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>




struct station
{
    int out_passengers; // in station waiting passengers
    int in_passengers; // in train passengers
    pthread_mutex_t lock;
    pthread_cond_t train_arrived_cond;
    pthread_cond_t passengers_seated_cond;
    pthread_cond_t train_is_full_cond;
};


struct load_train_args
{
    struct station *station;
    int free_seats;
};
int threads_completed = 0;
int load_train_returned = 0;



void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);

void* passenger_thread(void *arg);

void* load_train_thread(void *args);
int min(passengers_left, free_seats);


int main()
{
    struct station station;
    station_init(&station);
    int i;
    // Create a bunch of 'passengers', each in their own thread.
    printf("Enter number of passengers please:");
    int total_passengers;
    scanf("%d",&total_passengers);
    int passengers_left = total_passengers;
    for (i = 0; i < total_passengers; i++)
    {
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, passenger_thread, &station);
    }


    int total_passengers_boarded = 0;
    int max_free_seats_per_train ;
    printf("Enter number of free seats per train please:");
    scanf("%d",&max_free_seats_per_train);

    int pass = 0;
    while (passengers_left > 0)
    {

        int free_seats =max_free_seats_per_train;
        load_train_returned = 0;
        struct load_train_args args = { &station, free_seats };
        pthread_t lt_tid;
        int ret = pthread_create(&lt_tid, NULL, load_train_thread, &args);





        int threads_to_reap = min(passengers_left, free_seats);
        int threads_reaped = 0;
        while (threads_reaped < threads_to_reap)
        {
            if (threads_completed > 0)
            {
                threads_reaped++;
                station_on_board(&station);
                __sync_sub_and_fetch(&threads_completed, 1);
            }
        }


        while (threads_completed > 0)
        {
            threads_reaped++;
            __sync_sub_and_fetch(&threads_completed, 1);
        }

        passengers_left -= threads_reaped;
        total_passengers_boarded += threads_reaped;
        printf("Train departed station with %d new passenger(s)\n\n\n",threads_to_reap);

        pass++;

        if(passengers_left>0){
        printf("Enter number of free seats per train please:");
        scanf("%d",&max_free_seats_per_train);
}
    }

    if (total_passengers_boarded == total_passengers)
    {   return 0;
    }

}

void station_init(struct station *station)
{
    station->out_passengers = 0;
    station->in_passengers = 0;
    pthread_mutex_init(&(station->lock), NULL);
    pthread_cond_init(&(station->train_arrived_cond), NULL);
    pthread_cond_init(&(station->passengers_seated_cond), NULL);
    pthread_cond_init(&(station->train_is_full_cond), NULL);
}

void station_load_train(struct station *station, int count)
{
    // Enter critical region
    pthread_mutex_lock(&(station->lock));

    while ((station->out_passengers > 0) && (count > 0))
    {
        pthread_cond_signal(&(station->train_arrived_cond));
        count--;
        pthread_cond_wait(&(station->passengers_seated_cond), &(station->lock));
    }

        pthread_cond_wait(&(station->train_is_full_cond), &(station->lock));

    // Leave critical region
    pthread_mutex_unlock(&(station->lock));
}


void station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&(station->lock));

    station->out_passengers++;
    pthread_cond_wait(&(station->train_arrived_cond), &(station->lock));
    station->out_passengers--;
    station->in_passengers++;

    pthread_mutex_unlock(&(station->lock));

    pthread_cond_signal(&(station->passengers_seated_cond));
}

/**
Use this function to let the train know that it’s on board.
Params:
  stattion: current station pointer
*/
void station_on_board(struct station *station)
{
    pthread_mutex_lock(&(station->lock));

    station->in_passengers--;

    pthread_mutex_unlock(&(station->lock));

    if (station->in_passengers == 0)
        pthread_cond_broadcast(&(station->train_is_full_cond));
}










// Count of passenger threads that have completed (i.e. station_wait_for_train
// has returned) and are awaiting a station_on_board() invocation.

void* passenger_thread(void *arg)
{
    struct station *station = (struct station*)arg;
    station_wait_for_train(station);
    __sync_add_and_fetch(&threads_completed, 1);
    return NULL;
}



void* load_train_thread(void *args)
{
    struct load_train_args *ltargs = (struct load_train_args*)args;
    station_load_train(ltargs->station, ltargs->free_seats);
    load_train_returned = 1;
    return NULL;
}



int min(passengers_left, free_seats)
{
    if(passengers_left<free_seats)
    {
        return passengers_left;
    }
    else
        return free_seats;
}

