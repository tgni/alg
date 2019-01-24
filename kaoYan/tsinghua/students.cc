#include <iostream>
#include <map>

using namespace std;

struct Student {
	string seq;
	string name;	
	string sex;
	int    age;
};

map<string, Student> M;

int main()
{
	int n, m;

	while (cin >> n) {
		M.clear();
		while (n--) {
			Student s;
			cin >> s.seq >> s.name >> s.sex >> s.age;
			M[s.seq] = s;
		}
		cin >> m;
		while (m--) {
			string seq;
			cin >> seq;
			if (M.find(seq) == M.end()) {
				cout << "No Answer!" << endl;
			} else {
				cout << M[seq].seq << ' ' << M[seq].name << ' '
				     << M[seq].sex << ' ' << M[seq].age << endl;
			}
		}
	}

	return 0;
}
