#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <vector>
#include <utility>
#include "MapManager.h"
using namespace std;



class Snake {
    int x, y;
    pair<int, int> lastPos;
    //몸통의 마지막 좌표. 몸통길이를 증가시킬 때 필요함.

    int len;
    int growCnt;
    int poisCnt;
    int gateCnt;
    int dir; //dx,dy 를 조절할 수 있는 방향.

    vector<pair<int,int> > bodies;
    //몸통의 좌표들을 담고있음. pair first가 x좌표, second가 y좌표.
public:
    
    Snake() {}
    Snake(int x, int y);
    Snake(pair<int,int> pos);
    
    void updateSnake(); 
    //업데이트 스네이크, 스네이크를 움직인다.

    int getX();
    int getY();
    pair<int,int> getXYPair();
    int getLen();
    int getGrowCnt();
    int getPoisCnt();
    int getGateCnt();
    
    vector<pair<int,int> > getBodies(); 

    bool setDir(int d); 
    //머리방향을 바꿈, 이때 머리방향과 반대방향으로 바꾸려고 하면 false리턴.

    bool decreaseBody(); //몸통길이 감소, 3보다 작아지면 false를 리턴하고 게임오버
    void growBody(); //몸통길이 증가

    void inGate(MapManager *MapMan);

    bool conflictCheck();
};
#endif