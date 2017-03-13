#include<stdlib.h>
#include<stdio.h>
#include<semaphore.h>

sem_t *service_sem, *request_sem;
void pair();

void init() {
}

void wait_for_service() {
	// call pair() when ready
}

void wait_for_request() {
	// call pair() when ready
}
