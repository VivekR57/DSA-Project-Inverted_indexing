#include "header.h"

// Function to create a database by processing files and inserting/updating words in a hash table
Status create_Data_Base(file_node_t **head, main_node_t *hash_table[27])
{
    file_node_t *temp = *head;  // Pointer to traverse the file linked list
    char str[100];              // Array to store each word read from the file
    int index;                  // Variable to store the index for the hash table

    // Iterate through each file node in the linked list
    while (temp != NULL)
    {
        // Open the current file for reading
        FILE *fptr = fopen(temp->f_name, "r");
        if (fptr == NULL)
        {
            // If the file can't be opened, print an error message and return failure status
            printf("ERROR: Failed to open the file '%s'.\n", temp->f_name);
            return failure;
        }

        // Read each word from the file until EOF
        while ((fscanf(fptr, "%s", str)) != EOF)
        {
            // Find the hash table index based on the first character of the word
            index = find_index(str);

            // If the hash table at the calculated index is empty, create a new node
            if (hash_table[index] == NULL)
            {
                create_and_insert_node(hash_table, index, str, temp->f_name, 1); // Add count as 1
            }
            else
            {
                // If the word exists, update the node with file information
                update_to_node(hash_table, index, str, temp->f_name, 1); // Add count as 1
            }
        }

        fclose(fptr);      // Close the file after processing
        temp = temp->link; // Move to the next file node in the list
    }
    return success; // Return success after processing all files
}

// Function to determine the index for the hash table based on the first character of the word
int find_index(char *str)
{
    // If the first character is an alphabet letter, return its corresponding index
    if (isalpha(str[0]))
    {
        return tolower(str[0]) - 'a'; // Converts 'a' to index 0, 'b' to index 1, and so on
    }
    else
    {
        return 26; // For non-alphabetic characters, place them in the last index (26)
    }
}

// Function to create and insert a new node into the hash table at a specified index
void create_and_insert_node(main_node_t *hash_table[27], int index, char *str, char *f_name, int count)
{
    // Allocate memory for a new main node and sub-node
    main_node_t *m_new = malloc(sizeof(main_node_t));
    sub_node_t *sub_new = malloc(sizeof(sub_node_t));

    // Check if memory allocation was successful
    if (!m_new || !sub_new)
    {
        printf("Memory allocation failed!\n");
        return; // Exit if memory allocation fails
    }

    // Initialize the main node with the word and file count
    strncpy(m_new->word, str, sizeof(m_new->word) - 1);
    m_new->word[sizeof(m_new->word) - 1] = '\0'; // Ensure the word is null-terminated
    m_new->f_count = 1;    // Set the initial file count to 1
    m_new->link = NULL;    // Set the link of the main node to NULL (this will be a list)
    m_new->sub_link = sub_new; // Link the sub-node to the main node

    // Initialize the sub-node with the file name and word count
    strncpy(sub_new->f_name, f_name, sizeof(sub_new->f_name) - 1);
    sub_new->f_name[sizeof(sub_new->f_name) - 1] = '\0'; // Ensure the file name is null-terminated
    sub_new->w_count = count; // Set the word count for this file
    sub_new->link = NULL; // Set the link of the sub-node to NULL (initially no other files)

    // Insert the new main node into the hash table at the specified index
    if (hash_table[index] == NULL)
    {
        // If the slot is empty, insert the node directly
        hash_table[index] = m_new;
    }
    else
    {
        // Traverse to the end of the linked list in the hash table and insert the node
        main_node_t *current = hash_table[index];
        while (current->link != NULL)
        {
            current = current->link;
        }
        current->link = m_new; // Link the new main node to the last node in the list
    }
}

// Function to update an existing node in the hash table with new file data
void update_to_node(main_node_t *hash_table[27], int index, char *str, char *f_name, int count)
{
    // Start with the node at the specified index in the hash table
    main_node_t *temp = hash_table[index];

    while (temp != NULL)
    {
        // If the word matches the current node, update the file information
        if (strcmp(temp->word, str) == 0)
        {
            sub_node_t *sub_temp = temp->sub_link;
            int file_found = 0; // Flag to track if the file is already in the sub-node list

            // Traverse the sub-nodes (files) and check if the file already exists
            while (sub_temp != NULL)
            {
                // If the file is found, update the word count
                if (strcmp(sub_temp->f_name, f_name) == 0)
                {
                     sub_temp->w_count += count; // Increment word count in the file
                    file_found = 1; // Set flag to true
                    break;
                }
                sub_temp = sub_temp->link; // Move to the next sub-node
            }

            // If the file doesn't exist in the sub-node list, create a new sub-node
            if (!file_found)
            {
                sub_node_t *s_new = malloc(sizeof(sub_node_t));
                if (!s_new)
                {
                    printf("Memory allocation failed for sub-node\n");
                    return; // Exit if memory allocation fails
                }

                // Initialize the new sub-node
                strncpy(s_new->f_name, f_name, sizeof(s_new->f_name) - 1);
                s_new->f_name[sizeof(s_new->f_name) - 1] = '\0'; // Ensure null termination
                s_new->w_count = count;                          // Set word count for the new file
                s_new->link = temp->sub_link;                    // Link to the previous sub-node
                temp->sub_link = s_new;                          // Update the main node's sub-link to the new sub-node

                temp->f_count++; // Increment the file count in the main node
            }
            return; // Exit after updating the node
        }
        temp = temp->link; // Move to the next main node
    }

    // If the word doesn't exist in the hash table, create and insert a new node
    create_and_insert_node(hash_table, index, str, f_name, count);
}
