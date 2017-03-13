
all: nosync pthread_mutex semaphore futex atomicincrement

clean: 	
	rm -f nosync pthread_mutex semaphore futex atomicincrement

nosync: nosync.c counter.c
	gcc --std=gnu99 -o nosync nosync.c counter.c -lpthread


pthread_mutex:	pthread_mutex.c counter.c
	gcc --std=gnu99 -o pthread_mutex pthread_mutex.c counter.c -lpthread

semaphore: semaphore.c counter.c
	gcc --std=gnu99 -o semaphore semaphore.c counter.c -lpthread

futex: futex.c counter.c
	gcc --std=gnu99 -o futex futex.c counter.c -lpthread


atomicincrement: atomicincrement.c counter.c
	gcc --std=gnu99 -o atomicincrement atomicincrement.c counter.c -lpthread

hashmap: hashmap.c hashmain.c
	gcc --std=gnu99 -o hashmap hashmain.c hashmap.c -lpthread

globallock: globallock.c hashmain.c
	gcc --std=gnu99 -o globallock hashmain.c globallock.c -lpthread

test:	pthread_mutex semaphore futex atomicincrement hashmap globallock
	time	./pthread_mutex
	time 	./semaphore
	time 	./atomicincrement
	time 	./futex
	time 	./globallock
