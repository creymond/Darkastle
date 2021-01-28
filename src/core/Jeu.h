/**
@brief Module gérant le jeu
*/

#ifndef _JEU_H
#define _JEU_H

#include "Personnage.h"
#include "Terrain.h"
#include "Ennemis.h"
#include "Plateforme.h"
#include "Projectile.h"
#include "Dragon.h"

const unsigned int NB_ENNEMIS = 60;
const unsigned int NB_PROJECTILE = 6;
const unsigned int NB_PROJECTILE_ENNEMIS = 10;
const unsigned int NB_PROJECTILE_DRAGON = 10;
const  int NB_PLATEFORME = 20;

class Jeu {

private :

	Terrain ter;
	Personnage perso;
	Dragon dragon;
	Ennemis ennemi[NB_ENNEMIS];
	Plateforme plateforme[NB_PLATEFORME];
	Projectile projectile[NB_PROJECTILE];
	Projectile projectileEnnemis[NB_PROJECTILE_ENNEMIS];
	Projectile projectileDragon[NB_PROJECTILE_DRAGON];
	int testProjectile;
	int testSuperJump;
	int bonus;
	int testDeplaceSalle1;
	long int score;
	int testTypeMort;

public :

	/**
	@brief Constructeur du jeu par défaut
	*/
    	Jeu ();

	/**
	@brief Gère l'appatition des ennemis dans le jeu
	*/
	void apparitionEnnemis();

	/**
	@brief Accesseur au terrain
	*/
    	Terrain& getTerrain ();
	const Terrain& getConstTerrain () const;

	/**
	@brief Accesseur au personnage
	*/
    	Personnage& getPersonnage ();
	const Personnage& getConstPersonnage () const;
	Dragon& getDragon ();

	/**
	@brief Accesseur au testProjectile
	*/
	int getTestProjectile() const;

	/**
	@brief Accesseur au testSuperJump
	*/
	int getTestSuperJump() const;

	/**
	@brief Accesseur au type de mort
	*/
	int getTypeMort() const;
	void setTypeMort(int nvMort);

	/**
	@brief Accesseur au bonus
	*/
	int getBonus() const;
	void setBonus(int nvBonus);

	/**
	@brief Accesseur au score
	*/
	int getScore() const;
	void setScore(int nvScore);

	/**
	@brief Accesseur au testDeaceSalle1
	*/
	int getTestDeplaceSalle1() const;
	void setTestDeplaceSalle1(int testS1);

	/**
	@brief Accesseur a l'ennemi n
	*/
	Ennemis& getEnnemis (unsigned int n);
	const Ennemis& getConstEnnemis (const unsigned int n) const;

	/**
	@brief Accesseur a la plateforme n
	*/
	Plateforme& getPlateforme (unsigned int n);

  /**
	@brief Accesseur au projectile n
	*/
	Projectile& getProjectile (unsigned int n);
	Projectile& getProjectileEnnemis (unsigned int n);
	Projectile& getProjectileDragon (unsigned int n);

	/**
	@brief Teste si le personnage est sur la même case qu'un ennemi
	*/
	bool toucheEnnemisBOOL (const int xPerso, const int  yPerso, const int xEnnemis, const int yEnnemis) const;

	/**
	@brief Fait perdre un point de vie quand le personnage touche un ennemi
	*/
	void toucheEnnemis (unsigned int & invulnerabilite);

	/**
	@brief Tue l'ennemi si un projectile le touche
	*/
	void projectileToucheEnnemis (unsigned int & bouclierCouteau);

	/**
	@brief Rend une vie au personnage et fait disparaitre la pomme quand il en ramasse une
	*/
	void ramasseJambon();

	/**
	@brief Donne la compétence de lancer des couteaux
	*/
	void ramasseCouteau();

	/**
	@brief Donne la compétence de super jump
	*/
	void ramasseJump();

	/**
	@brief Ouvre un coffre
	*/
	void ramasseCoffre();

	/**
	@brief Permet de créer des petit_slime et gère la mort des ennemis
	*/
	void mortEnnemis2(const int i);

	/**
	@brief Renvoie vrai si les conditions de victoire sont vérifiées
	*/
	bool actionsVictoire () const;

	/**
	@brief Remet le personnage au début de la salle quand il meurt
	*/
	void mortPersonnage ();

	/**
	@brief Renvoie vrai si un projectile ennemi touche le perso
	*/
	bool toucheProjectileEnnemis(int Xproj, int Yproj, int PersoX, int PersoY);

	/**
	@brief Applique les actions automatiques sur le jeu
	*/
	void actionsAutomatiques (unsigned int test, unsigned int & invulnerabilite, unsigned int jump, const int PersoX, const int PersoY, int & nbProjEnnemis, int & nbProjDragon, unsigned int & bouclierCouteau, unsigned int & testMort);

	/**
	@brief Actionne l'attaque selon le coté
	*/
	void attaque (const unsigned int cote, unsigned int & testRepoussage);

	/**
	@brief Actionne le lancer de couteau selon le coté
	*/
	void lance (const unsigned int cote, int & nbProj);

	/**
	@brief Attaque du sorcier (création des boules de feu)
	*/
	void attaqueSorcier (Terrain &t, int & nbProjEnnemis, int ennemisX, int ennemisY);

	/**
	@brief Attaque du dragon (création des boules de feu)
	*/
	void attaqueDragon (Terrain &t, int & nbProjDragon, int PersoX, int PersoY, int ennemisX, int ennemisY);

	/**
	brief Téléportation
	*/

	void teleportation ();

	/**
	@brief Permet d'utiliser les touches du clavier
	*/
    	void actionClavier(const char touche, unsigned int & cote, int & nbProj, unsigned int & testRepoussage);

};

#endif
