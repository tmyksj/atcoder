#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
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
    int d_size = 4;
    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };

    int move[4] = { 'U', 'D', 'L', 'R' };
    int put[4] = { 'u', 'd', 'l', 'r' };

    int g_size = 30;
    int passable = 0;
    int impassable = 1;

    int loop = 300;

    int n, m;
    vector<int> px, py, pt, hx, hy;

    vector<vector<int>> c_grid;
    vector<int> c_px, c_py, c_hx, c_hy;

    int iter;
    int step;

public:
    int compare(int a, int b) {
        if (a < b) {
            return -1;
        } else if (a == b) {
            return 0;
        } else {
            return 1;
        }
    }

    int count_p(int ax, int ay, int bx, int by) {
        int ret = 0;

        for (int i = 0; i < n; i++) {
            if (min(ax, bx) <= c_px[i] && c_px[i] <= max(ax, bx)
                    && min(ay, by) <= c_py[i] && c_py[i] <= max(ay, by)) {
                ret++;
            }
        }

        return ret;
    }

    void input() {
        cin >> n;

        px = vector<int>(n);
        py = vector<int>(n);
        pt = vector<int>(n);
        for (int i = 0; i < n; i++) {
            cin >> px[i] >> py[i] >> pt[i];
        }

        cin >> m;

        hx = vector<int>(m);
        hy = vector<int>(m);
        for (int i = 0; i < m; i++) {
            cin >> hx[i] >> hy[i];
        }
    }

    bool is_sparse_p(int ax, int ay, int bx, int by) {
        return count_p(ax, ay, bx, by) == 0;
    }

    void run() {
        input();
        setup();

        for (; iter < loop; iter++) {
            switch (step) {
                case 0:
                    step_a();
                    break;
                case 1:
                    step_b();
                    break;
                case 2:
                    step_c();
                    break;
                case 3:
                    step_d();
                    break;
                default:
                    step_y();
                    break;
            }

            step_z();
        }
    }

    void setup() {
        c_grid = vector<vector<int>>(g_size + 2, vector<int>(g_size + 2, impassable));
        for (int i = 1; i <= g_size; i++) {
            for (int j = 1; j <= g_size; j++) {
                c_grid[i][j] = passable;
            }
        }

        c_px = vector<int>(px);
        c_py = vector<int>(py);

        c_hx = vector<int>(hx);
        c_hy = vector<int>(hy);

        iter = 0;
        step = 0;
    }

    void step_a() {
        string res = string(m, '.');
        bool ok = true;

        int dist_ax[] = { 3, 3, g_size - 2, g_size - 2 };
        int dist_ay[] = { 3, g_size - 2, g_size - 2, 3 };

        int dist_bx[] = { g_size / 2, g_size / 2, g_size / 2 + 1, g_size / 2 + 1 };
        int dist_by[] = { g_size / 2, g_size / 2 + 1, g_size / 2 + 1, g_size / 2 };

        for (int i = 0; i < 4; i++) {
            int x = compare(dist_ax[i], c_hx[i]);
            int y = x == 0 ? compare(dist_ay[i], c_hy[i]) : 0;

            for (int j = 0; j < d_size; j++) {
                if (x == dx[j] && y == dy[j]) {
                    c_hx[i] += dx[j];
                    c_hy[i] += dy[j];
                    res[i] = move[j];
                }
            }

            ok = ok && c_hx[i] == dist_ax[i] && c_hy[i] == dist_ay[i];
        }

        for (int i = 4; i < m; i++) {
            int x = compare(dist_bx[i % 4], c_hx[i]);
            int y = x == 0 ? compare(dist_by[i % 4], c_hy[i]) : 0;

            for (int j = 0; j < d_size; j++) {
                if (x == dx[j] && y == dy[j]) {
                    c_hx[i] += dx[j];
                    c_hy[i] += dy[j];
                    res[i] = move[j];
                }
            }

            ok = ok && c_hx[i] == dist_bx[i % 4] && c_hy[i] == dist_by[i % 4];
        }

        if (ok) {
            step++;
        }

        cout << res << endl;
    }

    void step_b() {
        string res = string(m, '.');
        bool ok = true;

        int dist_x[] = { 3, g_size - 2, g_size - 2, 3 };
        int dist_y[] = { g_size - 2, g_size - 2, 3, 3 };

        int put_x[] = { -1, 0, 1, 0 };
        int put_y[] = { 0, 1, 0, -1 };

        for (int i = 0; i < 4; i++) {
            if (c_hx[i] == dist_x[i] && c_hy[i] == dist_y[i]) {
                continue;
            }

            if (c_grid[c_hx[i] + put_x[i]][c_hy[i] + put_y[i]] == passable) {
                if (is_sparse_p(c_hx[i] + put_x[i] - 2, c_hy[i] + put_y[i] - 2,
                        c_hx[i] + put_x[i] + 2, c_hy[i] + put_y[i] + 2)) {
                    for (int j = 0; j < d_size; j++) {
                        if (put_x[i] == dx[j] && put_y[i] == dy[j]) {
                            c_grid[c_hx[i] + dx[j]][c_hy[i] + dy[j]] = impassable;
                            res[i] = put[j];
                        }
                    }
                }
            } else {
                int x = compare(dist_x[i], c_hx[i]);
                int y = x == 0 ? compare(dist_y[i], c_hy[i]) : 0;

                for (int j = 0; j < d_size; j++) {
                    if (x == dx[j] && y == dy[j]) {
                        c_hx[i] += dx[j];
                        c_hy[i] += dy[j];
                        res[i] = move[j];
                    }
                }
            }

            ok = ok && c_hx[i] == dist_x[i] && c_hy[i] == dist_y[i];
        }

        if (ok) {
            step++;
        }

        cout << res << endl;
    }

    void step_c() {
        string res = string(m, '.');
        bool ok = true;

        int dist_x[] = { 3, 3, g_size - 2, g_size - 2 };
        int dist_y[] = { 3, g_size - 2, g_size - 2, 3 };

        for (int i = 4; i < m; i++) {
            int x = compare(dist_x[i % 4], c_hx[i]);
            int y = x == 0 ? compare(dist_y[i % 4], c_hy[i]) : 0;

            for (int j = 0; j < d_size; j++) {
                if (x == dx[j] && y == dy[j]) {
                    c_hx[i] += dx[j];
                    c_hy[i] += dy[j];
                    res[i] = move[j];
                }
            }

            ok = ok && c_hx[i] == dist_x[i % 4] && c_hy[i] == dist_y[i % 4];
        }

        if (ok) {
            step++;
        }

        cout << res << endl;
    }

    void step_d() {
        string res = string(m, '.');

        int count = count_p(1, 1, 1, g_size - 1)
                + count_p(1, g_size, g_size - 1, g_size)
                + count_p(g_size, g_size, g_size, 2)
                + count_p(g_size, 1, 2, 1)
                + count_p(2, 2, 3, 3)
                + count_p(2, g_size - 1, 3, g_size - 2)
                + count_p(g_size - 1, g_size - 1, g_size - 2, g_size - 2)
                + count_p(g_size - 1, 2, g_size - 2, 3);

        if ((count == 0 || iter > 0.8 * loop) && c_grid[c_hx[0] + 1][c_hy[0]] == passable) {
            int x[] = { 1, 0, -1, 0 };
            int y[] = { 0, -1, 0, 1 };

            bool sparse = true;
            for (int i = 0; i < 4; i++) {
                sparse = sparse && is_sparse_p(c_hx[i] + x[i] - 1, c_hy[i] + y[i] - 1,
                        c_hx[i] + x[i] + 1, c_hy[i] + y[i] + 1);
            }

            if (sparse) {
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < d_size; j++) {
                        if (x[i] == dx[j] && y[i] == dy[j]) {
                            c_grid[c_hx[i] + dx[j]][c_hy[i] + dy[j]] = impassable;
                            res[i] = put[j];
                        }
                    }
                }
            }
        } else if ((count == 0 || iter > 0.9 * loop) && c_grid[c_hx[0] + 1][c_hy[0]] == impassable) {
            int x[] = { 0, -1, 0, 1 };
            int y[] = { -1, 0, 1, 0 };

            bool sparse = true;
            for (int i = 0; i < 4; i++) {
                sparse = sparse && is_sparse_p(c_hx[i] + x[i] - 1, c_hy[i] + y[i] - 1,
                        c_hx[i] + x[i] + 1, c_hy[i] + y[i] + 1);
            }

            if (sparse) {
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < d_size; j++) {
                        if (x[i] == dx[j] && y[i] == dy[j]) {
                            c_grid[c_hx[i] + dx[j]][c_hy[i] + dy[j]] = impassable;
                            res[i] = put[j];
                        }
                    }
                }

                step++;
            }
        }

        cout << res << endl;
    }

    void step_y() {
        string res = string(m, '.');

        cout << res << endl;
    }

    void step_z() {
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;

            for (int j = 0; j < static_cast<int>(s.size()); j++) {
                for (int k = 0; k < d_size; k++) {
                    if (s[j] == move[k]) {
                        c_px[i] += dx[k];
                        c_py[i] += dy[k];
                    }
                }
            }
        }
    }

    int time_limit_ms() {
        return 2980;
    }
};

int main() {
    application().run();
}
