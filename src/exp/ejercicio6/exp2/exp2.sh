#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n1="$(seq 100 20 600)"
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 
n2=600 #El grafo2 queda completamente fijo, el n es el mismo en los dos.
m2=2500 #Guarda que el grafo2 no sea uno especial, tipo estrella o algo asi. 
tamTabu=n1
cuantosMiro=n1
k=n1

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
for i in $n1; do
  aux=$((i-1))
  aux2=$((i*aux))
  m1=$((aux2/2))
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "f1 %d %d %d %d \n" $i $m1 $n2 $m2 | $(dirname $0)/../../../generador-grafo-rapido 
done

for i in $n1; do
  m1=$((i-1))
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "f2 %d %d %d %d \n" $i $m1 $n2 $m2 | $(dirname $0)/../../../generador-grafo-rapido 
done

for i in $n1; do
  m1=$((3*i))
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "f3 %d %d %d %d \n" $i $m1 $n2 $m2 | $(dirname $0)/../../../generador-grafo-rapido 
done

for i in $n1; do
  aux=$((i^2))
  m1=$((aux/10))
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "f4 %d %d %d %d \n" $i $m1 $n2 $m2 | $(dirname $0)/../../../generador-grafo-rapido
done


#==============================tipo1========================================================

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2-f1-tipo1.txt
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2-f2-tipo1.txt
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2-f3-tipo1.txt
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2-f4-tipo1.txt

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2-f1-tipo1.txt
  aux=$((k-1))
  aux2=$((k*aux))
  m1=$((aux2/2))
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/f1/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $k -t >> $(dirname $0)/tiempos-exp2-f1-tipo1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2-f1-tipo1.txt
done

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2-f2-tipo1.txt
  m1=$((k-1))
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/f2/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $k -t >> $(dirname $0)/tiempos-exp2-f2-tipo1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2-f2-tipo1.txt
done

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2-f3-tipo1.txt
  m1=$((3*k))
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/f3/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $k -t >> $(dirname $0)/tiempos-exp2-f3-tipo1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2-f3-tipo1.txt
done

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2-f4-tipo1.txt
  aux=$((k^2))
  m1=$((aux/10))
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/f4/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $k -t >> $(dirname $0)/tiempos-exp2-f4-tipo1.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2-f4-tipo1.txt
done


#==============================tipo2========================================================

printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2-f1-tipo2.txt
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2-f2-tipo2.txt
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2-f3-tipo2.txt
printf "%d \n" $iteraciones >> $(dirname $0)/tiempos-exp2-f4-tipo2.txt

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2-f1-tipo2.txt
  aux=$((k-1))
  aux2=$((k*aux))
  m1=$((aux2/2))
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo2 < $(dirname $0)/f1/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $k -t >> $(dirname $0)/tiempos-exp2-f1-tipo2.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2-f1-tipo2.txt
done

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2-f2-tipo2.txt
  m1=$((k-1))
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo2 < $(dirname $0)/f2/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $k -t >> $(dirname $0)/tiempos-exp2-f2-tipo2.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2-f2-tipo2.txt
done

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2-f3-tipo2.txt
  m1=$((3*k))
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo2 < $(dirname $0)/f3/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $k -t >> $(dirname $0)/tiempos-exp2-f3-tipo2.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2-f3-tipo2.txt
done

for k in $n1; do
  printf "%d " $k >> $(dirname $0)/tiempos-exp2-f4-tipo2.txt
  aux=$((k^2))
  m1=$((aux/10))
  echo "Esta corriendo la instancia numero"
  printf "%d\n " $k
  for h in $(seq 1 $iteraciones); do
    echo "iteracion numero"
    printf "%d\n " $h
    $(dirname $0)/../../../ejercicio6-tipo2 < $(dirname $0)/f4/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $k -t >> $(dirname $0)/tiempos-exp2-f4-tipo2.txt
  done
  printf "\n" >> $(dirname $0)/tiempos-exp2-f4-tipo2.txt
done
#ahora voy a tener 8 archivos con tiempo. 4 para tipo1, 4 para tipo2. Los graficos van a tener en el eje x a n1 (que va variando) y en el eje y el tiempo de ejecucion correspondiente. Vamos a graficar 4 curvas para cada tipo, todas de distintos colores pero con el mismo tipo de linea (por ejemplo punteada para tipo 1, rayitas para tipo2)


#octave -q $(dirname $0)/exp1.m