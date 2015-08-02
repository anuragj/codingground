#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t odd = PTHREAD_COND_INITIALIZER;
pthread_cond_t even = PTHREAD_COND_INITIALIZER;

void *oddf();
void *evenf();
int count = 0;
#define COUNTER 20

int main()
{
    pthread_t oddthread, eventhread;
    
    if(pthread_create(&oddthread, NULL, oddf, NULL)) {
        printf("Failed to create oddthread");
        return -1;
    }
    
    if(pthread_create(&eventhread, NULL, evenf, NULL)) {
        printf("Failed to create eventhread");
        return -1;
    }
    
    pthread_join(eventhread, NULL);
    pthread_join(oddthread, NULL);

    return 0;
}

void *oddf() {
    while(count < COUNTER) {
        pthread_mutex_lock(&mutex);
        while(count % 2 == 0) {
            pthread_cond_wait(&odd, &mutex);
        }
        printf("ODD: %d \n", count);
        count++;
        pthread_cond_signal(&even);
        pthread_mutex_unlock(&mutex);
    }
}

void *evenf() {
    while(count < COUNTER) {
        pthread_mutex_lock(&mutex);
        while(count % 2 != 0) {
            pthread_cond_wait(&even, &mutex);
        }
        printf("EVEN %d \n", count);
        count++;
        pthread_cond_signal(&odd);
        pthread_mutex_unlock(&mutex);
    }
}