#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include "../core/Jeu.h"

void txtAff(WinTXT & win, const Jeu & jeu, unsigned int & cote, int & tempsArme) {
	const Terrain& ter = jeu.getConstTerrain();
	const Personnage& perso = jeu.getConstPersonnage();
	const Ennemis& zombie1 = jeu.getConstEnnemis(1);

	win.clear();

    	// Affichage du terrain
	for(int x=0;x<ter.getDimX();++x)
		for(int y=0;y<ter.getDimY();++y)
			win.print(x,y,ter.getXY(x,y));

    	// Affichage du Personnage
	win.print(perso.getX(),perso.getY(),'0');

	// Affichage du Ennemis
	win.print(zombie1.getX(),zombie1.getY(),'Z');

	// Affichage de la vie
	win.print(6,1,perso.getVie()+48);

	// Affichage de l'arme
	if (tempsArme == 0)
	{
		win.print(perso.getX()-1,perso.getY(),' ');
		win.print(perso.getX()+1,perso.getY(),' ');
		tempsArme = -1;
	}
	else if (cote == 1 && tempsArme > 0 ) {
		win.print(perso.getX()-1,perso.getY(),'-');
		tempsArme--;
	}
	else if (cote == 2 && tempsArme > 0) {
		win.print(perso.getX()+1,perso.getY(),'-');
		tempsArme--;
	}

	win.draw();
}

void AffDefaite(WinTXT & win) {
	win.clear();
	const char def[15][57] = {
 "########################################################",
 "#                                                      #",
 "#                                                      #",
 "#                                                      #",
 "#             #       ######  ######  ######           #",
 "#             #       #    #  #       #                #",
 "#             #       #    #  #       #                #",
 "#             #       #    #  ######  ######           #",
 "#             #       #    #       #  #                #",
 "#             #       #    #       #  #                #",
 "#             ######  ######  ######  ######           #",
 "#                                                      #",
 "#                                                      #",
 "#                                                      #",
 "########################################################"
};
	for(int x=0;x<57;++x)
		for(int y=0;y<15;++y)
			win.print(x,y,def[y][x]);
	win.draw();
}

void AffVictoire(WinTXT & win) {
	win.clear();
	const char vic[15][57] = {
 "########################################################",
 "#                                                      #",
 "#                                                      #",
 "#                                                      #",
 "#                                                      #",
 "#             #      #  #######  #    #                #",
 "#             #      #     #     ##   #                #",
 "#             #      #     #     # #  #                #",
 "#             #  ##  #     #     #  # #                #",
 "#             # #  # #     #     #   ##                #",
 "#             #      #  #######  #    #                #",
 "#                                                      #",
 "#                                                      #",
 "#                                                      #",
 "########################################################"
};
	for(int x=0;x<57;++x)
		for(int y=0;y<15;++y)
			win.print(x,y,vic[y][x]);
	win.draw();
}

void txtBoucle (Jeu & jeu) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WinTXT win (jeu.getConstTerrain().getDimX(),jeu.getConstTerrain().getDimY());
	unsigned int test=0, invulnerabilite=0, jump=0, cote=2;
	bool ok = true;
	int nbProj = 0;
	const Terrain& ter = jeu.getConstTerrain();
	const Personnage& perso = jeu.getConstPersonnage();
	int c, tempsArme=0, nbProjEnnemis=0;
	do {
	txtAff(win,jeu,cote,tempsArme);
	usleep(100000);
        #ifdef _WIN32
		#else
        #endif // WIN32
	jeu.actionsAutomatiques(test,invulnerabilite,jump, perso.getX(), perso.getY(), int & nbProjEnnemis);
		c = win.getCh();
		switch (c) {
			case 'q':
				jeu.actionClavier('q',cote,nbProj);
				break;
			case 'd':
				jeu.actionClavier('d',cote,nbProj);
				break;
			case ' ':
				if ((jump == 0) && (ter.estPositionStructure(perso.getX(),perso.getY()+1))) jump = 4;
				break;
			case 'k':
				jeu.actionClavier('k',cote,nbProj);
				tempsArme = 3;
				break;
			case 'w':
				ok = false;
				break;
		}
	if (test == 0) test = 1;
	else test = 0;
	if (jump > 0) {
		jump--;
		jeu.actionClavier(' ',cote,nbProj);
	}
	if (jeu.actionsVictoire() || jeu.actionsDefaite()) ok = false;
	} while (ok);

	if (jeu.actionsVictoire()) {
		AffVictoire(win);
		sleep(5);
	}
	if (jeu.actionsDefaite()) {
		AffDefaite(win);
		sleep(5);
	}
}
