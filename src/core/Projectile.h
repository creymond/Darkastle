/**
@brief Module gérant un projectile
@file Projectile.h
@date 21/03/2017
*/

#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Terrain.h"
#include "Personnage.h"


class Projectile {

private :

	int x,y;
	int dir;
	int salle;
	int type;
	int basePersoX;
	int basePersoY;

public:

	/**
	@brief Constructeur par défaut du projectile
	*/
    	Projectile();

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
	@brief Accesseur à basePersoX
	*/
   	int getBasePersoX () const;

		/**
		@brief Accesseur à basePersoY
		*/
	   	int getBasePersoY () const;

			/**
			@brief Mutateur de basePersoX
			*/
		  	void setBasePersoX (const int posX);

				/**
				@brief Mutateur de basePersoY
				*/
			  	void setBasePersoY (const int posY);

	/**
	@brief Mutateur de x
	*/
  	void setX (const int posX);

	/**
	@brief Mutateur de dir
	*/
  	void setDir (const int laDir);

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
	@brief Gère la disparition d'un projectile
	*/
	void mortProjectile ();

	/**
	@brief Gère le mouvement d'un projectile
	*/
	void mouvementProjectile (Terrain & t);

	/**
	@brief Gère le mouvement d'un projectile du dragon
	*/
	void mouvementProjectileDragon (Terrain & t, int dragonX);

};
#endif
