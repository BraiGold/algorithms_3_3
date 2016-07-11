#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n1=30000
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 
m1="$(seq 448 5000 100001)"  #este parametro es el que hay que variar
n2=300000 #El grafo2 queda completamente fijo, el n es el mismo en los dos.
m2=300000 #Guarda que el grafo2 no sea uno especial, tipo estrella o algo asi. 
maxTamTabu=40000
cantVec=40000
k=400000

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
  printf "%d %d %d \n" $n1 $i $n2 $m2 | $(dirname $0)/generador-GrafoAleatorio 
done 

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp1-tipo1.txt

for k in $m1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp1-tipo1.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/grafo-n1-$n1-m1-$k-n2-$n2-m2-$m2.txt $maxTamTabu $cantVec $k -t >> $(dirname $0)/tiempos-exp1-tipo1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp1-tipo1.txt
done

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp1-tipo2.txt

for k in $m1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp1-tipo2.txt
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo2 < $(dirname $0)/grafo-n1-$n1-m1-$k-n2-$n2-m2-$m2.txt $maxTamTabu $cantVec $k -t >> $(dirname $0)/tiempos-exp1-tipo2.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp1-tipo2.txt
done

#hay dos archivos de tiempos, uno con los tiempos de "ejercicio6-tipo1" y otro con los tiempos de "ejercicio6-tipo1". Los graficos contienen en el eje x a m1 (que va variando) y en el eje y el tiempo de ejecucion correspondiente a cada m. Va a tener dos curvas, una para vecindad 1 y otra para vecindad 2. Además hay que graficar la complejidad. 

#octave -q $(dirname $0)/exp1.m