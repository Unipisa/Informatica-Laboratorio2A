#!/bin/bash
while true; do
  echo "Utilizzo CPU:"
  top -bn1 | grep "Cpu(s)"
  sleep 5
done