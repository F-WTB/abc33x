#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
ostream &operator<<(ostream &os, const mint &x) {
    os << x.val();
    return os;
}

int N;
mint p[3001][3001], c[3001], s = 0;

int main() {
    cin >> N;
    p[1][0] = 1;
    for (int n = 2; n < N + 1; ++n) {
        for (int i = 0; i < n; ++i) c[i + 1] = p[n - 1][i] * mint(2).pow(i) + c[i];
        for (int i = 0; i < n; ++i) p[n][i] = (mint(2).pow(n) * (c[i] - c[0]) + c[n] - c[i]) / mint(2).pow(i);
    }

    for (int i = 0; i < N; ++i) s += p[N][i];
    for (int i = 0; i < N; ++i) cout << p[N][i] / s << (i < N - 1 ? '\t' : '\n');
}
