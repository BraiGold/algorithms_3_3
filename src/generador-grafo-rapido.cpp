#include <iostream>     //cin cout
#include <stdio.h>      // printf fopen fclose fputs 
#include <stdlib.h>     //
#include <string>       //to_string
#include <vector>
#include <algorithm>    // std::sort

using namespace std;

int main() {
	int n1, m1, n2, m2;
	string nombreDeLaCarpeta;
	cin >> nombreDeLaCarpeta >> n1 >> m1 >> n2 >> m2;

	vector<pair<int,int> > aristas1;
	for(int i=0;i<n1;i++) {
		for(int j=0;j<i;j++) {
			aristas1.push_back(make_pair(i,j));
		}
	}
	random_shuffle(aristas1.begin(),aristas1.end());
	aristas1.resize(m1);

	vector<pair<int,int> > aristas2;
	for(int i=0;i<n2;i++) {
		for(int j=0;j<i;j++) {
			aristas2.push_back(make_pair(i,j));
		}
	}
	random_shuffle(aristas2.begin(),aristas2.end());
	aristas2.resize(m2);


	FILE * doc;


	char filename[64];
	char aux[64];
	sprintf(aux, "/grafo-n1-%d-m1-%d-n2-%d-m2-%d.txt", n1, m1, n2, m2);
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
}