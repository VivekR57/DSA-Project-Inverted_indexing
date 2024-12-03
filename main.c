#include "header.h"

int main(int argc, char *argv[])
{
    // Hash table initialization
    main_node_t *hash_table[27] = {NULL};
    file_node_t *head = NULL;

    // Validate the command-line arguments
    if (argc > 1)
    {
        if (validation(argc, argv, &head) == failure)
        {
            printf("Error: Validation failed\n");
            return failure;
        }
    }
    else
    {
        printf("Error: Please pass the valid number of arguments\n");
        return failure;
    }

    // Print the list of files
    print_list(head);

    // Main menu loop
    while (1)
    {
        int choice;
        printf("\n=====================================\n");
        printf("|             MAIN MENU             |\n");
        printf("=====================================\n");
        printf("|  Option |        Description      |\n");
        printf("=====================================\n");
        printf("|    1    | Create Data Base        |\n");
        printf("|    2    | Display Data Base       |\n");
        printf("|    3    | Search Data Base        |\n");
        printf("|    4    | Save Data Base          |\n");
        printf("|    5    | Update Data Base        |\n");
        printf("|    6    | Exit                    |\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle user choices
        switch (choice)
        {
        case 1:
            // Create the database
            if (create_Data_Base(&head, hash_table) == success)
            {
                printf("\n***** Operation Successful *****\n");
                printf("  Data Base created successfully.\n");
                printf("**********************************\n");
            }
            else
            {
                printf("\n***** Operation Failed *****\n");
                printf("  Error: Failed to create Data Base.\n");
                printf("******************************\n");
            }
            break;

        case 2:
            // Display the database
            printf("\n***** Displaying Database *****\n");
            Display_database(hash_table);
            printf("**********************************\n");
            break;

        case 3:
        {
            // Search for a word in the database
            char str[100];
            printf("Please enter the word you want to search for: ");
            scanf("%s", str);

            int search_result = search_Data_Base(hash_table, str);
            if (search_result == success)
            {
                printf("\n***** Operation Successful *****\n");
                printf("  Search successful: Word found in the Data Base.\n");
                printf("**********************************\n");
            }
            else if (search_result == DATA_NOT_FOUND)
            {
                printf("\n***** Operation Unsuccessful *****\n");
                printf("  Search unsuccessful: Word not found.\n");
                printf("************************************\n");
            }
            else
            {
                printf("\n***** Operation Failed *****\n");
                printf("  Error: Search operation failed.\n");
                printf("******************************\n");
            }
            break;
        }

        case 4:
            // Save the database
            if (save_Data_Base(hash_table) == success)
            {
                printf("\n***** Operation Successful *****\n");
                printf("  Data Base saved successfully.\n");
                printf("**********************************\n");
            }
            else
            {
                printf("\n***** Operation Failed *****\n");
                printf("  Error: Failed to save Data Base.\n");
                printf("******************************\n");
            }
            break;

        case 5:
            // Update the database
            if (Update_Data_base(hash_table, &head) == success)
            {
                printf("\n***** Operation Successful *****\n");
                printf("  Data Base updated successfully.\n");
                printf("**********************************\n");
            }
            else
            {
                printf("\n***** Operation Failed *****\n");
                printf("  Error: Failed to update Data Base.\n");
                printf("******************************\n");
            }
            break;

        case 6:
            // Exit the program
            printf("\n***** Exiting Program *****\n");
            printf("  Goodbye!\n");
            printf("*****************************\n");
            return 0;

        default:
            // Handle invalid menu choices
            printf("\n***** Invalid Choice *****\n");
            printf("  Error: Please enter a valid option.\n");
            printf("***************************\n");
        }
    }
}
