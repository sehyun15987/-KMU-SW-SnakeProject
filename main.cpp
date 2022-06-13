#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <clocale>
#include "Snake.h"
using namespace std;

bool inGate(Snake& snake, int **CurMap) {
  if(CurMap[snake.getX()][snake.getY()] == 5) return true;
  vector<pair<int, int> > bodies = snake.getBodies();
  for(pair<int, int> &p : bodies) {
    if(CurMap[p.first][p.second] == 5) return true;
  }
  return false;
}
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
  WINDOW *missionWin;

  //game
  gameWin = newwin(32,32,1,2);
  wbkgd(gameWin, COLOR_PAIR(1));
  wattron(gameWin, COLOR_PAIR(1));
  wborder(gameWin,'+','+','+','+','#','#','#','#');
  wrefresh(gameWin);
  

  //score
  scoreWin = newwin(14,30,1,63);
  wbkgd(scoreWin, COLOR_PAIR(1));
  wattron(scoreWin, COLOR_PAIR(1));
  wborder(scoreWin, '|', '|', '-', '-', '#', '#', '#', '#');
  mvwprintw(scoreWin, 1, 9, "SCORE BOARD");
  wrefresh(scoreWin);

  //mission
  missionWin = newwin(17,30,16,63);
  wbkgd(missionWin, COLOR_PAIR(1));
  wattron(missionWin, COLOR_PAIR(1));
  wborder(missionWin, '|', '|', '-', '-', '#', '#', '#', '#');
  mvwprintw(missionWin, 1, 8, "MISSION BOARD");
  wrefresh(missionWin);



  int StageCnt = 0;
  bool isGameOver = false;
  while(StageCnt < 3 && !isGameOver) {
    MapManager MapMan(StageCnt);
    Snake snake(MapMan.getInitPos());
    MapMan.groPoisSet();
    MapMan.gateSet();
    int **CurMap = MapMan.getMap();
    int turn = 1;
    bool missionFlag[4] = {false, };
    while(!isGameOver && turn++) {
      
      if(turn > 50) {
        MapMan.groPoisReset();
        MapMan.groPoisSet();
        if(!inGate(snake,CurMap)) {
          MapMan.gateReset();
          MapMan.gateSet();
        }
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
            nextDir = 3;
            break;
          case KEY_LEFT:
            nextDir = 1;
            break;
          case KEY_DOWN:
            nextDir = 0;
            break;
          case KEY_UP:
            nextDir = 2;
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
      } else if(headPos == 5) {
        snake.inGate(&MapMan);
      }
      

      vector<pair<int,int> > bodies = snake.getBodies();
      for(int i = 0; i < bodies.size(); i++) { 
        const int &Bx = bodies[i].first;
        const int &By = bodies[i].second;
        if(Bx == snake.getX() && By == snake.getY()) { //몸통과 머리가 만나면 게임오버
          isGameOver = true;
          break;
        }
      }


      wborder(gameWin,'+','+','+','+','#','#','#','#');
      for (int i = 1; i < 31; i++)
        for (int j = 1; j < 31; j++) {
          mvwprintw(gameWin, i, j, " "); // 게임화면 초기화
          if(CurMap[i][j] == 1 || CurMap[i][j] == 2) {
            mvwprintw(gameWin, i, j, "+");
          } else if(CurMap[i][j] == 3) { //grow 아이템
            mvwprintw(gameWin, i, j, "G");
          } else if(CurMap[i][j] == 4) { // poison 아이템
            mvwprintw(gameWin, i, j, "P");
          }
        }
      for(int i = 0; i < 2; i++) {
        mvwprintw(gameWin, MapMan.gateX[i], MapMan.gateY[i], "W"); // gate,warp
      }
          

      

      mvwprintw(gameWin, snake.getX(), snake.getY(), "@"); //머리출력
      for (int i = 0; i < bodies.size(); i++)
      {
        const pair<int,int> &p = bodies[i];
        mvwprintw(gameWin, p.first, p.second, "O"); //몸통 출력
      }
      wrefresh(gameWin);

      mvwprintw(scoreWin, 3, 9, "Size : %d / (15)", bodies.size() + 1);
      mvwprintw(scoreWin, 5, 9, "Grow : %d", snake.getGrowCnt());
      mvwprintw(scoreWin, 7, 9, "Pois : %d", snake.getPoisCnt());
      mvwprintw(scoreWin, 9, 9, "Gate : %d", snake.getGateCnt());
      wrefresh(scoreWin);

      if(bodies.size() + 1 >= 2) missionFlag[0] = true; // 미션 목표 수치
      if(snake.getGrowCnt() >= 2) missionFlag[1] = true;
      if(snake.getPoisCnt() >= 2) missionFlag[2] = true;
      if(snake.getGateCnt() >= 2) missionFlag[3] = true;
      mvwprintw(missionWin, 4, 9, "Size : 5 (%c)", missionFlag[0] ? 'V' : ' ');
      mvwprintw(missionWin, 7, 9, "Grow : 6 (%c)", missionFlag[1] ? 'V' : ' ');
      mvwprintw(missionWin, 10, 9, "Pois : 4 (%c)", missionFlag[2] ? 'V' : ' ');
      mvwprintw(missionWin, 13, 9, "Gate : 2 (%c)", missionFlag[3] ? 'V' : ' ');
      wrefresh(missionWin);
      int cnt = 0;
      for(int i = 0; i < 4; i++) {
        cnt += missionFlag[i];
      }
      if(cnt == 4) {
        StageCnt += 1;
        break;
      }
    }
  }
  return 0;
}