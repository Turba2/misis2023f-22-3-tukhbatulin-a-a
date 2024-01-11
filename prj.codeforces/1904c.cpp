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
long long t, n, k, a[200010];
long long res1, res2;
int main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		stable_sort(a + 1, a + n + 1);
		if (k >= 3) {
			cout << 0 << endl;
			continue;
		}
		res1 = a[1], res2 = 1e18;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				res1 = min(res1, abs(a[j] - a[i]));
				int d = lower_bound(a + 1, a + n + 1, abs(a[j] - a[i])) - a;
				res2 = min(res2, min(a[d] - abs(a[j] - a[i]), abs(a[j] - a[i]) - a[d - 1]));
			}
		}
		if (k == 1) {
			cout << res1 << endl;
		}
		else {
			cout << res2 << endl;
		}
	}
}