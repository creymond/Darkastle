all: DarkastleSdl.out deplaceObj

UNAME_S = $(shell uname)
ifeq ($(UNAME_S),Windows_NT)
	INCLUDE_DIR_SDL = 	-Iextern/SDL2_mingw/SDL2-2.0.3/include \
						-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2
	LIBS_SDL = 	-Lextern \
			-Lextern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/lib \
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll
else

	ifeq ($(UNAME_S),Darwin)
		DIR_SDL = -I/usr/local/include/SDL2
		LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image
	endif

	ifeq ($(UNAME_S), Linux)
		DIR_SDL = -I/usr/include/SDL2
		LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image
	endif
endif

DarkastleSdl.out: Jeu.o Ennemis.o Projectile.o Personnage.o Plateforme.o Terrain.o main_sdl.o sdlJeu.o Dragon.o
	g++ -g Jeu.o Ennemis.o Personnage.o Projectile.o Plateforme.o Terrain.o main_sdl.o sdlJeu.o Dragon.o -o bin/DarkastleSdl.out $(LIBS_SDL)

main_sdl.o: src/sdl2/sdlJeu.h src/sdl2/main_sdl.cpp
	g++ -g -Wall -c src/sdl2/main_sdl.cpp $(DIR_SDL)

sdlJeu.o: src/sdl2/sdlJeu.h src/sdl2/sdlJeu.cpp
	g++ -g -Wall -c src/sdl2/sdlJeu.cpp $(DIR_SDL)

Jeu.o: src/core/Jeu.h src/core/Jeu.cpp
	     g++ -g -Wall -c src/core/Jeu.cpp

Plateforme.o: src/core/Plateforme.h src/core/Plateforme.cpp
	     g++ -g -Wall -c src/core/Plateforme.cpp

Projectile.o: src/core/Projectile.h src/core/Projectile.cpp
	     g++ -g -Wall -c src/core/Projectile.cpp

Ennemis.o: src/core/Ennemis.h src/core/Ennemis.cpp
	     g++ -g -Wall -c src/core/Ennemis.cpp

Personnage.o: src/core/Personnage.h src/core/Personnage.cpp
	     g++ -g -Wall -c src/core/Personnage.cpp

Terrain.o: src/core/Terrain.h src/core/Terrain.cpp
	     g++ -g -Wall -c src/core/Terrain.cpp

Dragon.o: src/core/Dragon.h src/core/Dragon.cpp
	     g++ -g -Wall -c src/core/Dragon.cpp

clean:
	rm obj/*.o

veryclean: clean
	   rm bin/*.out


deplaceObj:
	mv *.o obj
