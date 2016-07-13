#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n1=100
n2=100
m1=200
m2=200
tamTabu="$(seq 5 5 30)"
cuanosMiro=10
k=10
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 

while getopts 'ha:' opt; do
  case $opt in
    a) iteraciones=$OPTARG ;;
    h) echo ""
       echo "    Experimento 5"
       echo ""
       echo "    Opciones disponibles:"
       echo "        -h        Imprime este texto de ayuda."
       echo "        -a <núm>  Cantidad de iteraciones - por defecto 1"
       echo ""
       exit 0 ;;
  esac
done

#genero archivos de entrada 

printf "grafosDeEntrada %d %d %d %d \n" $n1 $m1 $n2 $m2 | $(dirname $0)/../../../generador-grafo-rapido 

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp5.txt

for i in $tamTabu; do
  printf "%d " $i >> $(dirname $0)/tiempos-exp5.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $i
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/grafosDeEntrada/grafo-n1-$n1-m1-$m1-n2-$n2-m2-$m2.txt $cuanosMiro $i $k -t >> $(dirname $0)/tiempos-exp5.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp5.txt
done

#aca voy a tener dos archivos con tiempo. El eje x es "tamTabu" que varia y el eje y el tiempo de ejecucion. Vamos a tener dos curvas, una por cada vecindad.

#octave -q $(dirname $0)/exp1.m