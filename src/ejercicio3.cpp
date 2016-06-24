#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>

using namespace std;

struct Vertice {
  Vertice() {}
  list<int> adyacentes;
  bool pertenece;
};

struct Cotree {
  Cotree() {
    /*hijos = vector<Cotree*>();
    id = -3;
    n = 0;*/
  }
  vector<Cotree*> hijos;
  int id;
  vector<int> nodos; //voy a poner los nodos que pertenecen al subgrafo este.
  //int n; // es igual a hijos.size();
};

void imprimirCotree(Cotree raiz) {
  queue<Cotree*> colita;
  colita.push(&raiz);
  cout << raiz.id << endl;
  while(!colita.empty()) {
    Cotree* aux = colita.front();
    colita.pop();
    //cout << aux->id << endl;
    vector<Cotree*>::iterator inicio = aux->hijos.begin();
    vector<Cotree*>::iterator fin = aux->hijos.end();
    while(inicio != fin) {
      colita.push(*inicio);
      cout << (*inicio)->id << " ";
      inicio++;
    }
    cout << endl;
  }
}

void imprimirGrafo(vector<Vertice> grafo) {
  list<int>::iterator inicio;
  list<int>::iterator fin;
  for(int i = 0; i < (int)grafo.size(); i++) {
    if(!grafo[i].pertenece) continue;
    cout << "nodos adyacentes a " << i << ": ";
    inicio = grafo[i].adyacentes.begin();
    fin = grafo[i].adyacentes.end();
    while(inicio != fin) {
      if(grafo[*inicio].pertenece) cout << *inicio << " ";
      inicio++;
    }
    cout << endl;
  }
}

/*void init(int n, vector<int>& padre, vector<int>& altura){
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
}*/

int primer_indice(bool vec[], vector<Vertice>* g) { // Devuelve el numero de nodo para elegir, -1 si todos los nodos fueron recorridos O(n)
  int indice = 0;
  int n = (*g).size();
  while(indice < n && (!(*g)[indice].pertenece || vec[indice])) {
    indice++;
  }
  if(indice >= n) {
    indice = -3;
  }
  return indice;
}

int dame_unico_nodo(vector<Vertice>* g) {
  int res = -3; //-1 no porq esta reservado para join, y -2 para union
  for(int i = 0; i < (int)g->size(); i++) {
    if((*g)[i].pertenece) res = i;
  }
  return res;
}

int obtener_nodos_posta(vector<Vertice>* g) {
  int res = 0;
  for(int i = 0; i < (int)g->size(); i++) {
    if((*g)[i].pertenece) res++;
  }
  return res;
}

vector<vector<Vertice> > separar_componentes_conexas(vector<Vertice>* g) {
  int N = g->size();
  vector<vector<Vertice> > res;
  bool recorridos[N];
  int nodos_posta = obtener_nodos_posta(g);
  int cant_recorridos = 0;
  for(int i = 0; i < N; i++) {
    recorridos[i] = false; // al principio no recorri ningun nodo
  }
  while(cant_recorridos < nodos_posta) { //mientras hayan nodos sin visitar..
    queue<int> cola;
    vector<Vertice> componente = vector<Vertice>(N); // creo un grafo q seria cada componente conexa con n nodos ESTABA AFUERA DEL WHILE
    for(int i = 0; i < N; i++) { //primero pongo a todos los nodos como que no estan, y los que esten los voy a ir agregando en el bfs.
      Vertice v;
      v.pertenece = false;
      componente[i] = v;
    }
    int indice = primer_indice(recorridos, g); //agarro el primer nodo que no haya visitado que pertenezca al grafo
    if(indice < 0) break; // si no hay nodos corto todo (en realidad ni deberia entrar porq el while lo corta antes)
    cola.push(indice); //pusheo el primer nodo que no recorri
    while(!cola.empty()) {
      int aux = cola.front();
      cola.pop();
      Vertice v;
      v.pertenece = true;
      //v.adyacentes.push_back(aux);
      //cant_recorridos++;
      recorridos[aux] = true;
      list<int>::iterator inicio = (*g)[aux].adyacentes.begin();
      list<int>::iterator fin = (*g)[aux].adyacentes.end();
      while(inicio != fin) {
        if((*g)[*inicio].pertenece) {
          if(!recorridos[*inicio]) cola.push(*inicio);
          v.adyacentes.push_back(*inicio);
        }
        inicio++;
      }
      componente[aux] = v;
    }
    res.push_back(componente);
    cant_recorridos++;
    // VER BIEN TODA ESTA FUNCION, REVISARLA! DALE QUE CON ESTO DSP PUEDO HACER LO DEL COTREE Y DSP PIENSO COMO HACER LO DEMAS.
  }

  return res;
}


vector<Vertice> complementar(vector<Vertice> g) { // O(N^2), con N = |V(g)|
  vector<Vertice> g_complemento = vector<Vertice>(g.size()); // si complementaba el grafo k1 se jodia todo..
  bool pertenecen[g.size()];
  
  for(int i = 0; i < (int)g.size(); i++) {
      pertenecen[i] = false;
  }
  
  for(int i = 0; i < (int)g.size(); i++) {
    if(!g[i].pertenece) continue; //si ese nodo no pertenece, listo
    list<int>::iterator inicio = g[i].adyacentes.begin();
    list<int>::iterator fin = g[i].adyacentes.end();
    list<int> listaAux;
    
    while(inicio != fin) {
        if(g[*inicio].pertenece) pertenecen[*inicio] = true;
        inicio++;
    }
    for(int j = 0; j < (int)g.size(); j++) {
        if(!pertenecen[j] && j != i && g[j].pertenece) {
            listaAux.push_back(j);
        }
        pertenecen[j] = false;
    }
    g_complemento[i].adyacentes = listaAux;
    g_complemento[i].pertenece = true;
  }
  return g_complemento;
}

/*int cant_componentes_conexas(vector<list<int> > g) { // calcula la cantidad de componentes conexas del grafo g
  int N = g.size();
  vector<int> padre;
  vector<int> altura;
  init(N, padre, altura);
  for(int i = 0; i < N; i++) { // No se que complejidad tiene xD (hay q ver si me paso o no..)
    list<int>::iterator inicio = g[i].begin();
    list<int>::iterator fin = g[i].end();
    while(inicio != fin) {
        if(find(padre, i) != find(padre, *inicio)) {
            unions(i, *inicio, padre, altura);
        }
        inicio++;
    }
  }
  int cant = 0;
  for(int i = 0; i < N; i++) {
    if(padre[i] == i) cant++;
  }
  return cant;
}*/

struct Nodo_Cotree {
  Nodo_Cotree() {};
  //bool esHoja; // if true, ver el campo nro, otherwise ver el campo tipo. if true, the two pointers are NULL
  char tipo;
  int nro;
  int n; //cantidad de cotrees hijos
  Nodo_Cotree* hijos[];
  //Nodo_Cotree* izq;
};


void make_cotree(vector<Vertice>* g, Cotree* root) {
  if(obtener_nodos_posta(g) == 1) { // Es un K_1
    root->id = dame_unico_nodo(g); // O(n)
    cout << "es un solo nodo, " << root->id << endl;
    //root->n = 0;
    root->hijos = vector<Cotree*>();
    root->nodos.push_back(root->id);
    return;
  } else { // TESTEAR LA FUNCION DAME UNICO NODO DE ARRIBA PARA VER SI HACE LO QUE TIENE QUE HACER (TESTEAR EN CASA)
    vector<vector<Vertice> > componentes = separar_componentes_conexas(g);
    cout << "g no es K1, muestro g: " << endl;
    imprimirGrafo(*g);
    cout << "muestro cant de nodos posta: " << obtener_nodos_posta(g) << endl;
    int cc = componentes.size();
    if(cc == 1) { // es join
      cout << "g tiene una componente conexa" << endl;
      root->id = -1;
      //root->n = cc;
      vector<Vertice> auxx = complementar(componentes[0]);
      cout << "complemente el g, ahora me quedo asi: " << endl;
      imprimirGrafo(auxx);
      vector<vector<Vertice> > componentes_complementadas = separar_componentes_conexas(&auxx);
      if(componentes_complementadas.size() == 1) { // el complemento de un grafo conexo es conexo, entonces no es cografo.
        return; // ver si devovler false y en el merge de las soluciones, si uno es false entonces devolver false. NO HACE FALTA. SI LA USAS BIEN NO ENTRA A ESTE IF
      } else { // si hay mas de una componente conexa, puede ser cografo.
        //complementar cada componente y llamar recursivamente para cada componente.
        cout << "el complemento de g tiene varias componentes conexas" << endl;
        for(int i = 0; i < (int)componentes_complementadas.size(); i++) {
          cout << "muestro componente conexa. " << i << ":" << endl;
          imprimirGrafo(componentes_complementadas[i]);
          //vector<Vertice> grafo_aux;
          Cotree* co_aux = new Cotree();
          if(obtener_nodos_posta(&componentes_complementadas[i]) != 1) { 
            cout << "nodos posta = " << obtener_nodos_posta(&componentes_complementadas[i]) << endl;
            cout << "hago cotree del complemento del grafo que acabo de imprimir asd" << endl;
            vector<Vertice> grafo_aux = complementar(componentes_complementadas[i]);
            cout << "imprimo mi grafo_aux complementado" << endl;
            imprimirGrafo(grafo_aux);
            make_cotree(&grafo_aux, co_aux);
            //grafo_aux = complementar(componentes_complementadas[i]);
          } else {
            cout << "hago cotree del grafo que acabo de imprimir asd" << endl;
            make_cotree(&componentes_complementadas[i], co_aux);
            //grafo_aux = componentes_complementadas[i];
          }
          
          
          vector<int>::iterator inicio = co_aux->nodos.begin();
          vector<int>::iterator fin = co_aux->nodos.end();
          while(inicio != fin) {
            root->nodos.push_back(*inicio);
            inicio++;
          }
          
          root->hijos.push_back(co_aux);
        }
        return;
      }
      //si el complemento de g tiene 1 sola componente conexa, devolver false porq no es un cografo. (es cierto esto?)
      //agregar el complemento de cada componente conexa (de hecho, ver si anda bien lo de las componentes conexas!!)
    } else { // es union
      root->id = -2;
      cout << "g tiene mas de una componente conexa" << endl;
      //root->n = cc;
      for(int i = 0; i < cc; i++) {
        cout << "muestro la componente conexa " << i << ": " << endl;
        imprimirGrafo(componentes[i]);
        Cotree* co_aux = new Cotree();
        cout << "hago cotree del grafo que acabo de imprimir" << endl;
        make_cotree(&componentes[i], co_aux);
        vector<int>::iterator inicio = co_aux->nodos.begin();
        vector<int>::iterator fin = co_aux->nodos.end();
        while(inicio != fin) {
          root->nodos.push_back(*inicio);
          inicio++;
        }
        root->hijos.push_back(co_aux);
      }
      return;
      //agregar cada componente conexa de g a los hijos
    }
  }
  //llamar recursivamente a cada hijo de root.... CREO Q DE HECHO ESTO NO FUNCIONAA PORQ EL G CON EL Q LLAMO A CADA UNA DE LAS RECURSIONES TIENE QUE SER DISTINTO???? SI ES IGUAL NO PASA NADA!
}

/*void make_cotree(vector<list<int> > g, Nodo_Cotree* nodo) { //dado un grafo g, calcula el cotree asociado
  //Calcular componentes conexas del grafo. si tiene 1 componente conexa, es un join, si tiene mas de una es una union.
  int cant = cant_componentes_conexas(g);
  if(cant == 1) { // hubo un join
    vector<list<int> > complemento = complementar(g);
    int cant_2 = cant_componentes_conexas(complemento); //calculo la cant de componentes conexas del complemento.
    //por cada una llamo recursivamente
    nodo->tipo = 'J';
    nodo->n = cant_2;
    vector<list<int> > vector_de_componentes[cant_2]; //la gracia es poner en cada posicion el grafo que corresponde a la componente conexa
    for(int i = 0; i < cant_2; i++) {
      Nodo_Cotree* aux = new Nodo_Cotree();
      make_cotree(complementar(vector_de_componentes[i]), aux);
    }
  } else { //hubo un union
    
  }
}*/

void binarizar(Cotree* src) {
  if(src->hijos.size() > 2) {
    Cotree* aux = new Cotree();
    aux->id = src->id;
    for(int i = src->hijos.size()-1; i > 0; i--) {
      aux->hijos.push_back(src->hijos[i]);
      src->hijos.pop_back();
    }
    src->hijos.push_back(aux);
    binarizar(src->hijos[0]);
    binarizar(src->hijos[1]);
  } else if(src->hijos.size() == 2) {
    binarizar(src->hijos[0]);
    binarizar(src->hijos[1]);
  } else if(src->hijos.size() == 1) {
    binarizar(src->hijos[0]);
  }
}

bool es_cografo(vector<Vertice>* g) {
  vector<vector<Vertice> > componentes_conexas = separar_componentes_conexas(g);
  vector<Vertice> g_complemento = complementar(*g);
  vector<vector<Vertice> > componentes_conexas_complemento = separar_componentes_conexas(&g_complemento);
  return (obtener_nodos_posta(g) == 1 || ((componentes_conexas.size() == 1 && componentes_conexas_complemento.size() != 1) || (componentes_conexas.size() != 1 && componentes_conexas_complemento.size() == 1)));
}

int main() {
  //int N = 1;
  //int M = 8; //K4
  vector<Vertice> grafo;// = vector<Vertice>(4);
  /*for(int i = 0; i < N; i++) {
    Vertice v;
    v.pertenece = true;
    //if(i == 0) v.pertenece = false;
    for(int j = 0; j < N; j++) {
      if(i != j) {
        v.adyacentes.push_back(j);
      }
    }
    grafo[i] = v;
  }*/

  Vertice v0;
  v0.pertenece = true;
  /*v0.adyacentes.push_back(1);
  v0.adyacentes.push_back(2);
  v0.adyacentes.push_back(3);*/
  grafo.push_back(v0);

  Vertice v1;
  v1.pertenece = true;
  v1.adyacentes.push_back(2);
  v1.adyacentes.push_back(4);
  v1.adyacentes.push_back(5);
  grafo.push_back(v1);

  Vertice v2;
  v2.pertenece = true;
  v2.adyacentes.push_back(1);
  v2.adyacentes.push_back(3);
  v2.adyacentes.push_back(4);
  grafo.push_back(v2);

  Vertice v3;
  v3.pertenece = true;
  v3.adyacentes.push_back(2);
  v3.adyacentes.push_back(4);
  v3.adyacentes.push_back(5);
  grafo.push_back(v3);
  
  Vertice v4;
  v4.pertenece = true;
  v4.adyacentes.push_back(1);
  v4.adyacentes.push_back(2);
  v4.adyacentes.push_back(3);
  v4.adyacentes.push_back(5);
  grafo.push_back(v4);
  
  Vertice v5;
  v5.pertenece = true;
  v5.adyacentes.push_back(1);
  v5.adyacentes.push_back(3);
  v5.adyacentes.push_back(4);
  grafo.push_back(v5);

  /*list<int>::iterator inicio;
  list<int>::iterator fin;*/
  vector<Vertice> complemento = complementar(grafo);
  /*for(int i = 0; i < grafo.size(); i++) {
    if(!grafo[i].pertenece) continue;
    cout << "nodos adyacentes a " << i << ": ";
    inicio = grafo[i].adyacentes.begin();
    fin = grafo[i].adyacentes.end();
    while(inicio != fin) {
      if(grafo[*inicio].pertenece) cout << *inicio << " ";
      inicio++;
    }
    cout << endl;
  }*/
  /*bool rec[grafo.size()];
  for(int i = 0; i < grafo.size(); i++) {
    rec[i] = false;
  }
  rec[3] = true;
  cout << primer_indice(rec, &grafo) << endl;*/
  //cout << obtener_nodos_posta(&grafo) << endl;
  /*vector<vector<Vertice> > vect = separar_componentes_conexas(&grafo);
  cout << vect.size() << endl;*/
  //cout << "cant componentes conexas de g: " << cant_componentes_conexas(grafo) << endl;

  Cotree raiz;
  /*raiz.id = -2;
  Cotree j1;
  j1.id = -1;
  Cotree j2;
  j2.id = -1;
  Cotree u1;
  u1.id = -2;
  Cotree u2;
  u2.id = -2;
  Cotree v0;
  v0.id = 0;
  Cotree v1;
  v1.id = 1;
  Cotree v2;
  v2.id = 2;
  Cotree v3;
  v3.id = 3;
  Cotree v4;
  v4.id = 4;
  Cotree v5;
  v5.id = 5;
  u2.hijos.push_back(&v5);
  u2.hijos.push_back(&v2);
  j2.hijos.push_back(&v4);
  j2.hijos.push_back(&u2);
  u1.hijos.push_back(&v1);
  u1.hijos.push_back(&v3);
  j1.hijos.push_back(&u1);
  j1.hijos.push_back(&j2);
  raiz.hijos.push_back(&v0);
  raiz.hijos.push_back(&j1);*/

  //cout << "empiezo cotree: " << endl;
  
  
  
  make_cotree(&grafo, &raiz);

  imprimirCotree(raiz);
  cout << "binarizo" << endl;
  binarizar(&raiz);
  imprimirCotree(raiz);
  
  vector<int>::iterator inicio = raiz.hijos[1]->hijos[0]->hijos[1]->nodos.begin();
  vector<int>::iterator fin = raiz.hijos[1]->hijos[0]->hijos[1]->nodos.end();
  while(inicio != fin) {
      cout << *inicio << " ";
      inicio++;
  }
  
  
  //imprimirGrafo(complemento);

  /*vector<vector<Vertice> > cc = separar_componentes_conexas(&grafo);
  cout << "componente 0: " << endl;
  imprimirGrafo(cc[0]);
  cout << "componente 1: " << endl;
  imprimirGrafo(cc[1]);
  vector<Vertice> comp1 = complementar(cc[1]);
  cout << "complemente la 1, imprimo: " << endl;
  imprimirGrafo(comp1);
  vector<vector<Vertice> > cc2 = separar_componentes_conexas(&comp1);
  cout << "separe en componentes conexas el grafo anterior, muestro: " << endl;
  cout << "componente 0: " << endl;
  imprimirGrafo(cc2[0]);
  cout << "componente 1: " << endl;
  imprimirGrafo(cc2[1]);
  cout << "componente 2: " << endl;
  imprimirGrafo(cc2[2]);
  cout << "complemento la 1 " << endl;
  vector<Vertice> complemento_1 = complementar(cc2[1]);
  cout << "muestro: " << endl;
  imprimirGrafo(complemento_1);
  vector<vector<Vertice> > cc3 = separar_componentes_conexas(&complemento_1);
  cout << "muestro 0: " << endl;
  imprimirGrafo(cc3[0]);
  cout << "muestro 1: " << endl;
  imprimirGrafo(cc3[1]);*/
  //cout << obtener_nodos_posta(&cc2[1]) << endl;
  
  //cout << "el grafo es un cografo? " << es_cografo(&grafo) << endl;
}