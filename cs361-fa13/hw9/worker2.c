#include<stdlib.h>
#include<stdio.h>
#include<semaphore.h>

void group();
void init() {
}

void back_ready() {
	printf("back ready\n");
	group();
}

void front_ready() {
	printf("front ready\n");
	group();
}
