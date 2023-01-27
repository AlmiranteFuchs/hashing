// Implementation file for hash.h
// Author : B. Fuchs

#include "hash.h"
#include <math.h>

// Creates a new dictionary entry
dict *new_dict(int value)
{
    dict *entry = malloc(sizeof(dict));
    entry->value = value;

    return entry;
}

// Creates a new empty hash table, with the given size
hash_table *new_hash_table(int size)
{
    hash_table *table = malloc(sizeof(hash_table));
    table->size = size;

    // Allocate memory for the table
    table->table = malloc(sizeof(dict *) * size);

    // Initialize all entries to NULL
    for (int i = 0; i < size; i++)
    {
        table->table[i] = new_dict(NULL);
    }

    return table;
}

//// Hash functions

// Hash functions
int hash(int key, int size)
{
    return key % size;
}
int hash_2(int key, int size)
{
    // h2(k) = ⌊m * (k * 0.9 − ⌊k * 0.9⌋)⌋
    return floor(size * (key * 0.9 - floor(key * 0.9)));
}

int get_hash(hash_table *table, hash_table *table2, int value)
{
    int hash_key = hash(value, table->size);
    int hash_2_key = hash_2(value, table->size);

    // check if the key on the first table is empty
    if (table->table[hash_key]->value == NULL)
    {
        // Key don't exist
        printf("Key don't exist\n");
        return NULL;
    }

    if (table->table[hash_key]->value == value)
    {
        // Key found
        printf("Key found on t1\n");
        return hash_key;
    }

    // else the key is in t2
    // check if the key on the second table is empty
    if (table2->table[hash_2_key]->value == NULL)
    {
        // Key don't exist
        printf("Key don't exist in T2, this wasn't supposed to happen, something is very wrong, exiting now\n");
        exit(1);
        return NULL;
    }

    printf("Key found on t2\n");
    return hash_2_key;
}

void insert_hash(hash_table *table, hash_table *table2, int value)
{
    int hash_key = hash(value, table->size);
    int hash_2_key = hash_2(value, table->size);

    // check if the key on the first table is empty
    if (table->table[hash_key]->value == NULL)
    {
        // Key don't exist
        printf("Key don't exist, inserting on t1\n");
        table->table[hash_key]->value = value;
    }
    else
    {
        // Key exist, copy value in t1 to t2
        printf("Key exist, inserting old value on t2\n");
        table2->table[hash_2_key]->value = table->table[hash_key]->value;

        // Insert new value on t1
        table->table[hash_key]->value = value;
    }
    return;
}

void print_hash(hash_table *table)
{
    for (int i = 0; i < table->size; i++)
    {
        printf("%d: %d\n", i, table->table[i]->value);
    }
}