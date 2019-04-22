/* ����˼�룺
 *  1. e + 1 = v; ע��v����Ϊ��Ҳ��������������л��������Ҳ���԰ѻ��ų�
 *  2. ���Ϊ��Ķ������Ϊ1.(ֻ��һ��root��Ҳ�����ò��鼯)
 */
/* We can sort vector and use unique to remove the same value. 
 * But set is more easy and clean.
 *	vector<int> V;
 *	V.push_back(a); V.push_back(b);
 *	sort(V.begin(), V.end());
 *	auto end_unique = unique(V.begin(), V.end());
 *	V.erase(end_unique, V.end());
 */

#include <stdio.h>
#include <set>
#include <map>

using namespace std;

int main()
{
	int a, b, cas = 1, cnt = 0, edge = 0;
	map<int, int> inDegree;
	set<int> V;

	while (scanf("%d%d", &a, &b) != EOF) {
		if (a < 0 && b < 0) {
			break;
		} else if (a == 0 && b == 0) {
			if (V.size() && edge + 1 != V.size()) {
				printf("Case %d is not a tree.\n", cas);
				goto clear;
			}

			cnt = 0;
			for (auto i : V) {
				//if (inDegree[i] == 0) { 
				//inDegree�±�ָ��һ�������ڵ�λ�ã��᷵��ʲô���?
				//�ᴴ��inDegree[i], Ĭ��ֵΪ0.
				if (inDegree.find(i) == inDegree.end()) { 
					if (++cnt > 1) {
						printf("Case %d is not a tree.\n", cas);
						goto clear;
					}
				}
			}

			printf("Case %d is a tree.\n", cas);
clear:
			inDegree.clear();
			V.clear();
			edge = 0;
			cas++;
		} else {
			V.insert(a); V.insert(b); 
			inDegree[b]++;
			++edge;
		}
	}

	return 0;
}
