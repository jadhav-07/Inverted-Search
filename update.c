/*Name   : Jitesh Narayan Jadhav
 Batch   : 25013_010
 About   : This is inverted search project. Here,I have worked with DSA project in which allows 
           storing, searching, updating, and saving words from multiple text files efficiently. 
           It is a file-based system where each word is indexed with the files it appears in and 
           the number of occurrences, enabling quick lookups.*/

#include "INVERTED.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int updated_once = 0;

static int is_database_empty(Hashtable ht[])
{
    for (int i = 0; i < 27; i++)
        if (ht[i].head != NULL)
            return 0;
    return 1;
}

// Updates the database from a backup file
void update_database(Hashtable ht[], const char *backup_file)
{
    if (!is_database_empty(ht))
    {
        printf("\n Database already created. Skipping update to prevent duplication!\n");
        printf("\n");
        return;
    }
    // Prevent multiple updates from the same backup
    if (updated_once)
    {
        printf("\n Update already performed once. Skipping!\n");
        return;
    }

    // Open the backup file
    FILE *fp = fopen(backup_file, "r");
    if (!fp)
    {
        printf(" Cannot open %s\n", backup_file);
        return;
    }

    char word[50], file[30];
    int count;

    while (fscanf(fp, "%s %s %d", word, file, &count) == 3)
    {
        to_lowercase(word);
        for (int i = 0; i < count; i++)
            insert_word(ht, word, file);
    }

    fclose(fp);
    updated_once = 1;          // Mark update as done
    printf("\n Database restored successfully from '%s'!\n", backup_file);
}
