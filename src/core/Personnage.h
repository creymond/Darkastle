/**
@brief Module gérant le personnage
*/

#ifndef _PERSONNAGE_H
#define _PERSONNAGE_H

#include "Terrain.h"

/**
@brief Position du personnage
*/
class Personnage {

private :

	int x,y;
	int vie;

public:
		/**
		@brief Constructeur du personnage par défaut
		*/
    		Personnage ();

		/**
		@brief Déplacement à gauche
		*/
    		void gauche (const Terrain & t);

		/**
		@brief Saut du personnage
		*/
		void saut (const Terrain & t);

		/**
		@brief Déplacement à droite
		*/
    		void droite (const Terrain & t);

		/**
		@brief Applique la gravité au personnage
		*/
		void gravite (const Terrain & t);

		/**
		@brief Enlève n vie au personnage
		*/
		void perdVie (const int n);

		/**
		@brief Rend n vie au personnage
		*/
		void gagneVie (const int n);

		/**
		@brief Renvoie vrai si le personnage est sur la case de victoire
		*/
		bool victoire (const Terrain & t) const;

		/**
		@brief Renvoie vrai si le personnage est hors du terrain
		*/
		bool horsTerrain (const Terrain & t) const;

		/**
		@brief Renvoie vrai si le personnage n'a plus de vie
		*/
		bool plusDeVie () const;

		/**
		@brief Accesseur à x
		*/
    		int getX () const;

		/**
		@brief Accesseur à y
		*/
    		int getY () const;

		/**
		@brief Accesseur à vie
		*/
    		int getVie () const;

		/**
		@brief Mutateur de x
		*/
    		void setX (const int posX);

		/**
		@brief Mutateur de y
		*/
    		void setY (const int posY);

		/**
		@brief Mutateur de Vie
		*/
    		void setVie (const int nbVie);

};

#endif
