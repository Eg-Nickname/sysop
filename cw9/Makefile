#==============================================================================
# make all, run, clean, tar, help
#==============================================================================
THREAD_COUNT ?= 6
CRIT_SECTION_COUNT ?= 8

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
SMUTEKES = mutal_exclusion
SHARED_LIB = 
# Executables objects path
SMUTEKES_OBJ= $(OBJ_DIR)/$(SMUTEKES).o

# Shared behaviour object file
OBJ_SHARED_LIB = $(OBJ_DIR)/$(SHARED_LIB).o

# Executables path
SMUTEKES_EXE = $(EXE_DIR)/$(SMUTEKES).x


EXES = $(SMUTEKES_EXE)

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

$(SMUTEKES_EXE): $(SMUTEKES_OBJ)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run
run: $(SMUTEKES_EXE)
	$(SMUTEKES_EXE) $(THREAD_COUNT) $(CRIT_SECTION_COUNT)

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
