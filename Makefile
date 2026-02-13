# We take all of the .c files
SRC := $(wildcard *.c)
# Defining OBJ for all of our existing c files
OBJ := $(SRC:.c=.o)
# Name of our program
TARGET := addressbook

# Defining our compiler and the parameters for it
CC := gcc
CFLAGS := -Wall

.PHONY: all clean

# We input our target name which is addressbook in this case
all: $(TARGET)

# Linking object files to create the program
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compililing .c files into .o files 
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# cleaning up
clean:
	$(RM) $(OBJ) $(TARGET)
