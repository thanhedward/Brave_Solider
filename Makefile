all:
	g++ -ISDL2\include\SDL2 -LSDL2\lib -o main main.cpp baseObject.cpp BulletObject.cpp commonFunction.cpp ExplosionObject.cpp game_map.cpp Geometric.cpp ImpTimer.cpp MainObject.cpp PlayerPower.cpp TextObject.cpp ThreatObject.cpp -lmingw32 -lSDL2main -lSDL2  -lSDL2_image -lSDL2_ttf -lSDL2_mixer
