#ifndef HEADER_H
#define HEADER_H

// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Define constants
#define NAME_LENGTH 25    // Maximum length for file and word names
#define DATA_NOT_FOUND -1 // Error code for data not found

// Define a status enum for success and failure
typedef enum
{
    success, // Operation successful
    failure  // Operation failed
} Status;

// Define the sub-node structure
typedef struct sub_node
{
    char f_name[NAME_LENGTH]; // File name
    int w_count;              // Word count in the file
    struct sub_node *link;    // Pointer to the next sub-node
} sub_node_t;

// Define the main-node structure
typedef struct node
{
    char word[NAME_LENGTH]; // Word in the hash table
    struct node *link;      // Pointer to the next main-node
    sub_node_t *sub_link;   // Pointer to the list of sub-nodes
    int f_count;            // File count associated with the word
} main_node_t;

// Define the file-node structure
typedef struct file_node
{
    char f_name[NAME_LENGTH]; // File name
    struct file_node *link;   // Pointer to the next file-node
} file_node_t;

// Function prototypes

// Validation functions
Status validation(int argc, char *argv[], file_node_t **head);
// Validates command-line arguments and initializes the file list

// Display functions
void print_list(file_node_t *head);
// Prints the list of files
void Display_database(main_node_t *hash_table[27]);
// Displays the contents of the hash table

// Database creation and manipulation functions
Status create_Data_Base(file_node_t **head, main_node_t *hash_table[27]);
// Creates the initial database using file list and hash table
Status save_Data_Base(main_node_t *hash_table[27]);
// Saves the database to a file
Status Update_Data_base(main_node_t *hash_table[27], file_node_t **file_head);
// Updates the database with new files
Status update_hash_table(main_node_t *hash_table[27], char *str, file_node_t **file_head);
// Updates the hash table for a given word and file list

// Search function
Status search_Data_Base(main_node_t *hash_table[27], char *word);
// Searches for a word in the database

// Helper functions
int find_index(char *str);
// Finds the hash index for a given string
void create_and_insert_node(main_node_t *hash_table[27], int index, char *str, char *f_name, int count);
// Creates and inserts a new main-node into the hash table
void update_to_node(main_node_t *hash_table[27], int index, char *str, char *f_name, int count);
// Updates an existing main-node in the hash table
void free_hash_table(main_node_t *hash_table[27]);
// Frees all memory allocated for the hash table

#endif // HEADER_H
