#include "Plateforme.h"
#include <stdlib.h>
#include <math.h>

Plateforme::Plateforme() {
	x = -10;
	y = -10;
	dir = -1;
	longueur = 0;
}

int Plateforme::getX () const { return x; }

int Plateforme::getY () const { return y; }

int Plateforme::getDir () const { return dir; }

int Plateforme::getLongueur () const { return longueur; }

void Plateforme::setLongueur (const int nvLongueur) { longueur = nvLongueur; }

void Plateforme::setDir (const int nvDir) { dir = nvDir; }

void Plateforme::setX (const int posX) { x = posX; }

void Plateforme::setY (const int posY) { y = posY; }

void Plateforme::mortPlateforme() {x = -10; y = -10; longueur = 0;}

void Plateforme::mouvPlateforme (Terrain & t, Personnage & perso) {

	int a;
	int persoX = perso.getX();
	if (x != -10){

			if (dir == 1 && t.estPositionPlateformeValide(x+longueur,y))
				{
					a = x;
					x++;

					if ((persoX >= a && persoX <= a+longueur-1) &&  perso.getY() == y-1) {
						 perso.setX(persoX+1);
					 }

					t.setXY(a,y,' ');
					t.setXY(a+longueur,y,'=');
				}
			else if (dir == -1 && t.estPositionPlateformeValide(x-1,y)) {
					a = x;
					x--;
					if ((persoX >= a && persoX <=a+longueur-1) && (perso.getY() == y-1)){
						 perso.setX(persoX-1);
					 }

					t.setXY(a+longueur-1,y,' ');
					t.setXY(x,y,'=');
				}
			else { dir = -dir;}
		}
	}
