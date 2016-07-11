#include <vector>
#include <iostream>
#include <algorithm> //sort
#include <sys/time.h>
#include <stdio.h>      /* printf */


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
}//O(m1)

bool aparece(vector<int> mapeo, vector<vector<int > > grafoGrande, int i, int j) {
	int vertice1 = mapeo[i];
	int vertice2 = mapeo[j];
	bool respuesta = false;
	for (int h = 0; h < grafoGrande[vertice1].size(); h++) { // a lo sumo n vecinos, no m! porque m puede ser O(n^2)
		if (grafoGrande[vertice1][h] == vertice2) {  // me voy al grafo grande y busco si esta la arista (vertice1, vertice2)
			respuesta = true;
		}
	}
	return respuesta;
} //O(n2)

vector<pair<int, int> > calcularConjAristas(vector<int> mapeo, vector<vector<int > > grafoChico, vector<vector<int > > grafoGrande) {
	vector<pair<int, int> > respuesta; //para este mapeo, cual es el subgrafo comun maximo
	pair<int, int> arista;

	for (int i = 0; i < grafoChico.size(); i++) { //O(n1)//nos fijamos si la arista que esta en el grafoChico, aparece en el grafoGrande (con este mapeo)
		if (mapeo[i] != -1) { 
			for (int j = 0; j < grafoChico[i].size(); j++) {//O(n1)
				if(mapeo[grafoChico[i][j]] != -1){ 
					if (aparece(mapeo, grafoGrande, i, grafoChico[i][j]) && !yaEsta(respuesta, i, grafoChico[i][j])) { //O(m1+n2)
						arista.first = i;
						arista.second = grafoChico[i][j]; 
						respuesta.push_back(arista);
					}
				}
			}
		}
	}

	return respuesta;
}//O(n1^2 * (m1+n2))


vector<pair<int, int> > MCSgoloso(vector<vector<int> > grafoGrande, vector<vector<int> > grafoChico, vector<pair<int, int> > gradosGrafoGrande, vector<pair<int, int> > gradosGrafoChico) {

	vector<int> mapeo;

	for (int i = 0; i < grafoChico.size(); i++) {//O(n1)
		mapeo.push_back(-1);
	}

	for(int i = 0; i < gradosGrafoChico.size(); i++) {//O(n1)
		mapeo[gradosGrafoChico[i].first] = gradosGrafoGrande[i].first; 
	}

	vector<pair<int, int> > respuesta;
	respuesta = calcularConjAristas(mapeo, grafoChico, grafoGrande);//O(n1 * ni * (m1+n1))
	return respuesta;      
}//O(n1^2 * (m1+n2) + 2n1)






int main(int argc, char* argv[]) {
	bool pidieronTiempo = false; 
	double tiempo;
	if (argc > 1) {
	  if (argv[1] == string("-t")) {
	    pidieronTiempo = true;
	  }
	}
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

	init_time();

	vector<pair<int, int> > gradosGrafo1;//O(1) //vector que en cada posicion tiene (nodo, grado). Al principio cada posicion i del vector tiene (nodo i, grado), pero luego lo ordenamos y esto se deja de cumplir. Pierdo info de aristas
	vector<pair<int, int> > gradosGrafo2;//O(1) //vector que en cada posicion tiene (nodo, grado). Al principio cada posicion i del vector tiene (nodo i, grado), pero luego lo ordenamos y esto se deja de cumplir.

	pair<int, int> nodoGrado;//O(1)


	for (int i = 0; i < n1; i++) {//O(n1)
		nodoGrado.first = i;
		nodoGrado.second = grafo1[i].size();
		gradosGrafo1.push_back(nodoGrado);
	}

	for (int i = 0; i < n2; i++) { //O(n2)
		nodoGrado.first = i;
		nodoGrado.second = grafo2[i].size();
		gradosGrafo2.push_back(nodoGrado);
	}

	sort (gradosGrafo1.begin(), gradosGrafo1.end(), comparacion); // O(n1 log n1)//ordeno los nodos por grado (de mayor a menor)
	sort (gradosGrafo2.begin(), gradosGrafo2.end(), comparacion); //O(n2 log n2)//ordeno los nodos por grado (de mayor a menor)

	vector<pair<int, int> > respuesta;
	int chico;

	if (n1 > n2) { //el grafo grande es el 1
		respuesta = MCSgoloso(grafo1, grafo2, gradosGrafo1, gradosGrafo2);
		chico = n2;
	} else {
		//el grafo grande es el 2
		respuesta = MCSgoloso(grafo2, grafo1, gradosGrafo2, gradosGrafo1);
		chico = n1;
	}


	tiempo = get_time();

  	if (!pidieronTiempo) { 
		cout << chico << " " << respuesta.size() << endl;
		for(int i = 0; i < respuesta.size(); i++){
			cout << respuesta[i].first << " " << respuesta[i].second << endl;
		}

	} else {
    	printf("%.10f ", tiempo);
	}

	return 0;
}
