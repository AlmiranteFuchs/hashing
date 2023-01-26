// Implementation file for hash.h
// Author : B. Fuchs

#include "hash.h"
#include <math.h>

// Creates a new dictionary entry
dict *new_dict(char *key, int value){
    dict *entry = malloc(sizeof(dict));
    entry->key = key;
    entry->value = value;

    return entry;
}

// Creates a new empty hash table, with the given size
hash_table *new_hash_table(int size){
    hash_table *table = malloc(sizeof(hash_table));
    table->size = size;

    // Allocate memory for the table
    table->table = malloc(sizeof(dict *) * size);

    // Initialize all entries to NULL
    for(int i = 0; i < size; i++){
        table->table[i] = new_dict("", 0);
    }

    return table;
}

// Hash functions
int hash(int key, int size){
    return key % size;
}
int hash_2(int key, int size){
    //h2(k) = ⌊m * (k * 0.9 − ⌊k * 0.9⌋)⌋
    return floor(size * (key * 0.9 - floor(key * 0.9)));
}