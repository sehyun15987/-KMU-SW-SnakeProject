all:
	g++ -std=c++20 -fshort-wchar GameWindow.cpp -L/usr/local/opt/ncurses/lib -lncursesw -o ./main
