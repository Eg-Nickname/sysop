#==============================================================================
#                   Przykladowy plik Makefile
#==============================================================================
# make all, hello.x, clean, tar, help
#==============================================================================
# Objasnienia:
#------------------------------------------------------------------------------
# Jezeli nie chcemy by make wykonal okreslone dzialania, a jedynie wypisal
# na ekranie odpowiednie instrukcje, to wywolujemy go z opcja -n, np.
# make -n all
#------------------------------------------------------------------------------
# Aby byc pewnym, ze wykonywane sa polecenia zdefiniowane w pliku Makefile,
# a nie wbudowane polecenia programu make, uruchamiac make z opcja -r, np.
# make -r run          
#------------------------------------------------------------------------------
# Wszystko co jest po znaku # do konca linii jest traktowane jako komentarz.
#------------------------------------------------------------------------------
# Jezeli uzywamy rozszerzen w nazwach plikow, ktore nie znajduja sie na
# liscie parametrow wewnetrznych make (mozna je sprawdzic wykonujac: make -p),
# to nalezy je umiescic po slowie .SUFFIXES:, np.:
.SUFFIXES: .c .o .x .h
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
# Nazwy, ktorych bedziemy uzywac, tu: rdzenie nazw plikow
# UWAGA: Nie wstawiac spacji po przypisywanej nazwie, bo zostana do niej dodane!
NAME = witaj
# Plik wykonawalny: dodajemy rozszerzenie .x, ale moze byc dowolne, w tym zadne.
EXE  = $(NAME).x  
# Pliki powstale po kompilacji plikow zrodlowych, tzw. object files
OBJ  = $(NAME).o
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
all: $(EXE) 
###############################################################################
# Jawna regula zaleznosci - najpierw uaktualnij pliki po prawej stronie 
# dwukropka, a potem wykonaj komende, ktora jest w nastepnej linijce (tu:
# wykonaj linkowanie). 
# Zmienna wewnetrzna $@ oznacza cel, tzn. obiekt, ktory jest po lewej stronie 
# dwukropka, tu: $(EXEC1);  a zmienna $^ oznacza wszystkie prerekwizyty, tzn.
# obiekty stojace po prawej stronie dwukropka (tutaj wszystkie pliki .o, ktore
# powinny byc zlinkowane). 
$(EXE): $(OBJ) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $^
###############################################################################
# Aby zapewnic bezwzgledne wykonanie niezaleznie czy istnieja pliki o danych
# nazwach (podobie jak dla all). Jezeli jestesmy pewni, ze plikow o takich
# nazwach nie bedzie w danym katalogu, to mozemy pominac ponizsza deklaracje.
.PHONY: run
###############################################################################
# Uruchom program $(EXEC); najpierw sprawdz, czy plik wykonawalny jest aktualny
run: $(EXE)
	./$(EXE)
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
	@echo "Oto cele dla make zdefiniowane w tym Makefile:"
	@echo "   all"
	@echo "   $(OBJ)"
	@echo "   $(EXE)"
	@echo "   run"
	@echo "   clean"
	@echo "   tar"
	@echo "   help"
