#include <vector>
#include <iostream>
#include <algorithm> //sort , min
#include <sys/time.h>
#include <stdio.h>      /* printf */
#include <set>
#include <queue>
#include <cstdlib>

using namespace std;
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

int randombis() {
	return rand() % 1000 + (rand() % 1000) * 1000 + (rand() % 1000) * 1000000;
}

bool comparacion(pair<int, int> p1, pair<int, int> p2) {
	return (p1.second > p2.second);
} //O(1)

bool aparece(vector<int> mapeo, vector<vector<int > > grafoGrande, int i, int j) {
	int vertice1 = mapeo[i];
	int vertice2 = mapeo[j];
	bool respuesta = false;
	for (int h = 0; h < grafoGrande[vertice1].size(); h++) {
		if (grafoGrande[vertice1][h] == vertice2) {  // me voy al grafo grande y busco si esta la arista (vertice1, vertice2)
			respuesta = true;
		}
	}
	return respuesta;
}//O(n2)

bool yaEsta(vector<pair<int, int> > vec, int i, int j) {
	//esta función es para verificar que no hayamos agregado la arista todavia, es decir, si agregamos (u, v), no queremos que se agregue (v, u) ya que son la misma 
	bool res = false;
	for (int k = 0; k < vec.size(); k++) {
		if ( (vec[k].first == i && vec[k].second == j) || (vec[k].first == j && vec[k].second == i) ) {
			res = true;
		}
	}
	return res;
}//O(n1)

vector<pair<int, int> > calcularConjAristas(vector<int> mapeo, vector<vector<int > > grafoChico, vector<vector<int > > grafoGrande) {
	vector<pair<int, int> > respuesta; //para este mapeo, cual es el subgrafo comun maximo
	pair<int, int> arista;
	for (int i = 0; i < grafoChico.size(); i++) { //nos fijamos si la arista que esta en el grafoChico, aparece en el grafoGrande (con este mapeo)
		if (mapeo[i] != -1) { 
			for (int j = 0; j < grafoChico[i].size(); j++) {
				if(mapeo[grafoChico[i][j]] != -1){ 
					if (aparece(mapeo, grafoGrande, i, grafoChico[i][j]) && !yaEsta(respuesta, i, grafoChico[i][j])) {
						arista.first = i;
						arista.second = grafoChico[i][j]; 
						respuesta.push_back(arista);
					}
				}
			}
		}
	}
	return respuesta;
}


vector<int> MCSgoloso(vector<vector<int> > grafoGrande, vector<vector<int> > grafoChico, vector<pair<int, int> > gradosGrafoGrande, vector<pair<int, int> > gradosGrafoChico) {

	vector<int> mapeo;

	for (int i = 0; i < grafoChico.size(); i++) {
		mapeo.push_back(-1);
	}

	for(int i = 0; i < gradosGrafoChico.size(); i++) {
		mapeo[gradosGrafoChico[i].first] = gradosGrafoGrande[i].first; 
	}

	return mapeo;      
}//O(n1 * n1 * (m1+n1) + n1 + n1)


vector<int> hacerMCSgoloso(vector<vector<int> > grafo1, vector<vector<int> > grafo2, vector<vector<int> > grafo1ordenado, vector<vector<int> > grafo2ordenado, int n1, int n2) {
	vector<pair<int, int> > gradosGrafo1; //vector que en cada posicion tiene (nodo, grado). Al principio cada posicion i del vector tiene (nodo i, grado), pero luego lo ordenamos y esto se deja de cumplir. Pierdo info de aristas
	vector<pair<int, int> > gradosGrafo2; //vector que en cada posicion tiene (nodo, grado). Al principio cada posicion i del vector tiene (nodo i, grado), pero luego lo ordenamos y esto se deja de cumplir.

	pair<int, int> nodoGrado;

	for (int i = 0; i < n1; i++) {//O(n1)
		nodoGrado.first = i;
		nodoGrado.second = grafo1[i].size();
		gradosGrafo1.push_back(nodoGrado);
	}

	for (int i = 0; i < n2; i++) {//O(n2)
		nodoGrado.first = i;
		nodoGrado.second = grafo2[i].size();
		gradosGrafo2.push_back(nodoGrado);
	}

	sort (gradosGrafo1.begin(), gradosGrafo1.end(), comparacion); //O(n1^2)//ordeno los nodos por grado (de mayor a menor)
	sort (gradosGrafo2.begin(), gradosGrafo2.end(), comparacion);//O(n2^2) //ordeno los nodos por grado (de mayor a menor)

	vector<int> mapeoInicial;

	if (n1 > n2) { //el grafo grande es el 1
		mapeoInicial = MCSgoloso(grafo1, grafo2, gradosGrafo1, gradosGrafo2);//O(n1 * n1 * (m1+n1) + n1 + n1)
	} else {
		//el grafo grande es el 2
		mapeoInicial = MCSgoloso(grafo2, grafo1, gradosGrafo2, gradosGrafo1);//O(n1 * n1 * (m1+n1) + n1 + n1)
	}

	return mapeoInicial;
}

bool estaTupla(int a, int b, vector<pair<int, int> > lista){
	bool res = false;
	for(int i = 0; i < lista.size(); i++){
		if((lista[i].first == a && lista[i].second == b) || (lista[i].first == b && lista[i].second == a)){
			res = true;
		}
	}
	return res;
} //O(lista.size())

bool estaTripla(int a, int b, int c, vector<pair<int, pair<int, int> > > lista){
	bool res = false;
	for(int i = 0; i < lista.size(); i++){
		if(lista[i].first == a && lista[i].second.first == b && lista[i].second.second == c){
			res = true;
		}
	}
	return res;
} 

vector<vector<int> > calcularVecindadUnoTipoA(vector<int> mapeo, int cuantosVecinosMiro) {//devuelve una lista con todos los mapeos vecinos
	vector<vector<int> > respuesta;

	vector<pair<int, int> > randoms;
	int r1, r2;
	pair<int, int> par;
	int tamMapeo = (mapeo.size() * (mapeo.size() - 1))/2;
	int c = min(tamMapeo, cuantosVecinosMiro);
	for (int i = 0; i < c; i++) {//O(n1)
		//peso = randombis() %  (max_peso - min_peso + 1) + min_peso;  
		r1 = randombis() % (mapeo.size()); // entre 0 y mapeo.size() - 1
		r2 = randombis() % (mapeo.size()); // entre 0 y mapeo.size() - 1
		while(r1 == r2 || estaTupla(r1, r2, randoms)) { //O(n1)
			r1 = randombis() % (mapeo.size());
			r2 = randombis() % (mapeo.size());
		}
		par.first = r1;
		par.second = r2;
		randoms.push_back(par);
	}
	
	int a, b;
	for (int i = 0; i < randoms.size(); i++) { //O(n1)
		vector<int> mapeoVecino;
		for (int j = 0; j < mapeo.size(); j++) { //O(n1)// mapeoVecino = mapeo
			mapeoVecino.push_back(mapeo[j]);
		}

		a = randoms[i].first;
		b = randoms[i].second;

		mapeoVecino[a] = mapeo[b];
		mapeoVecino[b] = mapeo[a];

		respuesta.push_back(mapeoVecino);
	}	
	return respuesta;
}//O(n1^2)

//esta es la ultima version de vecindadTipoB
vector<vector<int> > calcularVecindadTipoB(vector<int> mapeo, int totalNodosGrafoGrande, int cuantosMiro) {//devuelve una lista con todos los mapeos vecinos
	vector<vector<int> > respuesta;

	vector<pair<int, int> > randoms;
	int r1, r2;
	pair<int, int> par;
	int tamMapeo = mapeo.size();
	if (mapeo.size() == totalNodosGrafoGrande)
		tamMapeo = 0;
	int c = min(tamMapeo, cuantosMiro);

	vector<int> auxiliar = mapeo;
	sort(auxiliar.begin(),auxiliar.end());

	vector<int> noMapeados;
	int indice1 = 0;
	for(int i=0;i<totalNodosGrafoGrande;i++) {
		if(indice1 < auxiliar.size() || auxiliar[indice1] != i) {
			noMapeados.push_back(i);
		} else {
			indice1++;
		}
	}

	for (int i = 0; i < c; i++) {
		//peso = randombis() %  (max_peso - min_peso + 1) + min_peso;  
		r1 = randombis() % (mapeo.size()); // entre 0 y mapeo.size() - 1
		//r2 = randombis() % (totalNodosGrafoGrande - mapeo.size()) + mapeo.size() - 1; // entre mapeo.size() - 1 y totalNodosGrafoGrande
		r2 = noMapeados[randombis()%noMapeados.size()]; 

		while(estaTupla(r1, r2, randoms)) {
			r1 = randombis() % (mapeo.size());
			//r2 = randombis() % (totalNodosGrafoGrande + 1); //entre 0 y totalNodosGrafoGrande
			//r2 = randombis() % (totalNodosGrafoGrande - mapeo.size() + 1) + mapeo.size(); //(totalNodosGrafoGrande - mapeo.size()) + mapeo.size() - 1; // entre mapeo.size() y totalNodosGrafoGrande //SOY LU CAMBIO ESTO
			r2 = noMapeados[randombis()%noMapeados.size()]; 
		}
		par.first = r1;
		par.second = r2;
		randoms.push_back(par);
	}
	
	int a, b;
	for (int i = 0; i < randoms.size(); i++) {
	vector<int> mapeoVecino;
		for (int j = 0; j < mapeo.size(); j++) { // mapeoVecino = mapeo
			mapeoVecino.push_back(mapeo[j]);
		}

		a = randoms[i].first;
		b = randoms[i].second;

		mapeoVecino[a] = b;

		respuesta.push_back(mapeoVecino);
	}	

	return respuesta;
}

set<vector<int> > tabuPorMapeo; //es la lista con los mapeos a los que no puedo entrar ordenada por mapeo, es rapido mirar si uno esta o no.
queue<vector<int> > tabuCola; //es la lista con los mapeos a los que no puedo entrar ordenada por orden en el que se los visita. Sacar el mas viejo es facil y agregar el nuevo tambien

bool estaEnTabu(vector<int> mapeo){
	return tabuPorMapeo.find(mapeo) != tabuPorMapeo.end();
/*	set<vector<int> >::iterator it;
	//iterator it;
	it = tabuPorMapeo.find(mapeo);

	bool res = (tabuPorMapeo.end() != it);
	return res;*/
}
 
vector<int> dameElMejorNoTabu(vector<vector<int> > vecindadA, vector<vector<int> > vecindadB, vector<vector<int> > grafoChico, vector<vector<int> > grafoGrande, int cuantosMiro) { //esta funcion devuelve el mejor de las opciones de vecinos pero que no se encuentre en la lista tabu. Como a veces puede tener demasiados vecinos un mapeo hay un maximo que puedo mirar.
	vector<pair<int,int> > conjAristas;
	int maximoTamanoHastaAhora = 0;
	int cantAristasMapeoNuevo;
	int indice = 0;
	vector<vector<int> > vecindadEntera = vecindadA;
	for(int i=0;i<vecindadB.size();i++) {
		vecindadEntera.push_back(vecindadB[i]);
	}
	random_shuffle(vecindadEntera.begin(), vecindadEntera.end());
	vecindadEntera.resize(cuantosMiro);
	for (int i = 0; i < vecindadEntera.size() ; i++) {
		if(!estaEnTabu(vecindadEntera[i])) {
			conjAristas = calcularConjAristas(vecindadEntera[i], grafoChico, grafoGrande);
			cantAristasMapeoNuevo = conjAristas.size();
			if(cantAristasMapeoNuevo > maximoTamanoHastaAhora){
				indice = i;
				maximoTamanoHastaAhora = cantAristasMapeoNuevo;
			}
		}
	}
	return vecindadEntera[indice];
}//O(n1)


vector<int> MCStabu(vector<int> mapeo, vector<vector<int> > grafoChico, vector<vector<int> > grafoGrande, int cuantosVecinosMiro, int maxTamTabu, int k) {//k = No se encontro una mejora en las ultimas k iteraciones.

	vector<int> mejorMapeo;
	for(int i = 0; i < mapeo.size(); i++){ //mejorMapeo = mapeo
		mejorMapeo.push_back(mapeo[i]);
	}

	vector<pair<int, int> > conjAristasMejorMapeo = calcularConjAristas(mejorMapeo, grafoChico, grafoGrande); 

	vector<vector<int> > vecindadA = calcularVecindadUnoTipoA(mapeo, cuantosVecinosMiro);//O(n1²)
	vector<vector<int> > vecindadB = calcularVecindadTipoB(mapeo, grafoGrande.size(), cuantosVecinosMiro);//O(n1²)
	
	vector<int> mejorVecino;
	vector<pair<int, int> > conjAristasMejorVecino;
	vector<int> mapeoQueTengoQueSacar;
	int j = 0;
	while(j < k){ 
		mejorVecino = dameElMejorNoTabu(vecindadA, vecindadB, grafoChico, grafoGrande, cuantosVecinosMiro);//O(n1)
		conjAristasMejorVecino = calcularConjAristas(mejorVecino, grafoChico, grafoGrande); 
		if(conjAristasMejorVecino.size() > conjAristasMejorMapeo.size()){ //el nuevo mapeo es mejor que lo que tenia antes
			j = -1;
			//mejorMapeo = mejorVecino:
			for(int i = 0; i < mejorMapeo.size(); i++){
				mejorMapeo[i] = mejorVecino[i];
			}
			conjAristasMejorMapeo = conjAristasMejorVecino;

		}
		if(tabuCola.size() == maxTamTabu){ //me fijo si la lista tabu ya tiene el tamaño máximo
			mapeoQueTengoQueSacar = tabuCola.front();
			tabuCola.pop();
			tabuPorMapeo.erase(mapeoQueTengoQueSacar);
		}
		tabuCola.push(mejorVecino);
		tabuPorMapeo.insert(mejorVecino);
		vecindadA = calcularVecindadUnoTipoA(mejorVecino, cuantosVecinosMiro);//O(n1^2)
		vecindadB = calcularVecindadTipoB(mejorVecino, grafoGrande.size(), cuantosVecinosMiro);
		j++;
	}
	return mejorMapeo;
}


int main(int argc, char* argv[]) {
	bool pidieronTiempo = false; 
	double tiempo;
	if (argc > 4) {
	  if (argv[4] == string("-t")) {
	    pidieronTiempo = true;
	  }
	}
	if (argc < 4){
		cout << "faltan parametros" << endl;
		return 0;
	}

	int cuantosVecinosMiro = atoi(argv[1]);
	int maxTamTabu = atoi(argv[2]); 
	int k = atoi(argv[3]);


	int m1, n1, m2, n2;
	cin >> n1 >> m1 >> n2 >> m2;

	vector<vector<int> > grafo1;
	vector<vector<int> > grafo2;
	vector<vector<int> > grafo1ordenado;
	vector<vector<int> > grafo2ordenado;

	vector<int> vacio;

	for (int i = 0; i < n1; i++) {
		grafo1.push_back(vacio);
		grafo1ordenado.push_back(vacio);
	}

	for (int i = 0; i < n2; i++) {
		grafo2.push_back(vacio);
		grafo2ordenado.push_back(vacio);	
	}

	int v1, v2;

	for (int i = 0; i < m1; i++) {
		cin >> v1 >> v2;
		grafo1[v1].push_back(v2);
		grafo1[v2].push_back(v1);
	}

	for (int i = 0; i < m2; i++) {
		cin >> v1 >> v2;
		grafo2[v1].push_back(v2);
		grafo2[v2].push_back(v1);
	}

	init_time();

	vector<int> mejorMapeo;
	vector<int> mapeoInicial = hacerMCSgoloso(grafo1, grafo2, grafo1ordenado, grafo2ordenado, n1, n2);
	vector<pair<int, int> > resultado;
	int chico;


	if(n1 < n2) {
		mejorMapeo = MCStabu(mapeoInicial, grafo1, grafo2, cuantosVecinosMiro, maxTamTabu, k);
		resultado = calcularConjAristas(mejorMapeo, grafo1, grafo2);
		chico = n1;
	}else{
		mejorMapeo = MCStabu(mapeoInicial, grafo2, grafo1, cuantosVecinosMiro, maxTamTabu, k);
		resultado = calcularConjAristas(mejorMapeo, grafo2, grafo1);
		chico = n2;
	}


	tiempo = get_time();

  	if (!pidieronTiempo) { 
		cout << chico << " " << resultado.size() << endl;
		for(int i = 0; i < resultado.size(); i++){
			cout << resultado[i].first << " " << resultado[i].second << endl;
		}
	} else {
    	printf("%.10f ", tiempo);
	}
	return 0;
}