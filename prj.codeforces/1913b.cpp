
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdint>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;
int t;
int main()
{
	cin >> t;
	while (t--)
	{
		string s;
		cin >> s;
		int cnt[2] = { 0,0 }, ans = 0;
		for (char c : s)++cnt[c - '0'];
		for (char c : s)if (!cnt[(c - '0') ^ 1]--)cout << s.size() - ans << "\n";
		else ++ans;
		if (ans == s.size())cout << 0 << "\n";
	}
	return 0;
}