#include "handler.h"

// Global variable for input
char input[200];

// A function that checks if the provided phone number is valid format.
int isValidPhone(const char *phone) {
    return strspn(phone, "0123456789 +-()") == strlen(phone);
}

// A function that checks if the provided characters were letters.
int isValidString(const char* str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

// A function that checks if the email has the correct format.
int isValidEmail(const char *email) {
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');
    return (at && dot && at < dot && strlen(dot) > 1);
}

// Function to set up signal handlers
void setup_signal_handlers()
{
    // Setting up signal handlers for SIGINT, SIGTERM, SIGQUIT
    if (signal(SIGINT, handle_signal) == SIG_ERR)
        printf("Error setting up SIGINT handler\n");
    
    if (signal(SIGTERM, handle_signal) == SIG_ERR)
        printf("Error setting up SIGTERM handler\n");
    
    if (signal(SIGQUIT, handle_signal) == SIG_ERR)
        printf("Error setting up SIGQUIT handler\n");
}

// A function that helps to get the input and clears the newlines & buffer.
void helper() {
    // Cleaning the buffer from illegal inputs.
    while (getchar() != '\n');
    printSeperator();
    // Getting the input
    fgets(input, sizeof(input), stdin);
    // Cleaning newlines.
    input[strcspn(input, "\n")] = 0;
    printSeperator();
}

// A function that handles adding node to the end of the address book
void handleAddToEnd(struct Addressbook **list) {
    char name[30], surname[30], email[30], phone[30];
    printSeperator();
    printf("Write the name surname email and phone to insert it at the end: \n");
    printf("Example: Tadas Tadaitis tadas@tadas.lt +37060000000\n");
    helper();
    if (sscanf(input, "%29s %29s %29s %29s", name, surname, email, phone) == 4) {
        if (isValidString(name) && isValidString(surname) && isValidPhone(phone) && isValidEmail(email)) {
            int rc = insertAtEnd(list, name, surname, email, phone);
            //printf("Return code: %d\n", rc);
            if (rc == SUCCESS_ENTRY_ADDED) {
                print_list(*list);
            } else {
                printf("Error while adding entry, rc: %d\n", rc);
            }
        } else {
            printf("Bad input! Inserted values: %s %s %s %s\n", name, surname, email, phone);
            printf("Must be: Name Surname email@email.com Phone number with spaces! \n");
        }
    } else {
        printf("Inserting at the end has failed\n");
    }
}

// A function that handles adding node to the position
void handleAddToPosition(struct Addressbook **list) {
    char name[30], surname[30], email[30], phone[30];
    int pos;
    printSeperator();
    printf("Write the name surname email phone and position to insert it at desired position");
    printf("Example: Tadas Tadaitis tadas@tadas.lt +37060000000 3\n");
    helper();
    if (sscanf(input, "%29s %29s %29s %29s %d", name, surname, email, phone, &pos) == 5) {
        if (isValidString(name) && isValidString(surname) && isValidEmail(email) && isValidPhone(phone)) {
            int rc = insertAtPosition(list, name, surname, email, phone, pos - 1);
            //printf("Return code: %d\n", rc);
            if (rc == SUCCESS_ENTRY_ADDED) {
                print_list(*list);
            } else {
                printf("Error while adding entry at position(position doesn't exist), rc: %d\n", rc);
            }
        } else {
            printf("Bad input! Inserted values: %s %s %s %s %d\n", name, surname, email, phone, pos);
            printf("Must be: Name Surname email@email.com Phone number Position with spaces! \n");
        }
    } else {
        printf("Inserting at a position has failed, position must be a number!\n");
    }
}

// A function that handles deletion at a provided position.
void handleDeleteAtPosition(struct Addressbook **list) {
    int pos;
    printSeperator();
    print_list(*list);
    printSeperator();
    printf("Write the position of the address you want to remove: \n");
    
    if (scanf("%d", &pos) == 1) {
        if (pos <= 0) {
            printf("Position must be greater than 0.\n");
            return;
        }
        
        struct Addressbook* deletedNode = deleteAtPosition(list, pos - 1);
        if (deletedNode != NULL) {
            // Print the deleted entry details (name, surname, email, phone)
            printf("Deleted address: [%d] %s %s %s %s\n", pos, deletedNode->name, deletedNode->surname, deletedNode->email, deletedNode->phone);
            print_list(*list);
            free(deletedNode);
        } else {
            printf("Error while deleting entry. Invalid position or empty list.\n");
        }
    } else {
        printf("Bad input! Position must be a number!\n");
        while (getchar() != '\n'); // Clear the buffer
    }
}

// A function that handles search by the provided position.
void handleFindByPosition(struct Addressbook **list) {
    int pos;
    printSeperator();
    print_list(*list);
    printSeperator();
    printf("Write the position of the address you want to find: \n");

    if (scanf("%d", &pos) == 1) {
        pos = pos - 1;
        struct Addressbook* foundNode = findByPosition(list, pos);
        
        if (foundNode != NULL) {
            printf("Found address: [%d] %s %s %s %s\n", pos + 1, foundNode->name, foundNode->surname, foundNode->email, foundNode->phone);
            print_list(*list);
        } else {
            printf("Error: No entry found at position %d.\n", pos + 1);
        }
    } else {
        printf("Bad input! Position must be a number!\n");
        while (getchar() != '\n'); // Clear the buffer
    }
}


// A function that handles search by the provided criteria
void handleSearchByCriteria(struct Addressbook **list) {
    int search, result;
    char searchTerm[30];
    printSeperator();
    print_list(*list);
    printSeperator();
    printf("Enter by what you want to search: [1] - Name | [2] - Surname | [3] - Email | [4] - Phone\n");
    result = scanf("%d", &search);
    if (result == 1 && search >= 1 && search <= 4) {
        while (getchar() != '\n'); // clear the buffer
        printf("Write the search term: \n");
        fgets(searchTerm, sizeof(searchTerm), stdin);
        searchTerm[strcspn(searchTerm, "\n")] = 0;  // Remove newline
        struct Addressbook* results = findByCriteria(*list, search, searchTerm);
        struct Addressbook* temp = results;
        if (temp) {
            while (temp != NULL) {
                printf("Found address: %s %s %s %s\n", temp->name, temp->surname, temp->email, temp->phone);
                temp = temp->next;
            }
        } else {
            printf("No results found.\n");
        }
        // Remove the list of results to free the memory
        delete_list(&results);
    } else {
        printf("Bad input, search must be selected 1-4!\n");
    }
}