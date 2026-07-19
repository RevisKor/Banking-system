# 1. Compiler and Flags
CC      := gcc
CFLAGS  := -Wall -Wextra -g -Iinclude

# 2. Directories
SRCDIR  := src
OBJDIR  := obj

# 3. Target Output
TARGET  := app

# 4. Source and Object File Discovery
# Finds main.c and all .c files inside the src/ directory (including nested folders)
SRCS    := main.c $(shell find $(SRCDIR) -name '*.c' 2>/dev/null)
# Converts those .c paths into corresponding .o paths inside the obj/ folder
OBJS    := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

# 5. Default Rule (What runs when you just type 'make')
all: $(TARGET)

# 6. Link Step: Combines all .o object files into the final executable
$(TARGET): $(OBJS)
	@echo "Linking executable: $(TARGET)"
	$(CC) $(CFLAGS) $^ -o $@

# 7. Compile Step: Compiles each individual .c file into a .o file
# It automatically mirrors your directory structure inside the obj/ folder
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# 8. Clean Rule: Deletes the built files so you can start fresh
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR) $(TARGET)

# Declares 'all' and 'clean' as phony targets so Make doesn't confuse them with real files
.PHONY: all clean

rebuild:
	make clean
	make

run: 
	./app