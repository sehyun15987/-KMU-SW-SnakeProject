#include "Snake.h"

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
// 0 == Right, 1 == Left, 2 == Down, 3 == Up;

Snake::Snake(int x, int y) : x(x), y(y) {
  for(int i = 1; i <= 2; i++) {
    bodies.push_back(make_pair(x, y + i));
  }
  dir = 1;
  lastPos = make_pair(x, y + 3);
  len = 3;
  growCnt = 0;
  poisCnt = 0;
  gateCnt = 0;
}

Snake::Snake(pair<int,int> pos) {
  x = pos.first;
  y = pos.second;
  for(int i = 1; i <= 2; i++) {
    bodies.push_back(make_pair(x, y + i));
  }
  dir = 1;
  lastPos = make_pair(x, y + 3);
  len = 3;
  growCnt = 0;
  poisCnt = 0;
  gateCnt = 0;
}

void Snake::updateSnake() {
  lastPos = bodies.back();
  for(int i = (int)(bodies.size()) - 1; i > 0; i--) {
    bodies[i] = bodies[i - 1];
  }
  bodies[0] = make_pair(x, y);
  x += dx[dir];
  y += dy[dir];
}


int Snake::getX() {
  return x;
}
int Snake::getY() {
  return y;
}
pair<int,int> Snake::getXYPair() {
  return make_pair(x, y);
}
int Snake::getLen() {
  return len;
}

int Snake::getGrowCnt() {
  return growCnt;
}

int Snake::getPoisCnt() {
  return poisCnt;
}

int Snake::getGateCnt() {
  return gateCnt;
}

vector<pair<int,int> > Snake::getBodies() {
  return bodies;
}

bool Snake::decreaseBody() {
  len -= 1;
  this->bodies.pop_back();
  if(len < 3) return false;
  return true;
}

void Snake::growBody() {
  this->bodies.push_back(this->lastPos);
  len += 1;
}

bool Snake::setDir(int d) {
  if(d == 0) {
    if(dir == 1) return false; 
  } else if(d == 1) {
    if(dir == 0) return false;
  } else if(d == 2) {
    if(dir == 3) return false;
  } else {
    if(dir == 2) return false;
  }
  dir = d;
  return true;
}