all: basic libcmalloc hw2

basic: main.c basic.c
	gcc  --std=gnu99 -g -o basic main.c basic.c 

libcmalloc: main.c libcmalloc.c
	gcc  --std=gnu99 -g -o libcmalloc main.c libcmalloc.c 

hw2: main.c hw2.c
	gcc  --std=gnu99 -g -o hw2 main.c hw2.c 

check:
	gcc  --std=gnu99 -g -o hw2 main.c hw2.c 
	./hw2 987987

perf:
	gcc  -DPERFTEST=1 --std=gnu99 -g -o hw2 main.c hw2.c 
	time ./hw2 987987

test: check perf

clean:
	rm -rf *~ *.dSYM basic libcmalloc hw2
