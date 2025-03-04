#!/bin/bash

numero=0  # Inizializza la variabile

# Continua a chiedere un numero finché non è maggiore di 10
while [ "$numero" -le 10 ]; do
  read -p "Inserisci un numero maggiore di 10: " numero
done

echo "Hai inserito $numero, che è maggiore di 10."

# Chiede all'utente di inserire un numero
read -p "Inserisci un numero: " numero

if [ "$numero" -gt 10 ]; then
  echo "Il numero è maggiore di 10."
else
  echo "Il numero è 10 o inferiore."
fi