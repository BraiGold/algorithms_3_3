#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n1=200
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 
m1="$(seq 0 30 210)"  #este parametro es el que hay que variar
n2=100 #El grafo2 queda completamente fijo, el n es el mismo en los dos.
m2=1000 #Guarda que el grafo2 no sea uno especial, tipo estrella o algo asi. 

tamTabu=10
cuantosMiro=10
z=10

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

#genero archivos de entrada 
for i in $m1; do
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "grafosDeEntrada %d %d %d %d \n" $n1 $i $n2 $m2 | $(dirname $0)/../../../generador-grafo-rapido
done 
#ej4
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-ej4-exp1.txt

for k in $m1; do
  printf "%d " $k >> $(dirname $0)/tiempos-ej4-exp1.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio4 < $(dirname $0)/grafosDeEntrada/grafo-n1-$n1-m1-$k-n2-$n2-m2-$m2.txt -t >> $(dirname $0)/tiempos-ej4-exp1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-ej4-exp1.txt
done
#ej5
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-ej5-exp1.txt

for k in $m1; do
  printf "%d " $k >> $(dirname $0)/tiempos-ej5-exp1.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio5-tipo1 < $(dirname $0)/grafosDeEntrada/grafo-n1-$n1-m1-$k-n2-$n2-m2-$m2.txt $cuantosMiro -t >> $(dirname $0)/tiempos-ej5-exp1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-ej5-exp1.txt
done
#ej6
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-ej6-exp1.txt

for k in $m1; do
  printf "%d " $k >> $(dirname $0)/tiempos-ej6-exp1.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/grafosDeEntrada/grafo-n1-$n1-m1-$k-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $z -t >> $(dirname $0)/tiempos-ej6-exp1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-ej6-exp1.txt
done

#octave -q $(dirname $0)/exp1.m