/**
@brief Module gérant un Ennemis
@file Ennemis.h
@date 07/03/2017
*/

#ifndef _ENNEMIS_H
#define _ENNEMIS_H

#include "Terrain.h"
#include "Personnage.h"


class Ennemis {

private :

	int x,y;
	int dir;
	int salle;
	int type; 	 // 1 = zombie ;	2 = chauve-souris 	; 3 = slime ; 4 = petit_slime ; 5 = sorcier
	int base;

public:

	/**
	@brief Constructeur par défaut d'un ennemi
	*/
    	Ennemis();

	/**
	@brief Accesseur à x
	*/
  	int getX () const;

	/**
	@brief Accesseur à salle
	*/
  	int getSalle () const;

	/**
	@brief Accesseur à y
	*/
   	int getY () const;

	/**
	@brief Accesseur à dir
	*/
   	int getDir () const;

	/**
	@brief Accesseur à type
	*/
	int getType () const;

	/**
	@brief Accesseur à base
	*/
	int getBase () const;

	/**
	@brief Mutateur de base
	*/
  	void setBase ();

	/**
	@brief Mutateur de x
	*/
  	void setX (const int posX);

	/**
	@brief Mutateur de salle
	*/
  	void setSalle (const int numSalle);

	/**
	@brief Mutateur de y
	*/
   	void setY (const int posY);

	/**
	@brief Mutateur de type
	*/
   	void setType (const int nvType);


	/**
	@brief Mort du zombie
	*/
	void mortEnnemis ();

	/**
	@brief Mouvement automatique du zombie
	*/
    	void bougeAuto (Terrain & t);


	/**
	@brief Mouvement automatique de la chauve souris
	*/
	void volAuto (Terrain & t, const int PersoX, const int PersoY);

	/**
	@brief Mouvement automatique du sorcier
	*/
	void bougeAutoSorcier (Terrain & t, const int PersoX);

	/**
	@brief Attaque du sorcier (création des boules de feu)
	*/
	void attaqueSorcier (Terrain &t, int & nbProj);

};
#endif
