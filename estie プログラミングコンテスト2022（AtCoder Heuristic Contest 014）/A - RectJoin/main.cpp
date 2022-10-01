#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

class heuristics_core {
    random_device device;
    mt19937 engine;

public:
    heuristics_core() :
        engine(mt19937(device())) {
    }

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

    double random_uniform(double a, double b) {
        return uniform_real_distribution<double>(a, b)(engine);
    }

    double random_weibull(double a, double b) {
        return weibull_distribution<double>(a, b)(engine);
    }
};

class heuristics_application : public heuristics_core {
    chrono::system_clock::time_point time_zero;

public:
    heuristics_application() :
        heuristics_core(),
        time_zero(chrono::system_clock::now()) {
    }

    virtual void run() = 0;

    int time_elapsed_ms() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - time_zero).count();
    }

    bool time_limit_exceeded() {
        return time_elapsed_ms() > time_limit_ms();
    }

    virtual int time_limit_ms() = 0;

    bool time_limit_within() {
        return time_elapsed_ms() <= time_limit_ms();
    }
};

class application : public heuristics_application {
    int n, m;
    vector<int> x, y;
    vector<vector<int>> w;

public:
    inline int delta(int a, int b) {
        if (a < b) {
            return 1;
        } else if (a == b) {
            return 0;
        } else {
            return -1;
        }
    }

    inline int in(int i, int j) {
        return 0 <= i && i < n
                && 0 <= j && j < n;
    }

    int evaluate(const vector<tuple<int, int, int, int, int, int, int, int>>& op) {
        int ret = 0;
        for (int i = 0; i < static_cast<int>(op.size()); i++) {
            ret += w[get<0>(op[i])][get<1>(op[i])];
        }

        return ret;
    }

    vector<bool> grid_init() {
        return vector<bool>(5 * n * n, false);
    }

    size_t grid_hash(const vector<bool>& grid) {
        return hash<vector<bool>>()(grid);
    }

    bool grid_get(const vector<bool>& grid, int i, int j) {
        return grid[i * n + j];
    }

    bool grid_get(const vector<bool>& grid, int i, int j, int dx, int dy) {
        if (dx == -1 && dy == -1) {
            return grid[2 * n * n + (i - 1) * n + j - 1];
        }

        if (dx == -1 && dy == 0) {
            return grid[n * n + (i - 1) * n + j];
        }

        if (dx == -1 && dy == 1) {
            return grid[4 * n * n + i * n + j];
        }

        if (dx == 0 && dy == -1) {
            return grid[3 * n * n + i * n + j - 1];
        }

        if (dx == 0 && dy == 1) {
            return grid[3 * n * n + i * n + j];
        }

        if (dx == 1 && dy == -1) {
            return grid[4 * n * n + (i + 1) * n + j - 1];
        }

        if (dx == 1 && dy == 0) {
            return grid[n * n + i * n + j];
        }

        if (dx == 1 && dy == 1) {
            return grid[2 * n * n + i * n + j];
        }

        return false;
    }

    void grid_set(vector<bool>& grid, int i, int j, bool value) {
        grid[i * n + j] = value;
    }

    void grid_set(vector<bool>& grid, int i, int j, int dx, int dy, bool value) {
        if (dx == -1 && dy == -1) {
            grid[2 * n * n + (i - 1) * n + j - 1] = value;
        }

        if (dx == -1 && dy == 0) {
            grid[n * n + (i - 1) * n + j] = value;
        }

        if (dx == -1 && dy == 1) {
            grid[4 * n * n + i * n + j] = value;
        }

        if (dx == 0 && dy == -1) {
            grid[3 * n * n + i * n + j - 1] = value;
        }

        if (dx == 0 && dy == 1) {
            grid[3 * n * n + i * n + j] = value;
        }

        if (dx == 1 && dy == -1) {
            grid[4 * n * n + (i + 1) * n + j - 1] = value;
        }

        if (dx == 1 && dy == 0) {
            grid[n * n + i * n + j] = value;
        }

        if (dx == 1 && dy == 1) {
            grid[2 * n * n + i * n + j] = value;
        }
    }

    void grid_push(vector<bool>& grid, const tuple<int, int, int, int, int, int, int, int>& a) {
        grid_set(grid, get<0>(a), get<1>(a), true);

        int sx[] = { get<0>(a), get<2>(a), get<4>(a), get<6>(a) };
        int sy[] = { get<1>(a), get<3>(a), get<5>(a), get<7>(a) };
        int tx[] = { get<2>(a), get<4>(a), get<6>(a), get<0>(a) };
        int ty[] = { get<3>(a), get<5>(a), get<7>(a), get<1>(a) };

        for (int i = 0; i < 4; i++) {
            for (int ix = sx[i], iy = sy[i], dx = delta(sx[i], tx[i]), dy = delta(sy[i], ty[i]);
                    ix != tx[i] || iy != ty[i]; ix += dx, iy += dy) {
                grid_set(grid, ix, iy, dx, dy, true);
            }
        }
    }

    void grid_enumerate(const vector<bool>& grid,
            vector<tuple<int, int, int, int, int, int, int, int>>& ret) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid_get(grid, i, j)) {
                    int dx0[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
                    int dy0[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
                    int dx1[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
                    int dy1[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

                    for (int k = 0; k < 8; k++) {
                        int p1_x = i + dx1[k], p1_y = j + dy1[k];
                        int p2_x = i, p2_y = j;
                        int p3_x = i + dx0[k], p3_y = j + dy0[k];

                        while (in(p1_x, p1_y) && !grid_get(grid, p1_x, p1_y)) { p1_x += dx1[k]; p1_y += dy1[k]; }
                        while (in(p3_x, p3_y) && !grid_get(grid, p3_x, p3_y)) { p3_x += dx0[k]; p3_y += dy0[k]; }

                        int p0_x = p1_x - p2_x + p3_x, p0_y = p1_y - p2_y + p3_y;

                        bool ok = in(p0_x, p0_y) && !grid_get(grid, p0_x, p0_y)
                                && in(p1_x, p1_y) && grid_get(grid, p1_x, p1_y)
                                && in(p3_x, p3_y) && grid_get(grid, p3_x, p3_y);

                        int sx[] = { p0_x, p1_x, p2_x, p3_x };
                        int sy[] = { p0_y, p1_y, p2_y, p3_y };
                        int tx[] = { p1_x, p2_x, p3_x, p0_x };
                        int ty[] = { p1_y, p2_y, p3_y, p0_y };

                        for (int l = 0; l < 4 && ok; l++) {
                            for (int ix = sx[l], iy = sy[l], dx = delta(sx[l], tx[l]), dy = delta(sy[l], ty[l]);
                                    (ix != tx[l] || iy != ty[l]) && ok; ix += dx, iy += dy) {
                                ok = ok && ((ix == sx[l] && iy == sy[l]) || !grid_get(grid, ix, iy))
                                        && !grid_get(grid, ix, iy, dx, dy);
                            }
                        }

                        if (ok) {
                            ret.push_back(make_tuple(p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, p3_x, p3_y));
                        }
                    }
                }
            }
        }
    }

    void run() {
        cin >> n >> m;

        x = vector<int>(m);
        y = vector<int>(m);
        for (int i = 0; i < m; i++) {
            cin >> x[i] >> y[i];
        }

        w = vector<vector<int>>(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                w[i][j] = (i - n / 2) * (i - n / 2) + (j - n / 2) * (j - n / 2);
            }
        }

        int t_lm1 = 0.5 * time_limit_ms();

        int prop1 = 2 * n;
        int prop2 = n;
        int prop3 = n / 6;
        int prop4 = n / 6;
        double prop5 = 0.01;

        double comp1 = (prop3 - prop2) / static_cast<double>(time_limit_ms() - t_lm1);

        vector<tuple<int, vector<tuple<int, int, int, int, int, int, int, int>>>> pool(0);

        auto pool_desc = [](const auto& a, const auto& b) {
            return get<0>(a) > get<0>(b);
        };

        map<size_t, vector<tuple<int, int, int, int, int, int, int, int>>> candidate;

        auto candidate_asc = [this](const auto& a, const auto& b) {
            return w[get<0>(a)][get<1>(a)] < w[get<0>(b)][get<1>(b)];
        };

        set<size_t> verified;

        vector<bool> g_init(grid_init());
        for (int i = 0; i < m; i++) {
            grid_set(g_init, x[i], y[i], true);
        }

        vector<bool> max_g(g_init);
        vector<tuple<int, int, int, int, int, int, int, int>> max_op(0);

        while (true) {
            size_t h = grid_hash(max_g);

            if (candidate.find(h) == candidate.end()) {
                vector<tuple<int, int, int, int, int, int, int, int>> c(0);
                grid_enumerate(max_g, c);
                candidate[h] = c;
            }

            vector<tuple<int, int, int, int, int, int, int, int>>& c = candidate[h];

            if (c.empty()) {
                break;
            }

            tuple<int, int, int, int, int, int, int, int>& next = *max_element(c.begin(), c.end(), candidate_asc);
            grid_push(max_g, next);
            max_op.push_back(next);

            verified.insert(grid_hash(max_g));
        }

        pool.push_back(make_tuple(evaluate(max_op), max_op));

        vector<bool> min_g(g_init);
        vector<tuple<int, int, int, int, int, int, int, int>> min_op(0);

        while (true) {
            size_t h = grid_hash(min_g);

            if (candidate.find(h) == candidate.end()) {
                vector<tuple<int, int, int, int, int, int, int, int>> c(0);
                grid_enumerate(min_g, c);
                candidate[h] = c;
            }

            vector<tuple<int, int, int, int, int, int, int, int>>& c = candidate[h];

            if (c.empty()) {
                break;
            }

            tuple<int, int, int, int, int, int, int, int>& next = *min_element(c.begin(), c.end(), candidate_asc);
            grid_push(min_g, next);
            min_op.push_back(next);
        }

        pool.push_back(make_tuple(evaluate(min_op), min_op));

        while (time_elapsed_ms() <= t_lm1) {
            vector<bool> g(g_init);
            vector<tuple<int, int, int, int, int, int, int, int>> op(0);

            for (int i = 0, rs = random_uniform_int(1, prop1); i < rs; i++) {
                size_t h = grid_hash(g);

                if (candidate.find(h) == candidate.end()) {
                    vector<tuple<int, int, int, int, int, int, int, int>> c(0);
                    grid_enumerate(g, c);
                    candidate[h] = c;
                }

                vector<tuple<int, int, int, int, int, int, int, int>>& c = candidate[h];

                if (c.empty()) {
                    break;
                }

                tuple<int, int, int, int, int, int, int, int>& next = c[random_uniform_int(0, c.size() - 1)];
                grid_push(g, next);
                op.push_back(next);
            }

            for (size_t h = grid_hash(g); verified.find(h) == verified.end(); h = grid_hash(g)) {
                verified.insert(h);

                if (candidate.find(h) == candidate.end()) {
                    vector<tuple<int, int, int, int, int, int, int, int>> c(0);
                    grid_enumerate(g, c);
                    candidate[h] = c;
                }

                vector<tuple<int, int, int, int, int, int, int, int>>& c = candidate[h];

                if (c.empty()) {
                    pool.push_back(make_tuple(evaluate(op), op));
                    break;
                }

                tuple<int, int, int, int, int, int, int, int>& next = *max_element(c.begin(), c.end(), candidate_asc);
                grid_push(g, next);
                op.push_back(next);
            }
        }

        sort(pool.begin(), pool.end(), pool_desc);
        if (static_cast<int>(pool.size()) > prop2) {
            pool.resize(prop2);
        }

        while (time_limit_within()) {
            double l = log(prop5) / static_cast<int>(1 - pool.size());
            int idx = min(static_cast<int>(random_exponential(l)), static_cast<int>(pool.size() - 1));

            vector<bool> g(g_init);
            vector<tuple<int, int, int, int, int, int, int, int>> op(get<1>(pool[idx]));

            op.resize(random_uniform_int(0, op.size() - 1));

            for (int i = 0; i < static_cast<int>(op.size()); i++) {
                grid_push(g, op[i]);
            }

            for (int i = 0, rs = random_uniform_int(1, prop4); i < rs; i++) {
                size_t h = grid_hash(g);

                if (candidate.find(h) == candidate.end()) {
                    vector<tuple<int, int, int, int, int, int, int, int>> c(0);
                    grid_enumerate(g, c);
                    candidate[h] = c;
                }

                vector<tuple<int, int, int, int, int, int, int, int>>& c = candidate[h];

                if (c.empty()) {
                    break;
                }

                tuple<int, int, int, int, int, int, int, int>& next = c[random_uniform_int(0, c.size() - 1)];
                grid_push(g, next);
                op.push_back(next);
            }

            for (size_t h = grid_hash(g); verified.find(h) == verified.end(); h = grid_hash(g)) {
                verified.insert(h);

                if (candidate.find(h) == candidate.end()) {
                    vector<tuple<int, int, int, int, int, int, int, int>> c(0);
                    grid_enumerate(g, c);
                    candidate[h] = c;
                }

                vector<tuple<int, int, int, int, int, int, int, int>>& c = candidate[h];

                if (c.empty()) {
                    tuple<int, vector<tuple<int, int, int, int, int, int, int, int>>> p = make_tuple(evaluate(op), op);
                    pool.insert(lower_bound(pool.begin(), pool.end(), p, pool_desc), p);
                    break;
                }

                tuple<int, int, int, int, int, int, int, int>& next = *max_element(c.begin(), c.end(), candidate_asc);
                grid_push(g, next);
                op.push_back(next);
            }

            int sz = max(static_cast<int>(comp1 * (time_elapsed_ms() - t_lm1) + prop2), prop3);
            if (static_cast<int>(pool.size()) > sz) {
                pool.resize(sz);
            }
        }

        vector<tuple<int, int, int, int, int, int, int, int>> ret(get<1>(pool[0]));

        cout << ret.size() << endl;
        for (int i = 0; i < static_cast<int>(ret.size()); i++) {
            cout << get<0>(ret[i]) << " " << get<1>(ret[i]) << " "
                    << get<2>(ret[i]) << " " << get<3>(ret[i]) << " "
                    << get<4>(ret[i]) << " " << get<5>(ret[i]) << " "
                    << get<6>(ret[i]) << " " << get<7>(ret[i]) << endl;
        }
    }

    int time_limit_ms() {
        return 4800;
    }
};

int main() {
    application().run();
}
