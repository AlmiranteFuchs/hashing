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
        table->table[i] = new_dict(-1);
        table->table[i]->table_name = NULL;
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

    // check if the key on the second table is empty
    if (table->table[hash_key]->value == value)
    {
        // Key don't exist
        printf("Key exist\n");
        return hash_key;
    }

    if (table2->table[hash_2_key]->value == value)
    {
        // Key don't exist
        printf("Key exist\n");
        return hash_2_key;
    }
    printf("Key don't exist, get\n");
    return -1;
}

void insert_hash(hash_table *table, hash_table *table2, int value)
{
    int hash_key = hash(value, table->size);

    // check if the key on the first table is empty
    if (table->table[hash_key]->value == -1)
    {
        // Key don't exist
        printf("Key don't exist, inserting on t1\n");
        table->table[hash_key]->value = value;
        table->table[hash_key]->table_name = "t1";
    }
    else
    {
        // get value on t1
        int old_value = table->table[hash_key]->value;
        int old_hash_2_key = hash_2(old_value, table->size);

        // Key exist, copy value in t1 to t2
        printf("Key exist, inserting old value on t2\n");
        table2->table[old_hash_2_key]->value = table->table[hash_key]->value;
        table2->table[old_hash_2_key]->table_name = "t2";

        // Insert new value on t1
        table->table[hash_key]->value = value;
        table->table[hash_key]->table_name = "t1";
    }
    return;
}

void remove_hash(hash_table *table, hash_table *table2, int value)
{
    int hash_key = hash(value, table->size);
    int hash_2_key = hash_2(value, table->size);

    // check if the key on the second table is empty
    if (table->table[hash_key]->value == value)
    {
        // Key don't exist
        printf("Key exist\n");
        table->table[hash_key]->value = -1;
        table->table[hash_key]->table_name = NULL;

        return;
    }

    if (table2->table[hash_2_key]->value == value)
    {
        // Key don't exist
        printf("Key exist\n");
        table2->table[hash_2_key]->value = -1;
        table2->table[hash_2_key]->table_name = NULL;

        return;
    }
    printf("Key don't exist, get\n");
    return;
}

void print_hash(hash_table *table)
{
    for (int i = 0; i < table->size; i++)
    {
        printf("%d: %d - %s\n", i, table->table[i]->value, table->table[i]->table_name);
    }
}

dict **get_ordered_hashs(hash_table *table, hash_table *table2)
{
    dict **ordered_hash = malloc(sizeof(dict *) * table->size * 2);

    int j = 11;
    for (int i = 0; i < table->size; i++)
    {
        ordered_hash[i] = table->table[i];
    }

    for (int i = 0; i < count; i++)
    {
        /* code */
    }
    

    return ordered_hash;
}