#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n1="$(seq 10 20 200)"
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 
#m1="$(seq 0 100 19900)"  #este parametro es el que hay que variar
n2=200 #El grafo2 queda completamente fijo, el n es el mismo en los dos.
#m2=2500 #Guarda que el grafo2 no sea uno especial, tipo estrella o algo asi. 

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

genero archivos de entrada 
for i in $n1; do
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "grafosDeEntrada %d %d %d %d \n" 5 5 $i $n2 | $(dirname $0)/../../../generador-grafosEspeciales
done 

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp1.txt

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp1.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio3 < $(dirname $0)/grafosDeEntrada/grafo-n1-$k-n2-$n2.txt -t >> $(dirname $0)/tiempos-exp1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp1.txt
done

#octave -q $(dirname $0)/exp1.m