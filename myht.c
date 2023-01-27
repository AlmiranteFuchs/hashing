// Main
// Author: B. Fuchs

#include "libs/hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Create a new hash table
    hash_table *t1 = new_hash_table(11);
    hash_table *t2 = new_hash_table(11);

    // Read from stdin
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1)
    {
        // Get the key and value in the line
        char *key = strtok(line, " ");
        int value = atoi(strtok(NULL, ""));

        // See what command it is
        if (strcmp(key, "i") == 0)
        {
            // Insert the value into the hash table
            insert_hash(t1, t2, value);
        }
        else if (strcmp(key, "r") == 0)
        {
            // Delete the value from the hash table
            // delete (t1, t2, value);
        }
        else
        {
            printf("Invalid command\n");
            break;
        }
    }

    printf("T1:\n");
    print_hash(t1);
    printf("T2:\n");
    print_hash(t2);

    return 0;
}