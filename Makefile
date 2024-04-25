# Flags
CC := gcc
HIDE := @
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := tests
INCLUDES := -I./$(SRC_DIR)
CFLAGS := -ansi -pedantic -Wall -g

#Files and Directories
TEST_SOURCES := $(wildcard ./$(TEST_DIR)/*.c)
SOURCES := $(filter-out ./$(SRC_DIR)/main.c, $(wildcard ./$(SRC_DIR)/*.c))
OBJECTS := $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.c=.o)))
TESTS := $(notdir $(TEST_SOURCES:.c=))
BIN := assembler

# -----
# Rules
# -----

.PHONY: all clean cleanup tests

all: $(BIN)

tests: $(TESTS)

clean: cleanup


# -----
# Build
# -----

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo $(BIN): Building $@...
	@$(HIDE)$(CC) $(CFLAGS) -c $(INCLUDES) $^ -o $@

$(BIN): ./$(SRC_DIR)/main.c $(OBJECTS)
	@echo $(BIN): Linking...
	@$(HIDE)$(CC) $(INCLUDES) $(CFLAGS) $^ -o $@
	@echo $(BIN): Done.

%: ./$(TEST_DIR)/%.c $(OBJECTS)
	@echo $@: Linking...
	@$(HIDE)$(CC) $(INCLUDES) $(CFLAGS) $^ -o $@
	@echo $@: Done.


# -----
# Clean
# -----

cleanup: $(eval remove_obj := $(shell find ./ -type f -name "*.o"))
cleanup: $(eval remove_am := $(shell find ./ -type f -name "*.am"))
cleanup: $(eval remove_ob := $(shell find ./ -type f -name "*.ob"))
cleanup: $(eval remove_ext := $(shell find ./ -type f -name "*.ext"))
cleanup: $(eval remove_ent := $(shell find ./ -type f -name "*.ent"))
cleanup: $(eval remove_bin := $(shell find ./ -maxdepth 1 -executable -type f -name $(BIN)))
cleanup: $(eval remove_tests := $(shell find ./ -maxdepth 1 -executable -type f -name "*test*"))
ifneq ($(remove_obj),)
	$(info Clean: Cleaning $(remove_obj)...)
	@rm $(remove_obj)
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
ifneq ($(remove_tests),)
	$(info Clean: Cleaning $(remove_tests)...)
	@rm $(remove_tests)
endif
ifneq ($(remove_bin),)
	$(info Clean: Cleaning $(remove_bin)...)
	@rm $(remove_bin)
endif
	$(info Clean: Done.)

