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

int N, Q, t, x, l, r;
string S;
char c;

mint b = 100;
struct st {
    mint v = 0;
    int w = 0;

    st(){};
    st(mint v, int w) : v(v), w(w){};
    st(char c) : v(c - 'a' + 1), w(1){};
};
st op(st x, st y) {
    mint v = x.v + y.v * b.pow(x.w);
    int w = x.w + y.w;
    return st(v, w);
}
st e() { return st(); }

int main() {
    cin >> N >> Q >> S;
    segtree<st, op, e> a(N), b(N);
    for (int i = 0; i < N; ++i) {
        a.set(i, S[i]);
        b.set(N - 1 - i, S[i]);
    }
    for (int _ = 0; _ < Q; ++_) {
        cin >> t;
        switch (t) {
            case 1:
                cin >> x >> c;
                --x;
                a.set(x, c);
                b.set(N - 1 - x, c);
                break;
            case 2:
                cin >> l >> r;
                --l;
                cout << (a.prod(l, r).v == b.prod(N - r, N - l).v ? "Yes\n" : "No\n");
        }
    }
}
