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


int main() {
	FILE * doc;
	
	int n1, m1, n2, m2;
	cin >> n1 >> m1 >> n2 >> m2; 
	
	vector<pair<int,int> > aristas1;
	vector<pair<int,int> > aristas2;



	char filename[64];
	sprintf(filename, "grafo-n1-%d-m1-%d-n2-%d-m2-%d.txt", n1, m1, n2, m2);
	

	doc = fopen(filename,"w");

	if (doc!=NULL) {
  	
		fprintf(doc, "%d %d %d %d\n", n1, m1, n2, m2);
		time_t seconds;
		time(&seconds);
		srand((unsigned int) seconds);
	
		int i;
		int j;
		pair<int, int> arista;

		while (aristas1.size() < m1) {
			cerr << "estoy buscando una nueva arista, ya tengo: " << aristas1.size() << endl;
			i = randombis() % n1;    //(n - 1 - 0 + 1) + 0   
			j = randombis() % n1;    //(n - 1 - 0 + 1) + 0   
			while (yaEsta(i, j, aristas1) || (i == j) ) {
				i = randombis() % n1;    //(n - 1 - 0 + 1) + 0   
				j = randombis() % n1;    //(n - 1 - 0 + 1) + 0   
			} 

			arista.first = i;
			arista.second = j;
			aristas1.push_back(arista);		

		}

		cerr << "estoy por imprimir grafo1" << endl;

		for (int i = 0; i < m1 ; i++) {
			fprintf(doc, "%d %d\n", aristas1[i].first, aristas1[i].second);
		}

		cerr << "ya imprimi grafo1" << endl;

		while (aristas2.size() < m2) {
			cerr << "estoy buscando una nueva arista, ya tengo: " << aristas2.size() << endl;
			i = randombis() % n2;    //(n - 1 - 0 + 1) + 0   
			j = randombis() % n2;    //(n - 1 - 0 + 1) + 0   
			while (yaEsta(i, j, aristas2) || (i == j) ) {
				i = randombis() % n2;    //(n - 1 - 0 + 1) + 0   
				j = randombis() % n2;    //(n - 1 - 0 + 1) + 0   
			} 

			arista.first = i;
			arista.second = j;
			aristas2.push_back(arista);		

		}

		cerr << "estoy por imprimir grafo2" << endl;

		for (int i = 0; i < m2 ; i++) {
			fprintf(doc, "%d %d\n", aristas2[i].first, aristas2[i].second);
		}
    	
		cerr << "ya imprimi todo " << endl;

    	fclose(doc);
	}
	return 0;
}