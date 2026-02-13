#ifndef BOOKLIST_H
#define BOOKLIST_H
#define DELIMETER ","
#include "includes.h"

// Booklist.c Addressbook structure
struct Addressbook
{
    char name[30];
    char surname[30];
    char email[30];
    char phone[30];
    struct Addressbook* next;
};

// Struct functions
struct Addressbook* create_address_node(char *address_line);
struct Addressbook* create_node(char *name, char *surname, char *email, char *phone);
struct Addressbook* findByCriteria(struct Addressbook* head, int choice, const char* term);
struct Addressbook* deleteAtPosition(struct Addressbook** head, int position);
struct Addressbook* findByPosition(struct Addressbook** head, int position);
struct Addressbook* preload_addresses();

// Int functions for rc
int load_addresses(FILE *file, struct Addressbook **list);
int add_to_list(struct Addressbook **list, struct Addressbook *irasas);
int delete_list(struct Addressbook **list);
int insertAtEnd(struct Addressbook** head, char *name, char *surname, char *email, char *phone);
int insertAtPosition(struct Addressbook** head, char *name, char *surname, char *email, char *phone, int position);

// Void functions
void print_list(struct Addressbook *list);

#endif