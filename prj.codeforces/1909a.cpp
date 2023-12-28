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
int t, n;
int main()
{
	cin >> t;
	while (t--)
	{
		int a = 0, b = 0, c = 0, d = 0;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			int x, y;
			cin >> x >> y;
			if (x < 0)a = 1;
			if (x > 0)b = 1;
			if (y < 0)c = 1;
			if (y > 0)d = 1;
		}
		if (a + b + c + d == 4)cout << "NO\n";
		else cout << "YES\n";
	}
}