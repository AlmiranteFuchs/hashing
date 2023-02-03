// Main
// Author: B. Fuchs, M. Telles

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

        char* value_tmp = strtok(NULL, "");
        int value = 0;
        if (value_tmp != NULL)
        {
            value = atoi(value_tmp);
        }

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
            remove_hash(t1, t2, value);
        }
        else if (strcmp(key, "p") == 0)
        {
            get_ordered_hashs(t1, t2);

            return 0;
        }
        else
        {
            printf("Invalid command\n");
            break;
        }
    }
    // Prints the hash tables
    get_ordered_hashs(t1, t2);
    destroy_hash_table(t1);
    destroy_hash_table(t2);
    free(line);

    return 0;
}