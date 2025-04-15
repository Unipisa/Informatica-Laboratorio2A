#!/bin/bash

# Dichiarazione di una funzione
function saluta {
  echo "Ciao, $1!"
  echo "Luca: $0!"
}

# utilizzo della funzione
saluta "Mario"

echo "$1"
echo "$2"