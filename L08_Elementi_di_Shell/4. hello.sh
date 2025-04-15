#!/bin/bash

# hello.sh
# Questo script saluta l'utente
nome="Mondo"

# Se è stato passato un argomento, lo assegno alla variabile nome
if [ $# -gt 0 ]; then
	nome=$1
	echo $#
fi

# Saluto l'utente
echo "Ciao $nome!"

# Esporto la variabile nome (solo visibile tramite source)
export NOME=$nome
