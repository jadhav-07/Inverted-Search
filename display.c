/*Name   : Jitesh Narayan Jadhav
 Batch   : 25013_010
 About   : This is inverted search project. Here, I have worked with DSA project in which allows 
           storing, searching, updating, and saving words from multiple text files efficiently. 
           It is a file-based system where each word is indexed with the files it appears in and 
           the number of occurrences, enabling quick lookups.*/
#include <stdio.h>
#include "INVERTED.h"

void display_database(Hashtable ht[])
{
    int data_found = 0;

    // Loop through all hash table indices (0–25 for a-z, 26 for others)
    for (int i = 0; i < 27; i++) 
    {
        MainNode *mtemp = ht[i].head;
        while (mtemp)
        {
            // Print header only once (when first data found)
            if (!data_found)
            {
                printf("\nData Found in the database!  \n");
            
                printf("\n%-8s %-15s %-12s %-15s %-12s\n", 
                       "Index", "Word", "File count", "File name", "Word count");
                printf("------------------------------------------------------------\n");
                data_found = 1;
            }

            printf("%-8d %-15s %-12d ", i, mtemp->word, mtemp->file_count);

            SubNode *stemp = mtemp->sub_link;
            if (stemp)
            {
                printf("%-15s %-12d\n", stemp->filename, stemp->word_count);
                stemp = stemp->next;
            }
            else
            {
                printf("\n");
            }

            while (stemp)
            {
                printf("%-8s %-15s %-12s %-15s %-12d\n",
                       "", "", "", stemp->filename, stemp->word_count);
                stemp = stemp->next;
            }

            mtemp = mtemp->next;
        }
    }

    // Only print separator if data exists, else just message
    if (data_found)
        printf("------------------------------------------------------------\n");
    else
        printf("\nNo data found in the database!\n");
        printf("\n");
}
