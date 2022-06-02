#include <ncurses.h>
#include "map.h"



const int W_X = 34;
const int W_Y = 95;

const int G_X = 32;
const int G_Y = 60;

int stage_num = 0; // test cases
int window()
{
  WINDOW *gameWin;
  WINDOW *scoreWin;
  initscr();
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);

  start_color();
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  resize_term(W_X, W_Y);
  border('|','|','-','-','+','+','+','+');
  refresh();

  gameWin = newwin(G_X,G_Y,1,2);
  wbkgd(gameWin,COLOR_PAIR(1));
  wattron(gameWin,COLOR_PAIR(1));



  wrefresh(gameWin);
  /*
  G_Y->32 solve range error
  change string map -> int map
  */
  int xo = 16;
  int yo = 16;
  //map[stage_num][xo][yo]=3;
  for(int i = 0; i<32;i++){
    for(int j = 0;j<32;j++){
      if(map[stage_num][i][j]==2) mvwprintw(gameWin,i,j,"%s","#");
      else if(map[stage_num][i][j]==1) mvwprintw(gameWin,i,j,"%s","+");
      else if(map[stage_num][i][j]==3) mvwprintw(gameWin,i,j,"%s","H");
      else if(map[stage_num][i][j]==4) mvwprintw(gameWin,i,j,"%s","B");

    }
  }
  mvprintw(1,45,"SNAKE GAME");
  wrefresh(gameWin);

  //score
  scoreWin = newwin(10,30,1,63);
  wbkgd(scoreWin, COLOR_PAIR(1));
  wattron(scoreWin, COLOR_PAIR(1));
  wborder(scoreWin, '|', '|', '-', '-', '#', '#', '#', '#');
  mvwprintw(scoreWin, 1, 10, "SCORE BOARD");

  wrefresh(scoreWin);

  getch();
  endwin();

}
