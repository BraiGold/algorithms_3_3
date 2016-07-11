#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n="$(seq 448 5000 100001)"
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 

while getopts 'ha:' opt; do
  case $opt in
    a) iteraciones=$OPTARG ;;
    h) echo ""
       echo "    Experimento 3"
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
  m = 3*$i
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "%d %d %d \n" $i $m $i $m | $(dirname $0)/generador-GrafoAleatorio 
done

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp3.txt

for k in $n; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp3.txt
  m = 3*$k
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio4 < $(dirname $0)/grafo-n1-$k-m1-$m-n2-$k-m2-$m.txt -t >> $(dirname $0)/tiempos-exp3.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp3.txt
done



#octave -q $(dirname $0)/exp1.m