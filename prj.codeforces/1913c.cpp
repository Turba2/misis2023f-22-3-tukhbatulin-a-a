
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
int main() {
	int n, cnt[30] = { 0 }; cin >> n;
	while (n--) {
		int a, x; cin >> a >> x;
		if (a == 1)
			cnt[x]++;
		else {
			for (int i = 29; i >= 0; i--)
				x -= min(x >> i, cnt[i]) << i;
			if (x == 0)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
}