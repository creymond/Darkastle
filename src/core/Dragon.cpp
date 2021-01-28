#include "Dragon.h"
#include "Personnage.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

Dragon::Dragon() {
	x = -10;
	y = -10;
	hauteur = 4;
	salle = 0;
	phase = 1;
	base = 0;
	dir = 1 ;
	vie = 5;


}

int Dragon::getX () const { return x; }

int Dragon::getY () const { return y; }

int Dragon::getPhase () const { return phase; }

int Dragon::getSalle () const { return salle; }

int Dragon::getBase () const { return base; }

int Dragon::getDir () const { return dir; }

int Dragon::getHitbox (const int n) const { return hitbox[n]; }

int Dragon::getVie () const { return vie; }

void Dragon::setVie (const int nvVie) { vie = nvVie;}

void Dragon::setHitbox (const int n, const int nvHitbox) { hitbox[n] = nvHitbox;}

void Dragon::setDir (const int posDir) { dir = posDir; }

void Dragon::setBase (const int nvBase) { base = nvBase; }

void Dragon::setX (const int posX) { x = posX; }

void Dragon::setY (const int posY) { y = posY; }

void Dragon::setSalle (const int numSalle) { salle = numSalle; }

void Dragon::setPhase (const int nvType) { phase = nvType; }

void Dragon::mortDragon () {
	if (vie <= 1){
		x=-10;
		y=-10;
	}
	else {vie--;}
	cout<<"Vie : "<<vie<<endl;

}

void Dragon::creerHitbox(Terrain & t){
	for ( int k=0;k<6;k++)
	{
		for ( int i=-2; i<6;i++)
		{
			if (t.getXY(x+k,y-i) == 'd' || t.getXY(x+k,y-i) == 'D')
			{
				t.setXY(x+k,y-i,' ');
			}
		}
	}

	for(unsigned int k=0;k<6;k++)
	{
		for (unsigned int i = 0; i <4; i++)
		{
			if (t.getXY(x+k,y-i) == ' ')
			{
				t.setXY(x+k,y-i,'d');
			}
		}
	}
}


void Dragon::bougeAuto ( Terrain & t) {
		if (dir == -1)
		{
			if (t.estPositionEnnemisValideVolant(x,y+dir+(dir*hauteur))){
						y = y+dir;
					}
			else
			{
				dir = -dir;
			}
		}
		else {
			if (t.estPositionEnnemisValideVolant(x,y+dir)){
	        	y = y+dir;
	    		}
	  	else
			{
				dir = -dir;
			}
		}
}

void Dragon::detruireHitbox(Terrain & t){
	for ( int k=0;k<6;k++)
	{
		for ( int i=-2; i<6;i++)
		{
			if (t.getXY(x+k,y-i) == 'd' || t.getXY(x+k,y-i) == 'D')
			{
				t.setXY(x+k,y-i,' ');
			}
		}
	}
}
