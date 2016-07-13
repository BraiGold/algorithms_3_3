#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n1=8
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 
m1="$(seq 0 2 28)"  #este parametro es el que hay que variar
n2=8 #El grafo2 queda completamente fijo, el n es el mismo en los dos.
m2=17 #Guarda que el grafo2 no sea uno especial, tipo estrella o algo asi. 

while getopts 'ha:' opt; do
  case $opt in
    a) iteraciones=$OPTARG ;;
    h) echo ""
       echo "    Experimento 1"
       echo ""
       echo "    Opciones disponibles:"
       echo "        -h        Imprime este texto de ayuda."
       echo "        -a <núm>  Cantidad de iteraciones - por defecto 1"
       echo ""
       exit 0 ;;
  esac
done


printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp1.txt

for k in $m1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp1.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio2-sinPoda < $(dirname $0)/grafosDeEntrada/grafo-n1-$n1-m1-$k-n2-$n2-m2-$m2.txt -t >> $(dirname $0)/tiempos-exp1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp1.txt
done

#octave -q $(dirname $0)/exp1.m