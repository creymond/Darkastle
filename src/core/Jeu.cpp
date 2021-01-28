#include "Jeu.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Jeu::Jeu () : ter(), perso() {

	testProjectile = 0;
	testSuperJump = 0;
	bonus = 0;
	testTypeMort = 0;
	apparitionEnnemis();
	testDeplaceSalle1 = 0;
	score = 0;


	int p=-1;
	int testPlateforme = 0;


		for(int y=0;y<ter.getDimY();++y) {
			for(int x=0;x<ter.getDimX();++x) {
						if (ter.getXY(x,y) == '=') {
								if (testPlateforme == 0)
								{
									p++;
									plateforme[p].setX(x);
									plateforme[p].setY(y);
									testPlateforme++;
									plateforme[p].setLongueur(1);
								}
							else{
								plateforme[p].setLongueur(plateforme[p].getLongueur()+1);
									}
							}
						else {
							testPlateforme = 0;
						}
			}
		}

}



void Jeu::apparitionEnnemis() {
	unsigned int i = 0;

	for(unsigned int k=0;k<NB_ENNEMIS;k++)
	{
		if (ennemi[k].getType() == 4)
		{
			ennemi[k].setX(-10);
			ennemi[k].setY(-10);
			ennemi[k].setSalle(0);
			ennemi[k].setType(0);
		}
	}
	for ( int k = 0; k<ter.getDimX();k++)
		{
			for ( int l = 0; l<ter.getDimY(); l++)
			{
				if (ter.getXY(k,l) == 'C')
				{
					ter.setXY(k,l,'c');
				}
			}
		}



	for(int y=0;y<ter.getDimY();++y) {
		for(int x=0;x<ter.getDimX();++x) {
			if (ter.getXY(x,y) == 'Z') {
				ennemi[i].setX(x);
				ennemi[i].setY(y);
				ennemi[i].setSalle(ter.numeroSalle(x,y));
				ennemi[i].setType(1);
				i++;

			}
			else if (ter.getXY(x,y) == 'B') {
				ennemi[i].setX(x);
				ennemi[i].setY(y);
				ennemi[i].setSalle(ter.numeroSalle(x,y));
				ennemi[i].setBase();
				ennemi[i].setType(2);
				i++;

			}
			else if (ter.getXY(x,y) == 'S') {
				ennemi[i].setX(x);
				ennemi[i].setY(y);
				ennemi[i].setSalle(ter.numeroSalle(x,y));
				ennemi[i].setType(3);
				i=i+2;

			}
			else if (ter.getXY(x,y) == 'W') {
				ennemi[i].setX(x);
				ennemi[i].setY(y);
				ennemi[i].setSalle(ter.numeroSalle(x,y));
				ennemi[i].setType(5);
				i++;

			}

			if (ter.getXY(x,y) == 'D') {
				dragon.setX(x);
				dragon.setY(y);
				dragon.setDir(1);
				dragon.setSalle(ter.numeroSalle(x,y));
				dragon.creerHitbox(ter);
			}
		}
	}

}

Terrain& Jeu::getTerrain () { return ter; }

Personnage& Jeu::getPersonnage () { return perso; }

Ennemis& Jeu::getEnnemis (unsigned int n) { return ennemi[n];}

Plateforme& Jeu::getPlateforme (unsigned int n) { return plateforme[n];}

Projectile& Jeu::getProjectile (unsigned int n) { return projectile[n];}

Projectile& Jeu::getProjectileEnnemis (unsigned int n) { return projectileEnnemis[n];}

Projectile& Jeu::getProjectileDragon (unsigned int n) { return projectileDragon[n];}

Dragon& Jeu::getDragon () { return dragon;}

int Jeu::getBonus() const {return bonus;}
void Jeu::setBonus(int nvBonus) {bonus = nvBonus;}

int Jeu::getScore() const {return score;}
void Jeu::setScore(int nvScore) {bonus = nvScore;}

int Jeu::getTypeMort() const {return testTypeMort;}
void Jeu::setTypeMort(int nvMort) {testTypeMort = nvMort;}

int Jeu::getTestDeplaceSalle1() const {return testDeplaceSalle1;}
void Jeu::setTestDeplaceSalle1(int testS1) {testDeplaceSalle1 = testS1;}

int Jeu::getTestProjectile () const {
	return testProjectile;
}

int Jeu::getTestSuperJump () const {
	return testSuperJump;
}

const Terrain& Jeu::getConstTerrain () const { return ter; }

const Personnage& Jeu::getConstPersonnage () const { return perso; }

const Ennemis& Jeu::getConstEnnemis (const unsigned int n) const {
	return ennemi[n];
}




void Jeu::actionsAutomatiques (unsigned int test, unsigned int & invulnerabilite, unsigned int jump, int PersoX, int PersoY, int & nbProjEnnemis, int & nbProjDragon, unsigned int & bouclierCouteau, unsigned int & testMort) {

	if (bouclierCouteau > 0) bouclierCouteau--;
	if (bonus >1) bonus--;
	if (bonus == 12 || bonus == 1 || bonus == 22) bonus = 0;

	if (jump <= 4) perso.gravite(ter);
	if (ter.estPositionCoffre(PersoX, PersoY)) ramasseCoffre();
	if (ter.estPositionTeleport(PersoX, PersoY)){
		teleportation();
	}
	if (perso.horsTerrain(ter)){
		testTypeMort = 1;
		testMort = 20;
		mortPersonnage();
		if (score > 1500) score = score - 1500;
		else score = 0;
	}
	else if (perso.plusDeVie()) {
		testTypeMort = 2;
		testMort = 20;
		mortPersonnage();
		if (score > 1500) score = score - 1500;
		else score = 0;
	}
	else if (test%2 == 1) { // mouvement ralentie des ennemis (et le %2 c'est pour les boules de feu)


				for ( int i = 0; i < NB_PLATEFORME; i++) {
					plateforme[i].mouvPlateforme(ter,perso);

				}



			for (unsigned int i = 0; i < NB_ENNEMIS; i++) {

				if (ter.numeroSalle(PersoX,PersoY) == ennemi[i].getSalle())
				{
						if (ennemi[i].getType() == 1 || ennemi[i].getType() == 3 || ennemi[i].getType() == 4)
						{
						ennemi[i].bougeAuto(ter);
						}
						else if (ennemi[i].getType() == 2)
						{
							ennemi[i].volAuto(ter, PersoX, PersoY);
						}
						else if (ennemi[i].getType() == 5)
						{
							ennemi[i].bougeAutoSorcier(ter, PersoX);
							if (test == 1) {attaqueSorcier(ter,nbProjEnnemis,ennemi[i].getX(),ennemi[i].getY());}

						}
				}

			}

			if (ter.numeroSalle(PersoX,PersoY) == dragon.getSalle())
			{
				dragon.bougeAuto(ter);
				dragon.creerHitbox(ter);
				if (test == 1) {attaqueDragon(ter,nbProjEnnemis,perso.getX(), perso.getY(), dragon.getX(),dragon.getY());}
			}

		}

		for (unsigned int k = 0; k < NB_PROJECTILE_DRAGON; k++) {
			projectileDragon[k].mouvementProjectileDragon(ter, dragon.getX());
				if (toucheProjectileEnnemis(projectileDragon[k].getX(), projectileDragon[k].getY(), PersoX, PersoY)) {
					if (invulnerabilite == 0) {
						perso.perdVie(1);
						invulnerabilite=10;
					}
					projectileDragon[k].mortProjectile();
				}
			}

		for (unsigned int k = 0; k < NB_PROJECTILE_ENNEMIS; k++) {
			projectileEnnemis[k].mouvementProjectile(ter);
				if (toucheProjectileEnnemis(projectileEnnemis[k].getX(), projectileEnnemis[k].getY(), PersoX, PersoY)) {
					if (invulnerabilite == 0) {
						perso.perdVie(1);
						invulnerabilite=10;
					}
					projectileEnnemis[k].mortProjectile();
				}
			}


	projectileToucheEnnemis(bouclierCouteau); // fais aussi le mouvement des projectiles du perso
	toucheEnnemis(invulnerabilite);
	if (invulnerabilite > 0) invulnerabilite--;
}


void Jeu::mortEnnemis2(const int i)
{
	if (ennemi[i].getType() == 3)
	{
		ennemi[i].setType(4);
		ennemi[i].setX(ennemi[i].getX()-2);
		ennemi[i+1].setX(ennemi[i].getX()+4);
		ennemi[i+1].setY(ennemi[i].getY());
		ennemi[i+1].setSalle(ennemi[i].getSalle());
		ennemi[i+1].setType(4);
		score = score + 100;
	}
	else {
		ennemi[i].mortEnnemis();
		if (ennemi[i].getType() == 1) score = score + 100;
		else if (ennemi[i].getType() == 2) score = score + 200;
		else if (ennemi[i].getType() == 4) score = score + 100;
		else if (ennemi[i].getType() == 5) score = score + 400;
	}
}

bool Jeu::toucheEnnemisBOOL (const int xPerso, const int  yPerso, const int xEnnemis, const int yEnnemis) const {
	return (((xPerso==xEnnemis) && (yPerso==yEnnemis)) || (ter.getXY(xPerso,yPerso) == 'd') || (ter.getXY(xPerso,yPerso) == 'D'));
}


bool Jeu::toucheProjectileEnnemis(int Xproj, int Yproj, int PersoX, int PersoY)
{
	return (PersoX==Xproj && PersoY==Yproj);
}

void Jeu::projectileToucheEnnemis (unsigned int & bouclierCouteau) {
	for (unsigned int k = 0; k < NB_PROJECTILE; k++) {
		projectile[k].mouvementProjectile(ter);
		for (unsigned int i = 0; i < NB_ENNEMIS; i++) {
			if ((toucheEnnemisBOOL(projectile[k].getX(),projectile[k].getY(),ennemi[i].getX(),ennemi[i].getY())) || (toucheEnnemisBOOL(projectile[k].getX()+1,projectile[k].getY(),ennemi[i].getX(),ennemi[i].getY())) || (toucheEnnemisBOOL(projectile[k].getX()-1,projectile[k].getY(),ennemi[i].getX(),ennemi[i].getY())))  {
					if (ennemi[i].getType() != 5)
					{
						mortEnnemis2(i);
					}
					else {
						bouclierCouteau = 5;
					}
					projectile[k].mortProjectile();
			}
		}
	}
}

void Jeu::toucheEnnemis (unsigned int & invulnerabilite) {
	for (unsigned int i = 0; i < NB_ENNEMIS; i++) {
		if (toucheEnnemisBOOL(perso.getX(),perso.getY(),ennemi[i].getX(),ennemi[i].getY())) {
			if (invulnerabilite == 0) {
				perso.perdVie(1);
				invulnerabilite=10;
			}
		}
	}
}

bool Jeu::actionsVictoire () const {
	return (perso.victoire(ter));
}

void Jeu::mortPersonnage () {
	int moinsSalle=0, salle = ter.numeroSalle(perso.getX(),perso.getY())-1;

	moinsSalle = (salle-2)%3;

	unsigned int j = 13;
	perso.setX(1+40*(salle-moinsSalle));
	while (j>0)
	{
		if (ter.estPositionPersoValide((1+40*(salle-moinsSalle)),j))
		{
			perso.setY(j);
			j=1;
		}
		j--;

	}
	perso.setVie(5);

	testProjectile = 0;
	testSuperJump = 0;
	apparitionEnnemis();

	for (unsigned int i=0; i<NB_PROJECTILE; i++) {
		projectile[i].mortProjectile();
	}
	for (unsigned int i=0; i<NB_PROJECTILE_ENNEMIS; i++) {
		projectileEnnemis[i].mortProjectile();
	}
	for (unsigned int i=0; i<NB_PROJECTILE_DRAGON; i++) {
		projectileDragon[i].mortProjectile();
	}
	/*for (unsigned int i=0; i<NB_PLATEFORME; i++) {
		plateforme[i].mortPlateforme();
	}*/


}


void Jeu::ramasseCoffre() {
	int random = rand()%10 + 1;
	if (testProjectile == 0) {
		if (random > 7) {
			ramasseCouteau();
			bonus = 11;
		}
		else if (random > 4) {
			if (testSuperJump == 0) {
				ramasseJump();
				bonus = 33;
			}
			else {
				ramasseJambon();
				bonus = 22;
			}
		}
		else if (random > 0) {
			ramasseJambon();
			bonus = 22;
		}
	}
	else {
		if (random > 7) {
			if (testSuperJump == 0) {
				ramasseJump();
				bonus = 33;
			}
			else {
				ramasseJambon();
				bonus = 22;
			}
		}
		else {
			ramasseJambon();
			bonus = 22;
		}
	}
	ter.setXY(perso.getX(),perso.getY(),'C');
}


void Jeu::ramasseJambon () {
	perso.gagneVie(1);
}


void Jeu::ramasseCouteau () {
	testProjectile = 1;
}

void Jeu::ramasseJump () {
	testSuperJump = 1;
}

void Jeu::teleportation ()
{
		perso.setX(41);
		perso.setY(13);
}



void Jeu::attaque (const unsigned int cote, unsigned int & testRepoussage) {

	if (cote == 1) { // à gauche

		if (toucheEnnemisBOOL(perso.getX()-1,perso.getY(),-10,-10)) {
			if (dragon.getVie() <= 1) { dragon.detruireHitbox(ter); }
			dragon.mortDragon();
			perso.setX((perso.getX()/40)*40+5);
			//testRepoussage = 7;

		}

		for (unsigned int i = 0; i < NB_ENNEMIS; i++) {
			if (toucheEnnemisBOOL(perso.getX()-1,perso.getY(),ennemi[i].getX(),ennemi[i].getY())) mortEnnemis2(i);
		}
	}

	if (cote == 2) { // à droite

		if (toucheEnnemisBOOL(perso.getX()+1,perso.getY(),-10,-10))  {
			if (dragon.getVie() <= 1) { dragon.detruireHitbox(ter); }
			dragon.mortDragon();
			perso.setX((perso.getX()/40)*40+5);

			//testRepoussage = 7;
		}

		for (unsigned int i = 0; i < NB_ENNEMIS; i++) {
			if (toucheEnnemisBOOL(perso.getX()+1,perso.getY(),ennemi[i].getX(),ennemi[i].getY())) mortEnnemis2(i);
		}
	}

	if (toucheEnnemisBOOL(perso.getX(),perso.getY(),-10,-10))  {
		if (dragon.getVie() <= 1) { dragon.detruireHitbox(ter); }
		dragon.mortDragon();
		perso.setX((perso.getX()/40)*40+5);
		//testRepoussage = 7;
	}
	for (unsigned int i = 0; i < NB_ENNEMIS; i++) {
		if (toucheEnnemisBOOL(perso.getX(),perso.getY(),ennemi[i].getX(),ennemi[i].getY())) { mortEnnemis2(i);} // attaque sur la case du personnage dans tous les cas
	}
}

void Jeu::lance (const unsigned int cote, int & nbProj) {


		if (testProjectile == 1) { // tu as rammasser le couteau
			if (nbProj == 5) nbProj = 0;
			if (cote == 1) { // à gauche
				projectile[nbProj].setX(perso.getX()-1);
				projectile[nbProj].setY(perso.getY());
				projectile[nbProj].setSalle(ter.numeroSalle(perso.getX(),perso.getY()));
				projectile[nbProj].setDir(-1);
				projectile[nbProj].setType(1);
				nbProj++;
			}

			if (cote == 2) { // à droite
				projectile[nbProj].setX(perso.getX()+1);
				projectile[nbProj].setY(perso.getY());
				projectile[nbProj].setSalle(ter.numeroSalle(perso.getX(),perso.getY()));
				projectile[nbProj].setDir(1);
				projectile[nbProj].setType(1);
				nbProj++;
			}
		}
}


void Jeu::attaqueSorcier (Terrain &t, int & nbProjEnnemis, int ennemisX, int ennemisY)
{
	int dir;
	if (nbProjEnnemis ==9) { nbProjEnnemis = 0;}
	if (ennemisX>perso.getX())
		{
			dir = -1;
		}
	else { dir = 1;}

	projectileEnnemis[nbProjEnnemis].setX(ennemisX+dir);
	projectileEnnemis[nbProjEnnemis].setY(ennemisY);
	projectileEnnemis[nbProjEnnemis].setSalle(ter.numeroSalle(perso.getX(),perso.getY())); // même salle que celle de l'ennemi
	projectileEnnemis[nbProjEnnemis].setDir(dir);
	projectileEnnemis[nbProjEnnemis].setType(2); // bouleDeFeu
	nbProjEnnemis++;
}


void Jeu::attaqueDragon (Terrain &t, int & nbProjDragon, int PersoX, int PersoY, int ennemisX, int ennemisY)
{

	if (nbProjDragon ==9) { nbProjDragon = 0;}

	projectileDragon[nbProjDragon].setX(ennemisX-1);
	projectileDragon[nbProjDragon].setY(ennemisY-3);
	projectileDragon[nbProjDragon].setSalle(ter.numeroSalle(perso.getX(),perso.getY())); // même salle que celle de l'ennemi
	projectileDragon[nbProjDragon].setDir(-1);
	projectileDragon[nbProjDragon].setType(2); // bouleDeFeu
	projectileDragon[nbProjDragon].setBasePersoX(PersoX);
	projectileDragon[nbProjDragon].setBasePersoY(PersoY);
	nbProjDragon++;
}



void Jeu::actionClavier (const char touche, unsigned int & cote, int & nbProj, unsigned int & testRepoussage) {
	switch(touche) {
		case 'q' :
				perso.gauche(ter);
				cote = 1;
				break;
		case 'd' :
				perso.droite(ter);
				cote = 2;
				break;

		case ' ' :
				perso.saut(ter);
				break;
		case 'k' :
				attaque(cote, testRepoussage);
				break;
		case 'z' :
				lance(cote,nbProj);
				break;
	}
}
