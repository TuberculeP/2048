Compilo = g++

2048 : 2048.cpp

	$(Compilo) -std=c++11 -o 2048 2048.cpp 2048-fonctions.cpp -lsfml-graphics

2048g : 2048-graphic.cpp

	$(Compilo) -std=c++11 -o 2048g 2048-graphic.cpp 2048-fonctions.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

2048c : 2048-ncurses.cpp

	$(Compilo) -std=c++11 -o 2048c 2048-ncurses.cpp -lncurses