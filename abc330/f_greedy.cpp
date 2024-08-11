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
ll K;
deque<pr> a, b;

void shape(int *X, deque<pr> &a) {
    map<int, int> c;
    for (int i = 0; i < N; ++i) ++c[X[i]];
    for (auto [x, k] : c) a.emplace_back(x, k);
}

int width(deque<pr> &a) { return a.back().first - a.front().first; }

int ans() { return max(width(a), width(b)); }

pr g(deque<pr> &a) {
    if (a.front().second < a.back().second) {
        pr p = a.front();
        a.pop_front();
        int x = a.front().first;
        a.push_front(p);
        p.first = x - p.first;
        return p;
    }
    pr p = a.back();
    a.pop_back();
    int x = a.back().first;
    a.push_back(p);
    p.first -= x;
    return p;
}

void reduce(deque<pr> &a, int t) {
    if (a.front().second < a.back().second) {
        pr p = a.front();
        a.pop_front();
        p.first += t;
        if (a.front().first == p.first) a.front().second += p.second;
        else a.push_front(p);
    } else {
        pr p = a.back();
        a.pop_back();
        p.first -= t;
        if (a.back().first == p.first) a.back().second += p.second;
        else a.push_back(p);
    }
}

bool f() {
    int w = ans();
    if (!w) return 0;
    ll c = 0;
    ll t = 1e9;
    if (width(a) == w) {
        pr p = g(a);
        chmin(t, (ll)p.first);
        c += p.second;
    }
    if (width(b) == w) {
        pr p = g(b);
        chmin(t, (ll)p.first);
        c += p.second;
    }
    if (width(a) != width(b)) chmin(t, (ll)abs(width(a) - width(b)));
    chmin(t, K / c);
    if (!t) return 0;

    if (width(a) == w) reduce(a, t);
    if (width(b) == w) reduce(b, t);
    K -= t * c;
    return 1;
}

void test(deque<pr> &a) {
    // int K = a.size();
    // for (int i = 0; i < K; ++i)
    //     cerr << a[i].first << ',' << a[i].second << '\n';
    // cerr << '\n';
}

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
    shape(X, a);
    shape(Y, b);

    test(a);
    test(b);

    while (f()) {
        test(a);
        test(b);
    }
    cout << ans() << '\n';
}
