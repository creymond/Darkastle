#include "Terrain.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

Terrain::Terrain () {
	dimx = 801;
	dimy = 15;
	ifstream fichier("data/Terrain.txt", ios::in);
	if(fichier){

		cout << "Le fichier a bien été ouvert." << endl;
		char caractere;
		string ligne;
		int k = dimy - 1;
		int j = 0;
		while(getline(fichier,ligne)){
			for(unsigned int i = 0; i < ligne.length() ; i++){
				caractere = ligne[i];

				if(caractere == ','){
					i = 3000;
				}
					else{
						ter[j][k] = caractere;
						j++;

					}

			}
			k--;
			j = 0;
		}
				fichier.close();
	}
	else {cout << "Le fichier ne s'est pas ouvert correctement." << endl;}
}


bool Terrain::estPositionPersoValide (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y]!='#') && (ter[x][y]!='$'));
}

bool Terrain::estPositionPlateformeValide (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y]!='#') && (ter[x][y]!='+') && (ter[x][y]!='-'));
}

bool Terrain::estPositionPersoValideRetour (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y]!='#') && (ter[x][y]!='$') && (ter[x][y]!='^') && (ter[x][y]!='&'));
}

bool Terrain::estPositionEnnemisValide (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y]!='#') && (ter[x][y]!='&') && (ter[x][y]!='^') && (ter[x][y+1]!='L') && (ter[x][y+1]!=' ') && (ter[x][y+1]!='='));
}

bool Terrain::estPositionSlimeValide (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x+2][y]!='#') && (ter[x+2][y]!='&') && (ter[x+2][y]!='^') && (ter[x+2][y+1]!=' ') && (ter[x+2][y+1]!='L') && (ter[x-2][y]!='#') && (ter[x-2][y]!='&') && (ter[x-2][y]!='^') && (ter[x-2][y+1]!='L') && (ter[x-2][y+1]!=' '));
}

bool Terrain::estPositionEnnemisValideVolant (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y]!='#') && (ter[x][y]!='&') && (ter[x][y]!='^') && (ter[x][y]!='%'));
}

bool Terrain::estPositionProjectileValide (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y]!='#') && (ter[x][y]!='&') && (ter[x][y]!='^'));
}

bool Terrain::positionVictoire (const int x, const int y) const {
	return (ter[x][y] == '*');
}


bool Terrain::estPositionCoffre (const int x, const int y) const {
	return (ter[x][y]=='c');
}

bool Terrain::estPositionTeleport (const int x, const int y) const {
	return (ter[x][y]=='T');
}


int Terrain::numeroSalle (const int x, const int y) const {
    int ret;
    for (int i=0;i<((dimx-1)/40);i++) {
        if ((x>=0+40*i) && (x<40*(i+1)) && (y>=0) && (y<=15)) ret = i+1;
    }
    return ret;
}

bool Terrain::estPositionStructure (const int x, const int y) const {
	return ((ter[x][y]=='#') || (ter[x][y]=='-') || (ter[x][y]=='$') || (ter[x][y]=='=') );
}

bool Terrain::estHorsTerrain (const int x, const int y) const {
	return (not((x>=0) && (x<dimx-1) && (y>=0) && (y<dimy)));
}

char Terrain::getXY (const int x, const int y) const {
	return ter[x][y];
}

void Terrain::setXY (const int x, const int y, const char c) {
	ter[x][y]=c;
}

int Terrain::getDimX () const { return dimx; }

int Terrain::getDimY () const {	return dimy; }
