#!/bin/bash



# LISTA SOLTANTO I FILE NELLA DIRECTORY PASSATA COME ARGOMENTO
# USA IL COMANDO find PER LISTARE I FILE NELLA DIRECTORY PASSATA COME ARGOMENTO
# NEL SEGUENTE MODO: find <directory> -maxdepth 1 -type f















# Controlla se è stato passato un argomento
if [ -z "$1" ]; then
    echo "Uso: $0 <directory>"
    exit 1
fi

# Verifica se l'argomento è una directory valida
if [ ! -d "$1" ]; then
    echo "Errore: $1 non è una directory valida"
    exit 1
fi

# Lista solo i file (escludendo le directory)
echo "File nella directory $1:"
find "$1" -maxdepth 1 -type f
