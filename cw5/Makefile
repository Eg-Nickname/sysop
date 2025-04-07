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
PROD_CON_MANAGER = prod_con_manager
PRODUCER = producer
CONSUMER = consumer
SHARED_LIB = 
# Executables objects path
PRODUCER_OBJ= $(OBJ_DIR)/$(PRODUCER).o
CONSUMER_OBJ= $(OBJ_DIR)/$(CONSUMER).o
PROD_CON_MANAGER_OBJ= $(OBJ_DIR)/$(PROD_CON_MANAGER).o


# Shared behaviour object file
OBJ_SHARED_LIB =
# Executables path
PRODUCER_EXE = $(EXE_DIR)/$(PRODUCER).x
CONSUMER_EXE = $(EXE_DIR)/$(CONSUMER).x
PROD_CON_MANAGER_EXE = $(EXE_DIR)/$(PROD_CON_MANAGER).x


EXES = $(PRODUCER_EXE) $(CONSUMER_EXE) $(PROD_CON_MANAGER)

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

$(PRODUCER_EXE): $(PRODUCER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(CONSUMER_EXE): $(CONSUMER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^


$(PROD_CON_MANAGER_EXE): $(PROD_CON_MANAGER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^



READ_FILE ?= ./read.txt
WRITE_FILE ?= ./write.txt
PIPE_NAME ?= ./prod_con_pipe
.PHONY: run
run: $(PROD_CON_MANAGER_EXE) $(CONSUMER_EXE) $(PRODUCER_EXE)
	rm $(WRITE_FILE)
	$(PROD_CON_MANAGER_EXE) $(PIPE_NAME) $(PRODUCER_EXE) $(CONSUMER_EXE) $(READ_FILE) $(WRITE_FILE)
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
