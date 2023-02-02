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
        table->table[i]->key = i;
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

dict *get_hash(hash_table *table, hash_table *table2, int value)
{
    int hash_key = hash(value, table->size);
    int hash_2_key = hash_2(value, table->size);

    // check if the key on the second table is empty
    if (table->table[hash_key]->value == value)
    {
        return table->table[hash_key];
    }

    if (table2->table[hash_2_key]->value == value)
    {
        return table2->table[hash_2_key];
    }
    return NULL;
}

void insert_hash(hash_table *table, hash_table *table2, int value)
{
    int hash_key = hash(value, table->size);

    // check if the key on the first table is empty
    if (table->table[hash_key]->value == -1)
    {
        // Key don't exist
        table->table[hash_key]->value = value;
        table->table[hash_key]->key = hash_key;
        table->table[hash_key]->table_name = "T1";
    }
    else
    {
        // get value on t1
        int old_value = table->table[hash_key]->value;
        int old_hash_2_key = hash_2(old_value, table->size);

        // Key exist, copy value in t1 to t2
        table2->table[old_hash_2_key]->value = table->table[hash_key]->value;
        table2->table[old_hash_2_key]->key = old_hash_2_key;
        table2->table[old_hash_2_key]->table_name = "T2";

        // Insert new value on t1
        table->table[hash_key]->value = value;
        table->table[hash_key]->key = hash_key;
        table->table[hash_key]->table_name = "T1";
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
        table->table[hash_key]->value = -1;
        table->table[hash_key]->key = -1;
        table->table[hash_key]->table_name = NULL;

        return;
    }

    if (table2->table[hash_2_key]->value == value)
    {
        // Key don't exist
        table2->table[hash_2_key]->value = -1;
        table2->table[hash_2_key]->key = -1;
        table2->table[hash_2_key]->table_name = NULL;

        return;
    }
    return;
}

void print_hash(hash_table *table)
{
    for (int i = 0; i < table->size; i++)
    {
        printf("%d: %d - %s\n", i, table->table[i]->value, table->table[i]->table_name);
    }
}

int *get_ordered_hashs(hash_table *table, hash_table *table2)
{
    int *ordered_hash = malloc(sizeof(int *) * table->size * 2);

    // This is very confusing, bc I didn't want to repeat the key of a dictionary because the index of the vector is already the key
    // In the loops i'm saving the value
    int c = 0;
    for (int i = 0; i < table->size; i++)
    {
        if (table->table[i]->value != -1)
        {
            ordered_hash[c] = table->table[i]->value;
            c++;
        }
    }

    for (int i = 0; i < table2->size; i++)
    {
        if (table2->table[i]->value != -1)
        {
            ordered_hash[c] = table2->table[i]->value;
            c++;
        }
    }

    // Print vector
    // for (int i = 0; i < c; i++)
    // {
    //     printf("Values before sort: fake key:    %d\n", i);
    //     printf("                  : actual key:  %d\n", ordered_hash[i]);
    //     printf("                  : table value: %d\n", ordered_hash[i] > 10 ? table2->table[ordered_hash[i] - 11]->value : table->table[ordered_hash[i]]->value);
    //     printf("                  : table name:  %s\n", ordered_hash[i] > 10 ? table2->table[ordered_hash[i] - 11]->table_name : table->table[ordered_hash[i]]->table_name);
    // }

    // Quick sort
    quick_sort(ordered_hash, 0, c - 1);

    // Print vector
    for (int i = 0; i < c; i++)
    {
        // Get hash key
        dict *d = get_hash(table, table2, ordered_hash[i]);

        // print like value, table name, table value
        printf("%d,%s,%d\n", d->value, d->table_name, d->key);
    }

    return ordered_hash;
}

void quick_sort(int *ordered_hash, int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = ordered_hash[(left + right) / 2];

    /* partition */
    while (i <= j)
    {
        while (ordered_hash[i] < pivot)
            i++;
        while (ordered_hash[j] > pivot)
            j--;
        if (i <= j)
        {
            tmp = ordered_hash[i];
            ordered_hash[i] = ordered_hash[j];
            ordered_hash[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quick_sort(ordered_hash, left, j);
    if (i < right)
        quick_sort(ordered_hash, i, right);
}

void destroy_hash_table(hash_table *table)
{
    for (int i = 0; i < table->size; i++)
    {
        free(table->table[i]);
    }
    free(table->table);
    free(table);
}