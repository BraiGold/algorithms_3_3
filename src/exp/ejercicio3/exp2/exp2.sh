#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n="$(seq 100 50 1200)"
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 

while getopts 'ha:' opt; do
  case $opt in
    a) iteraciones=$OPTARG ;;
    h) echo ""
       echo "    Experimento 2"
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
  n2=$i
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "grafosDeEntrada %d %d %d %d \n" 5 5 $i $i | $(dirname $0)/../../../generador-grafosEspeciales 
done

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2.txt

for k in $n; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2.txt
  n2=$i
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio3 < $(dirname $0)/grafosDeEntrada/grafo-n1-$k-n2-$k.txt -t >> $(dirname $0)/tiempos-exp2.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2.txt
done

#octave -q $(dirname $0)/exp1.m