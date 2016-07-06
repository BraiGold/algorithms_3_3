#include <vector>
#include <iostream>
#include <algorithm> //sort

using namespace std;

bool comparacion(pair<int, int> p1, pair<int, int> p2) {
	return (p1.second > p2.second);
}

bool esta(int a, vector<int> vec) {
	bool res = false;
	for (int j = 0; j < vec.size(); j++) {
		if (vec[j] == a) {
			res = true;
		}
	}
	return res;
}
bool yaEsta(vector<pair<int, int> > vec, int i, int j) {
	//esta función es para verificar que no hayamos agregado la arista todavia, es decir, si agregamos (u, v), no queremos que se agregue (v, u) ya que son la misma ni que este (u,v)
	bool res = false;
	for (int k = 0; k < vec.size(); k++) {
		if ( (vec[k].first == i && vec[k].second == j) || (vec[k].first == j && vec[k].second == i) ) {
			res = true;
		}
	}
	return res;
}

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
}

vector<pair<int, int> > calcularConjAristas(vector<int> mapeo, vector<vector<int > > grafoChico, vector<vector<int > > grafoGrande) {
	vector<pair<int, int> > respuesta; //para este mapeo, cual es el subgrafo comun maximo
	pair<int, int> arista;
/*
	cerr << "grafoChico:" << endl;
	for(int i = 0; i < grafoChico.size(); i++) {
		for(int j = 0; j < grafoChico[i].size(); j++) {
			cerr << "(" << i << ", " << grafoChico[i][j] << ")" << endl;
		}
	}

	cerr << "grafoGrande:" << endl;
	for(int i = 0; i < grafoGrande.size(); i++) {
		for(int j = 0; j < grafoGrande[i].size(); j++) {
			cerr << "(" << i << ", " << grafoGrande[i][j] << ")" << endl;
		}
	}
*/
	//cerr << "la respuesta esta llena de esta caca: " << endl;
	//cerr << "la respuesta tiene tam: " << respuesta.size() <<  endl;

	//for (int h = 0; h < respuesta.size(); h++) {
	//cerr << "(" << respuesta[h].first << ", " << respuesta[h].second << ")" << endl;
	//	}
	//DEBUG//cerr << "----------------------------" << endl;
	//DEBUG//cerr << "Calcular Conjunto de Aristas con Mapeo: " << endl;
	//DEBUG//for (int h = 0; h < mapeo.size(); h++) {
	//DEBUG//	cerr << "El nodo " << h << " del primer grafo es la " << mapeo[h] << " del segundo" << endl;
	//DEBUG//}
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
	/*cerr << "la respuesta para este mapeo es: " << endl;
	for (int h = 0; h < respuesta.size(); h++) {
		cerr << "(" << respuesta[h].first << ", " << respuesta[h].second << ")" << endl;
		}*/
	return respuesta;
}


void ordenarGrafo(vector<vector<int> > &grafoOriginal, vector<pair<int, int> > grafoPorGrados) {
	vector<vector<int> > grafoProvisorio;
	vector<int> vacio;
	for (int i = 0; i < grafoOriginal.size(); i++) {
		grafoProvisorio.push_back(vacio);
	}
	for (int i = 0; i < grafoOriginal.size(); i++) {
		for (int j = 0; j < grafoPorGrados.size(); j++) {
			if(esta(grafoPorGrados[j].first, grafoOriginal[i])) {
				grafoProvisorio[i].push_back(grafoPorGrados[j].first);
			}
		}
	}
	for (int i = 0; i < grafoOriginal.size(); i++) {
		for (int j = 0; j < grafoOriginal[i].size(); j++) {
			grafoOriginal[i][j] = grafoProvisorio[i][j];
		}
	}

}

/*
vector<int> DFS(vector<vector<int> > adyacencias) { 
	vector<int> pila;
	vector <int> orden;
	//inicializo el vector orden con 0
	for (int i = 0; i < adyacencias.size(); i++) {
		orden.push_back(-1);
	}

	//cerr << "despues de inicializar la pila" << endl;

	pila.push_back(0);
	int w;
	int ord = 0;

	while (pila.size() > 0) {
		w = pila.back();
		pila.pop_back();
		ord++;
		orden[w]= ord;
		//apilo todos los vecinos de w
		for (int j = 0; j < adyacencias[w].size(); j++) {
			if (orden[adyacencias[w][j]] < 0) {
				pila.push_back(adyacencias[w][j]);
			}
		}
		////cerr << "estoy en una iteracion del while" << endl;
	}

	return orden; 
}*/
int EldeMayorGradoSinUsarDelGGrande(vector<int> mapeo, vector<pair<int, int> > gradosGrafoGrande) {

}

vector<pair<int, int> > MCSgoloso(vector<vector<int> > grafoGrande, vector<vector<int> > grafoChico, vector<pair<int, int> > gradosGrafoGrande, vector<pair<int, int> > gradosGrafoChico) {

	//vector<int> pilaChico; //pila del grafo chico
	//vector<int> pilaGrande; //pila del grafo grande
	vector<int> mapeo;
	vector<int> pila;

	for (int i = 0; i < grafoChico.size(); i++) {
		mapeo.push_back(-1);
	}

	//pilaChico.push_back(grafoChico[0]);
	//pilaGrande.push_back(grafoGrande[0]);

	mapeo[gradosGrafoChico[0].first] = gradosGrafoGrande[0].first;
	pila.push_back(gradosGrafoChico[0].first);
	int j;
	int indice;

	while(noHayMapeoEnMenosUno(mapeo)){

		indice = buscarMayorGradoSinMapear(mapeo, gradosGrafoChico);
		mapeo[inice] = EldeMayorGradoSinUsarDelGGrande(mapeo, gradosGrafoGrande);

		while(pila.size() > 0) { 
			j = pila.back();
			pila.pop_back();
			for(int i = 0; i < min(grafoChico[j].size(), grafoGrande[mapeo[j]].size()); i++) {//hasta el que tiene menos vecinos
				if(mapeo[grafoChico[j][i]] == -1){ //mapeo los vecinos con los vecinos
					mapeo[grafoChico[j][i]] = grafoGrande[mapeo[j]][i];
					pila.push_back(grafoChico[j][i]);
				}
			}
		}

	}

	cerr << "----------------------------" << endl;
	cerr << "Calcular Conjunto de Aristas con Mapeo: " << endl;
	for (int h = 0; h < mapeo.size(); h++) {
		cerr << "El nodo " << h << " del primer grafo es la " << mapeo[h] << " del segundo" << endl;
	}

	vector<pair<int, int> > respuesta;

	respuesta = calcularConjAristas(mapeo, grafoChico, grafoGrande);


	return respuesta;      
}

/*

	int nodoDelChico, nodoDelGrande;

	while(pilaChico.size()>0) {
		nodoDelChico = pilaChico.back();
		nodoDelGrande = pilaGrande.back();
		//respuesta[nodoDelChico] = nodoDelGrande;
		if (grafoChico[nodoDelChico].size() == grafoGrande[nodoDelGrande].size()) { //tienen la misma cantidad de vecinos
			//mapeo todos			

		} else {
			if (grafoChico[nodoDelchico].size() < grafoGrande[nodoDelGrande.size()]) {//el chico tiene menos cantidad de vecinos. Esto puede ser que sea lo mismo que lo de arriba, o sea, mapear todos. Pero quizás los que me sobran del grande, me sirven para despues, asi que ojo

			} else {
				//el chico tiene más cantidad de vecinos, entonces que hago? No tengo en cuenta los que me sobran? los miro despues? 
			}
		}
	}
*/




int main() {

	int m1, n1, m2, n2;
	cin >> n1 >> m1 >> n2 >> m2;
	vector<vector<int> > grafo1;
	vector<vector<int> > grafo2;
	//vector<vector<int> > grafo1ordenado;
	//vector<vector<int> > grafo2ordenado;

	vector<int> vacio;

	for (int i = 0; i < n1; i++) {
		grafo1.push_back(vacio);
	//	grafo1ordenado.push_back(vacio);
	}

	for (int i = 0; i < n2; i++) {
		grafo2.push_back(vacio);
	//	grafo2ordenado.push_back(vacio);	
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

	vector<pair<int, int> > gradosGrafo1; //vector que en cada posicion tiene (nodo, grado). Al principio cada posicion i del vector tiene (nodo i, grado), pero luego lo ordenamos y esto se deja de cumplir. Pierdo info de aristas
	vector<pair<int, int> > gradosGrafo2; //vector que en cada posicion tiene (nodo, grado). Al principio cada posicion i del vector tiene (nodo i, grado), pero luego lo ordenamos y esto se deja de cumplir.

	pair<int, int> nodoGrado;

	for (int i = 0; i < n1; i++) {
		nodoGrado.first = i;
		nodoGrado.second = grafo1[i].size();
		gradosGrafo1.push_back(nodoGrado);
	}

	for (int i = 0; i < n2; i++) {
		nodoGrado.first = i;
		nodoGrado.second = grafo2[i].size();
		gradosGrafo2.push_back(nodoGrado);
	}

	sort (gradosGrafo1.begin(), gradosGrafo1.end(), comparacion); //ordeno los nodos por grado (de mayor a menor)
	sort (gradosGrafo2.begin(), gradosGrafo2.end(), comparacion); //ordeno los nodos por grado (de mayor a menor)


/*// DEBUG------------------------------------------------------------------
	cout << "Grafo 1 (nodos) ordenado por grados: " << endl;
	for(int i = 0; i < n1; i++) {
		cout << "(" << gradosGrafo1[i].first << ", " << gradosGrafo1[i].second << ")" << endl;
	}

	cout << "Grafo 2 (nodos) ordenado por grados: " << endl;
	for(int i = 0; i < n2; i++) {
		cout << "(" << gradosGrafo2[i].first << ", " << gradosGrafo2[i].second << ")" << endl;
	}

//	------------------------------------------------------------------ DEBUG */

	ordenarGrafo(grafo1, gradosGrafo1); //cada posicion es un nodo, y adentro tiene la lista de sus vecinos. Ordenamos esa lista por grado. 
	ordenarGrafo(grafo2, gradosGrafo2); //cada posicion es un nodo, y adentro tiene la lista de sus vecinos. Ordenamos esa lista por grado. 


/*// DEBUG------------------------------------------------------------------

	cout << "Grafo 1 ordenado por grados (con aristas tambien)" << endl;
	for (int i = 0; i < grafo1.size(); i++) {
		cout << "Vecinos del nodo " << i << ":" << endl;
		for (int j = 0; j < grafo1[i].size(); j++) {
			cout << grafo1[i][j] << " - " ;
		}
		cout << endl;
	}

	cout << "Grafo 2 ordenado por grados (con aristas tambien)" << endl;
	for (int i = 0; i < grafo2.size(); i++) {
		cout << "Vecinos del nodo " << i << ":" << endl;
		for (int j = 0; j < grafo2[i].size(); j++) {
			cout << grafo2[i][j] << " - " ;
		}
		cout << endl;
	}
//	------------------------------------------------------------------ DEBUG */

	vector<pair<int, int> > respuesta;

	if (n1 > n2) { //el grafo grande es el 1
		respuesta = MCSgoloso(grafo1, grafo2, gradosGrafo1, gradosGrafo2);
		cout << n2 << " " << respuesta.size() << endl;
	} else {
		//el grafo grande es el 2
		respuesta = MCSgoloso(grafo2, grafo1, gradosGrafo2, gradosGrafo1);
		cout << n1 << " " << respuesta.size() << endl;
	}


	for(int i = 0; i < respuesta.size(); i++){
		cout << respuesta[i].first << " " << respuesta[i].second << endl;
	}

	return 0;
}
