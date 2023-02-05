#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
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
    const long long inf = 1e12;
    const int cx = 500, cy = 500;

    int n, m, d, k;
    vector<int> u, v, w;
    vector<int> x, y;

    int e1, e2, e3, e4;

    int closest(int px, int py) {
        int ret = 0;
        for (int idx = 0; idx < n; idx++) {
            if ((x[ret] - px) * (x[ret] - px) + (y[ret] - py) * (y[ret] - py)
                    > (x[idx] - px) * (x[idx] - px) + (y[idx] - py) * (y[idx] - py)) {
                ret = idx;
            }
        }

        return ret;
    }

    vector<long long> dijkstra(const vector<vector<int>>& a, const vector<vector<long long>>& b, int p) {
        vector<long long> ret(a.size(), inf);
        ret[p] = 0;

        priority_queue<tuple<long long, int>,
                vector<tuple<long long, int>>,
                greater<tuple<long long, int>>> que;
        que.push(make_tuple(0, p));

        while (!que.empty()) {
            tuple<long long, int> q = que.top();
            que.pop();

            if (get<0>(q) > ret[get<1>(q)]) {
                continue;
            }

            for (int idx = 0; idx < static_cast<int>(a[get<1>(q)].size()); idx++) {
                if (ret[a[get<1>(q)][idx]] > ret[get<1>(q)] + b[get<1>(q)][idx]) {
                    ret[a[get<1>(q)][idx]] = ret[get<1>(q)] + b[get<1>(q)][idx];
                    que.push(make_tuple(ret[a[get<1>(q)][idx]], a[get<1>(q)][idx]));
                }
            }
        }

        return ret;
    }

    long long evaluate(const vector<int>& r, int p) {
        vector<vector<int>> g(n, vector<int>(0));
        for (int idx = 0; idx < m; idx++) {
            if (r[idx] != p) {
                g[u[idx]].push_back(v[idx]);
                g[v[idx]].push_back(u[idx]);
            }
        }

        vector<vector<long long>> h(n, vector<long long>(0));
        for (int idx = 0; idx < m; idx++) {
            if (r[idx] != p) {
                h[u[idx]].push_back(w[idx]);
                h[v[idx]].push_back(w[idx]);
            }
        }

        vector<long long> dist1(dijkstra(g, h, e1));
        vector<long long> dist2(dijkstra(g, h, e2));
        vector<long long> dist3(dijkstra(g, h, e3));
        vector<long long> dist4(dijkstra(g, h, e4));

        return accumulate(dist1.begin(), dist1.end(), 0LL)
                + accumulate(dist2.begin(), dist2.end(), 0LL)
                + accumulate(dist3.begin(), dist3.end(), 0LL)
                + accumulate(dist4.begin(), dist4.end(), 0LL);
    }

    int time_limit_ms() {
        return 5800;
    }

public:
    void run() {
        cin >> n >> m >> d >> k;

        u.resize(m);
        v.resize(m);
        w.resize(m);
        for (int idx = 0; idx < m; idx++) {
            cin >> u[idx] >> v[idx] >> w[idx];

            u[idx]--;
            v[idx]--;
        }

        x.resize(n);
        y.resize(n);
        for (int idx = 0; idx < n; idx++) {
            cin >> x[idx] >> y[idx];
        }

        e1 = closest(cx / 2, cy / 2);
        e2 = closest(cx / 2, 3 * cy / 2);
        e3 = closest(3 * cx / 2, cy / 2);
        e4 = closest(3 * cx / 2, 3 * cy / 2);

        vector<tuple<int, int>> vt(m);
        for (int idx = 0; idx < m; idx++) {
            get<0>(vt[idx]) = ((x[u[idx]] + x[v[idx]]) / 2 - cx) * ((x[u[idx]] + x[v[idx]]) / 2 - cx)
                    + ((y[u[idx]] + y[v[idx]]) / 2 - cy) * ((y[u[idx]] + y[v[idx]]) / 2 - cy);
            get<1>(vt[idx]) = idx;
        }

        sort(vt.begin(), vt.end());

        vector<int> r(m);
        for (int idx = 0; idx < m; idx++) {
            r[get<1>(vt[idx])] = idx % d;
        }

        while (time_limit_within()) {
            int a = random_uniform_int(0, m - 1);
            int b = random_uniform_int(0, m - 1);

            long long prev = evaluate(r, r[a]) + evaluate(r, r[b]);
            swap(r[a], r[b]);

            if (prev < evaluate(r, r[a]) + evaluate(r, r[b])) {
                swap(r[a], r[b]);
            }
        }

        for (int idx = 0; idx < m; idx++) {
            cout << r[idx] + 1 << endl;
        }
    }
};

int main() {
    application().run();
}
