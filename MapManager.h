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
// Map 크기 32 * 32


class MapManager {
private:
    pair<int,int> initPos;
    int **CurMap;
    int StageCnt;
    int growX[2];
    int growY[2];
    int poisX[2];
    int poisY[2];
    

public:
    int gateX[2];
    int gateY[2];
    MapManager(int StageCnt);
    // ~MapManager();
    int **getMap() {return CurMap;}
    pair<int,int> getInitPos() {return initPos;}
    void groPoisReset();
    void groPoisSet();
    void gateSet();
    void gateReset();
};
#endif