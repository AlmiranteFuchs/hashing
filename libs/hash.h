// Header file for hash.c
// Author : B. Fuchs
// Cuckoo Hashing without rehashing

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>

// Simple dictionary?
typedef struct {
    int key;
    int value;
} dict;

// Hash table
typedef struct {
    int size;
    dict **table;
    void (*add)(struct hash_table *table, int key, int value);
} hash_table;



// Create a new hash table
hash_table *new_hash_table(int size);

// Hash function
int hash(int key, int size);
int hash_2(int key, int size);


#endif