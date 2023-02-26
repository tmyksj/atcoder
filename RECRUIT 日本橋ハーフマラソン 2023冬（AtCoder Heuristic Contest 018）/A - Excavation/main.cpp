#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <tuple>
#include <vector>

using namespace std;

class heuristics_core {
protected:
    random_device device;
    mt19937 engine;

    bool random_bernoulli(double p) {
        return bernoulli_distribution(p)(engine);
    }

    int random_binomial(double p, int t) {
        return binomial_distribution<int>(t, p)(engine);
    }

    double random_cauchy(double a, double b) {
        return cauchy_distribution<double>(a, b)(engine);
    }

    double random_chi_squared(double n) {
        return chi_squared_distribution<double>(n)(engine);
    }

    double random_exponential(double l) {
        return exponential_distribution<double>(l)(engine);
    }

    double random_extreme_value(double a, double b) {
        return extreme_value_distribution<double>(a, b)(engine);
    }

    double random_fisher_f(double m, double n) {
        return fisher_f_distribution<double>(m, n)(engine);
    }

    double random_gamma(double a, double b) {
        return gamma_distribution<double>(a, b)(engine);
    }

    int random_geometric(double p) {
        return geometric_distribution<int>(p)(engine);
    }

    double random_lognormal(double m, double s) {
        return lognormal_distribution<double>(m, s)(engine);
    }

    int random_negative_binomial(double p, int k) {
        return negative_binomial_distribution<int>(k, p)(engine);
    }

    double random_normal(double m, double s) {
        return normal_distribution<double>(m, s)(engine);
    }

    int random_poisson(double m) {
        return poisson_distribution<int>(m)(engine);
    }

    double random_student_t(double n) {
        return student_t_distribution<double>(n)(engine);
    }

    int random_uniform_int(int a, int b) {
        return uniform_int_distribution<int>(a, b)(engine);
    }

    double random_uniform_real(double a, double b) {
        return uniform_real_distribution<double>(a, b)(engine);
    }

    double random_weibull(double a, double b) {
        return weibull_distribution<double>(a, b)(engine);
    }

public:
    heuristics_core() :
        engine(mt19937(device())) {
    }
};

class heuristics_application : public heuristics_core {
protected:
    chrono::system_clock::time_point time_zero;

    int time_elapsed_ms() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - time_zero).count();
    }

    bool time_limit_exceeded() {
        return time_elapsed_ms() > time_limit_ms();
    }

    bool time_limit_within() {
        return time_elapsed_ms() <= time_limit_ms();
    }

    virtual int time_limit_ms() = 0;

public:
    heuristics_application() :
        heuristics_core(),
        time_zero(chrono::system_clock::now()) {
    }

    virtual void run() = 0;
};

class application : public heuristics_application {
    const double inf = 1e18;

    int N, W, K, C;
    vector<int> a, b, c, d;

    vector<vector<double>> S;
    vector<vector<int>> s;

    template <class T>
    inline T abs(T a) {
        return a >= 0 ? a : -a;
    }

    template <class T>
    inline T distance(T y0, T x0, T y1, T x1) {
        return abs(y0 - y1) + abs(x0 - x1);
    }

    vector<vector<tuple<double, int, int>>> dijkstra(int y, int x) {
        vector<vector<tuple<double, int, int>>> ret(N, vector<tuple<double, int, int>>(N, make_tuple(inf, -1, -1)));
        get<0>(ret[y][x]) = 0;

        priority_queue<tuple<double, int, int>,
                vector<tuple<double, int, int>>,
                greater<tuple<double, int, int>>> que;
        que.push(make_tuple(0, y, x));

        while (!que.empty()) {
            tuple<double, int, int> q = que.top();
            que.pop();

            int cy = get<1>(q);
            int cx = get<2>(q);

            if (get<0>(q) > get<0>(ret[cy][cx])) {
                continue;
            }

            int dy[] = { -1, 0, 0, 1 };
            int dx[] = { 0, -1, 1, 0 };

            for (int idx = 0; idx < 4; idx++) {
                int ny = cy + dy[idx];
                int nx = cx + dx[idx];

                if (ny < 0 || N <= ny || nx < 0 || N <= nx) {
                    continue;
                }

                double dist = s[ny][nx] <= 0 ? S[ny][nx] : 0;

                if (get<0>(ret[ny][nx]) > get<0>(ret[cy][cx]) + dist) {
                    get<0>(ret[ny][nx]) = get<0>(ret[cy][cx]) + dist;
                    get<1>(ret[ny][nx]) = cy;
                    get<2>(ret[ny][nx]) = cx;
                    que.push(make_tuple(get<0>(ret[ny][nx]), ny, nx));
                }
            }
        }

        return ret;
    }

    void estimate() {
        vector<vector<vector<int>>> v(N, vector<vector<int>>(N, vector<int>(0)));
        vector<vector<vector<double>>> w(N, vector<vector<double>>(N, vector<double>(0)));

        for (int idx = 0; idx < N; idx++) {
            for (int jdx = 0; jdx < N; jdx++) {
                if (s[idx][jdx] > 0) {
                    for (int kdx = max(idx - 11, 0); kdx <= min(idx + 11, N - 1); kdx++) {
                        for (int ldx = max(jdx - 11, 0); ldx <= min(jdx + 11, N - 1); ldx++) {
                            v[kdx][ldx].push_back(s[idx][jdx]);
                            w[kdx][ldx].push_back(1.0 / (distance(idx, jdx, idx + kdx, jdx + ldx) + 1.0));
                        }
                    }
                }

                if (s[idx][jdx] < 0) {
                    for (int kdx = max(idx - 11, 0); kdx <= min(idx + 11, N - 1); kdx++) {
                        for (int ldx = max(jdx - 11, 0); ldx <= min(jdx + 11, N - 1); ldx++) {
                            v[kdx][ldx].push_back(5000);
                            w[kdx][ldx].push_back(1.0 / (distance(idx, jdx, idx + kdx, jdx + ldx) + 1.0));
                        }
                    }
                }
            }
        }

        for (int idx = 0; idx < N; idx++) {
            for (int jdx = 0; jdx < N; jdx++) {
                if (v[idx][jdx].size() > 0) {
                    double acc = accumulate(w[idx][jdx].begin(), w[idx][jdx].end(), 0.0);

                    S[idx][jdx] = 0;
                    for (int kdx = 0; kdx < static_cast<int>(v[idx][jdx].size()); kdx++) {
                        S[idx][jdx] += v[idx][jdx][kdx] * w[idx][jdx][kdx] / acc;
                    }
                }

                if (v[idx][jdx].size() == 0) {
                    S[idx][jdx] = 5000;
                }
            }
        }
    }

    int excavate(int y, int x, int p) {
        if (s[y][x] > 0) {
            return 1;
        }

        s[y][x] -= p;

        cout << y << " " << x << " " << p << endl;

        int r;
        cin >> r;

        if (r != 0) {
            s[y][x] = -s[y][x];
        }

        return r;
    }

    int time_limit_ms() {
        return 4600;
    }

public:
    void run() {
        cin >> N >> W >> K >> C;

        a.resize(W);
        b.resize(W);
        for (int idx = 0; idx < W; idx++) {
            cin >> a[idx] >> b[idx];
        }

        c.resize(K);
        d.resize(K);
        for (int idx = 0; idx < K; idx++) {
            cin >> c[idx] >> d[idx];
        }

        S.resize(N);
        s.resize(N);
        for (int idx = 0; idx < N; idx++) {
            S[idx].resize(N, 0);
            s[idx].resize(N, 0);
        }

        map<int, vector<int>> mp;
        mp[1] = { 1100, 1440, 890, 550, 340, 210, 130, 80, 50, 50, 30, 30, 30, 20, 20, 10, 20 };
        mp[2] = { 1110, 1440, 890, 550, 340, 210, 130, 80, 50, 50, 30, 30, 30, 20, 20, 20 };
        mp[4] = { 1130, 1440, 890, 550, 340, 210, 130, 80, 50, 50, 30, 30, 30, 20, 20 };
        mp[8] = { 1130, 1440, 890, 550, 340, 210, 130, 80, 50, 50, 30, 30, 30, 20, 20 };
        mp[16] = { 1150, 1440, 890, 550, 340, 210, 130, 80, 50, 50, 30, 30, 30, 20 };
        mp[32] = { 1150, 1440, 890, 550, 340, 210, 130, 80, 50, 50, 30, 30, 30, 20 };
        mp[64] = { 1170, 1440, 890, 550, 340, 210, 130, 80, 50, 50, 30, 30, 30 };
        mp[128] = { 1170, 1440, 890, 550, 340, 210, 130, 80, 50, 50, 30, 30, 30 };

        vector<vector<vector<int>>> vp(N, vector<vector<int>>(N, vector<int>(0)));
        for (int idx = 0; idx < N; idx++) {
            for (int jdx = 0; jdx < N; jdx++) {
                for (int kdx = 0; kdx < static_cast<int>(mp[C].size()); kdx++) {
                    vp[idx][jdx].push_back(mp[C][kdx]);
                }
            }
        }

        for (int idx = 0, ex = 0; idx < 9 && ex < 50; idx++) {
            for (int jdx = 0; jdx < 12; jdx++) {
                for (int kdx = 0; kdx < 12 - jdx % 2; kdx++) {
                    int y = N * (2 * jdx + 1) / 24;
                    int x = N * (2 * kdx + jdx % 2 + 1) / 24;

                    if (s[y][x] > 0) {
                        continue;
                    }

                    int dist = N * N;

                    for (int ldx = 0; ldx < W; ldx++) {
                        dist = min(dist, distance(y, x, a[ldx], b[ldx]));
                    }

                    for (int ldx = 0; ldx < K; ldx++) {
                        dist = min(dist, distance(y, x, c[ldx], d[ldx]));
                    }

                    if (dist > 75) {
                        continue;
                    }

                    int ret = excavate(y, x, vp[y][x][vp[y][x].size() - 1]);
                    vp[y][x].pop_back();

                    if (ret == -1 || ret == 2) {
                        return;
                    }

                    if (ret == 1) {
                        ex++;
                    }
                }
            }
        }

        for (int idx = 0; idx < K; idx++) {
            while (!vp[c[idx]][d[idx]].empty()) {
                int ret = excavate(c[idx], d[idx], vp[c[idx]][d[idx]][vp[c[idx]][d[idx]].size() - 1]);
                vp[c[idx]][d[idx]].pop_back();

                if (ret == -1 || ret == 2) {
                    return;
                }

                if (ret == 1) {
                    break;
                }
            }
        }

        int sp[] = { 24, 1 };

        for (int idx = 0; idx < 2; idx++) {
            vector<tuple<double, int, int>> m(K, make_tuple(inf, 0, 0));
            for (int jdx = 0; jdx < K; jdx++) {
                get<1>(m[jdx]) = jdx;
            }

            for (int jdx = 0; jdx < K; jdx++) {
                if (time_limit_within()) {
                    estimate();

                    for (int kdx = jdx; kdx < K; kdx++) {
                        vector<vector<tuple<double, int, int>>> dist(dijkstra(c[get<1>(m[kdx])], d[get<1>(m[kdx])]));

                        for (int ldx = 0; ldx < W; ldx++) {
                            if (get<0>(m[kdx]) > get<0>(dist[a[ldx]][b[ldx]])) {
                                get<0>(m[kdx]) = get<0>(dist[a[ldx]][b[ldx]]);
                                get<2>(m[kdx]) = ldx;
                            }
                        }
                    }

                    sort(m.begin() + jdx, m.end());
                }

                vector<vector<tuple<double, int, int>>> dist(dijkstra(c[get<1>(m[jdx])], d[get<1>(m[jdx])]));

                for (int kdx = 0, cy = a[get<2>(m[jdx])], cx = b[get<2>(m[jdx])]; cy != -1 && cx != -1; kdx++) {
                    if (kdx % sp[idx] == 0) {
                        while (!vp[cy][cx].empty()) {
                            int ret = excavate(cy, cx, vp[cy][cx][vp[cy][cx].size() - 1]);
                            vp[cy][cx].pop_back();

                            if (ret == -1 || ret == 2) {
                                return;
                            }

                            if (ret == 1) {
                                break;
                            }
                        }
                    }

                    int ny = get<1>(dist[cy][cx]);
                    int nx = get<2>(dist[cy][cx]);

                    cy = ny;
                    cx = nx;
                }
            }
        }
    }
};

int main() {
    application().run();
}
