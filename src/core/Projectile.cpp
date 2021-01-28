#include "Projectile.h"
#include "Personnage.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

Projectile::Projectile() {
	x = 0;
	y = 0;
	dir = 0;
	salle = 0;
	type = 0;
	basePersoX = 0;
	basePersoY = 0;
}

int Projectile::getX () const { return x; }

int Projectile::getY () const { return y; }

int Projectile::getDir () const { return dir; }

int Projectile::getSalle () const { return salle; }

int Projectile::getType () const { return type; }

int Projectile::getBasePersoX () const { return basePersoX; }

int Projectile::getBasePersoY () const { return basePersoY; }

void Projectile::setBasePersoY (const int posY) { basePersoY = posY; }

void Projectile::setBasePersoX (const int posX) { basePersoX = posX; }

void Projectile::setX (const int posX) { x = posX; }

void Projectile::setDir (const int laDir) { dir = laDir; }

void Projectile::setY (const int posY) { y = posY; }

void Projectile::setSalle (const int numSalle) { salle = numSalle; }

void Projectile::setType (const int nvType) { type = nvType; }

void Projectile::mortProjectile () {
	x=-20;
	y=-20;
}

void Projectile::mouvementProjectile (Terrain & t) {
  int xtmp;
	xtmp = x + dir;
	if ((t.estPositionProjectileValide(xtmp,y)) && (t.numeroSalle(xtmp,y)==salle)) {
        x = xtmp;
    	}
    	else mortProjectile();
}

void Projectile::mouvementProjectileDragon (Terrain & t,int dragonX) {
    	int xtmp, ytmp;

			if ((dragonX - basePersoX) < 3)
			{
				ytmp = y + 1;
				if (y != basePersoY)
				{
					if ((t.estPositionProjectileValide(x,ytmp)) && (t.numeroSalle(x,ytmp)==salle)) {
							y = ytmp;
					}
					else {
						mortProjectile();
					}
				}
				else {
					xtmp = x + 1;
					if ((t.estPositionProjectileValide(xtmp,y)) && (t.numeroSalle(xtmp,y)==salle)) {
							x = xtmp;
					}
					else {
						mortProjectile();
					}
				}

			}
			else
			{

				xtmp = x - 1;
				if ((t.estPositionProjectileValide(xtmp,y)) && (t.numeroSalle(xtmp,y)==salle)) {
						x = xtmp;
				}
				else {
					mortProjectile();
				}
				if (y>basePersoY)
				{
					ytmp = y - 1;
					if ((t.estPositionProjectileValide(x,ytmp)) && (t.numeroSalle(x,ytmp)==salle)) {
							y = ytmp;
					}
					else {
						mortProjectile();
					}
				}
				else if (y<basePersoY)
				{
					ytmp = y + 1;
					if ((t.estPositionProjectileValide(x,ytmp)) && (t.numeroSalle(x,ytmp)==salle)) {
							y = ytmp;
					}
					else {
						mortProjectile();
					}
				}
			}
}
