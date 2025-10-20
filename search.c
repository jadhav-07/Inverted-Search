/*Name   : Jitesh Narayan Jadhav
 Batch   : 25013_010
 About   : This is inverted search project. Here,I have worked with DSA project in which allows 
           storing, searching, updating, and saving words from multiple text files efficiently. 
           It is a file-based system where each word is indexed with the files it appears in and 
           the number of occurrences, enabling quick lookups.*/

#include "INVERTED.h"
#include <stdio.h>
#include <string.h>

void search_word(Hashtable ht[], const char *word)
{
    int index = get_index(word);
    MainNode *main = ht[index].head;
    int found = 0;
    // Traverse the linked list at the hash index
    while (main)
    {
        if (strcmp(main->word, word) == 0)
        {
            printf("\n Word '%s' found in:\n", word);
            // Traverse the SubNode list to print each file and word count
            SubNode *sub = main->sub_link;
            while (sub)
            {
                printf("   %-10s ->   %d times\n", sub->filename, sub->word_count);
                sub = sub->next;
            }
            printf("\n");
            found = 1;
            break;
        }
        main = main->next;      // Move to next word in the hash index
    }

    if (!found)
        printf("\n Word '%s' not found in database!\n", word);
}
