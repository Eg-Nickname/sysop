#==============================================================================
# make all, runa, runb, runc, clean, tar, help
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
PROGA = cw3a
PROGB = cw3b
PROGC = cw3c
SHARED_LIB = 
# Executables objects path
OBJA = $(OBJ_DIR)/$(PROGA).o
OBJB = $(OBJ_DIR)/$(PROGB).o
OBJC = $(OBJ_DIR)/$(PROGC).o
# Shared behaviour object file
OBJ_SHARED_LIB =
# Executables path
EXEA = $(EXE_DIR)/$(PROGA).x
EXEB = $(EXE_DIR)/$(PROGB).x
EXEC = $(EXE_DIR)/$(PROGC).x
EXES = $(EXEA) $(EXEB) $(EXEC)

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

$(EXEC): $(OBJC) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

# Run exectuable for program A
SIG ?= 2
SIG_HANDLING ?= 2
.PHONY: runa
runa: $(EXEA)
	$(EXEA) $(SIG) $(SIG_HANDLING)
# Run exectuable for program B
.PHONY: runb
runb: $(EXEA) $(EXEB)
	$(EXEB) $(EXEA) $(SIG) $(SIG_HANDLING)
# Run exectuable for program C
.PHONY: runc
runc: $(EXEC)
	$(EXEC)

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
	@echo "   runa"
	@echo "   runb"
	@echo "   runc"
	@echo "   rund"
	@echo "   rune"
	@echo "   clean"
	@echo "   tar"
	@echo "   help"
