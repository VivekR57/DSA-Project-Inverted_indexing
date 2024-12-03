#include "header.h"

/* Save hash table data to a file
 * Description: Saves the contents of the hash table to a .txt file in a structured format.
 * Input:
 *   - hash_table[27]: The hash table containing words and associated file details.
 * Output:
 *   - Returns `success` if the data is saved successfully.
 *   - Returns `failure` if the file name is invalid or file operations fail.
 */

Status save_Data_Base(main_node_t *hash_table[27])
{
    char file[100]; // Buffer for file name

    // Prompt user for file name
    printf("Enter file name (with .txt extension): ");
    scanf("%s", file);

    // Validate file extension
    char *Dot = strstr(file, ".");
    if (strcmp(Dot, ".txt") != 0)
    {
        printf("Error: File extension must be .txt\n");
        return failure;
    }

    // Open file in write mode
    FILE *fptr = fopen(file, "w");
    if (fptr == NULL)
    {
        printf("Error: Unable to open file\n");
        return failure;
    }

    // Write hash table data to file
    for (int i = 0; i < 27; i++)
    {
        if (hash_table[i]) // Check for non-empty index
        {
            main_node_t *main_node = hash_table[i];
            while (main_node) // Traverse main nodes
            {
                fprintf(fptr, "# [%d],%s,%d", i, main_node->word, main_node->f_count);

                // Write sub-node details
                sub_node_t *sub_node = main_node->sub_link;
                while (sub_node)
                {
                    fprintf(fptr, ",%s,%d", sub_node->f_name, sub_node->w_count);
                    sub_node = sub_node->link;
                }
                fprintf(fptr, " #\n");
                main_node = main_node->link;
            }
        }
    }

    fclose(fptr); // Close file
    return success;
}
