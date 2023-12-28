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

void call() {
    int n, k, z = -1; cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; a[i] += (i - 1 < 0 ? 0 : a[i - 1]); }
    for (int i = 0; i < n; i++) { cin >> b[i]; b[i] = max(b[i], (i - 1 < 0 ? -1 : b[i - 1])); }
    for (int i = 0; i < min(k, n); i++) {
        int s = a[i] + (k - (i + 1)) * b[i];
        z = max(z, s);
    }
    cout << z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    while (n--) {
        call();
        cout << endl;
    }

}