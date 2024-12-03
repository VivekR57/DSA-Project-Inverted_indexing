#include "header.h"

/* Search for a word in the hash table
 * Description: Searches for a given word in the hash table and prints its details if found.
 * Input:
 *   - hash_table[27]: The hash table to search in.
 *   - word: The word to be searched.
 * Output:
 *   - Returns success if the word is found, along with its details.
 *   - Returns DATA_NOT_FOUND if the word is not present.
 */

int find_index(char *str);
Status search_Data_Base(main_node_t *hash_table[27], char *word)
{
    int index = find_index(word);

    if (hash_table[index] == NULL)
    {
        printf("\n***** Search Unsuccessful *****\n");
        printf("  Word not found in the database.\n");
        printf("*******************************\n");
        return DATA_NOT_FOUND;
    }

    main_node_t *temp = hash_table[index];
    while (temp != NULL)
    {
        if (strcmp(word, temp->word) == 0)
        {
            // Print the header for the found word
            printf("\n***** Search Successful *****\n");
            printf("  Word found in the Data Base.\n");
            printf("  ===========================\n");
            printf("  Index: [%d]\n", index);
            printf("  Word: %s\n", temp->word);
            printf("  File Count: %d\n", temp->f_count);
            printf("  ===========================\n");

            // Print the sub-node details (file names and word counts)
            sub_node_t *s_temp = temp->sub_link;
            printf("\n  File Details:\n");
            printf("  -------------\n");
            while (s_temp != NULL)
            {
                printf("  File: %s, Count: %d\n", s_temp->f_name, s_temp->w_count);
                s_temp = s_temp->link;
            }
            printf("  -------------\n");
            printf("*******************************\n");
            return success;
        }
        temp = temp->link;
    }

    // If the word is not found after traversing the list
    printf("\n***** Search Unsuccessful *****\n");
    printf("  Word not found in the database.\n");
    printf("*******************************\n");
    return DATA_NOT_FOUND;
}
