#ifndef __MAPMAN_H__
#define __MAPMAN_H__
#include <utility>
using namespace std;

class MapManager {
private:
    pair<int,int> initPos;
    int **CurMap;
    int StageCnt;

public:
    MapManager(int StageCnt);
    int **getMap() {return CurMap;}
    pair<int,int> getInitPos() {return initPos;}
};
#endif