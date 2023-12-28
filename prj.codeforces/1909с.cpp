#include<bits/stdc++.h>
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
#include<bits/stdc++.h>
using namespace std;

void solve() {
	int n;
	cin >> n;
	int l[n], c[n], dif[n];
	set<int> r;
	for (int i = 0; i < n; i++) cin >> l[i];
	for (int i = 0, x; i < n; i++) cin >> x, r.insert(x);
	for (int i = 0; i < n; i++) cin >> c[i];
	sort(l, l + n, greater<int>()), sort(c, c + n, greater<int>());
	for (int i = 0; i < n; i++) {
		auto up = r.upper_bound(l[i]);
		dif[i] = *up - l[i];
		r.erase(up);
	}
	sort(dif, dif + n);
	long long ans = 0;
	for (int i = 0; i < n; i++) ans += 1LL * dif[i] * c[i];
	cout << ans << '\n';
}

int32_t main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t = 1;
	cin >> t;
	while (t--) solve();
}