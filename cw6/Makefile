#==============================================================================
# make all, run clean, tar, help
#==============================================================================
SEM_NAME ?= BlockSem
CHILD_PROC_COUNT ?= 4
CRIT_SECTION_COUNT ?= 
COUNTER_FILE ?= num.txt

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
SEM_CONTROLER = sem_controler
SEM_USER = sem_user
SHARED_LIB = semaphore
# Executables objects path
SEM_CONTROLER_OBJ= $(OBJ_DIR)/$(SEM_CONTROLER).o
SEM_USER_OBJ= $(OBJ_DIR)/$(SEM_USER).o

# Shared behaviour object file
OBJ_SHARED_LIB = $(OBJ_DIR)/$(SHARED_LIB).o

# Executables path
SEM_USER_EXE = $(EXE_DIR)/$(SEM_USER).x
SEM_CONTROLER_EXE = $(EXE_DIR)/$(SEM_CONTROLER).x


EXES = $(SEM_CONTROLER) $(SEM_USER_EXE)

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

$(SEM_USER_EXE): $(SEM_USER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(SEM_CONTROLER_EXE): $(SEM_CONTROLER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run
run: $(SEM_CONTROLER_EXE) $(SEM_USER_EXE)
	$(SEM_CONTROLER_EXE) $(COUNTER_FILE) $(SEM_NAME) $(SEM_USER_EXE) $(CHILD_PROC_COUNT) $(CRIT_SECTION_COUNT)

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
