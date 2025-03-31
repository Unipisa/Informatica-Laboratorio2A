#!/bin/bash

#  VEDIAMO SE UN FILE HA SUBITO MODIFICHE.
#  UTILIZZEREMO DIFF PER CONFRONTARE IL FILE ATTUALE 
#  CON UN FILE DI BACKUP.

# FILE DI BACKUP, SE NON ESISTE LO CREIAMO














# Controlla se è stato passato il file da monitorare
if [ -z "$1" ]; then
    echo "Uso: $0 <file_da_monitorare>"
    exit 1
fi

FILE="$1"
BACKUP="${FILE}.bak"

# Se il file di backup non esiste, crealo
if [ ! -f "$BACKUP" ]; then
    cp "$FILE" "$BACKUP"
    echo "Backup iniziale creato per $FILE"
    exit 0
fi

# Confronta il file attuale con il backup
diff "$BACKUP" "$FILE" > /dev/null
if [ $? -eq 0 ]; then
    echo "Nessuna modifica rilevata in $FILE"
else
    echo "Modifiche rilevate in $FILE:"
    diff -u "$BACKUP" "$FILE"
    cp "$FILE" "$BACKUP"  # Aggiorna il backup
fi
