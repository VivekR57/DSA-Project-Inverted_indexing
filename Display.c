#include "header.h"

// Function to display the contents of a hash table, which contains a linked list of words and their associated file data.
void Display_database(main_node_t *hash_table[27])
{
    // Print the table header with column names
    printf("\n+---------------------------------------------------------------------------------------------------------+\n");
    printf("| %-5s | %-15s | %-10s | %-50s |\n", "Index", "Word", "File Count", "File Names (Count)");
    printf("+---------------------------------------------------------------------------------------------------------+\n");

    // Iterate through each index of the hash table (assumed to have 27 possible entries)
    for (int i = 0; i < 27; i++)
    {
        // Check if the current index in the hash table is not NULL (meaning it contains data)
        if (hash_table[i] != NULL)
        {
            // Set the current node of the main linked list at this index
            main_node_t *main_node = hash_table[i];
            
            // Traverse the linked list of main_node_t structures at this index
            while (main_node != NULL)
            {
                // Print the word's index, word, and file count in the current row of the table
                printf("| %-5d | %-15s | %-10d | ", i, main_node->word, main_node->f_count);

                // Access the sub_node_t linked list that holds file names and word counts
                sub_node_t *sub_node = main_node->sub_link;

                // Check if there is any file data associated with the current word
                if (sub_node != NULL)
                {
                    // Traverse the linked list of sub_node_t structures (each representing a file)
                    while (sub_node != NULL)
                    {
                        // Print the file name and word count from the sub_node_t
                        printf("%s (%d)", sub_node->f_name, sub_node->w_count);

                        // Move to the next sub_node_t if available
                        sub_node = sub_node->link;

                        // If there are more files, separate them with a comma and space
                        if (sub_node != NULL)
                            printf(", ");
                    }
                }
                else
                {
                    // If there are no files associated with the current word, print "N/A"
                    printf("N/A");
                }

                // Close the current row of the table
                printf(" |\n");

                // Move to the next main_node_t in the linked list (if available)
                main_node = main_node->link;
            }
        }
    }

    // Print the footer of the table to close it
    printf("+---------------------------------------------------------------------------------------------------------+\n");
}
