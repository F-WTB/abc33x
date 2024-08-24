#include <bits/stdc++.h>
#include <atcoder/all>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace atcoder;
using ll = long long;
using bint = boost::multiprecision::cpp_int;
using mint = modint998244353;
using pr = pair<int, int>;
ostream &operator<<(ostream &os, const mint &x) {
    os << x.val();
    return os;
}
template <class T>
inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template <class T>
inline bool chmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
struct fast {
    fast() {
        cin.tie(0);
        ios::sync_with_stdio(0);
    }
} fast;

int N, M, U[400], V[400], W[400];

ll dp[1 << 20][20];

ll d[20][20];

int main() {
    cin >> N >> M;
    fill(dp[0], dp[1 << N], 1e18);
    for (int i = 0; i < N; ++i) dp[1 << i][i] = 0;

    fill(d[0], d[N], 1e18);
    for (int i = 0; i < M; ++i) cin >> U[i] >> V[i] >> W[i], --U[i], --V[i], d[U[i]][V[i]] = W[i];

    for (int x = 1; x < 1 << N; ++x) {
        for (int _ = 0; _ < __builtin_popcountll(x); ++_)
            for (int i = 0; i < N; ++i) {
                if (!(x & 1 << i) || dp[x][i] == 1e18) continue;
                for (int j = 0; j < N; ++j) {
                    if (!(x & 1 << j) || d[i][j] == 1e18) continue;
                    chmin(dp[x][j], dp[x][i] + d[i][j]);
                }
            }
        for (int i = 0; i < N; ++i) {
            if (!(x & 1 << i) || dp[x][i] == 1e18) continue;
            for (int j = 0; j < N; ++j) {
                if (d[i][j] == 1e18) continue;
                chmin(dp[x | 1 << j][j], dp[x][i] + d[i][j]);
            }
        }
    }

    ll ans = *min_element(dp[(1 << N) - 1], dp[(1 << N) - 1] + N);
    if (ans == 1e18) {
        cout << "No" << '\n';
        return 0;
    }
    cout << ans << '\n';
}
