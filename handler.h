#ifndef HANDLER_H
#define HANDLER_H

#include "includes.h"
#include "booklist.h"
#include "ui.h"

// Int functions for handling checks in the UI
int isValidPhone(const char *phone);
int isValidEmail(const char *email);
int isValidString(const char* str);

// Void function for handling the input in the UI
void helper();
void setup_signal_handlers();
void handleAddToEnd(struct Addressbook **list);
void handleAddToPosition(struct Addressbook **list);
void handleDeleteAtPosition(struct Addressbook **list);
void handleFindByPosition(struct Addressbook **list);
void handleSearchByCriteria(struct Addressbook **list);


#endif
