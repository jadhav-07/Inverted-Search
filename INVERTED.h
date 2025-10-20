/*Name   : Jitesh Narayan Jadhav
 Batch   : 25013_010
 About   : This is inverted search project. Here,I have worked with DSA project in which allows 
           storing, searching, updating, and saving words from multiple text files efficiently. 
           It is a file-based system where each word is indexed with the files it appears in and 
           the number of occurrences, enabling quick lookups.*/
           
#ifndef INVERTED_H
#define INVERTED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ---------- STRUCTURES ----------

typedef struct SubNode
{
    char filename[30];
    int word_count;
    struct SubNode *next;
} SubNode;

typedef struct MainNode
{
    char word[30];
    int file_count;
    struct MainNode *next;
    SubNode *sub_link;
} MainNode;

typedef struct Hashtable
{
    MainNode *head;
} Hashtable;

// ---------- FUNCTION DECLARATIONS ----------

// Core Operations
void create_database(Hashtable ht[], char *files[], int file_count);
void display_database(Hashtable ht[]);
void update_database(Hashtable ht[], const char *backup_file);
void search_word(Hashtable ht[], const char *word);
void save_database(Hashtable ht[], const char *outfile);
void insert_word(Hashtable ht[], const char *word, const char *filename);
// ---------- Helper Utilities ----------
void to_lowercase(char *str);
void to_uppercase(char *str);
int get_index(const char *word);

#endif
