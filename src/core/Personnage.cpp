#include "Personnage.h"

Personnage::Personnage () {
	x = 1;
	y = 13;
	vie = 5;
}

void Personnage::gauche (const Terrain & t) {
	if (t.estPositionPersoValideRetour(x-1,y)) x--;
}

void Personnage::saut (const Terrain & t) {
		if (t.estPositionPersoValide(x,y-1)) y--;
}

void Personnage::droite (const Terrain & t) {
	if (t.estPositionPersoValide(x+1,y)) x++;
}

void Personnage::gravite (const Terrain & t) {
	if (not(t.estPositionStructure(x,y+1))) y++;
}

bool Personnage::plusDeVie () const {
	return (vie <= 0);
}

void Personnage::perdVie (const int n) {
	vie = vie-n;
}

void Personnage::gagneVie (const int n) {
	vie = vie+n;
}

bool Personnage::victoire (const Terrain & t) const {
	return (t.positionVictoire(x,y));
}

bool Personnage::horsTerrain (const Terrain & t) const {
	return (t.estHorsTerrain(x,y));
}

int Personnage::getX () const { return x; }

int Personnage::getY () const { return y; }

int Personnage::getVie () const { return vie; }

void Personnage::setX (const int posX) { x = posX; }

void Personnage::setY (const int posY) { y = posY; }

void Personnage::setVie (const int nbVie) { vie = nbVie; }
