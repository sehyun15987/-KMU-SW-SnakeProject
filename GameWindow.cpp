#include <ncurses.h>
#include "map.h"

int stage_num = 0; // test cases
int main()
{
  WINDOW *win1;
  initscr();
  start_color();
  init_pair(1,COLOR_WHITE,COLOR_BLACK);

  border('|','|','-','-','+','+','+','+');
  mvprintw(9,12,"SNAKE GAME");
  refresh();

  win1 = newwin(32,32,10,10);
  wbkgd(win1,COLOR_PAIR(1));
  wattron(win1,COLOR_PAIR(1));

  wrefresh(win1);
  //mvwprintw(win1,1,1,"%d",map[stage_num][0][0]);
  for(int i = 0; i<32;i++){
    for(int j = 0;j<32;j++){
      if(map[stage_num][i][j]==2) mvwprintw(win1,i,j,"%s","#");
      else if(map[stage_num][i][j]==1) mvwprintw(win1,i,j,"%s","*");

    }
  }
  wrefresh(win1);
  getch();
  endwin();

}
