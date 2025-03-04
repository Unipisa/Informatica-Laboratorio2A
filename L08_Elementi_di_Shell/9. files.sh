#!/bin/bash

while read -r linea; do
  echo "Riga: $linea"
done < $1