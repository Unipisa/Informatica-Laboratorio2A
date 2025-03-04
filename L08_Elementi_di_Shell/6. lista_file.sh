#!/bin/bash

# Verifica che sia stato passato un argomento
if [ -z "$1" ]; then
  echo "Per favore, fornisci una directory come argomento."
  exit 1
fi

# Controlla se la directory passata esiste
if [ ! -d "$1" ]; then
  echo "La directory '$1' non esiste."
  exit 1
fi

# Per ogni file nella directory passata
for file in "$1"/*; do
  # Controlla se è un file regolare
  if [ -f "$file" ]; then
    nome=$(basename "$file")  # Estrae il nome del file
    dimensione=$(stat -c %s "$file")  # Ottiene la dimensione del file in byte
    echo "Il nome del file è $nome e la sua dimensione è $dimensione byte."
  fi
done

for file in *.sh; do
  echo "Trovato file: $file"
done