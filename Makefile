all:
	g++ -std=c++20 -fshort-wchar main.cpp Snake.cpp MapManager.cpp -L/usr/local/opt/ncurses/lib -lncursesw -o ./main
