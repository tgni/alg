#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int __reverse(int x) {
        if (x > -10 && x < 10)
            return x;
        
        string s = to_string(x);
        if (x < 0)
            std::reverse(s.begin()+1, s.end());
        else
            std::reverse(s.begin(), s.end());
	
        long ans = std::stol(s);
        if (ans > INT_MAX || ans < INT_MIN)
            return 0;
        
        return (int)ans;
}

int main()
{
	int n;
	while (cin >> n) {
		cout << __reverse(n) << endl;
	}

	return 0;
}
