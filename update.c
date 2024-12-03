#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Update the database from a file
 * Description: Reads a database file and updates the hash table with its content.
 * Input:
 *   - hash_table[27]: The hash table to populate.
 *   - file_head: Pointer to the head of the file linked list.
 * Process:
 *   - Ensures the hash table is empty.
 *   - Validates the file format (must start and end with '#').
 *   - Reads and processes each line from the file to update the hash table.
 * Output:
 *   - Returns success if the database is updated successfully.
 *   - Returns failure for errors (e.g., invalid file format, missing file).
 */

int extract_index(char str[]);
Status update_hash_table(main_node_t *hash_table[27], char *str, file_node_t **file_head);
void remove_file(file_node_t **head, char *filename);
Status Update_Data_base(main_node_t *hash_table[27], file_node_t **file_head)
{
    char file[100];
    printf("Please enter the database file name (with .txt extension): ");
    scanf("%s", file);

    for (int i = 0; i < 27; i++)
    {
        if (hash_table[i] != NULL)
        {
            printf("ERROR: A database has already been created. You cannot create a new one at this time.\n");
            return failure;
        }
    }

    // Open the file
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL)
    {
        printf("ERROR: Failed to open the file '%s'. Please ensure the file exists and you have permission to access it.\n", file);
        return failure;
    }

    // Validate the file (must start and end with '#')
    char target = '#';
    char first, last;
    first = fgetc(fptr);
    fseek(fptr, 0, SEEK_END);
    fseek(fptr, -2, SEEK_END);
    last = fgetc(fptr);

    if (first != target || last != target)
    {
        printf("ERROR: The file format is invalid. The file must start and end with '#' characters.\n");
        fclose(fptr);
        return failure;
    }

    // Move the file pointer back to the beginning of the file's content
    fseek(fptr, 0, SEEK_SET);

    // Process each line in the file and update the hash table
    char str[256];
    while (fscanf(fptr, "%[^\n]\n", str) > 0)
    {
        // Update the hash table with the extracted line
        if (update_hash_table(hash_table, str, file_head) == failure)
        {
            printf("ERROR: An issue occurred while updating the database. Please check the file format and data.\n");
            fclose(fptr);
            return failure;
        }
    }

    fclose(fptr);
    return success;
}

// Function to update the hash table with new data from the file
Status update_hash_table(main_node_t *hash_table[27], char *str, file_node_t **file_head)
{
    // Extract the index, word, and file count from the line
    int index = extract_index(strtok(str, ",")); // Extract the index
    char *word = strtok(NULL, ",");              // Extract the word
    int file_count = atoi(strtok(NULL, ","));    // Extract the file count

    // Iterate over each file and update the hash table
    for (int i = 0; i < file_count; i++)
    {
        char *file_name = strtok(NULL, ","); // Extract the file name
        int count = atoi(strtok(NULL, ",")); // Extract the count
        remove_file(file_head, file_name);
        // If the hash table for the given index is NULL, create a new node
        if (hash_table[index] == NULL)
        {
            create_and_insert_node(hash_table, index, word, file_name, count);
        }
        else
        {
            // If the node exists, update it with the file and count
            update_to_node(hash_table, index, word, file_name, count);
        }
    }

    return success;
}
int extract_index(char str[])
{
    char index[10];
    sscanf(str, "# [%[^]]]", index);
    return atoi(index);
}

void remove_file(file_node_t **head, char *filename)
{
    file_node_t *temp = *head, *prev = NULL;
    while (temp != NULL && strcmp(temp->f_name, filename) != 0)
    {
        prev = temp;
        temp = temp->link;
    }
    if (temp != NULL)
    {
        if (prev == NULL)
            *head = temp->link;
        else
            prev->link = temp->link;

        free(temp);
    }
}
