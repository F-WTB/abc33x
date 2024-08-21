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

int N, K;
int X[200001], Y[200001];

double f(int i, int j) { return sqrt(pow(double(X[i] - X[j]), 2) + pow(double(Y[i] - Y[j]), 2)); }

double g(int i) { return f(i, N) + f(N, i + 1) - f(i, i + 1); }

double dp[200001];

template <class T>
struct SM {
    deque<T> q;
    T top() { return q.front(); }
    void push(T x) {
        while (q.size() && q.back() < x) q.pop_back();
        q.push_back(x);
    }
    void pop(T x) {
        if (top() == x) q.pop_front();
    }
};

int main() {
    cin >> N >> K >> X[N] >> Y[N];
    for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];

    double base = f(0, N) + f(N - 1, N);
    for (int i = 0; i < N - 1; ++i) base += f(i, i + 1);

    SM<double> q;
    for (int i = 0; i < N; ++i) {
        // dp[i] = min of dp[j]+g(j) for j in [i-K,i);
        if (i >= K) {
            dp[i] = -q.top();
            q.pop(-dp[i - K] - g(i - K));
        };
        q.push(-dp[i] - g(i));
    }

    cout << fixed << setprecision(7) << base + dp[N - 1] << '\n';
}
