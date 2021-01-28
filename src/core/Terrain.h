/**
@brief Module gérant un terrain
*/


#ifndef _TERRAIN_H
#define _TERRAIN_H


class Terrain {

private :

	int dimx;
	int dimy;
	char ter [1000][20];

public :
	/**
    	@brief Constructeur du terrain par défaut
    	*/
	Terrain();

	/**
	@brief Renvoie vrai si on peut postionner notre personnage sur la case (x,y) passée en paramètres.
	*/
	bool estPositionPersoValide(const int x, const int y) const;

	/**
	@brief Renvoie vrai si on peut postionner notre personnage sur la case (x,y) passée en paramètres et empêche le retour dans une salle précédente
	*/
	bool estPositionPersoValideRetour(const int x, const int y) const;

	/**
	@brief Renvoie vrai si on peut postionner un ennemi sur la case (x,y) passée en paramètres.
	*/
	bool estPositionEnnemisValide(const int x, const int y) const;

	/**
	@brief Renvoie vrai si on peut postionner un ennemi VOLANT sur la case (x,y) passée en paramètres.
	*/
	bool estPositionEnnemisValideVolant(const int x, const int y) const;

	/**
	@brief Renvoie vrai si on peut postionner un projectile sur la case (x,y) passée en paramètres.
	*/
	bool estPositionProjectileValide(const int x, const int y) const;

	/**
	@brief Renvoie vrai si la case est '*'
	*/
	bool positionVictoire (const int x, const int y) const;

	/**
	@brief Renvoie vrai si la case est 'c'
	*/
	bool estPositionCoffre (const int x, const int y) const;

	/**
	@brief Renvoie vrai si la case (x,y) passée en paramètres est une structure ('#').
	*/
	bool estPositionStructure(const int x, const int y) const;

	/**
	@brief Renvoie vrai si la case (x,y) passée en paramètres est une structure ('T').
	*/
	bool estPositionTeleport (const int x, const int y) const;


	/**
	@brief Renvoie le numero de la salle où se trouve la case (x,y) passée en paramètre
	*/
	int numeroSalle(const int x, const int y) const;

	/**
	@brief Renvoie vrai si la case est hors du terrain
	*/
	bool estHorsTerrain(const int x, const int y) const;

	/**
	@brief Renvoie vrai si la case est valide pour un slime
	*/
	bool estPositionSlimeValide(const int x, const int y) const;

	/**
	@brief Renvoie vrai si la case est valide pour une plateforme
	*/
	bool estPositionPlateformeValide(const int x, const int y) const;


    	/**
    	@brief Renvoie le type d'objet se trouvant en (x,y)
    	*/
    	char getXY (const int x, const int y) const;

	/**
    	@brief Remplace l'objet se trouvant en (x,y) par c
    	*/
    	void setXY (const int x, const int y, const char c);

	/**
    	@brief Renvoie la largeur du terrain
    	*/
    	int getDimX () const;

    	/**
    	@brief Renvoie la hauteur du terrain
    	*/
    	int getDimY () const;

};



#endif
