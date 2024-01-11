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
int t, n, m, x;
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int lm = 2e9, sm = 2e9;
		long long st = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &m);
			int xm = 2e9, mx = 2e9;
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &x);
				if (x < mx) xm = mx, mx = x;
				else
					if (x < xm) xm = x;
				lm = min(lm, x);
			}
			st = st + 1ll * xm;
			sm = min(sm, xm);
		}
		printf("%lld\n", st - sm + lm);
	}
	return 0;
}