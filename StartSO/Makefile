# make clean, tar
DIR = $(notdir $(CURDIR))
.PHONY: clean tar
clean:                                                     
	rm -f *~
	cd Program1; make clean
	cd Program2; make clean
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
