#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "../core/Jeu.h"


class Image {

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

public:
   	Image () ;
	~Image () ;
   	void loadFromFile (const char* filename, SDL_Renderer * renderer);
    	void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
};



/**
    La classe g�rant le jeu avec un affichage SDL
*/
class sdlJeu {

private :

	Jeu jeu;

    	SDL_Window * window;
    	SDL_Renderer * renderer;
        TTF_Font * police;
      	SDL_Surface * texteScore;
	SDL_Surface * texteSalle;
      	SDL_Rect positionScore;
	SDL_Rect positionSalle;
      	SDL_Texture * textureScore;
	SDL_Texture * textureSalle;

	Image im_personnageDroite;
	Image im_personnageGauche;
	Image im_personnageAttaqueDroite;
	Image im_personnageAttaqueGauche;
  	Image im_mur;
  	Image im_zombieDroite;
	Image im_zombieGauche;
	Image im_chauveSouris;
	Image im_coeur;
	Image im_lave;
	Image im_porte;
 	Image im_slimeDroite;
	Image im_slimeGauche;
	Image im_petitSlimeDroite;
	Image im_petitSlimeGauche;
	Image im_plateforme;
	Image im_jambon;
	Image im_petitSlime;
	Image im_fond;
	Image im_fondS1a;
	Image im_fondS1b;
	Image im_fondS2;
	Image im_couteauDroite;
	Image im_couteauGauche;
  Image im_sorcierDroite;
	Image im_sorcierGauche;
  Image im_bouleDeFeu;
  Image im_bouclierGauche;
  Image im_bouclierDroite;
	Image im_coffreOuvert;
	Image im_coffreFerme;
	Image im_chaussures;
	Image im_ecranMort;
	Image im_superJump;
	Image im_inventaire;
  Image im_dragon;
  Image im_mortVie;
  Image im_mortLave;
  Image im_plateformeMobile;


public :

    sdlJeu ();
    ~sdlJeu ();
    void sdlBoucle ();
    void sdlAff (unsigned int cote, unsigned int & attaque, unsigned int & bouclierCouteau, unsigned int & testMort,unsigned int & testFondS1, unsigned int invulnerabilite);

};

#endif
