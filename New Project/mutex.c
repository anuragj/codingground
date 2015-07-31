#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int count= 0;
void func();

int main() {
    
    pthread_t thread1, thread2;
    
    if(pthread_create(&thread1, NULL, (void *)&func, NULL)) {
        printf("Failed to create thread 1");
    }
    
    if(pthread_create(&thread2, NULL, (void *)&func, NULL)) {
        printf("Failed to create thread 2");
    }
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return 0;
}

void func() {
    
    pthread_mutex_lock(&mutex1);
    count++;
    printf("Value of count is %d \n", count);
    pthread_mutex_unlock(&mutex1);
    
}