#==============================================================================
# make all, run clean, tar, help
#==============================================================================
SEM_NAME ?= BlockSem

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
SEM_MEM_CONTROLER = sem_mem_controler
PRODUCER = producer
CONSUMER = consumer
# SHARED_LIB = semaphore
# Executables objects path
SEM_MEM_CONTROLER_OBJ= $(OBJ_DIR)/$(SEM_MEM_CONTOLER).o
PRODUCER_OBJ= $(OBJ_DIR)/$(PRODUCER).o
CONSUMER_OBJ = $(OBJ_DIR)/$(CONSUMER).o

# Shared behaviour object file
OBJ_SHARED_LIB = 

# Executables path
SEM_MEM_CONTROLER_EXE = $(EXE_DIR)/$(SEM_MEM_CONTOLER).x
PRODUCER_EXE = $(EXE_DIR)/$(PRODUCER).x
CONSUMER_EXE = $(EXE_DIR)/$(CONSUMER).x

EXES = $(SEM_MEM_CONTOLER) $(PRODUCER_EXE) $(CONSUMER_EXE)

# Compilator flags
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
# Linker flags
LFLAGS = -Wall -std=c99 -pedantic -pthread -O
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

$(SEM_MEM_CONTROLER_EXE): $(SEM_CONTROLER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(PRODUCER_EXE): $(PRODUCER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(CONSUMER_EXE): $(CONSUMER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run
run: $(SEM_MEM__CONTROLER_EXE) $(PRODUCER_EXE) $(CONSUMER_EXE)
	$(SEM_MEM_CONTROLER_EXE)

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
