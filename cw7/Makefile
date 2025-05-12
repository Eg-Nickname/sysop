#==============================================================================
# make all, run clean, tar, help
#==============================================================================
PRODUCER_SEM_NAME ?= BlockSemShmSem
M_NAME ?= BlockProdSemShmSem
CONSUMER_SEM_NAME ?= BlockConSemShmSem
SHM_NAME ?= SharedSemShmShm
READ_FILE ?= read.txt
WRITE_FILE ?= wrtie.txt

.SUFFIXES: .c .o .x .h
DIR = $(notdir $(CURDIR))
# Compilation target directory
TARGET_DIR = ./target
# Object directory in target
OBJ_DIR = $(TARGET_DIR)/obj
# Executables directory in target
EXE_DIR = $(TARGET_DIR)/exe
# Libraries directory
LIB_DIR = $(TARGET_DIR)/lib
# Source code directory
SRC_DIR = ./src
# Names for object and exe files for programs
SEM_MEM_CONTROLER = sem_mem_controler
PRODUCER = producer
CONSUMER = consumer
# Libraries
SEM_LIB = semaphore
SHM_LIB = shared_mem
RB_LIB = ring_buf
COMBINED_LIB_NAME = EgCustomLib

# Static library
STAT_LIB = lib$(COMBINED_LIB_NAME).a
# Shared Lib
SHARE_LIB = lib$(COMBINED_LIB_NAME).so

# Executables objects path
SEM_MEM_CONTROLER_OBJ= $(OBJ_DIR)/$(SEM_MEM_CONTROLER).o
PRODUCER_OBJ= $(OBJ_DIR)/$(PRODUCER).o
CONSUMER_OBJ = $(OBJ_DIR)/$(CONSUMER).o

SEM_LIB_OBJ = $(OBJ_DIR)/$(SEM_LIB).o
SHM_LIB_OBJ = $(OBJ_DIR)/$(SHM_LIB).o
RB_LIB_OBJ = $(OBJ_DIR)/$(RB_LIB).o

LIBS_OBJ = $(SEM_LIB_OBJ) $(SHM_LIB_OBJ) $(RB_LIB_OBJ)

# Executables path
SEM_MEM_CONTROLER_STATIC_EXE = $(EXE_DIR)/$(SEM_MEM_CONTROLER)_static.x
PRODUCER_STATIC_EXE = $(EXE_DIR)/$(PRODUCER)_static.x
CONSUMER_STATIC_EXE = $(EXE_DIR)/$(CONSUMER)_static.x

SEM_MEM_CONTROLER_DYNAMIC_EXE = $(EXE_DIR)/$(SEM_MEM_CONTROLER)_dynamic.x
PRODUCER_DYNAMIC_EXE = $(EXE_DIR)/$(PRODUCER)_dynamic.x
CONSUMER_DYNAMIC_EXE = $(EXE_DIR)/$(CONSUMER)_dynamic.x

# Compilator flags
CFLAGS = -Wall -std=c99 -pedantic -fPIC -fvisibility=default
# Linker flags
LFLAGS = -Wall -std=c99 -pedantic -pthread -lrt -fPIC -fvisibility=default
# Flags for ar
ARFLAGS = rsv
# Linker lib
LDLIBS = -lm

# Compiler and linker
CO = gcc
LD = $(CO)
# Static library creaion program
AR = ar

# Compilation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h target_dir
	$(CO) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c target_dir
	$(CO) $(CFLAGS) -c $< -o $@


.PHONY: target_dir
target_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(EXE_DIR)

# Static library creation with ar program
$(STAT_LIB): $(LIBS_OBJ)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(STAT_LIB) $(LIB_DIR)

# Shared library creation
$(SHARE_LIB): $(LIBS_OBJ)
	$(LD) -shared $? -o $@ $(LFLAGS) 
	mkdir -p $(LIB_DIR)
	mv $(SHARE_LIB) $(LIB_DIR)

# Static library executables
$(SEM_MEM_CONTROLER_STATIC_EXE): $(SEM_MEM_CONTROLER_OBJ) $(STAT_LIB)
	rm -f $(LIB_DIR)/$(SHARE_LIB)
	$(LD) -o $@ $(LFLAGS) $(SEM_MEM_CONTROLER_OBJ) -L$(LIB_DIR) -l$(COMBINED_LIB_NAME) $(LDLIBS)


$(CONSUMER_STATIC_EXE): $(CONSUMER_OBJ) $(STAT_LIB)
	rm -f $(LIB_DIR)/$(SHARE_LIB)
	$(LD) -o $@ $(LFLAGS) $(CONSUMER_OBJ) -L$(LIB_DIR) -l$(COMBINED_LIB_NAME) $(LDLIBS)

$(PRODUCER_STATIC_EXE): $(PRODUCER_OBJ) $(STAT_LIB)
	rm -f $(LIB_DIR)/$(SHARE_LIB)
	$(LD) -o $@ $(LFLAGS) $(PRODUCER_OBJ) -L$(LIB_DIR) -l$(COMBINED_LIB_NAME) $(LDLIBS)

# Dynamic library executables
$(SEM_MEM_CONTROLER_DYNAMIC_EXE): $(SEM_MEM_CONTROLER_OBJ) $(SHARE_LIB)
	$(LD) -o $@ $(LFLAGS) $(SEM_MEM_CONTROLER_OBJ) -L$(LIB_DIR) -l$(COMBINED_LIB_NAME) $(LDLIBS) -Wl,-rpath,$(LIB_DIR)

$(CONSUMER_DYNAMIC_EXE): $(CONSUMER_OBJ) $(SHARE_LIB)
	$(LD) -o $@ $(LFLAGS) $(CONSUMER_OBJ) -L$(LIB_DIR) -l$(COMBINED_LIB_NAME) $(LDLIBS) -Wl,-rpath $(LIB_DIR)

$(PRODUCER_DYNAMIC_EXE): $(PRODUCER_OBJ) $(SHARE_LIB)
	$(LD) -o $@ $(LFLAGS) $(PRODUCER_OBJ) -L$(LIB_DIR) -l$(COMBINED_LIB_NAME) $(LDLIBS) -Wl,-rpath $(LIB_DIR)







# Run static library exes
.PHONY: runs
runs: $(SEM_MEM_CONTROLER_STATIC_EXE) $(PRODUCER_STATIC_EXE) $(CONSUMER_STATIC_EXE)
	$(SEM_MEM_CONTROLER_STATIC_EXE) $(SHM_NAME) $(PRODUCER_SEM_NAME) $(CONSUMER_SEM_NAME) $(PRODUCER_STATIC_EXE) $(CONSUMER_STATIC_EXE) $(READ_FILE) $(WRITE_FILE)
	diff -s $(READ_FILE) $(WRITE_FILE)

# Run dynamic library exes
.PHONY: rund
rund: $(SEM_MEM_CONTROLER_DYNAMIC_EXE) $(PRODUCER_DYNAMIC_EXE) $(CONSUMER_DYNAMIC_EXE)
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	echo LD_LIBRARY_PATH; \
	$(SEM_MEM_CONTROLER_DYNAMIC_EXE) $(SHM_NAME) $(PRODUCER_SEM_NAME) $(CONSUMER_SEM_NAME) $(PRODUCER_DYNAMIC_EXE) $(CONSUMER_DYNAMIC_EXE) $(READ_FILE) $(WRITE_FILE)
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
