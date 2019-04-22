#include <iostream>
 
using namespace std;
 
int map[8][8];
bool visited[8][8];
int res = 0x3f3f3f3f;

//right left up down
int dir[4][2] = {{ 1, 0},
                 {-1, 0},
                 { 0, -1},
                 { 0, 1}};
 
int s_x, s_y, t_x, t_y;
 
 /*
规则：
 总代价是没走一步的代价之和
 每步（从a,b到c,d）的代价是c,d上的值与其在a,b上的状态的乘积
 初始状态为1     每走一步，状态按如下公式变化：（走这步的代价%4）+1。
 */
 
void dfs(int x, int y, int val, int state){
    //搜索结束
    if (x == t_x && y == t_y){
        if (val <= res) res = val;
        return;
    }

    //剪枝
    if (val >= res){
        return;
    }
 
    //记当前节点已访问过
    visited[x][y] = true;
    for (int i=0; i<4; i++){
        int new_x = x + dir[i][0];
        int new_y = y + dir[i][1];
 
        // 下一个节点可以走 && 未访问过
        if (map[new_x][new_y] != 0 && !visited[new_x][new_y]){
            visited[new_x][new_y] = true;
            int cur_val = map[new_x][new_y] * state;
            dfs(new_x, new_y, val+cur_val, cur_val%4+1);
            visited[new_x][new_y] = false;
        }
    }
}
 
 
 
int main(){
 
    //8*8棋盘 保证最外围的一层都是0
    for (int i=1; i<=6; i++){
        for (int j=1; j<=6; j++){
            cin >> map[i][j];
        }
    }
 
    cin >> s_x >> s_y >> t_x >> t_y;
    s_x++;
    s_y++;
    t_x++;
    t_y++;
 
    visited[s_x][s_y] = true;
    dfs(s_x, s_y, 0, 1);
    cout<<res << endl;
}
