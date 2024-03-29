// Header file for hash.c
// Author : B. Fuchs
// Cuckoo Hashing without rehashing

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>

// Simple dictionary?
typedef struct
{
    int key;
    int value;
    char* table_name;
} dict;

// Hash table
typedef struct
{
    int size;
    dict **table;
} hash_table;

// Create a new hash table
hash_table *new_hash_table(int size);
void destroy_hash_table(hash_table *table);

// Hash function
int hash(int key, int size);
int hash_2(int key, int size);
dict *get_hash(hash_table *table, hash_table *table2, int key);
void insert_hash(hash_table *table, hash_table *table2, int value);
void remove_hash(hash_table *table, hash_table *table2, int value);

void print_hash(hash_table *table);
void print(hash_table *table, hash_table *table2);
int *get_ordered_hashs(hash_table *table, hash_table *table2);

void quick_sort(int *ordered_hash, int left, int right);

#endif