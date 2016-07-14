#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1
n1="$(seq 10 5 70)"
# el minimo n que puedo tener dado el m es: min n {n * (n - 1) /2 >= m} 
n2=50 #El grafo2 queda completamente fijo, el n es el mismo en los dos.
m2=200 #Guarda que el grafo2 no sea uno especial, tipo estrella o algo asi. 
tamTabu=10
cuantosMiro=10
z=10

while getopts 'ha:' opt; do
  case $opt in
    a) iteraciones=$OPTARG ;;
    h) echo ""
       echo "    Experimento 4"
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
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  printf "combinacion1 %d %d %d %d \n"  5 6 $i $i | $(dirname $0)/../../../generador-grafosEspeciales
done

for i in $n1; do
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  mBipartito=$((i*30))
  printf "combinacion2 %d %d %d %d %d %d \n"  3 1 $i $i 30 $mBipartito | $(dirname $0)/../../../generador-grafosEspeciales
done

for i in $n1; do
  echo "Esta creando el archivo numero "
  printf "%d\n " $i
  mCiclo=$i
  printf "combinacion3 %d %d %d %d \n"  2 3 $i $i | $(dirname $0)/../../../generador-grafosEspeciales
done

#==============================tipo1=aristas=======================================================
#corro los de la combinacion 1 para todos: 
printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion1-ej3-exp4.txt

printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion1-ej4-exp4.txt
printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion1-ej5-exp4-tipo1.txt
printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion1-ej6-exp4-tipo1.txt


  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion1-ej3-exp4.txt
    aux=$((k-1))
    aux2=$((k*aux))
    m2=$((aux2/2))
    echo "EL M2 ES"
    printf "%d\n " $m2
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio3 < $(dirname $0)/combinacion1/grafo-n1-$k-n2-$k-m2-$m2.txt | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion1-ej3-exp4.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion1-ej3-exp4.txt
  done

  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion1-ej4-exp4.txt
    aux=$((k-1))
    aux2=$((k*aux))
    m2=$((aux2/2))
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio4 < $(dirname $0)/combinacion1/grafo-n1-$k-n2-$k-m2-$m2.txt | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion1-ej4-exp4.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion1-ej4-exp4.txt
  done

  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion1-ej5-exp4-tipo1.txt
    aux=$((k-1))
    aux2=$((k*aux))
    mCompleto=$((aux2/2))
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio5-tipo1 < $(dirname $0)/combinacion1/grafo-n1-$k-n2-$k-m2-$mCompleto.txt $cuantosMiro | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion1-ej5-exp4-tipo1.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion1-ej5-exp4-tipo1.txt
  done

  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion1-ej5-exp4-tipo1.txt
    aux=$((k-1))
    aux2=$((k*aux))
    mCompleto=$((aux2/2))
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/combinacion1/grafo-n1-$k-n2-$k-m2-$mCompleto.txt $cuantosMiro $tamTabu $z | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion1-ej6-exp4-tipo1.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion1-ej6-exp4-tipo1.txt
  done







#corro los de la combinacion 2 para todos: 

printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion2-ej4-exp4.txt
printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion2-ej5-exp4-tipo1.txt
printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion2-ej6-exp4-tipo1.txt


  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion2-ej4-exp4.txt
    m1=$k
    n2=$((30+k))
    m2=$((k*30))
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio4 < $(dirname $0)/combinacion2/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion2-ej4-exp4.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion2-ej4-exp4.txt
  done

  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion2-ej5-exp4-tipo1.txt
    m1=$k
    n2=$((30+k))
    m2=$((k*30))
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio5-tipo1 < $(dirname $0)/combinacion2/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion2-ej5-exp4-tipo1.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion2-ej5-exp4-tipo1.txt
  done

  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion2-ej5-exp4-tipo1.txt
    m1=$k
    n2=$((30+k))
    m2=$((k*30))
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/combinacion2/grafo-n1-$k-m1-$m1-n2-$n2-m2-$m2.txt $cuantosMiro $tamTabu $z | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion2-ej6-exp4-tipo1.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion2-ej6-exp4-tipo1.txt
  done






#corro los de la combinacion 3 para todos: 

printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion3-ej4-exp4.txt
printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion3-ej5-exp4-tipo1.txt
printf "%d \n" 1 >> $(dirname $0)/aristas-combinacion3-ej6-exp4-tipo1.txt


  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion3-ej4-exp4.txt
    m1=$((k-1))
    n2=$k
    m2=$k
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio4 < $(dirname $0)/combinacion3/grafo-n1-$k-m1-$m1-n2-$k-m2-$m2.txt | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion3-ej4-exp4.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion3-ej4-exp4.txt
  done

  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion3-ej5-exp4-tipo1.txt
    m1=$((k-1))
    n2=$k
    m2=$k
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio5-tipo1 < $(dirname $0)/combinacion3/grafo-n1-$k-m1-$m1-n2-$k-m2-$m2.txt $cuantosMiro | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion3-ej5-exp4-tipo1.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion3-ej5-exp4-tipo1.txt
  done

  for k in $n1; do
    printf "%d " $k >> $(dirname $0)/aristas-combinacion3-ej5-exp4-tipo1.txt
    m1=$((k-1))
    n2=$k
    m2=$k
    echo "Esta corriendo la instancia numero"
    printf "%d\n " $k
    $(dirname $0)/../../../ejercicio6-tipo1 < $(dirname $0)/combinacion3/grafo-n1-$k-m1-$m1-n2-$k-m2-$m2.txt $cuantosMiro $tamTabu $z | $(dirname $0)/../../../dameCantAristas >> $(dirname $0)/aristas-combinacion3-ej6-exp4-tipo1.txt
    printf "\n" >> $(dirname $0)/aristas-combinacion3-ej6-exp4-tipo1.txt
  done

#octave -q $(dirname $0)/exp4.m