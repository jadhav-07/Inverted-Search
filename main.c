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

int main(int argc, char *argv[])
{
    Hashtable ht[27] = {0};
    int file_count = argc - 1;
    char word[30];
    char savefile[50];
    int choice;
    // Check if at least one file is provided as command-line argument
    if (argc < 2)
    {
        printf("Usage: %s <file1.txt> [file2.txt] ...\n", argv[0]);
        return 1;
    }
    // Validate each input file
    for (int i = 1; i < argc; i++)
    {
        char *file = argv[i];
        int len = strlen(file);
        // Check for valid .txt extension
        if (len < 5 || strcmp(file + len - 4, ".txt") != 0)
        {
            printf("%s is not a valid .txt file\n", file);
            return 1;
        }
        // Check if the file can be opened
        FILE *fp = fopen(file, "r");
        if (fp == NULL)
        {
            printf("%s not found or cannot be opened\n", file);
            return 1;
        }
        fclose(fp);
        // Print confirmation that file is valid
        printf("%s is valid\n", file);
    }

    printf("\n=========== INVERTED SEARCH ===========\n");

    while (1)
    {
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Update Database\n");
        printf("4. Search Word\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                create_database(ht, &argv[1], file_count);
                break;

            case 2:
                display_database(ht);
                break;

            case 3:
                update_database(ht, "backup.txt");
                break;

            case 4:
                printf("Enter word to search: ");
                scanf("%s", word);
                to_lowercase(word);
                search_word(ht, word);
                break;

            case 5:
                printf("Enter filename to save database (e.g., output.txt): ");
                scanf("%s", savefile);
                // Validate filename
                if (strlen(savefile) < 5 || strcmp(savefile + strlen(savefile) - 4, ".txt") != 0)
                {
                    printf("Invalid filename! Must end with .txt\n");
                }
                else
                {
                    save_database(ht, savefile);
                   // printf("\nDatabase saved successfully to %s\n", savefile);
                }
                break;

            case 6:
                printf("Exit__ \n");
                printf("\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
