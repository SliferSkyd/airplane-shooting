all: 
	g++ -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -I src/include -L src/lib -o main main.cpp SDL_utils.cpp Level.cpp Intro.cpp BaseObject.cpp MainObject.cpp BulletObject.cpp ThreatObject.cpp ExplosionObject.cpp HPObject.cpp BonusObject.cpp TextObject.cpp ButtonObject.cpp target.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf