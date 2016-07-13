#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <time.h>
#include <algorithm>

using namespace std;

struct Vertice { // Representa un nodo en el grafo
  Vertice() {} // Constructor por defecto para que no moleste el compilador
  list<int> adyacentes; // Guarda la lista de nodos adyacentes a "this"
  bool pertenece; // Proporciona información sobre si el nodo pertenece al grafo (para subgrafos del mismo, algunos nodos tendrán esta variable en false)
};

struct Cotree { // Representa un nodo del cotree
  Cotree() {} // Constructor por defecto para que no moleste el compilador
  vector<Cotree*> hijos; // Guarda un vector de punteros a los hijos
  int id; // El identificador del nodo. -1: Join; -2: Union; n = Nro. Vertice (n >= 0)
  vector<int> nodos; // Guarda los nodos que pertenecen al subcografo que representa el cotree cuya raíz es "this"
};

struct AristasNodos {
  AristasNodos() {
    aristas = 0;
    nodos = vector<int>();
  }
  AristasNodos(int x, vector<int> y) {
    aristas = x;
    nodos = y;
  }
  int aristas;
  vector<int> nodos;
};

void imprimirCotree(Cotree raiz) { // Imprime el Cotree
  queue<Cotree*> cola;
  cola.push(&raiz);
  cout << raiz.id << endl;
  while(!cola.empty()) {
    Cotree* aux = cola.front();
    cola.pop();
    vector<Cotree*>::iterator inicio = aux->hijos.begin();
    vector<Cotree*>::iterator fin = aux->hijos.end();
    while(inicio != fin) {
      cola.push(*inicio);
      cout << (*inicio)->id << " ";
      inicio++;
    }
    cout << endl;
  }
}

void imprimirGrafo(vector<Vertice> grafo) { // Imprime el Grafo
  list<int>::iterator inicio;
  list<int>::iterator fin;
  for(int i = 0; i < (int)grafo.size(); i++) {
    if(!grafo[i].pertenece) cout << "El nodo " << i << " no pertenece. ";
    cout << "Nodos adyacentes a " << i << ": ";
    inicio = grafo[i].adyacentes.begin();
    fin = grafo[i].adyacentes.end();
    while(inicio != fin) {
      if(!grafo[*inicio].pertenece) cout << "*";
      cout << *inicio << " ";
      inicio++;
    }
    cout << endl;
  }
}
