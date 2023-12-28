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
long long a[100005], b[100005], s[100005];
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int cnt = 0;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) cin >> a[i], b[i] = a[i];
		sort(a, a + n);
		s[0] = a[0];
		for (int i = 1; i < n; i++) s[i] = s[i - 1] + a[i];
		map<int, int>d;
		d[a[n - 1]] = n - 1;
		for (int i = n - 2; i >= 0; i--)
		{
			if (s[i] >= a[i + 1]) d[a[i]] = d[a[i + 1]];
			else d[a[i]] = i;
		}
		for (int i = 0; i < n; i++) cout << d[b[i]] << ' ';
		cout << endl;
	}

	return 0;
}