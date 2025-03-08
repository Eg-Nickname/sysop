#==============================================================================
#                   Przykladowy plik Makefile
#==============================================================================
# make all, runs, rund1, rund2, clean, tar
#==============================================================================
# Objasnienia:
#------------------------------------------------------------------------------
# Jezeli nie chcemy by make wykonal okreslone dzialania, a jedynie wypisal
# na ekranie odpowiednie instrukcje, to wywolujemy go z opcja -n, np.
# make -n all
#------------------------------------------------------------------------------
# Aby byc pewnym, ze wykonywane sa polecenia zdefiniowane w pliku Makefile,
# a nie wbudowane polecenia programu make, uruchamiac make z opcja -r, np.
# make -r runs          
#------------------------------------------------------------------------------
# Wszystko co jest po znaku # do konca linii jest traktowane jako komentarz.
#------------------------------------------------------------------------------
# Jezeli uzywamy rozszerzen w nazwach plikow, ktore nie znajduja sie na
# liscie parametrow wewnetrznych make (mozna je sprawdzic wykonujac: make -p),
# to nalezy je umiescic po slowie .SUFFIXES:, np.:
.SUFFIXES: .c .cpp .o .x .h
#------------------------------------------------------------------------------
# Ponizej przyklady definiowania zmiennych (nie musza byc oznaczane wielkimi
# literami, ale moze byc to wygodne, np.latwiej je odroznic od reszty).
# Do zmiennej ZMIENNA sie przez $(ZMIENNA)
#------------------------------------------------------------------------------
# Nazwa katalogu (moze sie przydac); wstawiamy wynik funkcji wbudowanej notdir, 
# ktora z nazwy sciezkowej wybiera wlasciwa nazwe katalogu lub pliku
# (po ostatnim /), natomiast funkcja wbudowana dir wybiera sciezke do danego
# pliku czy katalogu (przed ostatnim /).
DIR = $(notdir $(CURDIR))
# Nazwa systemu operacyjnego (jadra) - moze byc przydatna dla opcji/komend
# zaleznych od systemu. Wbudowana funkcja shell wykonuje w powloce wystepujace
# po niej polecenie, tu: uname -s (zwraca nazwe jadra systemu operacyjnego).
SYSNAME = $(shell uname -s)
# Nazwy, ktorych bedziemy uzywac, tu: rdzenie nazw plikow
# UWAGA: Nie wstawiac spacji po przypisywanej nazwie, bo zostana do niej dodane!
NAME1 = mcint
NAME2 = funkcja
# Argument wywolania programu, ?= oznacza, ze domyslnie zostanie uzyta
# przypisana wartosc, ale mozna ja zmienic w wywolaniu make'a, np.
# make NGEN=1e6 runs
NGEN ?= 1e7
# Pliki wykonawalne: dodajemy rozszerzenie .x, ale moze byc dowolne, w tym zadne.
# Tworzymy 3 pliki wykonywalne - po jednym dla kazdej wersji biblioteki.
EXES  = $(NAME1)s.x
EXED1  = $(NAME1)d1.x
EXED2  = $(NAME1)d2.x
OBJ1  = $(NAME1).o 
OBJ2  = $(NAME2).o
# Dla drugiego programu utworzymy biblioteke statyczna oraz dzielona
LIB_NAME = MojeFunkcje
# Katalog dla bibliotek
LIB_DIR = ./lib
# Biblioteka statyczna (static library)
LIB_STAT = lib$(LIB_NAME).a
# Biblioteka dzielona linkowana dynamicznie - nazwa zalezy od systemu:
# Linux - rozszerzenie: .so
# macOS - rozszerzenie: .dylib
# Dyrektywa warunkowa sprawdzajaca, czy system nazywa sie Linux
# i wykonujaca okreslone polecenie.
ifeq ($(SYSNAME), Linux)
  LIB_SHAR = lib$(LIB_NAME).so
endif
# macOS - nazwa jadra to Darwin
ifeq ($(SYSNAME), Darwin)
  LIB_SHAR = lib$(LIB_NAME).dylib
endif
# Pliki skompilowane wchodzace do biblioteki
LIB_OBJS = $(OBJ2)
# Pliki naglowkowe
HEAD = 
HEAD2 = $(NAME2).h
#------------------------------------------------------------------------------
# Opcje kompilatora i linkera; -fPIC potrzebna dla bibliotek dzielonych
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O
# Biblioteki linkera zainstalowane w systemie 
# (tu: biblioteka matematyczna libm)
LDLIBS = -lm
# Kompilator i linker (czesto ta sama nazwa)
CO = gcc
LD = $(CO)
# Program-archiwizer do tworzenia bibliotek statycznych
AR = ar
# Opcje archiwizera: tworzenie/uaktualnianie biblioteki wraz z indeksem plikow
#                    i wypisywanie komunikatow 
ARFLAGS = rsv
###############################################################################
# Ponizej przyklady definiowania regul zaleznosci
###############################################################################
# Tzw. regula wzorcowa - mowiaca jak pliki z rozszerzeniem .o otrzymac 
# z plikow o rozszerzeniach .c i .h. 
# To co jest po lewej stronie dwukropka nazywa sie "cel", a to co jest po
# prawej - "prerekwizyty" (tzn. to od czego zalezy "cel"). 
# Najpierw make sprawdza czy plik celowy (tu: odpowiedni plik z rozszerzeniem 
# .o) jest aktualny (tzn. nowszy od odpowiednich plikow .c i .h) - jezeli nie, 
# to wykonuje komende ponizej (tutaj: kompilacja). 
# Znak % oznacza wzorzec, tzn. dowolny ciag znakow, ktore tworza rdzen nazwy 
# pliku. 
# Zmienna wewnetrzna $< oznacza pierwszy prerekwizyt, tu: nazwe odpowiedniego 
# pliku z rozszerzeniem .c, ktory nalezy uaktualnic aby otrzymac plik .o. 
# Uwaga: Komenda zaczyna sie od znaku tabulacji (niewidocznego).
%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
# Jak wyzej, ale bez zaleznosci od plikow naglowkowych
%.o: %.c
	$(CO) $(CFLAGS) -c $<
###############################################################################
# Regula zaleznosci - uaktualnij pliki po prawej stronie dwukropka.
# Na ogol zakladamy, ze w danym katalogu nie ma pliku o nazwie all,
# tzn. ze dana regula zawsze sie wykona. 
# Gdyby plik o takiej nazwie przypadkowo znalazl sie w danym katalogu,
# to mozna wymusic bezwzgledne wykonanie sie ponizszej reguly wpisujac
# nazwe celu po slowie .PHONY:, np.
.PHONY: all
all: $(EXES) $(EXED1) $(EXED2) 
#==============================================================================
# Tworzenie biblioteki statycznej przy pomocy programu archiwizacyjnego ar.
# Zmienna automatyczne $? oznacza wszystkie prerekwizyty, ktore sa nowsze niz cel
# (dzieki temu tylko zmodyfikowane pliki beda wstawiane do biblioteki-archiwum).
# Nastepnie tworzony jest katalog dla biblioteki (jezeli nie istnieje)
# i do niego przenoszona jest stworzona biblioteka.
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)
###############################################################################
# Tworzenie biblioteki dzielonej (shared library)
$(LIB_SHAR): $(LIB_OBJS)
# Linux - opcja linkera: -shared
ifeq ($(SYSNAME), Linux)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
endif
# macOS - opcje linkera: -dynamiclib,  -install_name @rpath/$(LIB_DIR)/$@
ifeq ($(SYSNAME), Darwin)
	$(LD) -dynamiclib -o $@ $(LFLAGS) $(LIB_OBJS) -install_name @rpath/$(LIB_DIR)/$@
endif
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)
###############################################################################
# Regula zaleznosci dla pliku wykonywalnego z biblioteka statyczna:
# -> po -L podajemy sciezke do biblioteki, a po -l jej nazwe bez poczatkowego 
#    lib i koncowego .a 
$(EXES): $(OBJ1) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJ1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
###############################################################################
#  Plik wykonywalny z biblioteka dzielona - wersja 1
#  -> informacja o lokalizacji bibliteki przekazywana jest przez opcje linkera:
#     -Wl,-R $(LIB_DIR)  (zamiast -R mozna uzyc -rpath) dla Linuksa.       
$(EXED1): $(OBJ1) $(LIB_SHAR)
ifeq ($(SYSNAME), Linux)
	$(LD) -o $@ $(LFLAGS) $(OBJ1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
endif
# macOS: opcje -Xlinker -rpath -Xlinker $(CURDIR)
ifeq ($(SYSNAME), Darwin)
	$(LD) -o $@ $(LFLAGS) $(OBJ1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Xlinker -rpath -Xlinker $(CURDIR)
endif
#-------------------------------------------------------------------------------------------------
#  Plik wykonywalny z biblioteka dzielona - wersja 2
#  -> informacja o lokalizacji biblioteki nie jest przekazywana przez opcje 
#     linkera, lecz na etapie wykonania przez zmienna srodowiskowa:
#     LD_LIBRARY_PATH (patrz ponizej na przyklad uruchomienia programu).
$(EXED2): $(OBJ1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJ1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
###############################################################################
# Dodatkowe reguly zaleznosci plikow objectowych od naglowkowych, ktorych
# nie uwglednia regula wzorcowa (powyzej).
###############################################################################
$(OBJS1): $(HEADS2)
###############################################################################
.PHONY: runs rund1 rund2
###############################################################################
# Uruchom program z jednym argumentem, ale najpierw sprawdz czy plik wykonywalny
# jest aktualny. 
# 1) z biblioteka statyczna
runs: $(EXES)
	./$(EXES) $(NGEN)
# 2.1) z biblioteka dzielona - wersja 1
rund1: $(EXED1)
	./$(EXED1) $(NGEN)
# 2.2) z biblioteka dzielona - wersja 2 (znak \ oznacza kontynuacje w nastepnej
#      linii) -> do zmiennej srodowiskowej LD_LIBRARY_PATH trzeba dodac sciezke
#      do katalogu z nowa biblioteka dzielona i uruchomic program w tej samej
#      powloce (dlatego znak kontynuacji \, bo bez tego make wykonujac komende
#      w danej linii tworzy nowa powloke, a nastepnie ja zamyka itd.).
#      Robiac to samo bezposrednio z powloki (tzn. bez make) wystarczy raz
#      wykonac pierwsza linijke (bez znakow ; i \), a potem mozna wielokrotnie
#      wykonywac program w tej powloce.     
rund2: $(EXED2)
# Linux
ifeq ($(SYSNAME), Linux)
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXED2) $(NGEN)
endif
# macOS - tu odpowiednia zmienna srodowiskowa to: DYLD_LIBRARY_PATH
ifeq ($(SYSNAME), Darwin)
	export DYLD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXED2) $(NGEN)
endif
###############################################################################
# Sprzataczka (tez "phony target")
###############################################################################
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
###############################################################################
# Wskazowka wywolania make dla tego Makefile.
# Polecenie echo wypisuje nastepujacy po nim tekst.
# Znak @ powoduje, ze sama nazwa polecenia nie jest wypisywana.
###############################################################################
.PHONY: help
help:
	@echo "Oto najwazniejsze cele dla make zdefiniowane w tym Makefile:"
	@echo "   all"
	@echo "   $(EXES)"
	@echo "   $(EXED1)"
	@echo "   $(EXED2)"
	@echo "   runs"
	@echo "   rund1"
	@echo "   rund2"
	@echo "   clean"
	@echo "   tar"
	@echo "   help"
