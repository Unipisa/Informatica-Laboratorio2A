#!/bin/bash

FILE="file.txt"
PAROLA="errore"

# Verifica che il file esista
if [ ! -f "$FILE" ]; then
  echo "Il file $FILE non esiste."
  exit 1
fi

echo "Monitoraggio di $FILE per la parola '$PAROLA'. Premere Ctrl+C per uscire."

# Loop infinito
while true; do
    sleep 2  # Aspetta 2 secondi

    # Cerca la parola nel file
    if grep -q "$PAROLA" "$FILE"; then
        echo "La parola '$PAROLA' è stata trovata in $FILE!"
    fi
done
