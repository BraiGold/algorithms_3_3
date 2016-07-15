#include <vector>
#include <iostream>
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

bool EstaYaMapeado(int j, vector<int> mapeo) {
	bool respuesta = false;
	for (int h = 0; h < mapeo.size(); h++){
		if (j == mapeo[h]) {
			respuesta = true;
		}
	}
	return respuesta;
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

vector<int> mejorSolucion;
vector<pair<int, int> > aristasMejorSolucion;
int maximaCantidadDeAristasPosibles;

void MCS(vector<int> mapeo, vector<vector<int> > grafoChico, vector<vector<int> > grafoGrande) { // O(n2+m2) 
	// mapeo va a tener las cosas que mapeamos HASTA EL MOMENTO
	if(aristasMejorSolucion.size() == maximaCantidadDeAristasPosibles){
		return;
	}
	if (mapeo.size() == grafoChico.size()) {// ya mapeamos todo
		// Nos fijamos si mapeo es mejor que mejorSolucion y si lo es hacemos mejorSolucion = mapeo;
		vector<pair<int, int> > solucionProvisoria = calcularConjAristas(mapeo, grafoChico, grafoGrande);
		if (solucionProvisoria.size() > aristasMejorSolucion.size()) {
			aristasMejorSolucion.clear();
			pair<int, int> arista;
			for (int i = 0; i < solucionProvisoria.size(); i++) {
				arista.first = solucionProvisoria[i].first;
				arista.second = solucionProvisoria[i].second;
				aristasMejorSolucion.push_back(arista);
			}
			//int tam = mejorSolucion.size();
			/*for (int i = 0; i < tam; i++) {
				mejorSolucion.pop_back();
			}*/
			mejorSolucion.clear();
			for (int i = 0; i < mapeo.size(); i++) {
				mejorSolucion.push_back(mapeo[i]);
			}
		}
		return;
	}
	for(int i = 0; i < grafoGrande.size(); i++) {
		if(!EstaYaMapeado(i,mapeo)) {
			mapeo.push_back(i);
			MCS(mapeo,grafoChico,grafoGrande);
			mapeo.pop_back();
		}
	}
	return;
}

/*
void MCS(vector<int> mapeo, vector<vector<int> > grafoChico, vector<vector<int> > grafoGrande)  // O(n2+m2) {
	// mapeo va a tener las cosas que mapeamos HASTA EL MOMENTO
	// asumimos G1.size() <= G2.size() para no llenar nuestro codigo de IFs que son FEOS LOS IFs
	if(mapeo.size() == G1.size()) {// ya mapeamos todo
		// Nos fijamos si mapeo es mejor que mejorSolucion y si lo es hacemos mejorSolucion = mapeo;
		return;
	}
	for(int i=0;i<G2.size();i++) {
		if(noEstaYaMapeado(i,mapeo)) {
			mapeo.push_back(i);
			MCS(mapeo,G1,G2); //O(1)
			mapeo.pop_back();
		}
	}
	return;
}

n2 tomado de a n1 = n2!/(n2-n1)!(n1)! esta en O(n2!/(n2-n1)!) = n2 (n2-1) (n2-2) ... (n2-n1+1) < n2 * n2 * n2... = (n2^n1)*n1 

// voy a llamar a MCS(vacio,G1,G2);
*/
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
	vector<vector<int> > grafo1(n1,vector<int>(0));
	vector<vector<int> > grafo2(n2,vector<int>(0));

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

	vector<int> mapeo;
	
	int chico;

	init_time();

	if (n1 > n2) {
		maximaCantidadDeAristasPosibles = n2;
		MCS(mapeo, grafo2, grafo1);
		chico = n2;
	} else {
		maximaCantidadDeAristasPosibles = n1;
		MCS(mapeo, grafo1, grafo2);
		chico = n1;
	}

	tiempo = get_time();

  	if (!pidieronTiempo) { 
		cout << chico << " " << aristasMejorSolucion.size() << endl;
		if(chico == n1){
			for(int i = 0; i < n1; i++){
				cout << i << " ";
			}
			cout << endl;
			for(int i = 0; i < n1; i++){
				cout << mapeo[i] << " ";
			}
			cout << endl;
		}else{
			for(int i = 0; i < n2; i++){
				cout << mapeo[i] << " ";
			}
			cout << endl;
			for(int i = 0; i < n2; i++){
				cout << i << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < aristasMejorSolucion.size(); i++) {
			cout << aristasMejorSolucion[i].first << " " << aristasMejorSolucion[i].second << endl; 
		}
	} else {
    	printf("%.10f ", tiempo);
	}

	return 0;
}