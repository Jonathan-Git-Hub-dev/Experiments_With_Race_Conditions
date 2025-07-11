#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

const int threads_number = 5;
const int large_number_of_operations = 1000;
const int not_canceled = 1;
const int thread_operation_failed = -1;

pthread_mutex_t mutex;

char globalString[1000] = "Random quote";


void* consume(void* arg)
{
        for(int operation = 0; operation < large_number_of_operations ; operation++)
        {
                //pthread_mutex_lock(&mutex);
                printf("%s\n", globalString);
                //pthread_mutex_unlock(&mutex);
                usleep(rand() % 100);
        }
        return NULL;
}

void* mutate(void* arg)
{
        char globalStringOption[6][1000] = {
                "Be yourself; everyone else is already taken",
                "Two things are infinite: the universe and human stupidity; and I'm not sure about the universe",
                "You know you're in love when you can't fall asleep because reality is finally better than your dreams",
                "Be the change that you wish to see in the world",
                "I believe that everything happens for a reason. People change so that you can learn to let go, things go wrong so that you appreciate them when they're right, you believe lies so you eventually learn to trust no one but yourself, and sometimes good things fall apart so better things can fall together",
                "Twenty years from now you will be more disappointed by the things that you didn't do than by the ones you did do. So throw off the bowlines. Sail away from the safe harbor. Catch the trade winds in your sails. Explore. Dream. Discover"
        };

        int option = 0;

        while(not_canceled)
        {
                option++;
                if(option == 6)
                {
                        option = 0;
                }
                //pthread_mutex_lock(&mutex);
                strcpy(globalString, globalStringOption[option]);
                //pthread_mutex_unlock(&mutex);
                usleep(rand() % 50);
        }
        return NULL;
}

int main(void)
{
        srand(time(NULL));


        pthread_mutex_init(&mutex, NULL);

        pthread_t consumer_thread[threads_number];
        pthread_t mutator_thread;

        for(int each_thread = 0; each_thread < threads_number; each_thread++)
        {
                if(pthread_create(&consumer_thread[each_thread], NULL, &consume, NULL) != 0)
                {
                        return thread_operation_failed;
                }
        }


        if(pthread_create(&mutator_thread, NULL, &mutate, NULL) != 0)
        {
                return thread_operation_failed;
        }


        for(int each_thread = 0; each_thread < threads_number; each_thread++)
        {
                if(pthread_join(consumer_thread[each_thread], NULL) != 0)
                {
                        return thread_operation_failed;
                }
        }


        if(pthread_cancel(mutator_thread) != 0)//when all cosuming threads are done kill producer thread
        {
                return  thread_operation_failed;
        }

        pthread_mutex_destroy(&mutex);

        return 0;
}

