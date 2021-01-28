/**
@brief Module gérant les plateformes qui bougent
@file Plateforme.h
@date 07/03/2017
*/

#ifndef _PLATEFORME_H
#define _PLATEFORME_H

#include "Terrain.h"
#include "Personnage.h"


class Plateforme {

private :

	int x,y;
	int dir;
	int longueur;

public:

	/**
	@brief Constructeur par défaut
	*/
    	Plateforme();

	/**
	@brief Accesseur à x
	*/
  	int getX () const;

	/**
	@brief Accesseur à y
	*/
   	int getY () const;

	/**
	@brief Accesseur à dir
	*/
   	int getDir () const;

		/**
		@brief Accesseur à longueur
		*/
	   	int getLongueur () const;

		/**
		@brief Mutateur de longueur
		*/
	  	void setLongueur (const int nvLongueur);

	/**
	@brief Mutateur de x
	*/
  	void setX (const int posX);

	/**
	@brief Mutateur de y
	*/
   	void setY (const int posY);

	/**
	@brief Mutateur de dir
	*/
   	void setDir (const int nvDir);

	/**
	@brief Mouvement automatique
	*/
    	void mouvPlateforme (Terrain & t, Personnage & perso);

			/**
			@brief Mort des plateformes
			*/
		   	void mortPlateforme ();


};
#endif
