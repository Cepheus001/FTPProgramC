#ifndef TABLE_HASH
#define TABLE_HASH

#define SIZE_TABLE 1000;

struct tableOfKeys {
    int key;
    char path[1024];
};

srand(time(0));

struct tableOfKeys *array;
int capacity = SIZE_TABLE;
int size = 0;

int hashFunc(int key) {
    return key = ( rand() % capacity);
}

void initArray() {
    capacity = (struct set *)malloc(capacity * sizeof(struct set));
    for (int i = 0; i < capacity; i++) {
        array[i].key = 0;
        array[i].path = ' ';
    }
}

void insertArray(int key, char path) {
    int index = hashFunc(key);
    if (array[index].path == '\0') {
        array[index].key = key;
        array[index].path = path;
        size++;
        printf("\n Key (%d) has been added", key);
    } else if (array[index].key == key) {
        array[index].path = path;
    } else {
        printf("\nA Collision has occured!");
    }
}

void removeItem(int key) {
    int index = hashFunc(key);
    if (array[index].path == '\0') {
        printf("This key to an entry does not exist!");
    }
    else {
        array[index].key = 0;
        array[index].path = ' ';
        size--;
        printf("\n Key (%d) has been removed \n", key);
    }
}

void display() {
  int i;
  for (i = 0; i < capacity; i++) {
    if (array[i].path == 0) {
    printf("\n array[%d]: / ", i);
    } else {
    printf("\n key: %d array[%d]: %d \t", array[i].key, i, array[i].data);
    }
  }
}

int SizeOfTable() {
    return size;
}


#endif