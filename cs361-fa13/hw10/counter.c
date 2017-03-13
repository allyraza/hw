#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void init();
void increment();

int shared=0;

void* run_thread(void* nothing) {
	for(int i=0;i<100000;i++)
		increment();	
	return 0;
}

int main(int argc, char** argv) {	
	init();
	
	pthread_t thread[100];
	for(int i=0;i<100;i++) 
		pthread_create(&thread[i],0,run_thread,0);
		
	void* rval;
	for(int i=0;i<100;i++) 
		pthread_join(thread[i],&rval);		

	if(shared==100*100000) {
		printf("[PASS] Counter %s\n",argv[0]);
	}
	else {
		printf("[FAIL] Counter %s, value is %d\n",argv[0],shared);
		exit(1);
	}
}
