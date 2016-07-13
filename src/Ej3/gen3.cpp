#include "ejercicio3.h"

void init(int n, vector<int>& padre, vector<int>& altura){
  for(int i = 0; i < n; i++) {
    altura.push_back(1);
    padre.push_back(i);
  }
}

int find(vector<int>& padre, int x) {
  if(padre[x] != x) {
    padre[x] = find(padre, padre[x]);
  }
  return padre[x];
}

void unions(int x, int y, vector<int>& padre, vector<int>& altura) {
  x = find(padre, x);
  y = find(padre, y);
  if(altura[x] < altura[y]) {
    padre[x] = y;
  } else {
    if(altura[x] == altura[y]) {
      altura[x]++;
    }
    padre[y] = x;
  }
}

int main(int argc, char *argv[]) {
  cout << "Indique la cantidad de nodos del cotree: " << endl;
  int N;
  cin >> N;
  srand(time(NULL));
  vector<int> padre;
  vector<int> altura;
  init(N, padre, altura);
  vector<Vertice> grafo;
  
  for(int i = 0; i < N; i++) { //pongo al grafo los N vertices.
      Vertice v;
      v.pertenece = true;
      grafo.push_back(v);
  }
  // Ahora tengo que crear aristas entre ellos por medio de union y join
  // Tiene que haber N-1 unions o joins (porque hay N-1 nodos internos)
  for(int i = 0; i < N-1; i++) {
    int nodo1 = rand()%N; // Elijo un nodo
    int nodo2;
    do
    {
      nodo2 = rand()%N; // Elijo otro nodo
    } while(find(padre,nodo2) == find(padre,nodo1)); // Elijo dos nodos de componentes conexas distintas
    int operacion = (rand()%2)-2; // Va a dar -1 o -2. Elijo la operacion
    if(operacion == -1) { // Es un join
      int padre1 = find(padre, nodo1);
      int padre2 = find(padre, nodo2);
      for(int i = 0; i < N; i++) {
        if(find(padre, i) == padre1) {
          for(int j = 0; j < N; j++) {
            if(i != j) {
              if(find(padre, j) == padre2) {
                // Unir i con j y j con i en grafo.
                bool res = false;
                list<int>::iterator inicio = grafo[i].adyacentes.begin();
                list<int>::iterator fin = grafo[i].adyacentes.end();
                while(inicio != fin) {
                  if(*inicio == j) res = true;
                  inicio++;
                }
                if(!res) grafo[i].adyacentes.push_back(j);
                res = false;
                inicio = grafo[j].adyacentes.begin();
                fin = grafo[j].adyacentes.end();
                while(inicio != fin) {
                  if(*inicio == i) res = true;
                  inicio++;
                }
                if(!res) grafo[j].adyacentes.push_back(i);
              }
            }
          }
        }
      }
      unions(nodo1,nodo2,padre,altura); // Uno las componentes conexas después de haber tirado aristas entre las dos componentes conexas
    } else { // Es un union
      unions(nodo1,nodo2,padre,altura); // Uno las componentes conexas
    }
  }
  imprimirGrafo(grafo);
}