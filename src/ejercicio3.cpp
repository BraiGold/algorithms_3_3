#include "ejercicio3.h"

timeval timeStart, timeEnd;

void init_time()
{
    gettimeofday(&timeStart,NULL);
}

double get_time()
{
    gettimeofday(&timeEnd,NULL);
    return (1000000*(timeEnd.tv_sec-timeStart.tv_sec)+(timeEnd.tv_usec-timeStart.tv_usec))/1000000.0;
}

int primer_indice(bool vec[], vector<Vertice>* g) { // Devuelve el número de nodo para elegir, -3 si todos los nodos fueron recorridos
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

int dame_unico_nodo(vector<Vertice>* g) { // Devuelve el unico nodo del grafo g
  int res = -3; //-1 no porque está reservado para join, y -2 para union
  for(int i = 0; i < (int)g->size(); i++) {
    if((*g)[i].pertenece) res = i;
  }
  return res;
}

int obtener_nodos_posta(vector<Vertice>* g) { // Devuelve la cantidad de nodos que tiene un grafo (únicamente los que pertenecen a él)
  int res = 0;
  for(int i = 0; i < (int)g->size(); i++) {
    if((*g)[i].pertenece) res++;
  }
  return res;
}

vector<vector<Vertice> > separar_componentes_conexas(vector<Vertice>* g) { // Separa el grafo g en sus componentes conexas
  int N = g->size();
  vector<vector<Vertice> > res;
  bool recorridos[N];
  int nodos_posta = obtener_nodos_posta(g);
  int cant_recorridos = 0;
  for(int i = 0; i < N; i++) {
    recorridos[i] = false; // Al principio no recorrí ningún nodo
  }
  while(cant_recorridos < nodos_posta) { // Mientras hayan nodos sin visitar..
    queue<int> cola;
    vector<Vertice> componente = vector<Vertice>(N); // Creo un grafo que sería cada componente conexa con N nodos
    for(int i = 0; i < N; i++) { // Primero pongo a todos los nodos como que no están, y los que estén los voy a ir agregando en el bfs.
      Vertice v;
      v.pertenece = false;
      componente[i] = v;
    }
    int indice = primer_indice(recorridos, g); // Agarro el primer nodo que no haya visitado que pertenezca al grafo
    if(indice < 0) break; // Si no hay nodos corto todo (en realidad ni debería entrar porque el while lo corta antes)
    cola.push(indice); // Pusheo el primer nodo que no recorrí
    while(!cola.empty()) {
      int aux = cola.front();
      cola.pop();
      Vertice v;
      v.pertenece = true;
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
  }
  return res;
}


vector<Vertice> complementar(vector<Vertice> g) { // Complementa el grafo g
  vector<Vertice> g_complemento = vector<Vertice>(g.size());
  for(int i = 0; i < (int)g.size(); i++) {
    g_complemento[i].pertenece = false;
    bool pertenecen[g.size()];
    for(int k = 0; k < (int)g.size(); k++) {
        pertenecen[k] = false;
    }
    if(!g[i].pertenece) continue; // Si ése nodo no pertenece, listo
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

void solucion(Cotree* root, int n, vector<AristasNodos>* res) {
  if(root->id >= 0) { // Es hoja
    AristasNodos aux;
    aux.aristas = 0;
    vector<int> vec;
    vec.push_back(root->id);
    aux.nodos = vec;
    for(int i = 1; i <= n; i++) {
      (*res)[i] = aux;
    }
  } else { // No es hoja, es join o union
    vector<AristasNodos> vecIzq = vector<AristasNodos>(n+1);
    vector<AristasNodos> vecDer = vector<AristasNodos>(n+1);
    solucion(root->hijos[0], n, &vecIzq);
    solucion(root->hijos[1], n, &vecDer);
    for(int i = 1; i <= n; i++) {
      int maxAristas = 0;
      vector<int> noditos;
      for(int j = 0; j <= i; j++) {
        int aristasI = 0;
        int aristasD = 0;
        int aristasTotales;
        vector<int> vec;
        if(j != 0) {
          aristasI = vecIzq[j].aristas;
          vector<int>::iterator inicio = vecIzq[j].nodos.begin();
          vector<int>::iterator fin = vecIzq[j].nodos.end();
          while(inicio != fin) {
            vec.push_back(*inicio);
            inicio++;
          }
        }
        if(i-j != 0) {
          aristasD = vecDer[i-j].aristas;
          vector<int>::iterator inicio = vecDer[i-j].nodos.begin();
          vector<int>::iterator fin = vecDer[i-j].nodos.end();
          while(inicio != fin) {
            vec.push_back(*inicio);
            inicio++;
          }
        }
        aristasTotales = aristasI + aristasD;
        if(root->id == -1) aristasTotales += (vecIzq[j].nodos.size()*vecDer[i-j].nodos.size());
        if(aristasTotales >= maxAristas && vec.size() >= noditos.size()) {
          maxAristas = aristasTotales;
          noditos = vec;
        }
      }
      AristasNodos aux;
      aux.aristas = maxAristas;
      aux.nodos = noditos;
      (*res)[i] = aux;
    }
  }
}

/*int generar_solucion(vector<int>* res, Cotree* root, int n) { // Devuelve la cantidad de aristas de la solucion, y modifica res con los nodos de la solucion
  if(root->id >= 0) {
    res->push_back(root->id);
    return 0;
  } else {
    vector<int> solucion;
    int maxGlobal=0;
    for(int i = 0; i < min(root->hijos[0]->nodos.size(), root->hijos[1]->nodos.size()); i++) {
      int indice_menor = (min(root->hijos[0]->nodos.size(), root->hijos[1]->nodos.size()) == root->hijos[0]->nodos.size())? 0 : 1;
      vector<int> vecIzq;
      int aristasIzq = generar_solucion(&vecIzq, root->hijos[indice_menor], i);
      vector<int> vecDer;
      int aristasDer = generar_solucion(&vecDer, root->hijos[(indice_menor+1)%2], min(n-i, (int)root->hijos[(indice_menor+1)%2]->nodos.size()));
      if(aristasDer + aristasIzq >= maxGlobal) {
        maxGlobal = aristasDer + aristasIzq;
        if(root->id == -1) maxGlobal+=(i*(n-i));
        solucion.clear();
        vector<int>::iterator inicio = vecIzq.begin();
        vector<int>::iterator fin = vecIzq.end();
        while(inicio != fin) {
          solucion.push_back(*inicio);
          inicio++;
        }
        inicio = vecDer.begin();
        fin = vecDer.end();
        while(inicio != fin) {
          solucion.push_back(*inicio);
          inicio++;
        }
      }
    }
    vector<int>::iterator inicio = solucion.begin();
    vector<int>::iterator fin = solucion.end();
    while(inicio != fin) {
      res->push_back(*inicio);
      inicio++;
    }
    return maxGlobal;
  }
} */

void make_cotree(vector<Vertice>* g, Cotree* root) { // Dado el grafo g, arma el cotree y lo guarda en root
  if(obtener_nodos_posta(g) == 1) { // Es un K_1
    root->id = dame_unico_nodo(g); // O(n)
    //cout << "es un solo nodo, " << root->id << endl;
    root->hijos = vector<Cotree*>();
    root->nodos.push_back(root->id);
    return;
  } else {
    vector<vector<Vertice> > componentes = separar_componentes_conexas(g);
    //cout << "g no es K1, muestro g: " << endl;
    //imprimirGrafo(*g);
    //cout << "muestro cant de nodos posta: " << obtener_nodos_posta(g) << endl;
    int cc = componentes.size();
    if(cc == 1) { // Es join
      //cout << "g tiene una componente conexa" << endl;
      root->id = -1;
      vector<Vertice> auxx = complementar(componentes[0]);
      //cout << "complemente el g, ahora me quedo asi: " << endl;
      //imprimirGrafo(auxx);
      vector<vector<Vertice> > componentes_complementadas = separar_componentes_conexas(&auxx);
      if(componentes_complementadas.size() == 1) { // El complemento de un grafo conexo es conexo, entonces no es cografo.
        return;
      } else { // Si hay más de una componente conexa, puede ser cografo.
        // Complementar cada componente y llamar recursivamente para cada componente.
        //cout << "el complemento de g tiene varias componentes conexas" << endl;
        for(int i = 0; i < (int)componentes_complementadas.size(); i++) {
          //cout << "muestro componente conexa. " << i << ":" << endl;
          //imprimirGrafo(componentes_complementadas[i]);
          Cotree* co_aux = new Cotree();
          if(obtener_nodos_posta(&componentes_complementadas[i]) != 1) { 
            //cout << "nodos posta = " << obtener_nodos_posta(&componentes_complementadas[i]) << endl;
            //cout << "hago cotree del complemento del grafo que acabo de imprimir asd" << endl;
            vector<Vertice> grafo_aux = complementar(componentes_complementadas[i]);
            //cout << "imprimo mi grafo_aux complementado" << endl;
            //imprimirGrafo(grafo_aux);
            make_cotree(&grafo_aux, co_aux);
            //grafo_aux = complementar(componentes_complementadas[i]);
          } else {
            //cout << "hago cotree del grafo que acabo de imprimir asd" << endl;
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
    } else { // Es union
      root->id = -2;
      //cout << "g tiene mas de una componente conexa" << endl;
      for(int i = 0; i < cc; i++) {
        //cout << "muestro la componente conexa " << i << ": " << endl;
        //imprimirGrafo(componentes[i]);
        Cotree* co_aux = new Cotree();
        //cout << "hago cotree del grafo que acabo de imprimir" << endl;
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
      // Agregar cada componente conexa de g a los hijos
    }
  }
}

void binarizar(Cotree* src) { // Binariza el cotree pasado por parámetro
  if(src->hijos.size() > 2) {
    Cotree* aux = new Cotree();
    aux->id = src->id;
    for(int i = src->hijos.size()-1; i > 0; i--) {
      aux->hijos.push_back(src->hijos[i]);
      vector<int>::iterator inicio = src->hijos[i]->nodos.begin();
      vector<int>::iterator fin = src->hijos[i]->nodos.end();
      while(inicio != fin) {
        aux->nodos.push_back(*inicio);
        inicio++;
      }
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

bool es_cografo(vector<Vertice>* g) { // Devuelve true si g es cografo, false en otro caso
  vector<vector<Vertice> > componentes_conexas = separar_componentes_conexas(g);
  vector<Vertice> g_complemento = complementar(*g);
  vector<vector<Vertice> > componentes_conexas_complemento = separar_componentes_conexas(&g_complemento);
  return (obtener_nodos_posta(g) == 1 || ((componentes_conexas.size() == 1 && componentes_conexas_complemento.size() != 1) || (componentes_conexas.size() != 1 && componentes_conexas_complemento.size() == 1)));
}

int main(int argc, char *argv[]) {
  bool pidieronTiempo = false; 
  double tiempo;
  if (argc > 1) {
    if (argv[1] == string("-t")) {
      pidieronTiempo = true;
    }
  }
  int N1, M1, N2, M2;
  cin >> N1;
  cin >> M1;
  cin >> N2;
  cin >> M2;
  
  vector<Vertice> G_1 = vector<Vertice>(N1);
  vector<Vertice> G_2 = vector<Vertice>(N2);
  
  for(int i = 0; i < N1; i++) {
    G_1[i].pertenece = true;
  }
  
  for(int i = 0; i < N2; i++) {
    G_2[i].pertenece = true;
  }
  
  for(int i = 0; i < M1; i++) {
    int u, v;
    cin >> u;
    cin >> v;
    G_1[u].adyacentes.push_back(v);
    G_1[v].adyacentes.push_back(u);
  }
  
  for(int i = 0; i < M2; i++) {
    int u, v;
    cin >> u;
    cin >> v;
    G_2[u].adyacentes.push_back(v);
    G_2[v].adyacentes.push_back(u);
  }
  
  init_time();


  Cotree raiz;
  make_cotree(&G_1, &raiz); // Asumo que el G_1 es el cografo
  binarizar(&raiz);
  
  int K_n = N2; // Asumo que el G_2 es el grafo completo
  vector<AristasNodos> sol = vector<AristasNodos>(K_n+1);
  solucion(&raiz, K_n, &sol);
  
  
  tiempo = get_time();
  if (!pidieronTiempo) { 
    cout << sol[K_n].nodos.size() << " " << sol[K_n].aristas << endl;
    
    //ordeno el vector solucion:
    sort(sol[K_n].nodos.begin(), sol[K_n].nodos.end());
    
    
    for(int i = 0; i < (int)G_1.size(); i++) {
      G_1[i].pertenece = false;
    }
    
    vector<int>::iterator inicio = sol[K_n].nodos.begin();
    vector<int>::iterator fin = sol[K_n].nodos.end();
    while(inicio != fin) {
      G_1[*inicio].pertenece = true; // pongo true en los nodos de la solucion
      cout << *inicio << " ";
      inicio++;
    }
    cout << endl;
    for(int i = 0; i < sol[K_n].nodos.size(); i++) {
      cout << i << " ";
    }
    cout << endl;
    //ahora tengo que mostrar las adyacencias
    list<int>::iterator begin;
    list<int>::iterator end;
    for(int i = 0; i < (int)G_1.size(); i++) {
      if(!G_1[i].pertenece) continue;
      begin = G_1[i].adyacentes.begin();
      end = G_1[i].adyacentes.end();
      while(begin != end) {
        if(!G_1[*begin].pertenece) {
          *begin++;
          continue;
        }
        cout << i << " " << *begin << endl;
        // hay que borrar la otra arista, la <*begin,i>
        G_1[*begin].adyacentes.remove(i);
        begin++;
      }
    }
  } else {
    printf("%.10f ", tiempo);
  }
  
  // Debería checkear si uno de los dos grafos es cografo, y si el otro grafo es completo, si eso ocurre entonces ejecutar este algoritmo, y sino ejecutar el algoritmo exacto del ejercicio 2.
  // Para este algoritmo, primero hay que ver si el cotree tiene menor o igual cantidad de vértices que el K_n. Si es así, devolver el cografo, y sino...
  // hay que generar el cotree del cografo y luego recorrerlo buscando el subgrafo de n (n = cantidad de nodos del K_n) vertices que mayor cantidad de aristas tiene.
  // Nos falta ver cómo hacer esto último... para el RTP xD
  /*vector<Vertice> grafo;

  Vertice v0;
  v0.pertenece = true;
  v0.adyacentes.push_back(3);
  v0.adyacentes.push_back(4);
  v0.adyacentes.push_back(5);
  v0.adyacentes.push_back(6);
  v0.adyacentes.push_back(7);
  v0.adyacentes.push_back(8);
  v0.adyacentes.push_back(9);
  v0.adyacentes.push_back(10);
  grafo.push_back(v0);

  Vertice v1;
  v1.pertenece = true;
  v1.adyacentes.push_back(3);
  v1.adyacentes.push_back(4);
  v1.adyacentes.push_back(5);
  v1.adyacentes.push_back(6);
  v1.adyacentes.push_back(7);
  v1.adyacentes.push_back(8);
  v1.adyacentes.push_back(9);
  v1.adyacentes.push_back(10);
  grafo.push_back(v1);

  Vertice v2;
  v2.pertenece = true;
  v2.adyacentes.push_back(3);
  v2.adyacentes.push_back(4);
  v2.adyacentes.push_back(5);
  v2.adyacentes.push_back(6);
  v2.adyacentes.push_back(7);
  v2.adyacentes.push_back(8);
  v2.adyacentes.push_back(9);
  v2.adyacentes.push_back(10);
  grafo.push_back(v2);

  Vertice v3;
  v3.pertenece = true;
  v3.adyacentes.push_back(0);
  v3.adyacentes.push_back(1);
  v3.adyacentes.push_back(2);
  v3.adyacentes.push_back(4);
  v3.adyacentes.push_back(5);
  v3.adyacentes.push_back(6);
  v3.adyacentes.push_back(7);
  v3.adyacentes.push_back(8);
  v3.adyacentes.push_back(9);
  v3.adyacentes.push_back(10);
  grafo.push_back(v3);
  
  Vertice v4;
  v4.pertenece = true;
  v4.adyacentes.push_back(0);
  v4.adyacentes.push_back(1);
  v4.adyacentes.push_back(2);
  v4.adyacentes.push_back(3);
  v4.adyacentes.push_back(7);
  v4.adyacentes.push_back(8);
  v4.adyacentes.push_back(9);
  v4.adyacentes.push_back(10);
  grafo.push_back(v4);
  
  Vertice v5;
  v5.pertenece = true;
  v5.adyacentes.push_back(0);
  v5.adyacentes.push_back(1);
  v5.adyacentes.push_back(2);
  v5.adyacentes.push_back(3);
  v5.adyacentes.push_back(6);
  v5.adyacentes.push_back(7);
  v5.adyacentes.push_back(8);
  v5.adyacentes.push_back(9);
  v5.adyacentes.push_back(10);
  grafo.push_back(v5);
  
  Vertice v6;
  v6.pertenece = true;
  v6.adyacentes.push_back(0);
  v6.adyacentes.push_back(1);
  v6.adyacentes.push_back(2);
  v6.adyacentes.push_back(3);
  v6.adyacentes.push_back(5);
  v6.adyacentes.push_back(7);
  v6.adyacentes.push_back(8);
  v6.adyacentes.push_back(9);
  v6.adyacentes.push_back(10);
  grafo.push_back(v6);
  
  Vertice v7;
  v7.pertenece = true;
  v7.adyacentes.push_back(0);
  v7.adyacentes.push_back(1);
  v7.adyacentes.push_back(2);
  v7.adyacentes.push_back(3);
  v7.adyacentes.push_back(4);
  v7.adyacentes.push_back(5);
  v7.adyacentes.push_back(6);
  grafo.push_back(v7);
  
  Vertice v8;
  v8.pertenece = true;
  v8.adyacentes.push_back(0);
  v8.adyacentes.push_back(1);
  v8.adyacentes.push_back(2);
  v8.adyacentes.push_back(3);
  v8.adyacentes.push_back(4);
  v8.adyacentes.push_back(5);
  v8.adyacentes.push_back(6);
  v8.adyacentes.push_back(9);
  v8.adyacentes.push_back(10);
  grafo.push_back(v8);
  
  Vertice v9;
  v9.pertenece = true;
  v9.adyacentes.push_back(0);
  v9.adyacentes.push_back(1);
  v9.adyacentes.push_back(2);
  v9.adyacentes.push_back(3);
  v9.adyacentes.push_back(4);
  v9.adyacentes.push_back(5);
  v9.adyacentes.push_back(6);
  v9.adyacentes.push_back(8);
  grafo.push_back(v9);
  
  Vertice v10;
  v10.pertenece = true;
  v10.adyacentes.push_back(0);
  v10.adyacentes.push_back(1);
  v10.adyacentes.push_back(2);
  v10.adyacentes.push_back(3);
  v10.adyacentes.push_back(4);
  v10.adyacentes.push_back(5);
  v10.adyacentes.push_back(6);
  v10.adyacentes.push_back(8);
  grafo.push_back(v10);*/
  

  //vector<Vertice> complemento = complementar(grafo);

  //Cotree raiz;
  /*raiz.id = -1;
  Cotree j1;
  j1.id = -1;
  Cotree j2;
  j2.id = -1;
  Cotree j3;
  j3.id = -1;
  Cotree j4;
  j4.id = -1;
  Cotree u1;
  u1.id = -2;
  Cotree u2;
  u2.id = -2;
  Cotree u3;
  u3.id = -2;
  Cotree u4;
  u4.id = -2;
  Cotree u5;
  u5.id = -2;
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
  Cotree v6;
  v6.id = 6;
  Cotree v7;
  v7.id = 7;
  Cotree v8;
  v8.id = 8;
  Cotree v9;
  v9.id = 9;
  Cotree v10;
  v10.id = 10;
  j4.hijos.push_back(&v5);
  j4.hijos.push_back(&v6);
  u5.hijos.push_back(&v9);
  u5.hijos.push_back(&v10);
  u4.hijos.push_back(&v4);
  u4.hijos.push_back(&j4);
  u3.hijos.push_back(&v1);
  u3.hijos.push_back(&v2);
  j3.hijos.push_back(&v8);
  j3.hijos.push_back(&u5);
  j2.hijos.push_back(&v3);
  j2.hijos.push_back(&u4);
  u2.hijos.push_back(&v0);
  u2.hijos.push_back(&u3);
  u1.hijos.push_back(&v7);
  u1.hijos.push_back(&j3);
  j1.hijos.push_back(&u2);
  j1.hijos.push_back(&j2);
  raiz.hijos.push_back(&j1);
  raiz.hijos.push_back(&u1);*/
  
  /*make_cotree(&grafo, &raiz);
  cout << "Imprimo cotree:" << endl;
  imprimirCotree(raiz);
  cout << "Binarizo el cotree y lo imprimo:" << endl;
  binarizar(&raiz);
  imprimirCotree(raiz);
  
  int K_n = 8;
  vector<AristasNodos> sol = vector<AristasNodos>(K_n+1); // Tamanio n+1
  solucion(&raiz, K_n, &sol); // Tamanio n
  cout << "Max aristas: " << sol[K_n].aristas << endl; // Tamanio n
  cout << "Nodos: " << endl;
  vector<int>::iterator inicio = sol[K_n].nodos.begin(); // Tamanio n
  vector<int>::iterator fin = sol[K_n].nodos.end(); // Tamanio n
  while(inicio != fin) {
    cout << *inicio << ", ";
    inicio++;
  }
  cout << endl;*/

  /*cout << "imprimo vector de nodos pertenecientes" << endl;
  vector<int> sol;
  int aristasMax = generar_solucion(&sol, &raiz, 3);
  vector<int>::iterator inicio = sol.begin();
  vector<int>::iterator fin = sol.end();
  while(inicio != fin) {
    cout << *inicio << " ";
    inicio++;
  }
  cout << endl;
  cout << "aristas max:" << aristasMax << endl;*/

  //cout << raiz.hijos[1]->hijos[1]->hijos[1]->aristas;
  /*vector<int>::iterator inicio = raiz.hijos[1]->hijos[1]->nodos.begin();
  vector<int>::iterator fin = raiz.hijos[1]->hijos[1]->nodos.end();
  while(inicio != fin) {
    cout << *inicio << " ";
    inicio++;
  }*/
}
