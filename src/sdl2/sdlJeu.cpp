#include <cassert>
#include <time.h>
#include "sdlJeu.h"
#include <stdlib.h>

#include <iostream>
using namespace std;

const int TAILLE_SPRITE = 32;

float temps () {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

Image::~Image () {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	has_changed = true;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (has_changed) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(ok == 0);
}

// ============= CLASS SDLJEU =============== //

sdlJeu::sdlJeu () : jeu() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }

	int dimx, dimy;
	dimx = 40;
	dimy = 15;
	dimx = dimx * TAILLE_SPRITE;
	dimy = dimy * TAILLE_SPRITE;

    // Creation de la fenetre
    window = SDL_CreateWindow("Darkastle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

      	police = TTF_OpenFont("data/police.TTF", 65);
    	TTF_SetFontStyle(police, TTF_STYLE_BOLD);

    	im_personnageDroite.loadFromFile("data/personnageDroite.png",renderer);
	im_personnageGauche.loadFromFile("data/personnageGauche.png",renderer);
	im_personnageAttaqueDroite.loadFromFile("data/personnageAttaqueDroite.png",renderer);
	im_personnageAttaqueGauche.loadFromFile("data/personnageAttaqueGauche.png",renderer);
    	im_mur.loadFromFile("data/mur.png",renderer);
    	im_zombieDroite.loadFromFile("data/zombieDroite.png",renderer);
	im_zombieGauche.loadFromFile("data/zombieGauche.png",renderer);
	im_chauveSouris.loadFromFile("data/chauveSouris.png",renderer);
	im_coeur.loadFromFile("data/coeur.png",renderer);
	im_lave.loadFromFile("data/lave.png",renderer);
	im_porte.loadFromFile("data/porte.png",renderer);
  	im_slimeDroite.loadFromFile("data/slimeDroite.png",renderer);
	im_slimeGauche.loadFromFile("data/slimeGauche.png",renderer);
	im_petitSlimeDroite.loadFromFile("data/petitSlimeDroite.png",renderer);
	im_petitSlimeGauche.loadFromFile("data/petitSlimeGauche.png",renderer);
	im_plateforme.loadFromFile("data/plateforme.png",renderer);
	im_jambon.loadFromFile("data/jambon.png",renderer);
	im_fond.loadFromFile("data/fond.png",renderer);
	im_fondS1a.loadFromFile("data/fondS1a.png",renderer);
	im_fondS1b.loadFromFile("data/fondS1b.png",renderer);
	im_fondS2.loadFromFile("data/fondS2.png",renderer);
	im_couteauDroite.loadFromFile("data/couteauDroite.png",renderer);
	im_couteauGauche.loadFromFile("data/couteauGauche.png",renderer);
  	im_sorcierDroite.loadFromFile("data/sorcierDroite.png", renderer);
	im_sorcierGauche.loadFromFile("data/sorcierGauche.png", renderer);
  	im_bouleDeFeu.loadFromFile("data/bouleDeFeu.png", renderer);
    	im_bouclierGauche.loadFromFile("data/bouclierGauche.png", renderer);
    	im_bouclierDroite.loadFromFile("data/bouclierDroite.png", renderer);
  	im_coffreFerme.loadFromFile("data/coffreFerme.png", renderer);
  	im_coffreOuvert.loadFromFile("data/coffreOuvert.png", renderer);
	im_superJump.loadFromFile("data/superJump.png", renderer);
	im_inventaire.loadFromFile("data/inventaire.png", renderer);
  	im_dragon.loadFromFile("data/dragon.png", renderer);
  	im_mortVie.loadFromFile("data/fondMortVie.png", renderer);
  	im_mortLave.loadFromFile("data/fondMortLave.png", renderer);
  	im_plateformeMobile.loadFromFile("data/plateformeMobile.png", renderer);


}

sdlJeu::~sdlJeu () {
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void sdlJeu::sdlAff (unsigned int cote, unsigned int & attaque, unsigned int & bouclierCouteau, unsigned int & testMort, unsigned int & testFondS1, unsigned int invulnerabilite) {
    	SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    	SDL_RenderClear(renderer);

	int x,y,i;
	const Terrain& ter = jeu.getConstTerrain();
	const Personnage& perso = jeu.getConstPersonnage();
  	char score[20];
	char numSalle[20];

	int salle = (jeu.getConstTerrain().numeroSalle(jeu.getConstPersonnage().getX(),jeu.getConstPersonnage().getY()))-1;

  	SDL_Color couleur = {0, 0, 0};

  // Affichage de l'ecran lors de la mort du personnage
	if (testMort > 0) {
    if (jeu.getTypeMort() == 1) {im_mortLave.draw(renderer,0,0,1280,480);}
    else if (jeu.getTypeMort() == 2) {im_mortVie.draw(renderer,0,0,1280,480);}
  }
  else {
          // Affichage du fond
        	if (salle == 0) {
			if (jeu.getTestDeplaceSalle1() == 0) {
				if (testFondS1 > 5) im_fondS1a.draw(renderer,0,0,1280,480);
				else if (testFondS1 >= 0) im_fondS1b.draw(renderer,0,0,1280,480);
			}
			else im_fondS1b.draw(renderer,0,0,1280,480);
		}
        	else if (salle == 1) im_fondS2.draw(renderer,0,0,1280,480);
        	else im_fond.draw(renderer,0,0,1280,480);


            // Afficher les sprites des murs
        	for (x=40*salle;x<40*(salle+1);++x) {
        		for (y=0;y<ter.getDimY();++y) {
        			if (ter.getXY(x,y)=='#') im_mur.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
        			if (ter.getXY(x,y)=='L') im_lave.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
        			if (ter.getXY(x,y)=='-') im_plateforme.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
        			if (ter.getXY(x,y)=='&') im_porte.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE*2);
        			if (ter.getXY(x,y)=='c') im_coffreFerme.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
              if (ter.getXY(x,y)=='C') im_coffreOuvert.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
              if (ter.getXY(x,y)=='=') im_plateformeMobile.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
              if (ter.getXY(x,y)=='d') im_lave.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
              if (ter.getXY(x,y)=='D') im_mur.draw(renderer,(x-40*salle)*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);



        		}
        	}

          // Affichage des bonus
          int bonus = jeu.getBonus();

	  if (bonus > 22) {
            im_superJump.draw(renderer,(perso.getX()-40*salle)*TAILLE_SPRITE,(perso.getY()-1.5)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
          }
          else if (bonus > 11) {
            im_jambon.draw(renderer,(perso.getX()-40*salle)*TAILLE_SPRITE,(perso.getY()-1.5)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
          }
          else if (bonus > 1) {
            im_couteauDroite.draw(renderer,(perso.getX()-40*salle)*TAILLE_SPRITE,(perso.getY()-1.5)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
          }


        	// Afficher le sprite du personnage
        	if ((attaque == 0)) {
        		if (cote == 2)
              {
                im_personnageDroite.draw(renderer,(perso.getX()-40*salle)*TAILLE_SPRITE,(perso.getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
              }

        		else if (cote == 1)
            {
              im_personnageGauche.draw(renderer,((perso.getX()-0.5)-40*salle)*TAILLE_SPRITE,(perso.getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
        	  }
          }

        	else if (attaque == 1) {
        		if (cote == 1)
            {
              im_personnageAttaqueGauche.draw(renderer,((perso.getX()-0.5)-40*salle)*TAILLE_SPRITE,(perso.getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
            }
        		else if (cote == 2) {
              im_personnageAttaqueDroite.draw(renderer,(perso.getX()-40*salle)*TAILLE_SPRITE,(perso.getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
            }
        	}

          if (invulnerabilite != 0){
            im_bouclierGauche.draw(renderer,(perso.getX()-1.5-40*salle)*TAILLE_SPRITE,(perso.getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
            im_bouclierDroite.draw(renderer,(perso.getX()+0.5-40*salle)*TAILLE_SPRITE,(perso.getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);

          }

        	// Affichage des projectiles

          for (unsigned int k=0; k<NB_PROJECTILE;k++)
          {
            if (jeu.getProjectile(k).getX() >=0) // utile si les projectiles sont morts
            {
              if (jeu.getProjectile(k).getSalle()-1 == salle)
              {
                if (jeu.getProjectile(k).getType() == 1)
                {
                  if (jeu.getProjectile(k).getDir() == -1) { im_couteauGauche.draw(renderer,(jeu.getProjectile(k).getX()-40*salle)*TAILLE_SPRITE,(jeu.getProjectile(k).getY())*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);}
                  else im_couteauDroite.draw(renderer,(jeu.getProjectile(k).getX()-40*salle)*TAILLE_SPRITE,(jeu.getProjectile(k).getY())*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
                }
              }
            }
          }

          for (unsigned int k=0; k<NB_PROJECTILE_ENNEMIS;k++)
          {
            if (jeu.getProjectileEnnemis(k).getX() >=0) // utile si les projectiles sont morts
            {
              if (jeu.getProjectileEnnemis(k).getSalle()-1 == salle)
              {
                if (jeu.getProjectileEnnemis(k).getType() == 2)
                {
                  if (jeu.getProjectileEnnemis(k).getDir() == -1) { im_bouleDeFeu.draw(renderer,(jeu.getProjectileEnnemis(k).getX()-40*salle)*TAILLE_SPRITE,(jeu.getProjectileEnnemis(k).getY())*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);}
                  else im_bouleDeFeu.draw(renderer,(jeu.getProjectileEnnemis(k).getX()-40*salle)*TAILLE_SPRITE,(jeu.getProjectileEnnemis(k).getY())*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
                }
              }
            }
          }

          for (unsigned int k=0; k<NB_PROJECTILE_DRAGON;k++)
          {
            if (jeu.getProjectileDragon(k).getX() >=0) // utile si les projectiles sont morts
            {
              if (jeu.getProjectileDragon(k).getSalle()-1 == salle)
              {
                if (jeu.getProjectileDragon(k).getType() == 2)
                {
                  im_bouleDeFeu.draw(renderer,(jeu.getProjectileDragon(k).getX()-40*salle)*TAILLE_SPRITE,(jeu.getProjectileDragon(k).getY())*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);

                }
              }
            }
          }


          //Affiche le sprite des Ennemis

          for (unsigned int k=0; k<NB_ENNEMIS;k++)
          {
            if (jeu.getEnnemis(k).getX() >=0) // utile si les ennemis sont morts
            {
              if (jeu.getEnnemis(k).getSalle()-1 == salle)
              {
                if (jeu.getEnnemis(k).getType() == 1) // zombie
                  {
                    if (jeu.getEnnemis(k).getDir() == 0) { im_zombieGauche.draw(renderer,(jeu.getEnnemis(k).getX()-0.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);}
                    else im_zombieDroite.draw(renderer,(jeu.getEnnemis(k).getX()-0.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
                  }
                else if (jeu.getEnnemis(k).getType() == 2) // chauveSouris
                  {
                    im_chauveSouris.draw(renderer,(jeu.getEnnemis(k).getX()-0.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
                  }
                else if (jeu.getEnnemis(k).getType() == 3) // slime
                  {
                    if (jeu.getEnnemis(k).getDir() == 0) { im_slimeGauche.draw(renderer,(jeu.getEnnemis(k).getX()-0.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);}
                    else im_slimeDroite.draw(renderer,(jeu.getEnnemis(k).getX()-0.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
                  }
        	      else if (jeu.getEnnemis(k).getType() == 4) // petit_slime
                  {
                    if (jeu.getEnnemis(k).getDir() == 0) { im_petitSlimeGauche.draw(renderer,(jeu.getEnnemis(k).getX()-40*salle)*TAILLE_SPRITE,jeu.getEnnemis(k).getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);}
                    else im_petitSlimeDroite.draw(renderer,(jeu.getEnnemis(k).getX()-40*salle)*TAILLE_SPRITE,jeu.getEnnemis(k).getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
                  }
                else if (jeu.getEnnemis(k).getType() == 5) // sorcier
                  {
                    if (jeu.getEnnemis(k).getDir() == 0) {
                      im_sorcierGauche.draw(renderer,(jeu.getEnnemis(k).getX()-0.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
                      if (bouclierCouteau >0)
                      {
                        im_bouclierGauche.draw(renderer,(jeu.getEnnemis(k).getX()-1.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
                      }
                    }
                    else {
                      im_sorcierDroite.draw(renderer,(jeu.getEnnemis(k).getX()-0.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
                      if (bouclierCouteau >0)
                      {
                        im_bouclierDroite.draw(renderer,(jeu.getEnnemis(k).getX()+0.5-40*salle)*TAILLE_SPRITE,(jeu.getEnnemis(k).getY()-0.5)*TAILLE_SPRITE,TAILLE_SPRITE*1.5,TAILLE_SPRITE*1.5);
                      }
                    }
                  }
              }
            }
          }


          //Affichage du dragon

          im_dragon.draw(renderer,(jeu.getDragon().getX()-40*salle)*TAILLE_SPRITE,(jeu.getDragon().getY()-3)*TAILLE_SPRITE,TAILLE_SPRITE*6,TAILLE_SPRITE*4);


        	// Affichage de la vie
        	if (salle > 0) {
        		for (i=1;i<=perso.getVie();i++) {
        		im_coeur.draw(renderer,(5+i)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
        		}
        	}

		// Affichage de l'inventaire
		if (salle > 0) im_inventaire.draw(renderer,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE*5,TAILLE_SPRITE);
		if (jeu.getTestProjectile() == 1) {
			im_couteauDroite.draw(renderer,TAILLE_SPRITE*1.05,TAILLE_SPRITE,TAILLE_SPRITE*0.9,TAILLE_SPRITE);
			if (jeu.getTestSuperJump() == 1) im_superJump.draw(renderer,2*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
		}
		else if (jeu.getTestProjectile() == 0) {
			if (jeu.getTestSuperJump() == 1) im_superJump.draw(renderer,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
		}

    		// Affichage du score
		if (salle > 0) {
			sprintf(score, "Score: %d", jeu.getScore());
			texteScore = TTF_RenderText_Blended(police, score, couleur);

			positionScore.x = TAILLE_SPRITE;
      			positionScore.y = 0;
			positionScore.w = TAILLE_SPRITE*3;
			positionScore.h = TAILLE_SPRITE;
			textureScore = SDL_CreateTextureFromSurface(renderer,texteScore);
			SDL_FreeSurface(texteScore);
       			SDL_UpdateTexture(textureScore,NULL,texteScore->pixels,texteScore->pitch);
			SDL_RenderCopy(renderer,textureScore,NULL,&positionScore);
			SDL_DestroyTexture(textureScore);
		}
			
		// Affichage du numero de la salle
		if (salle > 1) {
			sprintf(numSalle, "Salle: %d", salle-1);
			texteSalle = TTF_RenderText_Blended(police, numSalle, couleur);

			positionSalle.x = 5*TAILLE_SPRITE;
      			positionSalle.y = 0;
			positionSalle.w = TAILLE_SPRITE*3;
			positionSalle.h = TAILLE_SPRITE;
			textureSalle = SDL_CreateTextureFromSurface(renderer,texteSalle);
			SDL_FreeSurface(texteSalle);
       			SDL_UpdateTexture(textureSalle,NULL,texteSalle->pixels,texteSalle->pitch);
			SDL_RenderCopy(renderer,textureSalle,NULL,&positionSalle);
			SDL_DestroyTexture(textureSalle);
		}


    }
}


void sdlJeu:: sdlBoucle () {
    	SDL_Event events;
	const Terrain& ter = jeu.getConstTerrain();
	const Personnage& perso = jeu.getConstPersonnage();
	bool quit = true;
	bool touche_droit = false, touche_gauche = false, touche_saut = false, touche_attaque = false, touche_lance = false;
	unsigned int test=0, invulnerabilite=0, jump=0, cote=2, attaque=0, testLance = 0, bouclierCouteau = 0, testMort = 0, testFondS1 = 0, testRepoussage = 0;;
	int nbProj = 0, nbProjEnnemis = 0, nbProjDragon = 0;

    Uint32 t = SDL_GetTicks(), nt;

	while (quit) {
        nt = SDL_GetTicks();
        if (nt-t>75) {
            	t = nt;

		while (SDL_PollEvent(&events)) {
			switch (events.type) {
				case SDL_QUIT:
					quit = false;
					break;

				case SDL_KEYDOWN:
					jeu.setTestDeplaceSalle1(1);
					switch (events.key.keysym.sym) {
						case SDLK_RIGHT:
							touche_droit = true;
							break;
						case SDLK_LEFT:
							touche_gauche = true;
							break;
						case SDLK_SPACE:
							touche_saut = true;
							break;
						case SDLK_a:
							if (attaque == 0) {
								touche_attaque = true;
								attaque = 1;
							}
							break;
						case SDLK_z:
							touche_lance = true;
							break;
						case SDLK_ESCAPE:
                    					quit = false;
							break;
					}
					break;

				case SDL_KEYUP:
					switch (events.key.keysym.sym) {
						case SDLK_RIGHT:
							touche_droit = false;
							break;
						case SDLK_LEFT:
							touche_gauche = false;
							break;
						case SDLK_SPACE:
							touche_saut = false;
							break;
						case SDLK_a:
							touche_attaque = false;
							attaque = 0;
							break;
						case SDLK_z:
							touche_lance = false;
							break;
					}
					break;
			}
		}

		if ((ter.numeroSalle(perso.getX(),perso.getY()) > 1) && (testMort == 0) && testRepoussage == 0) {
			if (touche_saut) {
				if ((jump == 0) && (ter.estPositionStructure(perso.getX(),perso.getY()+1)) && (jeu.getTestSuperJump() == 1)) jump = 10;
				if ((jump == 0) && (ter.estPositionStructure(perso.getX(),perso.getY()+1)) && (jeu.getTestSuperJump() == 0)) jump = 8;
			}
			if (jump > 4) {
				jeu.actionClavier(' ',cote,nbProj,testRepoussage);
			}
			if (touche_droit)  jeu.actionClavier('d',cote,nbProj,testRepoussage);
			if (touche_gauche) jeu.actionClavier('q',cote,nbProj,testRepoussage);
			if (touche_attaque) {
				jeu.actionClavier('k',cote,nbProj,testRepoussage);
				touche_attaque = false;
			}
			else if (touche_lance && (testLance == 0)) {
				testLance = 10;
				jeu.actionClavier('z',cote,nbProj,testRepoussage);
				touche_lance = false;
			}
			if (testLance > 0) testLance--;

    			if (test == 15) test = 0;
			else test++;

			if (jump > 0) {
				jump--;
			}
		}
  /*  if (testRepoussage > 0)
    {
      if (ter.estPositionPersoValide(perso.getX()-1, perso.getY())) { perso.setX(5);} //perso.getX()-1);} // MARCHE PAS
      testRepoussage--;
    }*/
		if (testMort > 0) {
			testMort--;
		}
		if (testFondS1 > 0) testFondS1--;
		else if (testFondS1 == 0) testFondS1 = 10;
		if ((ter.numeroSalle(perso.getX(),perso.getY()) == 1) && (jeu.getTestDeplaceSalle1() == 1)) jeu.actionClavier('d', cote, nbProj,testRepoussage);
		if (testMort == 0) jeu.actionsAutomatiques(test,invulnerabilite,jump, perso.getX(), perso.getY(), nbProjEnnemis,  nbProjDragon, bouclierCouteau, testMort);

	}
		sdlAff(cote,attaque,bouclierCouteau,testMort,testFondS1, invulnerabilite);

        	SDL_RenderPresent(renderer);
	}
}
