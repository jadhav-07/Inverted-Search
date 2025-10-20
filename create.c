/*Name   : Jitesh Narayan Jadhav
 Batch   : 25013_010
 About   : This is inverted search project. Here,I have worked with DSA project in which allows 
           storing, searching, updating, and saving words from multiple text files efficiently. 
           It is a file-based system where each word is indexed with the files it appears in and 
           the number of occurrences, enabling quick lookups.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "INVERTED.h"
// Converts a string to lowercase (used for case-insensitive storage/search)
void to_lowercase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {  
        str[i] = tolower(str[i]);
    }
}
// Converts a string to uppercase (optional utility)
void to_uppercase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper((unsigned char)str[i]);
    }
}

int get_index(const char *word)
{
    if (word[0] >= 'A' && word[0] <= 'Z')
        return word[0] - 'A';
    else if (word[0] >= 'a' && word[0] <= 'z')
        return word[0] - 'a';
    else
        return 26; 
}


void insert_word(Hashtable ht[], const char *word, const char *filename)
{
    int index = get_index(word);
    MainNode *main = ht[index].head;

    while (main)
    {
        if (strcmp(main->word, word) == 0)
        {
            SubNode *sub = main->sub_link;
            while (sub)
            {
                if (strcmp(sub->filename, filename) == 0)
                {
                    sub->word_count++;
                    return;
                }
                sub = sub->next;
            }
            SubNode *new_sub = malloc(sizeof(SubNode));
            if (!new_sub) return;
            strcpy(new_sub->filename, filename);
            new_sub->word_count = 1;
            new_sub->next = main->sub_link;
            main->sub_link = new_sub;
            main->file_count++;
            return;
        }
        main = main->next;
    }

    MainNode *new_main = malloc(sizeof(MainNode));
    if (!new_main) return;
    strcpy(new_main->word, word);
    new_main->file_count = 1;
    new_main->next = ht[index].head;
    ht[index].head = new_main;
    new_main->sub_link = NULL;

    SubNode *new_sub = malloc(sizeof(SubNode));
    if (!new_sub) return;
    strcpy(new_sub->filename, filename);
    new_sub->word_count = 1;
    new_sub->next = NULL;
    new_main->sub_link = new_sub;
}
// Creates the inverted index database from the given text files
void create_database(Hashtable ht[], char *files[], int file_count)
{
  static int created_once = 0;

    if (created_once)
    {
        printf("\nDatabase already created once. Skipping!\n");
        return;
    }

    if (file_count < 1)
    {
        printf("\nError: Need at least one .txt file.\n");
        return;
    }

    printf("\nCreating database...\n");
    int valid_files = 0;

    for (int i = 0; i < file_count; i++)
    {
        int len = strlen(files[i]);
        if (len < 5 || strcmp(files[i] + len - 4, ".txt") != 0)
        {
            printf("Skipping invalid file: %s\n", files[i]);
            continue;
        }

        FILE *fp = fopen(files[i], "r");
        if (!fp)
        {
            printf("Could not open file: %s\n", files[i]);
            continue;
        }

        valid_files++;
        char word[50];
        while (fscanf(fp, "%49s", word) == 1)
        {
            to_lowercase(word);
            int index = get_index(word);
            insert_word(ht, word, files[i]);
        }
        fclose(fp);
    }

    if (valid_files == 0)
    {
        printf("\nError: No valid .txt files found.\n");
        return;
    }

    created_once = 1;
    printf("\nDatabase created successfully using %d valid file(s).\n", valid_files);
}
