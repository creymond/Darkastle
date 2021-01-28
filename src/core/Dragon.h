/**
@brief Module gérant le dragon
@file Dragon.h
@date 07/03/2017
*/

#ifndef _DRAGON_H
#define _DRAGON_H

#include "Terrain.h"
#include "Personnage.h"


class Dragon {

private :

	int x,y,hauteur;
	int dir;
	int salle;
	int phase;
	int base;
	int hitbox[24];
	int vie;

public:

	/**
	@brief Constructeur par défaut d'un ennemi
	*/
    	Dragon();

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
   	int getPhase () const;


	/**
	@brief Accesseur à base
	*/
	int getBase () const;


	/**
	@brief Accesseur à dir
	*/
	int getDir () const;

	/**
	@brief Accesseur à hitbox[n]
	*/
	int getHitbox (const int n) const;

	/**
	@brief Accesseur à vie
	*/
	int getVie ()const;

	/**
	@brief Mutateur de vie=
	*/
  	void setVie (const int nvVie);

	/**
	@brief Mutateur de hitbox[n]
	*/
  	void setHitbox (const int n, const int nvHitbox);

	/**
	@brief Mutateur de dir
	*/
  	void setDir (const int posDir);

	/**
	@brief Mutateur de base
	*/
  	void setBase (const int nvBase);

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
	   	void setPhase (const int nvType);

	/**
	@brief Mort du dragon
	*/
	void mortDragon ();

	/**
	@brief Mouvement automatique du draogn
	*/
    	void bougeAuto (Terrain & t);

/**
@brief creer la hitbox du dragon
*/

void creerHitbox(Terrain & t);

/**
@brief détrui la hitbox du dragon
*/

void detruireHitbox(Terrain & t);

};
#endif
