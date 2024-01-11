
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
	int T;
	cin >> T;
	while (T--) {
		int x, f = 1;
		cin >> x;
		for (int i = 10; x / i > 0; i *= 10) {
			if (x % i > x / i && x % i >= i / 10) {
				f = 0;
				cout << x / i << ' ' << x % i << endl;
				break;
			}
		}
		if (f) cout << -1 << endl;
	}
	return 0;
}