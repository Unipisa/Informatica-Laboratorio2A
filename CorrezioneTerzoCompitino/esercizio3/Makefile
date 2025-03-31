COMPILATORE = gcc
ATTRIBUTI = -Wall -pedantic
ATTRIBUTI_PRELIMINARI = -g $(CFLAGS)
ATTRIBUTI_DEFINITIVI = -O3 $(CFLAGS)
FILE_OGGETTO = main.o

all: preliminare definitivo

main: $(FILE_OGGETTO)

%.o: %.c
	$(COMPILATORE) -c $(ATTRIBUTI) $< -o $@

preliminare: main
	$(COMPILATORE) $(ATTRIBUTI_PRELIMINARI) main.o -o preliminare

definitivo: main
	$(COMPILATORE) $(ATTRIBUTI_PRELIMINARI) main.o -o definitivo
	zip definitivo.zip definitivo

pulizia:
	rm -f $(FILE_OGGETTO) main preliminare definitivo definitivo.zip

.PHONY: definitivo preliminare pulizia

