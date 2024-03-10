# Flags
CC = gcc
CFLAGS = -ansi -pedantic -Wall -std=c99 -g 
INCLUDES = -I./$(SRC_DIR)
HIDE = @
SRC_DIR = src

#Files and Directories
SOURCES = $(wildcard ./$(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)
BIN = assembler

# -----
# Rules
# -----

.PHONY: all clean cleanup

all: $(BIN)

clean: cleanup

# -----
# Build
# -----

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo $(BIN): Building $@...
	@$(HIDE)$(CC) $(CFLAGS) -c $(INCLUDES) $^ -o $@

$(BIN): $(OBJECTS)
	@echo $(BIN): Linking...
	@$(HIDE)$(CC) $(CFLAGS) $(OBJECTS) -o $(BIN)
	@echo $(BIN): Done.


# -----
# Clean
# -----

cleanup: $(eval remove_obj := $(shell find ./ -type f -name "*.o"))
cleanup: $(eval remove_bin := $(shell find ./ -maxdepth 1 -executable -type f -name $(BIN)))
cleanup: $(eval remove_am := $(shell find ./ -type f -name "*.am"))
cleanup: $(eval remove_ob := $(shell find ./ -type f -name "*.ob"))
cleanup: $(eval remove_ext := $(shell find ./ -type f -name "*.ext"))
cleanup: $(eval remove_ent := $(shell find ./ -type f -name "*.ent"))
ifneq ($(remove_obj),)
	$(info Clean: Cleaning $(remove_obj)...)
	@rm $(remove_obj)
endif
ifneq ($(remove_bin),)
	$(info Clean: Cleaning $(remove_bin)...)
	@rm $(remove_bin)
endif
ifneq ($(remove_am),)
	$(info Clean: Cleaning $(remove_am)...)
	@rm $(remove_am)
endif
ifneq ($(remove_ob),)
	$(info Clean: Cleaning $(remove_ob)...)
	@rm $(remove_ob)
endif
ifneq ($(remove_ext),)
	$(info Clean: Cleaning $(remove_ext)...)
	@rm $(remove_ext)
endif
ifneq ($(remove_ent),)
	$(info Clean: Cleaning $(remove_ent)...)
	@rm $(remove_ent)
endif
	$(info Clean: Done.)

