
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
long long a[1010];
void solve() {
	int n;
	scanf("%d", &n);
	unsigned long long mask = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		mask |= (a[i] ^ a[1]);
	}
	printf("%llu\n", (mask & (-mask)) * 2);
}
int main() {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		solve();
	}
	return 0;
}