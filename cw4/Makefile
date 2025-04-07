#==============================================================================
# make all, run clean, tar, help
#==============================================================================

.SUFFIXES: .c .o .x .h
DIR = $(notdir $(CURDIR))
# Compilation target directory
TARGET_DIR = ./target
# Object directory in target
OBJ_DIR = $(TARGET_DIR)/obj
# Executables directory in target
EXE_DIR = $(TARGET_DIR)/exe
# Source code directory
SRC_DIR = ./src
# Names for object and exe files for programs
PRODUCER_CONSUMER = producer_consumer
SHARED_LIB = 
# Executables objects path
PRODUCER_CONSUMER_OBJ= $(OBJ_DIR)/$(PRODUCER_CONSUMER).o
# Shared behaviour object file
OBJ_SHARED_LIB =
# Executables path
PRODUCER_CONSUMER_EXE = $(EXE_DIR)/$(PRODUCER_CONSUMER).x

EXES = $(PRODUCER_CONSUMER_EXE)

# Compilator flags
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
# Linker flags
LFLAGS = -Wall -std=c99 -pedantic -O
# Compiler and linker
CO = gcc
LD = $(CO)

# Compilation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h target_dir
	$(CO) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c target_dir
	$(CO) $(CFLAGS) -c $< -o $@


.PHONY: target_dir
target_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(EXE_DIR)

.PHONY: all
all: target_dir $(EXES)

$(PRODUCER_CONSUMER_EXE): $(PRODUCER_CONSUMER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^


# Run exectuables for PRODUCER_CONSUMER consumer problem
READ_FILE ?= ./read.txt
WRITE_FILE ?= ./write.txt
.PHONY: runa
run: $(PRODUCER_CONSUMER_EXE)
	rm $(WRITE_FILE)
	$(PRODUCER_CONSUMER_EXE) $(READ_FILE) $(WRITE_FILE)
	diff -s $(READ_FILE) $(WRITE_FILE)
.PHONY: clean tar
# File cleanup before archiving and compressing
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}; rm -rf $(TARGET_DIR)
# Archivization and compresssion
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

.PHONY: help
help:
	@echo "Oto cele dla make zdefiniowane w tym Makefile:"
	@echo "   all"
	@echo "   run"
	@echo "   clean"
	@echo "   tar"
	@echo "   help"
