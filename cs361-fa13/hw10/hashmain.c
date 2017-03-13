#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include"hashmap.h"

void* run_thread(void* threadid) {
	for(int i=0;i<256;i++){
		map_put(1+(random()%(1024*1024)),(int)threadid);
	}			
	return 0;
}

extern struct entry buckets[HSIZE];

int check() {
	int ones=0,twos=0;
	for(int i=0;i<HSIZE;i++) {
		if(buckets[i].value==1) ones++;
		if(buckets[i].value==2) twos++;
	}
	if(ones==256 && twos==256) return 1;
	else {
		printf("Got %d ones, %d twos\n",ones,twos);
		return 0;
	}
}

int main(int argc, char** argv) {	
	srandom(12341234);
	map_init();
	memset(buckets,0,sizeof(buckets));

	for(int i=0;i<1000;i++) {
		pthread_t a,b;
		pthread_create(&a,0,run_thread,(void*)1);
		pthread_create(&b,0,run_thread,(void*)2);
		void* rval;
		pthread_join(a,&rval);
		pthread_join(b,&rval);
		
		if(!check()) {
			fprintf(stderr,"Error, hash map inconsistency\n");
			exit(1);
		}
		else {
			memset(buckets,0,sizeof(buckets));
		}
	}

	printf("[PASSED] basic hashmap put test\n");
}
