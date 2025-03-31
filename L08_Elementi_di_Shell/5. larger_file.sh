#!/bin/bash
read -p "Inserisci la directory: " dir

if [ -d "$dir" ]; then
  max_file=$(ls -S "$dir" | head -n 1)
  echo "Il file più grande è: $max_file"
else
  echo "Directory non trovata."
fi