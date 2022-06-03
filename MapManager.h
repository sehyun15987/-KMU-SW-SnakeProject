#ifndef __MAPMAN_H__
#define __MAPMAN_H__
#include <utility>
#include <ctime>
#include <cstdlib>
using namespace std;

// 0 == empty
// 1 == wall
// 2 == immunewall
// 3 == grow
// 4 == poison
// 5 == gate

class MapManager {
private:
    pair<int,int> initPos;
    int **CurMap;
    int StageCnt;
    int growX[2];
    int growY[2];
    int poisX[2];
    int poisY[2];
    int gat1X, gat2X, gat1Y, gat2Y;

public:
    MapManager(int StageCnt);
    int **getMap() {return CurMap;}
    pair<int,int> getInitPos() {return initPos;}
    void groPoisGateReset();
    void groPoisGateSet();
};
#endif