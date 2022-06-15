all:
	g++ -std=c++20 -fshort-wchar main.cpp Snake.cpp MapManager.cpp -lncursesw -o ./main
