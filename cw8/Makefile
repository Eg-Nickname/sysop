#==============================================================================
# make all, runs, runc, clean, tar, help
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
SERVER = server
CLIENT = client
SHARED_LIB = mqueue
# Executables objects path
SERVER_OBJ= $(OBJ_DIR)/$(SERVER).o
CLIENT_OBJ= $(OBJ_DIR)/$(CLIENT).o

# Shared behaviour object file
OBJ_SHARED_LIB = $(OBJ_DIR)/$(SHARED_LIB).o

# Executables path
CLIENT_EXE = $(EXE_DIR)/$(CLIENT).x
SERVER_EXE = $(EXE_DIR)/$(SERVER).x


EXES = $(SERVER_EXE) $(CLIENT_EXE)

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

$(CLIENT_EXE): $(CLIENT_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(SERVER_EXE): $(SERVER_OBJ) $(OBJ_SHARED_LIB) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: runs
runs: $(SERVER_EXE)
	$(SERVER_EXE)


.PHONY: runc
runc: $(CLIENT_EXE)
	$(CLIENT_EXE)

.PHONY: runall
runall: $(SERVER_EXE) $(CLIENT_EXE)
	xterm -hold -title SERWER -bg red -fg black -e $(SERVER_EXE) &
	xterm -hold -title KLIENT1 -bg green -fg black -e $(CLIENT_EXE) &
	xterm -hold -title KLIENT2 -bg green -fg black -e $(CLIENT_EXE) &


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
	@echo "   runs"
	@echo "   rund"
	@echo "	  runall"
	@echo "   clean"
	@echo "   tar"
	@echo "   help"
