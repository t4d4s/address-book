#include "booklist.h"

int load_addresses(FILE *file, struct Addressbook **list)
{
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        struct Addressbook *entry = NULL;

        // If we find an empty line we continue
        if(strcmp(line, "\n") == 0) {
            continue;
        }
        
        // We remove the empty lines.
        line[strcspn(line, "\n")] = 0;

        entry = create_address_node(line);
        if (entry != NULL) {
            add_to_list(list, entry);
        }
        else
        {
            return ERROR_MEMORY_ALLOCATION;
        }
    }
    return SUCCESS;
}

// A function that creates node address and returns the entry.
struct Addressbook* create_address_node(char *address_line)
{
    struct Addressbook *entry = NULL;
    char *name;
    char *surname;
    char *email;
    char *phone;

    name = strtok(address_line, DELIMETER);
    surname = strtok(NULL, DELIMETER);
    email = strtok(NULL, DELIMETER);
    phone = strtok(NULL, DELIMETER);

    // Checking if we have all the information we need to avoid adding empty entries
    if (name && surname && email && phone) {
        entry = create_node(name, surname, email, phone);
    }
    
    return entry;
}

// A function that creates new node and returns it.
struct Addressbook* create_node(char *name, char *surname, char *email, char *phone)
{
    struct Addressbook *entry = NULL;
    entry = (struct Addressbook*) malloc(sizeof(struct Addressbook));
    if (entry == NULL) {
        return NULL;
    }
    strcpy(entry->name, name);
    strcpy(entry->surname, surname);
    strcpy(entry->email, email);
    strcpy(entry->phone, phone);
    entry->next = NULL;
    return entry;
}

// A function that adds an entry to the list.
int add_to_list(struct Addressbook **list, struct Addressbook *entry)
{
    struct Addressbook* temp = *list;
    if (temp == NULL) {
        *list = entry;
        return SUCCESS_ENTRY_ADDED; 
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = entry;
    return SUCCESS_ENTRY_ADDED;
}

// A function that prints out the list with names, surnames, emails, phone numbers.
void print_list(struct Addressbook *list)
{
    if (list == NULL)
    {
        return;
    }

    struct Addressbook *temp = list;
    int index = 1;
    while (temp != NULL) {
        printf("[%d] %s %s %s %s\n", index, temp->name, temp->surname, temp->email, temp->phone);
        temp = temp->next;
        index++;
    }
}

// A function that completely removes the list.
int delete_list(struct Addressbook **list)
{
    if (*list == NULL)
    {
        return ERROR_EMPTY_LIST;
    }

    struct Addressbook *current = *list;
    struct Addressbook *next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *list = NULL;
    return SUCCESS;
}

// A function that inserts and address at the end
int insertAtEnd(struct Addressbook** head, char *name, char *surname, char *email, char *phone) 
{
    // Creating a new node using the structure
    struct Addressbook* newNode = create_node(name, surname, email, phone);
    // Returning error if memory alloc failed
    if (newNode == NULL)
    {
        return ERROR_MEMORY_ALLOCATION;
    }
    // If there are no nodes we insert it so it becomes the first and the last one
    if (*head == NULL) {
        *head = newNode;
        return SUCCESS_ENTRY_ADDED;
    }
    struct Addressbook* temp = *head;
    // Looping through all the nodes to see if its the end.
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return SUCCESS_ENTRY_ADDED;
}

// A function that inserts an address by the provided position
int insertAtPosition(struct Addressbook** head, char *name, char *surname, char *email, char *phone, int position) 
{
    struct Addressbook* newNode = create_node(name, surname, email, phone);

    // Checking newNode malloc
    if (newNode == NULL)
    {
        return ERROR_MEMORY_ALLOCATION;
    }

    // If we want to insert at the first place[0] we create a new node
    // And put it in the first place[0] with the information from the structure
    if (position == 0) {
        newNode->next = *head;
        *head = newNode;
        return SUCCESS_ENTRY_ADDED;
    }
    struct Addressbook* temp = *head;
    // Looping through existing nodes
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // If there are no nodes we print out rc
    if (temp == NULL) {
        //printf("Negalima irasyti, nes nera tokios pozicijos(nera tiek irasu)\n");
        free(newNode);
        return ERROR_INVALID_POSITION;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    return SUCCESS_ENTRY_ADDED;
}

// A function that deletes address in the book and returns it
struct Addressbook* deleteAtPosition(struct Addressbook** head, int position)
{
    // Checking if the list is not empty
    if (*head == NULL)
    {
        return NULL;
    }
    
    struct Addressbook* temp = *head;
    
    // Checking if the provided position is 0 (deleting the first node)
    if (position == 0)
    {
        *head = temp->next;
        temp->next = NULL;  // Disconnect the node to be deleted
        return temp;  // Return the deleted node
    }
    
    // Looping through all existing nodes
    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }
    
    // If there are no nodes or position is invalid, return NULL
    if (temp == NULL || temp->next == NULL)
    {
        return NULL; // Invalid position
    }
    
    struct Addressbook* next = temp->next;
    temp->next = temp->next->next;
    next->next = NULL;

    return next;  // Returning the deleted node
}

// A function that finds an address in the book by the provided position
struct Addressbook* findByPosition(struct Addressbook** head, int position)
{
    if (*head == NULL)
    {
        return NULL;  // Return NULL if the list is empty
    }

    struct Addressbook* temp = *head;
    int i = 0;
    while (temp != NULL)
    {
        if (i == position)
        {
            //printf("Found entry at position [%d]: %s %s %s %s\n", position + 1, temp->name, temp->surname, temp->email, temp->phone);
            return temp;  // Return the found node
        }
        i++;
        temp = temp->next;
    }

    return NULL;  // Returning NULL if the position is out of bounds or non existant
}

// A function that preloads addresses from HOME directory and returns it as a list
struct Addressbook* preload_addresses() {
    char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        //printf("Unable to get the home directory\n");
        return 0; 
    }

    char address_file_path[256];
    snprintf(address_file_path, sizeof(address_file_path), "%s/addresses.csv", home_dir);

    struct Addressbook *list = NULL;
    FILE *address_file = fopen(address_file_path, "r");

    if (address_file == NULL) {
        //printf("File not found at %s, proceeding without loading addresses.\n", address_file_path);
    } else {
        load_addresses(address_file, &list);
        fclose(address_file);
    }

    return list;
}

// A function that finds people by a criteria: name, surname, email or phone number.
struct Addressbook* findByCriteria(struct Addressbook* head, int choice, const char* term)
{
    struct Addressbook* result = NULL;  // new list that will keep track of the first node in the list
    struct Addressbook* result_tail = NULL;  // new list that will keep track of the last node in the list
    struct Addressbook* temp = head;

    while (temp != NULL)
    {
        int match = 0;
        switch(choice)
        {
            case 1: match = (strcmp(temp->name, term) == 0); break;  // name
            case 2: match = (strcmp(temp->surname, term) == 0); break;  // surname
            case 3: match = (strcmp(temp->email, term) == 0); break;  // email
            case 4: match = (strcmp(temp->phone, term) == 0); break;  // phone number
        }

        if (match)
        {
            // creating new node and adding it to the list
            struct Addressbook* new_node = malloc(sizeof(struct Addressbook));
            if (new_node == NULL)
            {
                //printf("Nepavyko priskirti atminties\n");
                return NULL;
            }
            *new_node = *temp;  // transferring whole structure
            new_node->next = NULL;

            if (result == NULL)
            {
                result = new_node;  // if result list is empty new node is the first
                result_tail = new_node;  // set result_tail to the new node
            }
            else
            {
                result_tail->next = new_node;  // link the last node in result to the new node
                result_tail = new_node;  // update result_tail to the new node
            }
        }

        temp = temp->next;
    }
    
    return result;  // returning new list containing the information we need
}