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
����
 �ܴ�����û��һ���Ĵ���֮��
 ÿ������a,b��c,d���Ĵ�����c,d�ϵ�ֵ������a,b�ϵ�״̬�ĳ˻�
 ��ʼ״̬Ϊ1     ÿ��һ����״̬�����¹�ʽ�仯�������ⲽ�Ĵ���%4��+1��
 */
 
void dfs(int x, int y, int val, int state){
    //��������
    if (x == t_x && y == t_y){
        if (val <= res) res = val;
        return;
    }

    //��֦
    if (val >= res){
        return;
    }
 
    //�ǵ�ǰ�ڵ��ѷ��ʹ�
    visited[x][y] = true;
    for (int i=0; i<4; i++){
        int new_x = x + dir[i][0];
        int new_y = y + dir[i][1];
 
        // ��һ���ڵ������ && δ���ʹ�
        if (map[new_x][new_y] != 0 && !visited[new_x][new_y]){
            visited[new_x][new_y] = true;
            int cur_val = map[new_x][new_y] * state;
            dfs(new_x, new_y, val+cur_val, cur_val%4+1);
            visited[new_x][new_y] = false;
        }
    }
}
 
 
 
int main(){
 
    //8*8���� ��֤����Χ��һ�㶼��0
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
