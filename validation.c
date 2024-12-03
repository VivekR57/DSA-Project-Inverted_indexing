#include "header.h"

// Function declarations
FILE *check_file(char *file_name);         // Function to check if a file exists
int is_file_empty(FILE *fptr);             // Function to check if a file is empty
void insert_node(file_node_t **head, char *filename);  // Function to insert a file into the linked list
Status check_extension(char *file_name);  // Function to validate the file extension

// Function to validate the input files and perform several checks (extension, existence, emptiness)
Status validation(int argc, char *argv[], file_node_t **head)
{
    printf("\n========== VALIDATION RESULT ==========\n");

    // Iterate over each file argument (starting from index 1 to skip program name)
    for (int i = 1; i < argc; i++)
    {
        printf("\nChecking file: %s\n", argv[i]);

        // Check the file extension first
        if (check_extension(argv[i]) == failure)
        {
            // If the extension is invalid, print error and skip the file
            printf("  [ERROR] Invalid file extension. Skipped: %s\n", argv[i]);
            continue;
        }

        // Check if the file exists
        FILE *fptr = check_file(argv[i]);
        if (fptr == NULL)
        {
            // If the file does not exist, print error and skip the file
            printf("  [ERROR] File does not exist: %s. Skipped.\n", argv[i]);
            continue;
        }

        // Check if the file is empty
        if (is_file_empty(fptr) == 0)
        {
            // If the file is empty, print error
            printf("  [ERROR] File is empty: %s\n", argv[i]);
        }
        else
        {
            // If all checks pass, print success and insert the file into the list
            printf("  [SUCCESS] File is valid: %s\n", argv[i]);
            insert_node(head, argv[i]);  // Add the file to the linked list
        }

        fclose(fptr);  // Close the file after processing
    }

    printf("\n=======================================\n");
    return success; // Return success after processing all files
}

// Function to check if a file exists by attempting to open it
FILE *check_file(char *file_name)
{
    // Try to open the file in read mode
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL)
    {
        // If the file can't be opened, print an error and return NULL
        printf("[ERROR] File does not exist: %s\n", file_name);
        return NULL;
    }

    return fptr; // Return the file pointer if the file exists
}

// Function to check if a file is empty
int is_file_empty(FILE *fptr)
{
    // Move the file pointer to the end to get the size of the file
    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr); // Get the size of the file
    fseek(fptr, 0, SEEK_SET); // Reset the file pointer to the beginning

    return size; // Return the file size (0 if the file is empty)
}

// Function to insert a file into the linked list of file nodes
void insert_node(file_node_t **head, char *filename)
{
    // Allocate memory for a new file node
    file_node_t *new = malloc(sizeof(file_node_t));
    if (new == NULL)
    {
        // If memory allocation fails, print an error and return
        printf("[ERROR] Memory allocation failed while inserting file: %s\n", filename);
        return;
    }
    // Copy the file name into the new node
    strcpy(new->f_name, filename);
    new->link = NULL; // Initialize the link to NULL (will be used to link to the next node)

    // Check if the list is empty (no head node)
    if (*head == NULL)
    {
        *head = new; // Set the head of the list to the new node
    }
    else
    {
        // If the list is not empty, traverse to the end of the list
        file_node_t *temp = *head;
        file_node_t *prev = NULL;
        while (temp != NULL)
        {
            // Check for duplicate file names in the list
            if (strcmp(temp->f_name, filename) == 0)
            {
                // If duplicate found, print error and return without inserting
                printf("[ERROR] Duplicate file name exists: %s\n", filename);
                free(new);  // Free the allocated memory for the new node
                return;
            }
            prev = temp;  // Move to the next node
            temp = temp->link;
        }
        // Link the new node to the last node in the list
        prev->link = new;
    }
}

// Function to print the list of files (for debugging or verification purposes)
void print_list(file_node_t *head)
{
    if (head == NULL)
    {
        printf("[INFO] List is empty\n"); // If the list is empty, print a message
    }
    else
    {
        // Traverse the list and print each file name
        while (head != NULL)
        {
            printf("%s -> ", head->f_name);
            head = head->link;
        }
        printf("NULL\n"); // End of list
    }
}

// Function to check the file extension (only ".txt" is allowed)
Status check_extension(char *file_name)
{
    // Find the last occurrence of '.' in the file name
    char *str = strstr(file_name, ".");
    if (str == NULL || strcmp(str, ".txt") != 0)
    {
        // If the extension is not ".txt", print an error and return failure
        printf("[ERROR] Invalid file extension for: %s. File extension should be .txt\n", file_name);
        return failure;
    }
    return success; // Return success if the extension is valid
}
