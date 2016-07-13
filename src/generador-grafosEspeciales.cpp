#include <iostream>     //cin cout
#include <stdio.h>      // printf fopen fclose fputs 
#include <stdlib.h>     //
#include <string>       //to_string
#include <vector>
#include <algorithm>    // std::sort

using namespace std;

bool yaEsta(int i, int j, vector<pair<int, int> > aristas) {
	int h = 0;
	bool loEncontre = false;
	while(h < aristas.size() && !loEncontre) {
		if ( (aristas[h].first == i && aristas[h].second == j) || (aristas[h].first == j && aristas[h].second == i) ) {
			loEncontre = true;
		}
		h++;
	}
	return loEncontre;
}

int randombis() {
	return rand() % 1000 + (rand() % 1000) * 1000 + (rand() % 1000) * 1000000;
}

vector<pair<int,int> > union1(vector<pair<int,int> > g1, int n1, vector<pair<int,int> > g2, int n2) {
	vector<pair<int,int> > respuesta = g1;
	pair<int,int> arista;
	for(int i = 0; i < g2.size(); i++) {
		arista.first = g2[i].first + n1;
		arista.second = g2[i].second + n1;
		respuesta.push_back(arista);
	}
	return respuesta;
}

vector<pair<int,int> >  join(vector<pair<int,int> > g1, int n1, vector<pair<int,int> > g2, int n2) {
	vector<pair<int,int> > respuesta = g1;
	pair<int,int> arista;
	for(int i = 0; i < g2.size(); i++) {
		arista.first = g2[i].first + n1;
		arista.second = g2[i].second + n1;
		respuesta.push_back(arista);
	}
	for (int i = 0; i < n1; i++) {
		for(int j = 0; j < n2; j++) {
			arista.first = i;
			arista.second = j + n1;
			respuesta.push_back(arista);
		}
	}
	return respuesta;

}

vector<pair<int,int> > dameCografo(int n) {
    //rand = randombis() %  (max - min + 1) + min; 
 	vector<pair<int,int> >res;
	if (n != 1){
		int random = randombis() % 	2; //entre 0 y 1
		int n1 = randombis() % (n - 1) + 1; //entre 0 y n-1
		int n2 = n - n1;
		vector<pair<int,int> > G1 = dameCografo(n1);
		vector<pair<int,int> > G2 = dameCografo(n2);
		if(random == 0) {
			res = join(G1, n1, G2, n2);
		} else{
			res = union1(G1, n1, G2, n2);
		}
	}
	return res;
}



vector<pair<int,int> > generarArbol(int n) {
	
	vector<bool> loUse;
	vector<pair<int,int> > aristas;


		time_t seconds;
		time(&seconds);
		srand((unsigned int) seconds);
	
		int i;
		int j;

		for (int h = 0; h < n; h++) {
			loUse.push_back(false);
		}

		i = randombis() % n;
		j = randombis() % n;

		while (i == j) {
			j = randombis() % n;
		}

		loUse[j] = true;
		loUse[i] = true;
		pair<int, int> arista;
		arista.first = i;
		arista.second = j;
		aristas.push_back(arista);		

		for (int h = 1; h < n -1; h++) { //como es un árbol, tiene n-1 aristas

			i = randombis() % n;    //(n - 1 - 0 + 1) + 0   
			j = randombis() % n;    //(n - 1 - 0 + 1) + 0   

			while (loUse[i] == false) {
				i = randombis() % n;    //(n - 1 - 0 + 1) + 0   
			}
		

			while (loUse[j] == true) {
				j = randombis() % n;    //(n - 1 - 0 + 1) + 0   
			}


			loUse[j] = true;


			arista.first = i;
			arista.second = j;

			aristas.push_back(arista);		

		}
		return aristas;
}

vector<pair<int,int> > generarCn(int n) {
		
	vector<pair<int,int> > aristas;

	int m;
	if (n <= 2) {
		m = n - 1;
	}else{
		m = n;
	}

		pair<int, int> arista;

		for (int i = 0; i < n - 1; i++) {
			arista.first = i;
			arista.second = i+1;
			aristas.push_back(arista);
		}		

		if (n > 2) {
		arista.first = n - 1; //para la ultima arista (n-1, 0)
		arista.second = 0; 
		aristas.push_back(arista); 
	    }

	return aristas;

}

vector<pair<int,int> >  generarBipartito(int n1, int n2, int m) {
   
    vector<pair<int,int> > aristas;
         
        int nodos = n1 + n2;
        time_t seconds;
        time(&seconds);
        srand((unsigned int) seconds);
   
        int i;
        int j;
        pair<int, int> arista;

        while (aristas.size() < m) {
            //peso = randombis() %  (max_peso - min_peso + 1) + min_peso; 
            i = randombis() % n1;    //(n1 - 1 - 0 + 1) + 0   es entre 0 y n1-1
            j = randombis() % n2 + n1;    //(n1 + n2 -1 - n1 + 1) + n1 es entre n1 y n1+n2-1
            while (yaEsta(i, j, aristas)) {
                i = randombis() % n1;    //(n1 - 1 - 0 + 1) + 0   es entre 0 y n1-1
                j = randombis() % n2 + n1;    //(n1 + n2 -1 - n1 + 1) + n1 es entre n1 y n1+n2-1
            }

            arista.first = i;
            arista.second = j;
            aristas.push_back(arista);       

        }

        return aristas;
}

vector<pair<int,int> > dameCompleto(int n1) {
	vector<pair<int,int> > aristas;

	for(int i=0;i<n1;i++)
		for(int j=0;j<i;j++)
			aristas.push_back(make_pair(i,j));

	return aristas;
}

int main() {
	FILE * doc;
	string nombreDeLaCarpeta;
	cin >> nombreDeLaCarpeta;
	int tipog1, tipog2; //para los tipos de grafos
	//1 == grafo bipartito
	//2 == grafo arbol
	//3 == grafo Cn
	//4 == grafo estrella
	//5 == cografo
	//6 == completo

	cin >> tipog1 >> tipog2;
	int n1, m1, n2, m2;
	vector<pair<int,int> > aristas1;
	vector<pair<int,int> > aristas2;


	if (tipog1 == 1) { //pidieron bipartito para el primer grafo
		int v1,v2;
		cin >> v1 >> v2 >> m1;
		n1 = v1 + v2;
		aristas1 = generarBipartito(v1, v2, m1);
	}else{
		if (tipog1 == 2) { //pidieron grafo arbol para el primer grafo
			cin >> n1;
			m1 = n1 - 1;
			aristas1 = generarArbol(n1);
		}else{
			if (tipog1 == 3){ //pidieron grafo Cn para el primer grafo
				cin >> n1;
				if (n1 <= 2) {
					m1 = n1 - 1;
				}else{
					m1 = n1;
				} 
				aristas1 = generarCn(n1);
			}else{
				if (tipog1 == 4) { //pidieron grafo estrella 
					int v2;
					cin >> v2;
					n1 = v2 + 1;
					m1 = v2;
					aristas1 = generarBipartito(1, v2, m1);
				}
				else {
					if (tipog1 == 5) { // pidieron cografo
						cin >> n1;
						aristas1 = dameCografo(n1);
					}
					else {
						if(tipog1 == 6) { // pidieron Kn
							cin >> n1;
							aristas1 = dameCompleto(n1);
						}
					}
					m1 = aristas1.size();
					cerr << m1 << endl;
				}
			}
		}
	}

	if (tipog2 == 1) { //pidieron bipartito para el primer grafo
		int v1,v2;
		cin >> v1 >> v2 >> m2;
		n2 = v1 + v2;
		aristas2 = generarBipartito(v1, v2, m2);
	}else{
		if (tipog2 == 2) { //pidieron grafo arbol para el primer grafo
			cin >> n2;
			m2 = n2 - 1;
			aristas2 = generarArbol(n2);
		}else{
			if (tipog2 == 3){ //pidieron grafo Cn para el primer grafo
				cin >> n2;
				if (n2 <= 2) {
					m2 = n2 - 1;
				}else{
					m2 = n2;
				} 
				aristas2 = generarCn(n2);
			}else{
				if (tipog2 == 4) { //pidieron grafo estrella 
					int v2;
					cin >> v2;
					n2 = v2 + 1;
					m2 = v2;
					aristas2 = generarBipartito(1, v2, m2);
				}
				else {
					if (tipog2 == 5) { // pidieron cografo
						cin >> n2;
						aristas2 = dameCografo(n2);
					}
					else {
						if(tipog2 == 6) { // pidieron Kn
							cin >> n2;
							aristas2 = dameCompleto(n2);
						}
					}
					m2 = aristas2.size();
					cerr << m2 << endl;
				}
			}
		}
	}

	char filename[64];
	char aux[64];
	if(tipog2 == 5){
		if(tipog1 == 5){
			sprintf(aux, "/grafo-n1-%d-n2-%d.txt", n1, n2);
		} else {
			sprintf(aux, "/grafo-n1-%d-m1-%d-n2-%d.txt", n1, m1, n2);
		}
	}else{
		if(tipog1 == 5){
			sprintf(aux, "/grafo-n1-%d-n2-%d-m2-%d.txt", n1, n2, m2);
		} else {
			sprintf(aux, "/grafo-n1-%d-m1-%d-n2-%d-m2-%d.txt", n1, m1, n2, m2);
			
		}
	}
	int i;
	for(i=0;i<nombreDeLaCarpeta.size();i++)
		filename[i] = nombreDeLaCarpeta[i];
	for(i=0;aux[i] != 0;i++)
		filename[i+nombreDeLaCarpeta.size()] = aux[i];
	filename[i+nombreDeLaCarpeta.size()] = 0;

	doc = fopen(filename,"w");

	if (doc!=NULL) {
		fprintf(doc, "%d %d %d %d\n", n1, m1, n2, m2);

		for (int i = 0; i < m1 ; i++) {
			fprintf(doc, "%d %d\n", aristas1[i].first, aristas1[i].second);
		}

		for (int i = 0; i < m2 ; i++) {
			fprintf(doc, "%d %d\n", aristas2[i].first, aristas2[i].second);
		}

    	fclose(doc);
	}

	return 0;
}