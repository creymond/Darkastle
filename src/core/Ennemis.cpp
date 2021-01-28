#include "Ennemis.h"
#include "Personnage.h"
#include <stdlib.h>
#include <math.h>

Ennemis::Ennemis() {
	x = 0;
	y = 0;
	dir = 0;
	salle = 0;
	type = 0;
	base = 0;
}

int Ennemis::getX () const { return x; }

int Ennemis::getY () const { return y; }

int Ennemis::getDir () const { return dir; }

int Ennemis::getSalle () const { return salle; }

int Ennemis::getType () const { return type; }

int Ennemis::getBase () const { return base; }

void Ennemis::setBase () { base = y; }

void Ennemis::setX (const int posX) { x = posX; }

void Ennemis::setY (const int posY) { y = posY; }

void Ennemis::setSalle (const int numSalle) { salle = numSalle; }

void Ennemis::setType (const int nvType) { type = nvType; }

void Ennemis::mortEnnemis () {
	x=-10;
	y=-10;
}

void Ennemis::bougeAuto ( Terrain & t) {
    	int xtmp;
	if (dir == 0) xtmp = x-1;
	if (dir == 1) xtmp = x+1;
	if ((type == 1) || (type == 4)) {
		if ((t.estPositionEnnemisValide(xtmp,y)) && (t.numeroSalle(xtmp,y)==salle)) {
        	x = xtmp;
    		}
    		else if (dir == 0) dir = 1;
		else if (dir == 1) dir = 0;
	}
	else if (type == 3) {
    		if ((t.estPositionSlimeValide(xtmp,y)) && (t.numeroSalle(xtmp,y)==salle)) {
        		x = xtmp;
    		}
    		else if (dir == 0) dir = 1;
		else if (dir == 1) dir = 0;
	}

}

void Ennemis::volAuto (Terrain & t, const int PersoX, const int PersoY) {
    			int xtmp;
			if (dir == 0) xtmp = x-1;
			if (dir == 1) xtmp = x+1;
			bool Xmoins, Ymoins, Xplus, Yplus;
			Xmoins = t.estPositionEnnemisValideVolant(x-1,y);
			Ymoins = t.estPositionEnnemisValideVolant(x,y-1);
			Xplus = t.estPositionEnnemisValideVolant(x+1,y);
			Yplus = t.estPositionEnnemisValideVolant(x,y+1);
			if (y>PersoY)
			{
				if (Ymoins)
					{
						y--;
					}
				else if (Xmoins)
					{
						x--;
					}
				else if (Xplus)
					{
						x++;
					}
				}

			else if (abs(PersoX - (x - 4)) <= 4) // descente quand elle arrive de la droite
			{
				if (y <13 && Yplus && y<PersoY) {
					y++;
				}
				if (Xmoins)
				x--;
			}
			else if (abs(PersoX - (x + 4)) <= 4) // descente quand elle arrive de la gauche
			{
				if (y <13  && Yplus  && y<PersoY) {
					y++;
				}
				if (Xplus)
 				x++;
			}


			else if (y>base) {
				if (Ymoins) { y--;}

				if (dir == 0) xtmp = x-1;
				if (dir == 1) xtmp = x+1;
				if (t.estPositionEnnemisValideVolant(xtmp,y)) {
					x = xtmp; }
	   		else if (dir == 0) dir = 1;
			else if (dir == 1) dir = 0;
			}
			else
			{
				if (dir == 0) xtmp = x-1;
				if (dir == 1) xtmp = x+1;
				if (t.estPositionEnnemisValideVolant(xtmp,y)) {
					x = xtmp; }
	   		else if (dir == 0) dir = 1;
			else if (dir == 1) dir = 0;
			}
}


void Ennemis::bougeAutoSorcier (Terrain & t, const int PersoX)
{
	bool Xmoins, Xplus;
	Xmoins = t.estPositionEnnemisValide(x-1,y);
	Xplus = t.estPositionEnnemisValide(x+1,y);

	if ( x<PersoX && abs(x-PersoX) <10 && Xmoins)
	{
		x--;
		dir = 1;
	}
	else if (  x>PersoX && abs(x-PersoX)<10 && Xplus)
	{
		x++;
		dir = 0;
	}
}
