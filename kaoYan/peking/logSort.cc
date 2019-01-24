#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Log {
	string record;
	string name;
	string date;
	string time;
	string cost;

	bool operator < (const Log &A) const {
		if (stof(cost) < stof(A.cost)) {
			return true;
		} else if (stof(cost) > stof(A.cost)) {
			return false;
		} else if (date < A.date) {
			return true;
		} else if (date > A.date) {
			return false;
		} else if (time < A.time) {
			return true;
		} else {
			return false;
		}
	}
};

int main()
{
	vector<Log> vec;
        string line;
        
        while (getline(cin, line) && line.size() != 0) {
		Log log;
		log.record = line;
		istringstream record(line);
		record >> log.name >> log.date >> log.time >> log.cost;
		log.cost = log.cost.substr(0, log.cost.size()-3);
		vec.push_back(log);
	}

	sort(vec.begin(), vec.end());
	for (auto s : vec)
		cout << s.record << endl;

	return 0;
}
