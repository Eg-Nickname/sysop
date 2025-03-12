#==============================================================================
# make all, runa, runb, runc, rund, rune clean, tar, help
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
PROGA = cw2
PROGB = process_info
# Executables objects path
OBJA = $(OBJ_DIR)/$(PROGA).o
OBJB = $(OBJ_DIR)/$(PROGB).o

# Executables path
EXEA = $(EXE_DIR)/$(PROGA).x
EXEB = $(EXE_DIR)/$(PROGB).x
EXES = $(EXEA) $(EXEB)

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

$(EXEA): $(OBJA) $(OBJ_SHARED_LIB)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEB): $(OBJB) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

# Run exectuable for program A
.PHONY: run
run: $(EXEA) $(EXEB)
	$(EXEA) $(EXEB)

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
