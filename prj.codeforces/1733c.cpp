#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <map>
#include <chrono>
#include <set>
#include <stack>
#include <vector>
#include <time.h>
#include <random>
#include <algorithm>
#include <string>
#include <string.h>
#include <queue>
#include <deque>
#include <functional>
#include <cctype>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <complex>
#define mp make_pair
#define pii pair<int, int>
#define pll pair<long, long>
#define sp << " "
#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a < b) ? b : a)

using namespace std;
typedef long long ll;
std::mt19937 rng(time(0)); std::uniform_int_distribution<int>uid(-1e9, 1e9);
const int INF = 1e9 + 7;


void solve() { 
	int n, vr;
	vector<int> ar;
	cin >> n;
	if (n == 1) {
		cin >> vr;
		cout << 0 << endl;
		return;
	}
	for (int i = 0; i < n; ++i) {
		cin >> vr;
		ar.push_back(vr);
	}
	cout << n - 1 << endl;
	cout << 1 sp << n << endl;
	if ((ar[0] + ar[n - 1]) % 2 == 1) {
		ar[n - 1] = ar[0];
	}
	else {
		ar[0] = ar[n - 1];
	}
	int chet = ar[0] % 2;
	for (int i = 1; i < n - 1; ++i) {
		if (ar[i] % 2 == chet) {
			cout << i + 1 sp << n << endl;
		}
		else {
			cout << 1 sp << i + 1 << endl;
		}
	}
}


signed main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
#ifdef _DEBUG
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}