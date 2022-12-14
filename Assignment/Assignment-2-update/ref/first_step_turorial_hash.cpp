#include <iostream>
#include <string.h>
using namespace std;

// link tutorial: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus

#define CAPACITY 5000   // size of the hash table

/* Choose a Hash Function */
unsigned long hash_function(const char *str) {
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

/* Define the Hash Table data structures */
typedef struct Ht_item Ht_item;

struct Ht_item {
    char *key;
    char *value;
};

typedef struct HashTable HashTable;
struct HashTable {
    Ht_item **items;
    int size;
    int count;
};

/* Create the Hash Table and its items */
Ht_item* create_item(const char *key, const char *value) {
    // Creates a pointer to a new hash table item
    Ht_item *item = (Ht_item*) malloc(sizeof(Ht_item));
    item->key = (char*) malloc(strlen(key) + 1);
    item->value = (char*) malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

HashTable* create_table(int size) {
    // Create a new hash table
    HashTable *table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;
    
    return table;
}

/* free up memory that you’ve allocated on the heap */
void free_item(Ht_item *item) {
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}

/* Insert into the Hash table */
void ht_insert(HashTable* table, const char *key, const char *value) {    
    // Create a item
    Ht_item *item = create_item(key, value);
    // Compute the index
    int index = hash_function(key);
    Ht_item *current_item = table->items[index];
    if (current_item == NULL) {
        if (table->count == table->size) {
            cout << "Insert failed: Hash table is full" << endl;
            free_item(item);
            return;
        }

        table->items[index] = item;
        table->count++;
    } else {
        // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0) {
            strcpy(table->items[index]->value, value);
            return;
        }
    }
}

/* Search Items in the Hash Table */
char* ht_search(HashTable *table, const char *key) {
    int index = hash_function(key);
    Ht_item *item = table->items[index];
    
    if (item != NULL) {
        if (strcmp(item->value, key) == 0)
            return item->value;
    }

    return NULL;
}

/* Print function */

void print_search(HashTable* table, const char* key) {
    char* val;
    if ((val = ht_search(table, key)) == NULL) {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_table(HashTable* table) {
    printf("\nHash Table\n-------------------\n");
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->value);
        }
    }
    printf("-------------------\n\n");
}

int main() {
    HashTable* ht = create_table(CAPACITY);
    ht_insert(ht, "1", "First address");
    ht_insert(ht, "2", "Second address");
    print_search(ht, "1");
    print_search(ht, "2");
    print_search(ht, "3");
    print_table(ht);
    free_table(ht);
    
    return 0;
}
