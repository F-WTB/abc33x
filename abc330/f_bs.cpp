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
int N, X[200000], Y[200000];
ll K, cum_X[200001], cum_Y[200001];

void calc_cum(int *X, ll *cum) {
    sort(X, X + N);
    for (int i = 0; i < N; ++i)
        cum[i + 1] = X[i] + cum[i];
}

ll cost_lr(int l, int r, int *X, ll *a) {
    ll t = 0;
    int idx = lower_bound(X, X + N, l) - X;
    t += (ll)l * idx - (a[idx] - a[0]);
    idx = upper_bound(X, X + N, r) - X;
    t += a[N] - a[idx] - (ll)r * (N - idx);
    return t;
}

ll cost_w(int w, int *X, ll *a) {
    if (X[N - 1] - X[0] <= w) return 0;
    ll val = K + 1;

    for (int i = 0; i < N; ++i) {
        chmin(val, cost_lr(X[i], X[i] + w, X, a));
        chmin(val, cost_lr(X[i] - w, X[i], X, a));
    }

    return val;
}

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
    calc_cum(X, cum_X);
    calc_cum(Y, cum_Y);

    int ok = 1e9, ng = -1;
    while (abs(ok - ng) > 1) {
        int m = (ok + ng) / 2;
        ll c = cost_w(m, X, cum_X) + cost_w(m, Y, cum_Y);
        (c <= K ? ok : ng) = m;
    }
    cout << ok << '\n';
}
