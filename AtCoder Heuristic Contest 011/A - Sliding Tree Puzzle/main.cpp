#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <tuple>

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
    int size, op;
    vector<int> grid;

public:
    int evaluate(const vector<int>& g) {
        vector<int> a(size * size), b(size * size, -1);
        for (int i = 0; i < size * size; i++) {
            a[i] = i;
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (a[p(i, j)] == p(i, j)) {
                    evaluate_dfs(g, a, b, i, j, -1, -1);
                }
            }
        }

        vector<int> ret(size * size, 0);
        for (int i = 0; i < size * size; i++) {
            ret[a[i]]++;
        }

        for (int i = 0; i < size * size; i++) {
            ret[i] &= b[i];
        }

        return *max_element(ret.begin(), ret.end());
    }

    int evaluate(const vector<int>& g, int y, int x) {
        vector<int> a(size * size), b(size * size, -1);
        for (int i = 0; i < size * size; i++) {
            a[i] = i;
        }

        evaluate_dfs(g, a, b, y, x, -1, -1);

        if (b[p(y, x)] == 0) {
            return 0;
        }

        int ret = 0;
        for (int i = 0; i < size * size; i++) {
            if (a[i] == p(y, x)) {
                ret++;
            }
        }

        return ret;
    }

    void evaluate_dfs(const vector<int>& g, vector<int>& a, vector<int>& b, int y, int x, int sy, int sx) {
        if (x > 0 && (g[p(y, x)] & 0b0001) > 0 && (g[p(y, x - 1)] & 0b0100) > 0) {
            if (a[p(y, x)] != a[p(y, x - 1)]) {
                a[p(y, x - 1)] = a[p(y, x)];
                evaluate_dfs(g, a, b, y, x - 1, y, x);
            } else if (x - 1 != sx) {
                b[a[p(y, x)]] = 0;
            }
        }

        if (y > 0 && (g[p(y, x)] & 0b0010) > 0 && (g[p(y - 1, x)] & 0b1000) > 0) {
            if (a[p(y, x)] != a[p(y - 1, x)]) {
                a[p(y - 1, x)] = a[p(y, x)];
                evaluate_dfs(g, a, b, y - 1, x, y, x);
            } else if (y - 1 != sy) {
                b[a[p(y, x)]] = 0;
            }
        }

        if (x < size - 1 && (g[p(y, x)] & 0b0100) > 0 && (g[p(y, x + 1)] & 0b0001) > 0) {
            if (a[p(y, x)] != a[p(y, x + 1)]) {
                a[p(y, x + 1)] = a[p(y, x)];
                evaluate_dfs(g, a, b, y, x + 1, y, x);
            } else if (x + 1 != sx) {
                b[a[p(y, x)]] = 0;
            }
        }

        if (y < size - 1 && (g[p(y, x)] & 0b1000) > 0 && (g[p(y + 1, x)] & 0b0010) > 0) {
            if (a[p(y, x)] != a[p(y + 1, x)]) {
                a[p(y + 1, x)] = a[p(y, x)];
                evaluate_dfs(g, a, b, y + 1, x, y, x);
            } else if (y + 1 != sy) {
                b[a[p(y, x)]] = 0;
            }
        }
    }

    void move(string& r, vector<int>& g, int& y, int& x, string path, int s_lty, int s_ltx, int s_rby, int s_rbx) {
        for (int i = 0; i < static_cast<int>(path.size()); i++) {
            if (path[i] == 'L' && x > s_ltx) {
                r += "L";
                swap(g[p(y, x)], g[p(y, x - 1)]);
                x--;
            }

            if (path[i] == 'U' && y > s_lty) {
                r += "U";
                swap(g[p(y, x)], g[p(y - 1, x)]);
                y--;
            }

            if (path[i] == 'R' && x < s_rbx) {
                r += "R";
                swap(g[p(y, x)], g[p(y, x + 1)]);
                x++;
            }

            if (path[i] == 'D' && y < s_rby) {
                r += "D";
                swap(g[p(y, x)], g[p(y + 1, x)]);
                y++;
            }
        }
    }

    void move(string& r, vector<int>& g, int& y, int& x, int sy, int sx, int ty, int tx) {
        auto mv_l = [&]() {
            r += "L";
            swap(g[p(y, x)], g[p(y, x - 1)]);
            x--;
        };

        auto mv_u = [&]() {
            r += "U";
            swap(g[p(y, x)], g[p(y - 1, x)]);
            y--;
        };

        auto mv_r = [&]() {
            r += "R";
            swap(g[p(y, x)], g[p(y, x + 1)]);
            x++;
        };

        auto mv_d = [&]() {
            r += "D";
            swap(g[p(y, x)], g[p(y + 1, x)]);
            y++;
        };

        if (sy != ty) {
            while (y < sy - 1) {
                mv_d();
            }

            while (y > sy + 1) {
                mv_u();
            }

            if (y == sy) {
                if (sy < ty) {
                    mv_d();
                } else {
                    mv_u();
                }
            }

            while (x < sx) {
                mv_r();
            }

            while (x > sx) {
                mv_l();
            }

            function<void()> sf_l = mv_l, sf_r = mv_r;
            if (x == 0) {
                swap(sf_l, sf_r);
            }

            if (y < sy && sy < ty) {
                while (y + 1 < ty) {
                    sf_l();
                    mv_d();
                    mv_d();
                    sf_r();
                    mv_u();
                }
            } else if (y < sy && sy > ty) {
                mv_d();
                while (y - 1 > ty) {
                    sf_l();
                    mv_u();
                    mv_u();
                    sf_r();
                    mv_d();
                }
            } else if (y > sy && sy < ty) {
                mv_u();
                while (y + 1 < ty) {
                    sf_l();
                    mv_d();
                    mv_d();
                    sf_r();
                    mv_u();
                }
            } else if (y > sy && sy > ty) {
                while (y - 1 > ty) {
                    sf_l();
                    mv_u();
                    mv_u();
                    sf_r();
                    mv_d();
                }
            }
        }

        if (sx != tx) {
            while (x < sx - 1) {
                mv_r();
            }

            while (x > sx + 1) {
                mv_l();
            }

            if (x == sx) {
                if (sx < tx) {
                    mv_r();
                } else {
                    mv_l();
                }
            }

            while (y < ty) {
                mv_d();
            }

            while (y > ty) {
                mv_u();
            }

            function<void()> sf_u = mv_u, sf_d = mv_d;
            if (y == 0) {
                swap(sf_u, sf_d);
            }

            if (x < sx && sx < tx) {
                while (x + 1 < tx) {
                    sf_u();
                    mv_r();
                    mv_r();
                    sf_d();
                    mv_l();
                }
            } else if (x < sx && sx > tx) {
                mv_r();
                while (x - 1 > tx) {
                    sf_u();
                    mv_l();
                    mv_l();
                    sf_d();
                    mv_r();
                }
            } else if (x > sx && sx < tx) {
                mv_l();
                while (x + 1 < tx) {
                    sf_u();
                    mv_r();
                    mv_r();
                    sf_d();
                    mv_l();
                }
            } else if (x > sx && sx > tx) {
                while (x - 1 > tx) {
                    sf_u();
                    mv_l();
                    mv_l();
                    sf_d();
                    mv_r();
                }
            }
        }
    }

    int p(int i, int j) {
        return i * size + j;
    }

    void run() {
        cin >> size >> op;

        grid = vector<int>(size * size);
        for (int i = 0; i < size; i++) {
            string s;
            cin >> s;

            for (int j = 0; j < size; j++) {
                if ('0' <= s[j] && s[j] <= '9') {
                    grid[p(i, j)] = s[j] - '0';
                } else {
                    grid[p(i, j)] = s[j] - 'a' + 10;
                }
            }
        }

        int val = evaluate(grid);
        string res = "";

        int sy = -1, sx = -1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[p(i, j)] == 0) {
                    sy = i;
                    sx = j;
                }
            }
        }

        vector<int> v_rty(0), v_rtx(0);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if ((grid[p(i, j)] & 0b0110) == 0 && grid[p(i, j)] > 0) {
                    v_rty.push_back(i);
                    v_rtx.push_back(j);
                }
            }
        }

        vector<int> s_lty = { 0, 0, (size - 1) / 2, (size - 1) / 2, 0 };
        vector<int> s_ltx = { (size - 1) / 2, 0, 0, (size - 1) / 2, 0 };
        vector<int> s_rby = { size / 2, size / 2, size - 1, size - 1, size - 1 };
        vector<int> s_rbx = { size - 1, size / 2, size / 2, size - 1, size - 1 };

        vector<string> path = {
            "L",
            "U",
            "R",
            "D",
            "LL",
            "LU",
            "LD",
            "UL",
            "UU",
            "UR",
            "RU",
            "RR",
            "RD",
            "DL",
            "DR",
            "DD",
            "LUR",
            "LDR",
            "ULD",
            "URD",
            "RUL",
            "RDL",
            "DLU",
            "DRU",
        };

        int b_keep = 4, b_breadth = 20, b_depth = 6;

        while (time_limit_within()) {
            vector<tuple<string, vector<int>, int, int, int>> b(b_keep);
            for (int i = 0; i < static_cast<int>(b.size()); i++) {
                int v_idx = random_uniform_int(0, v_rty.size() - 1);

                get<0>(b[i]) = "";
                get<1>(b[i]) = vector<int>(grid);
                get<2>(b[i]) = sy;
                get<3>(b[i]) = sx;
                get<4>(b[i]) = grid[p(v_rty[v_idx], v_rtx[v_idx])];

                move(get<0>(b[i]), get<1>(b[i]), get<2>(b[i]), get<3>(b[i]), v_rty[v_idx], v_rtx[v_idx], 0, size - 1);
            }

            while (true) {
                vector<tuple<string, vector<int>, int, int, int, int>> next(0);
                for (int i = 0; i < static_cast<int>(b.size()); i++) {
                    for (int j = 0; j < b_breadth; j++) {
                        int s_idx = get<0>(b[i]).size() / (op / s_lty.size() + 1);

                        string r = "";
                        vector<int> g(get<1>(b[i]));
                        int y = get<2>(b[i]);
                        int x = get<3>(b[i]);
                        int rtg = get<4>(b[i]);

                        for (int k = 0; k < b_depth; k++) {
                            move(r, g, y, x, path[random_uniform_int(0, path.size() - 1)],
                                    s_lty[s_idx], s_ltx[s_idx], s_rby[s_idx], s_rbx[s_idx]);
                        }

                        if (static_cast<int>(get<0>(b[i]).size() + r.size()) <= op && g[p(0, size - 1)] == rtg) {
                            next.push_back(make_tuple(get<0>(b[i]) + r, g, y, x, rtg, evaluate(g, 0, size - 1)));
                        }
                    }
                }

                if (next.empty()) {
                    break;
                }

                sort(next.begin(), next.end(), [](const auto& a, const auto& b) {
                    return get<5>(a) > get<5>(b);
                });

                b.clear();
                for (int i = 0; i < min(b_keep, static_cast<int>(next.size())); i++) {
                    b.push_back(make_tuple(get<0>(next[i]), get<1>(next[i]),
                            get<2>(next[i]), get<3>(next[i]), get<4>(next[i])));

                    int v = evaluate(get<1>(next[i]));
                    if (val < v) {
                        val = v;
                        res = get<0>(next[i]);
                    }
                }
            }
        }

        cout << res << endl;
    }

    int time_limit_ms() {
        return 2900;
    }
};

int main() {
    application().run();
}
