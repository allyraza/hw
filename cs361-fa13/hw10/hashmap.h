
struct entry {
	int key;
	int value;
};

#define HSIZE 1024

void map_init();
void map_put(int key, int value);
int map_get(int key);
