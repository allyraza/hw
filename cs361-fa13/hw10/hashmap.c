#include<stdio.h>
#include<stdlib.h>
#include"hashmap.h"
#include<string.h>

struct entry buckets[HSIZE];


void map_init() {
	memset(buckets,0,sizeof(buckets));
}

static int hash(int key) {
	return ((unsigned)key*229) % HSIZE;
}

void map_put(int key, int value) { 
	int h = hash(key);
	int count = 0;
	while(buckets[h].key!=0 && count++<1024)  
		h=(h+1)%HSIZE;
	
	if(count>=1024) {
		fprintf(stderr,"Ran out of buckets %d!\n",count);
			exit(1);
	}

	buckets[h].key=key;
	buckets[h].value=value;

}

int map_get(int key) {
	int h = hash(key);
	int count = 0;
	while(buckets[h].key && buckets[h].key!=key && count++<1024) 
		h=(h+1)%HSIZE;

	if(count==1024) {
		fprintf(stderr,"Ran out of buckets!\n");
		exit(1);
	}
	
	if(buckets[h].key==0)
		return 0;
	else if(buckets[h].key==key)
		return buckets[h].value;
	
	// really shouldn't reach this line
	printf("Huh?\n");
	exit(1);
}
