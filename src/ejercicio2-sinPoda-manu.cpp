#include <vector>
#include <iostream>

using namespace std;

bool estaRepetido(int j, vector<int> mapeo, int k) {
	bool respuesta = false;
	for (int h = 0; h < k; h++){
		if (j == mapeo[h]) {
			respuesta = true;
		}
	}
	return respuesta;
}

bool estanTodosVacios(vector<vector<int > > verticesPosibles) {
	bool respuesta = true;
	for (int i = 0; i < verticesPosibles.size(); i++) {
		if (verticesPosibles[i].size() != 0) {
			respuesta = false;
		}
	}
	return respuesta;
}

bool aparece(vector<int> mapeo, vector<vector<int > > grafoGrande, int i, int j) {
	int vertice1 = mapeo[i];
	int vertice2 = mapeo[j];
	bool respuesta = false;
	for (int i = 0; i < grafoGrande[vertice1].size(); i++) {
		if (grafoGrande[vertice1][i] == vertice2) {
			respuesta = true;
		}
	}
	return respuesta;
}

bool yaEsta(vector<pair<int, int> > vec, int i, int j) {
	//esta función es para verificar que no hayamos agregado la arista todavia, es decir, si agregamos (u, v), no queremos que se agregue (v, u) ya que son la misma 
	bool res = false;
	for (int k = 0; k < vec.size(); k++) {
		if ( (vec[k].first == i && vec[k].second == j) || (vec[k].first == j && vec[k].second == i) ) {
			res = true;
		}
	}
	return res;
}

vector<pair<int, int> > calcularConjAristas(vector<int> mapeo, vector<vector<int > > grafoChico, vector<vector<int > > grafoGrande) {
	vector<pair<int, int> > respuesta; //para este mapeo, cual es el subgrafo comun maximo
	pair<int, int> arista;
	cerr << "----------------------------" << endl;
	cerr << "Calcular Conjunto de Aristas con Mapeo: " << endl;
	for (int h = 0; h < mapeo.size(); h++) {
		cerr <<  mapeo[h];
	}
	cerr << endl;
	for (int i = 0; i < grafoChico.size(); i++) { //nos fijamos si la arista que esta en el grafoChico, aparece en el grafoGrande (con este mapeo)
		for (int j = 0; j < grafoChico[i].size(); j++) {
			if (aparece(mapeo, grafoGrande, i, grafoChico[i][j]) && !yaEsta(respuesta, i, grafoChico[i][j])) { //cambie j por grafoChico[i][j] y agregue "!yaEsta" . Manu
				arista.first = i;
				arista.second = grafoChico[i][j]; //cambie j por grafoChico[i][j]
				respuesta.push_back(arista);
			}
		}
	}
	cerr << "el tamaño de la respuesta para este mapeo es: "<< respuesta.size() << endl;
	return respuesta;
}

vector<pair<int, int > > MCS(vector<int> mapeo, vector<vector<int > > verticesPosibles, vector<pair<int, int> > mejorActual, int tamGrande, vector<vector<int > > grafoChico, vector<vector<int > > grafoGrande) { //en mejorActual tengo el conjunto de aristas que representa el MCS hasta el momento
	cerr << "el tamaño de la respuesta hasta el momento: "<< mejorActual.size() << endl;
	if (estanTodosVacios(verticesPosibles)) {
		return mejorActual;
	} else {
		if (verticesPosibles[verticesPosibles.size()-1].size() == 0) { // esta vacio el ultimo?
			int ultimoNoVacio;
			cerr << "esta vacio el ultimo" << endl;
			for (int i = verticesPosibles.size() - 1; i >= 0; i--) { //buscamos el ultimo no vacio
				if (verticesPosibles[i].size() != 0) {
					ultimoNoVacio = i;
					break;
				}
			}
			int dameUno = verticesPosibles[ultimoNoVacio].back();
			verticesPosibles[ultimoNoVacio].pop_back(); //sinUno
			mapeo[ultimoNoVacio] = dameUno;
			for (int k = ultimoNoVacio + 1; k < mapeo.size(); k++) { //llenamos todos los conjuntos siguientes (ya que todos estan vacios)
				for (int j = 0; j < tamGrande; j++) {
					if (!estaRepetido(j, mapeo, k)) {
						verticesPosibles[k].push_back(j);
					}					
				}
				dameUno = verticesPosibles[k].back();
				verticesPosibles[k].pop_back(); //sinUno
				mapeo[k] = dameUno;
			}
			cerr << "ya llene los conjuntos siguientes" << endl;
		} else {
			cerr << "NOOO esta vacio el ultimo" << endl;
			int dameUno = verticesPosibles[verticesPosibles.size()-1].back();
			verticesPosibles[verticesPosibles.size()-1].pop_back(); //sinUno
			mapeo[verticesPosibles.size()-1] = dameUno;
		}
		cerr << "estoy por llamar a calcularconjAristas" << endl;
		vector<pair<int, int> > nuevasAristas = calcularConjAristas(mapeo, grafoChico, grafoGrande);
		cerr << "volvi de calcularconjAristas" << endl;
		vector<pair<int, int > > respuesta;
		if (nuevasAristas.size() > mejorActual.size() ) {
			cerr << "estoy por llamar de nuevo a MCS y el mejor es nuevas aristas" << endl;
			respuesta = MCS(mapeo, verticesPosibles,nuevasAristas,tamGrande, grafoChico, grafoGrande);
		} else {
			cerr << "estoy por llamar de nuevo a MCS y el mejor es mejorActual. MejorActual:" << endl;

			respuesta = MCS(mapeo, verticesPosibles,mejorActual,tamGrande, grafoChico, grafoGrande);
		}
		return respuesta;
	}

}

int main() {
	int m1, n1, m2, n2;
	cin >> n1 >> m1 >> n2 >> m2;
	vector<vector<int> > grafo1;
	vector<vector<int> > grafo2;

	vector<int> vacio;

	for (int i = 0; i < n1; i++) {
		grafo1.push_back(vacio);
	}

	for (int i = 0; i < n2; i++) {
		grafo2.push_back(vacio);
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

	vector<vector<int > > verticesPosibles;
	vector<int> mapeo;
	if (n1 < n2) {
		for (int i = 0; i < n1; i++) {
			mapeo.push_back(i);
			verticesPosibles.push_back(vacio);
			for (int k = i + 1; k < n2; k++) {
				verticesPosibles[i].push_back(k);
			}
		}
	} else {
		for (int i = 0; i < n2; i++) {
			mapeo.push_back(i);
			verticesPosibles.push_back(vacio);
			for (int k = i + 1; k < n1; k++) {
				verticesPosibles[i].push_back(k);
			}
		}
	}
	
	vector<pair<int, int> > mejorActual;
	vector<pair<int, int> > maxcomsub;

	//MCS(vector<int> mapeo, vector<vector<int > > verticesPosibles, vector<pair<int, int> > mejorActual, int tamGrande, vector<vector<int > > grafoChico, vector<vector<int > > grafoGrande)
	if (n1 > n2) {
		mejorActual = calcularConjAristas(mapeo, grafo2, grafo1);
		maxcomsub = MCS(mapeo, verticesPosibles, mejorActual, n1, grafo2, grafo1);
		cerr << "despues de MCS" << endl;
	} else {
		mejorActual = calcularConjAristas(mapeo, grafo1, grafo2);
		maxcomsub = MCS(mapeo, verticesPosibles, mejorActual, n2, grafo1, grafo2);
		cerr << "despues de MCS" << endl;

	}

	cout << "Respuesta: " << endl;

	for (int i = 0; i < maxcomsub.size(); i++) {
		cout << "(" << maxcomsub[i].first << ", " << maxcomsub[i].second << ")" << endl; 
	}

	return 0;
}