#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n1="$(seq 46 50 1001)"
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 
m1="1000" 
n2=
m2=

while getopts 'ha:' opt; do
  case $opt in
    a) iteraciones=$OPTARG ;;
    h) echo ""
       echo "    Experimento 1 - Tiempo de ejecución variando cantidad de nodos"
       echo ""
       echo "    Opciones disponibles:"
       echo "        -h        Imprime este texto de ayuda."
       echo "        -a <núm>  Cantidad de iteraciones - por defecto 1"
       echo ""
       exit 0 ;;
  esac
done

#genero archivos de entrada
for i in $n; do
  echo "Esta creando el archivo numero"
  printf "%d\n " $i
  printf "%d %d %d \n" $i $m1 $n2 $m2 | $(dirname $0)/generador-GrafoAleatorio #parametros del programa generador de archivos de entrada (n, m, pesomin, pesomax) 
done 

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp1.txt

for k in $n; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp1.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio4 < $(dirname $0)/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt -t >> $(dirname $0)/tiempos-exp1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp1.txt
done

#octave -q $(dirname $0)/exp1.m