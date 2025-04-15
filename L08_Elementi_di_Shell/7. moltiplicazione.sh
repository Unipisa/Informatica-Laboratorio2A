#!/bin/bash
read -p "Inserisci un numero: " num

for i in {1..10}; do
  echo "$num MOLTIPLICATO $i = $((num * i * 2))"
done