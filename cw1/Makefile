#==============================================================================
# make all, clean, tar, help
#==============================================================================

.SUFFIXES: .c .o .x .h
DIR = $(notdir $(CURDIR))
TARGET_DIR = ./target
OBJ_DIR = $(TARGET_DIR)/obj
EXE_DIR = $(TARGET_DIR)/exe
SRC_DIR = ./src
# Nazwy, ktorych bedziemy uzywac, tu: rdzenie nazw plikow
PROGA = cw1a
PROGB = cw1b
PROGC = cw1c
PROGD = cw1d
PROGE = cw1e

# Plik wykonawalny: dodajemy rozszerzenie .x, ale moze byc dowolne, w tym zadne.
EXEA = $(TARGET_DIR)/exe/$(PROGA).x
EXEB = $(TARGET_DIR)/exe/$(PROGB).x
EXEC = $(TARGET_DIR)/exe/$(PROGC).x
EXED = $(TARGET_DIR)/exe/$(PROGD).x
EXEE = $(TARGET_DIR)/exe/$(PROGE).x
EXES = $(EXEA) $(EXEB) $(EXEC) $(EXED) $(EXEE)
# Pliki powstale po kompilacji plikow zrodlowych, tzw. object files
OBJA = $(TARGET_DIR)/obj/$(PROGA).o
OBJB = $(TARGET_DIR)/obj/$(PROGB).o
OBJC = $(TARGET_DIR)/obj/$(PROGC).o
OBJD = $(TARGET_DIR)/obj/$(PROGD).o
OBJE = $(TARGET_DIR)/obj/$(PROGE).o
OBJS = $(OBJA) $(OBJB) $(OBJC) $(OBJD) $(OBJE)
# Dolaczane biblioteki (poza standardowymi). 
# Makra moga byc puste, np. przewidziane na przyszlosc.
LIB  = 
# Pliki naglowkowe (tu: nie ma zadnych)
HEAD = 
#------------------------------------------------------------------------------
# Opcje kompilatora i linkera; -fPIC potrzebna dla bibliotek dzielonych
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O
# Kompilator i linker (czesto ta sama nazwa)
CO = gcc
LD = $(CO)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h target_dir
	$(CO) $(CFLAGS) -c $<
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c target_dir
	$(CO) $(CFLAGS) -c $< -o $@


.PHONY: target_dir
target_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(EXE_DIR)

.PHONY: all
all: target_dir $(EXES)

$(EXEA): $(OBJA) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEB): $(OBJB) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC): $(OBJC) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXED): $(OBJD) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEE): $(OBJE) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: runa
runa: $(EXEA)
	$(EXEA)

.PHONY: runb
runb: $(EXEB)
	$(EXEB)

.PHONY: runc
runc: $(EXEC)
	$(EXEC)

.PHONY: rund
rund: $(EXED)
	$(EXED)

.PHONY: rune
rune: $(EXEE)
	$(EXEE)

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}; rm -rf $(TARGET_DIR)
# Archiwizacja i kompresja
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
