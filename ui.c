#include "ui.h"

struct Addressbook *list = NULL;

// Signal handler function
void handle_signal(int signal)
{
    switch (signal)
    {
        case SIGINT:
            printf("\nCaught SIGINT (Interrupt). Exiting...\n");
            break;
        case SIGTERM:
            printf("\nCaught SIGTERM (Terminate). Exiting...\n");
            break;
        case SIGQUIT:
            printf("\nCaught SIGQUIT (Quit). Exiting...\n");
            break;
        default:
            printf("\nCaught unknown signal. Exiting...\n");
            break;
    }
    delete_list(&list);
    exit(0);
}

// A function that prints out a seperator.
void printSeperator() {
    printf("****************************\n");
}

// A function that prints out the choices of the menu.
void printHelper() {
    printf("\nPress 1 to display all records in the address book\n");
    printf("Press 2 to add a new address to the book(to the end)\n");
    printf("Press 3 to add a new address indicating the position\n");
    printf("Press 4 to delete address indicating its position in the book\n");
    printf("Press 5 to delete the whole address book\n");
    printf("Press 6 to find an address by position\n");
    printf("Press 7 to find address by name, surname, email, or phone number\n");
    printf("Enter your choice: ");
}

// Entrypoint
int main(void) {
    setup_signal_handlers();
    ui_loop();
    return 0;
}

// UI loop function
void ui_loop() {
    list = preload_addresses();
    int choice;
    while (1) {
        printHelper();
        if (scanf("%d", &choice) != 1) {
            printf("Bad input! Please enter a valid number.\n");
            while (getchar() != '\n'); // clear the buffer
            continue;
        }

        switch (choice) {
            case 1: {
                printSeperator();
                if (list != NULL) {
                    print_list(list);
                } else {
                    printf("Address book is empty\n");
                }
                printSeperator();
                break;
            }
            case 2:
                handleAddToEnd(&list);
                break;
            case 3:
                handleAddToPosition(&list);
                break;
            case 4:
                handleDeleteAtPosition(&list);
                break;
            case 5: {
                delete_list(&list);
                printf("Address book has been deleted!\n");
                break;
            }
            case 6:
                handleFindByPosition(&list);
                break;
            case 7:
                handleSearchByCriteria(&list);
                break;
            default:
                printf("Invalid choice! Selection must be 1-7\n");
                //delete_list(&list);
                break;
        }
    }
}