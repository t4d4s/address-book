# 📇 Address Book CLI

A simple, command-line address book application written in C. This program uses a linked list to manage contact information, allowing users to add, delete, find, and display contacts. On startup, it automatically loads contacts from a `addresses.csv` file located in the user's home directory.

## Features

- **Display All Records**: View the entire list of contacts in the address book.
- **Add New Contacts**:
    - Append a new contact to the end of the list.
    - Insert a new contact at a specific position.
- **Delete Contacts**:
    - Remove a contact by specifying its position in the list.
    - Delete the entire address book from memory.
- **Find Contacts**:
    - Search for a contact by its position.
    - Search for contacts by criteria: name, surname, email, or phone number.
- **Automatic Data Loading**: Preloads contacts from `~/addresses.csv` if the file exists.
- **Input Validation**: Ensures that names, surnames, emails, and phone numbers are in a valid format before adding them.
- **Graceful Exit**: Handles `SIGINT`, `SIGTERM`, and `SIGQUIT` signals to clean up memory and exit properly.

## Getting Started

### Prerequisites

- A C compiler such as `gcc`.
- `make` build automation tool.

### Compilation

Clone the repository and compile the source code using the provided `Makefile`:

```bash
git clone https://github.com/t4d4s/c-address-book.git
cd c-address-book
make
```

This will create an executable file named `addressbook` in the project directory.

### Running the Application

To run the address book program, execute the compiled binary:

```bash
./addressbook
```

You will be presented with a menu of options to manage your contacts.

### Preloading Addresses

To have contacts loaded automatically when the application starts, create a file named `addresses.csv` in your home directory (`~`). The file should contain one contact per line, with fields separated by commas.

**Format:**
```
name,surname,email,phone
```

**Example `~/addresses.csv` file:**

```
John,Doe,john.doe@email.com,+15551234567
Jane,Smith,jane.s@email.com,+15557654321
```

## File Structure

The project is organized into several source and header files, each with a specific role:

-   `ui.c` / `ui.h`: Manages the main user interface loop, prints the menu, and handles user choices. Contains the `main` entry point.
-   `handler.c` / `handler.h`: Implements the logic for each menu option, including input parsing, validation, and calling the appropriate list management functions.
-   `booklist.c` / `booklist.h`: Contains the implementation of the linked list data structure for the address book. All core operations like adding, deleting, finding, and printing nodes are defined here.
-   `includes.h`: A central header file that includes standard C libraries used throughout the project.
-   `rc.h`: Defines integer constants for success and error return codes used by various functions.
-   `Makefile`: The build script to compile the source code into the final executable.

### Cleaning Up

To remove the compiled object files and the `addressbook` executable, run:

```bash
make clean
