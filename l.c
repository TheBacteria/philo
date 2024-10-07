#include <stdio.h>
#include <pthread.h>

int shared_variable = 0;

void* thread_func(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        shared_variable++;  // Incrementing the shared variable
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create two threads that will increment the shared variable
    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final value of shared_variable: %d\n", shared_variable);
    return 0;
}
