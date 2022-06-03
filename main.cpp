#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <clocale>
#include "Snake.h"
#include "MapManager.h"
using namespace std;

/********************************************************/
// kbhit()함수 일단 복붙해서 가져옴.
bool kbhit()
{
  int ch;
  bool ret;

  nodelay(stdscr, TRUE);

  ch = getch();
  if (ch == ERR) {
    ret = false; //키 입력이 없을 경우 false 반환
  } else {
    ret = true;  //키 입력이 있을 경우 true 반환
    ungetch(ch); // 마지막에 받은 문자를 버퍼에 다시 넣어서 다음 getch()가 받을 수 있도록 함
  }

  nodelay(stdscr, FALSE);
  return ret;
}
/********************************************************/


int main() {

  initscr(); //메인화면
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
  start_color();
  resize_term(34, 95);
  border('|','|','-','-','+','+','+','+');
  mvprintw(1,44,"SNAKE GAME");
  refresh();
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  WINDOW *gameWin;
  WINDOW *scoreWin;
  

  //game
  gameWin = newwin(32,32,1,2);
  wbkgd(gameWin, COLOR_PAIR(1));
  wattron(gameWin, COLOR_PAIR(1));
  wborder(gameWin,'+','+','+','+','#','#','#','#');
  
  wrefresh(gameWin);
  

  //score
  scoreWin = newwin(10,30,1,63);
  wbkgd(scoreWin, COLOR_PAIR(1));
  wattron(scoreWin, COLOR_PAIR(1));
  wborder(scoreWin, '|', '|', '-', '-', '#', '#', '#', '#');
  mvwprintw(scoreWin, 1, 10, "SCORE BOARD");
  wrefresh(scoreWin);



  int StageCnt = 0;
  bool isGameOver = false;
  while(StageCnt < 3 && !isGameOver) {
    MapManager MapMan(StageCnt);
    Snake snake(MapMan.getInitPos());
    isGameOver = false;
    MapMan.groPoisGateSet();
    int **CurMap = MapMan.getMap();
  
    int turn = 1;
    while(!isGameOver && turn++) {
      
      if(turn > 50) {
        MapMan.groPoisGateReset();
        MapMan.groPoisGateSet();
        CurMap = MapMan.getMap();
        turn = 1;
      }
      
      int nextDir = -1;
      
      long int refTime = clock(); //프로그램이 시작한 시점부터 현재까지 경과한 시간
      long int currentTime = 0;
      while (1)
      {
        if (kbhit())
        {                   //키 입력이 확인되었을 때
          int ch = getch(); //키 입력 받기
          switch (ch) {
          case KEY_RIGHT:
            nextDir = 0;
            break;
          case KEY_LEFT:
            nextDir = 1;
            break;
          case KEY_DOWN:
            nextDir = 2;
            break;
          case KEY_UP:
            nextDir = 3;
            break;
          default:
            break;
          }
          if(nextDir == -1)
            continue;
          
          if (snake.setDir(nextDir) != true)
          {
            isGameOver = true;
          }
        }
        
        /*프로그램이 시작한 시점부터 키 입력 확인 및 반영 기능 이후까지 경과한 시간에서
                    프로그램 시작 시점부터 입력 받기 전까지 경과한 시간의 차*/
        currentTime += clock() - refTime;
        if (currentTime > clock_t(10000000000)) break;
      }

      if(isGameOver) break; // 반대방향 입력이 들어온거므로 반복문 종료.

      
      //머리 위치의 맵 상태
      snake.updateSnake();
      int &headPos = CurMap[snake.getX()][snake.getY()];
      if(headPos == 1 || headPos == 2) { //벽이면 게임오버
        isGameOver = true;
        break;
      } else if(headPos == 3) {
        snake.growBody();
        headPos = 0;
      } else if (headPos == 4) {
        if(!snake.decreaseBody()) {
          isGameOver = true;
          break;
        }
        headPos = 0;
      }
      

      vector<pair<int,int> > bodies = snake.getBodies();
      for(int i = 0; i < bodies.size(); i++) { 
        if(bodies[i].first == snake.getX() && bodies[i].second == snake.getY()) {
          //몸통과 머리가 만나면 게임오버
          isGameOver = true;
          break;
        }
      }

      for (int i = 1; i < 31; i++)
        for (int j = 1; j < 31; j++) {
          mvwprintw(gameWin, i, j, " "); // 게임화면 초기화
          if(CurMap[i][j] == 3) { //grow 아이템
            mvwprintw(gameWin, i, j, "G");
          } else if(CurMap[i][j] == 4) { // poison 아이템
            mvwprintw(gameWin, i, j, "P");
          }
        }
          

      

      mvwprintw(gameWin, snake.getX(), snake.getY(), "@"); //머리출력
      mvwprintw(gameWin, 1, 12, "Head = %d, %d",snake.getX(), snake.getY());
      for (int i = 0; i < bodies.size(); i++)
      {
        const pair<int,int> &p = bodies[i];
        mvwprintw(gameWin, p.first, p.second, "O"); //몸통 출력
        mvwprintw(gameWin, 2+i, 10, "Body:%d = %d, %d",i + 1, p.first, p.second);
      }

    

      
      // else if(headPos == 5) {
        
      // }

      //이쪽에서 게이트와 아이템을 설정
      //한 10~20턴정도마다 초기화되면서 만들어지면
      //MapManager 에 curmap에서 아이템 게이트만듦

      //아이템, 게이트 위치를 따로 MapManager안에 저장해놓고
      //다른 숫자로 바꿨다가 없앨때는 저장해놓은 위치들을 원래대로 돌리고
      //다른 위치에 다시 만듦
      
      wrefresh(gameWin);

    }
  }
  return 0;
}