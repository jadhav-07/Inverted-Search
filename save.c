/*Name   : Jitesh Narayan Jadhav
 Batch   : 25013_010
 About   : This is inverted search project. Here,I have worked with DSA project in which allows 
           storing, searching, updating, and saving words from multiple text files efficiently. 
           It is a file-based system where each word is indexed with the files it appears in and 
           the number of occurrences, enabling quick lookups.*/
           
#include "INVERTED.h"
#include <stdio.h>

void save_database(Hashtable ht[], const char *outfile)
{
    FILE *fp = fopen(outfile, "w");
    if (!fp)
    {
        printf("Cannot open %s for writing\n", outfile);
        return;
    }

    for (int i = 0; i < 27; i++)
    {
        MainNode *main = ht[i].head;
        while (main)
        {
            int file_count = 0;
            SubNode *tmp = main->sub_link;
            while (tmp)
            {
                file_count++;
                tmp = tmp->next;
            }

            SubNode *sub = main->sub_link;
            while (sub)
            {
                fprintf(fp, "# %d ; %s ; %d ; %s ; %d #\n",
                    i,
                    main->word,
                    file_count,
                    sub->filename,
                    sub->word_count
                );
                sub = sub->next;
            }

            main = main->next;
        }
    }

    fclose(fp);
    printf("\nDatabase saved successfully to %s\n", outfile);
    printf("\n");
}
