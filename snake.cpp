#include <iostream>


using namespace std;

void snake()
{
  //setting
  int body_len = 3;
  //first snake postion
  int xo = 16;
  int yo = 16;

  //snake head
  map[stage_num][xo][yo-1]=3;
  for(int i = 0;i<body_len;i++)
  {
    map[stage_num][xo][yo+i]=4;
  }
}
