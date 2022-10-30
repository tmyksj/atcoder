#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <tuple>
#include <vector>

using namespace std;

class union_find {
    vector<int> p;
    vector<int> r;
    vector<int> s;

public:
    union_find(int n) {
        p = vector<int>(n);
        r = vector<int>(n);
        s = vector<int>(n);

        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 0;
            s[i] = 1;
        }
    }

    int root(int a) {
        if (p[a] != a) {
            p[a] = root(p[a]);
        }

        return p[a];
    }

    void unite(int a, int b) {
        int ra = root(a);
        int rb = root(b);

        if (ra == rb) {
            return;
        }

        if (r[ra] < r[rb]) {
            p[ra] = rb;
            s[ra] = s[rb] = s[ra] + s[rb];
        } else {
            p[rb] = ra;
            s[ra] = s[rb] = s[ra] + s[rb];

            if (r[ra] == r[rb]) {
                r[ra]++;
            }
        }
    }

    int size(int a) {
        s[a] = s[root(a)];
        return s[a];
    }
};

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
    int inf = 1 << 29;

    int n = 10;
    vector<int> f, p;

public:
    void distance(const vector<vector<int>>& g, int ry, int rx, vector<vector<int>>& d) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = inf;
            }
        }

        d[ry][rx] = 0;

        int dy[] = { -1, 0, 0, 1 };
        int dx[] = { 0, -1, 1, 0 };

        queue<tuple<int, int>> que0;
        que0.push(make_tuple(ry, rx));

        while (!que0.empty()) {
            int y = get<0>(que0.front()), x = get<1>(que0.front());
            que0.pop();

            for (int i = 0; i < 4; i++) {
                if (0 <= y + dy[i] && y + dy[i] < n
                        && 0 <= x + dx[i] && x + dx[i] < n
                        && g[y + dy[i]][x + dx[i]] == g[ry][rx]
                        && d[y + dy[i]][x + dx[i]] == inf) {
                    d[y + dy[i]][x + dx[i]] = -1;
                    que0.push(make_tuple(y + dy[i], x + dx[i]));
                }
            }
        }

        priority_queue<tuple<int, int, int>,
                vector<tuple<int, int, int>>,
                greater<tuple<int, int, int>>> que1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][j] == -1) {
                    for (int k = 0; k < 4; k++) {
                        if (0 <= i + dy[k] && i + dy[k] < n
                                && 0 <= j + dx[k] && j + dx[k] < n
                                && g[i + dy[k]][j + dx[k]] == 0
                                && d[i + dy[k]][j + dx[k]] == inf) {
                            d[i + dy[k]][j + dx[k]] = 0;
                            que1.push(make_tuple(d[i + dy[k]][j + dx[k]], i + dy[k], j + dx[k]));
                        }
                    }
                }
            }
        }

        while (!que1.empty()) {
            int y = get<1>(que1.top()), x = get<2>(que1.top());
            que1.pop();

            for (int i = 0; i < 4; i++) {
                for (int cy = y + dy[i], cx = x + dx[i];
                        0 <= cy && cy < n
                        && 0 <= cx && cx < n
                        && g[cy][cx] == 0; cy += dy[i], cx += dx[i]) {
                    if (d[cy][cx] > d[y][x] + 1) {
                        d[cy][cx] = d[y][x] + 1;
                        que1.push(make_tuple(d[cy][cx], cy, cx));
                    }
                }
            }
        }
    }

    int evaluate(const vector<vector<int>>& g) {
        union_find uf(n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i < n - 1 && g[i + 1][j] == g[i][j]) {
                    uf.unite(n * i + j, n * (i + 1) + j);
                }

                if (j < n - 1 && g[i][j + 1] == g[i][j]) {
                    uf.unite(n * i + j, n * i + j + 1);
                }
            }
        }

        int ret = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (uf.root(n * i + j)) {
                    ret += uf.size(n * i + j) * uf.size(n * i + j);
                }
            }
        }

        return ret;
    }

    void move_b(vector<vector<int>>& g) {
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                for (int k = i - 1; g[i][j] == 0 && k >= 0; k--) {
                    swap(g[i][j], g[k][j]);
                }
            }
        }
    }

    void move_f(vector<vector<int>>& g) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = i + 1; g[i][j] == 0 && k < n; k++) {
                    swap(g[i][j], g[k][j]);
                }
            }
        }
    }

    void move_l(vector<vector<int>>& g) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = j + 1; g[i][j] == 0 && k < n; k++) {
                    swap(g[i][j], g[i][k]);
                }
            }
        }
    }

    void move_r(vector<vector<int>>& g) {
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j >= 0; j--) {
                for (int k = j - 1; g[i][j] == 0 && k >= 0; k--) {
                    swap(g[i][j], g[i][k]);
                }
            }
        }
    }

    void pick(const vector<vector<int>>& g, int p, int& y, int& x) {
        for (int i = 0, j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (g[j][k] == 0 && ++i == p) {
                    y = j;
                    x = k;
                    return;
                }
            }
        }
    }

    void pick_f(const vector<vector<int>>& g, int p, int& y, int& x) {
        pick(g, p, y, x);

        while (y > 0 && g[y - 1][x] == 0) {
            y--;
        }
    }

    void pick_l(const vector<vector<int>>& g, int p, int& y, int& x) {
        pick(g, p, y, x);

        while (x > 0 && g[y][x - 1] == 0) {
            x--;
        }
    }

    void root(const vector<vector<int>>& g, int& y, int& x) {
        auto is_root = [&](int a, int b) {
            vector<vector<int>> d(n, vector<int>(n, inf));
            d[a][b] = 0;

            int dy[] = { -1, 0, 0, 1 };
            int dx[] = { 0, -1, 1, 0 };

            queue<tuple<int, int>> que0;
            que0.push(make_tuple(a, b));

            while (!que0.empty()) {
                int y = get<0>(que0.front()), x = get<1>(que0.front());
                que0.pop();

                for (int i = 0; i < 4; i++) {
                    if (0 <= y + dy[i] && y + dy[i] < n
                            && 0 <= x + dx[i] && x + dx[i] < n
                            && g[y + dy[i]][x + dx[i]] == g[a][b]
                            && d[y + dy[i]][x + dx[i]] == inf) {
                        d[y + dy[i]][x + dx[i]] = -1;
                        que0.push(make_tuple(y + dy[i], x + dx[i]));
                    }
                }
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (d[i][j] == -1) {
                        for (int k = 0; k < 4; k++) {
                            if (0 <= i + dy[k] && i + dy[k] < n
                                    && 0 <= j + dx[k] && j + dx[k] < n
                                    && g[i + dy[k]][j + dx[k]] == 0
                                    && d[i + dy[k]][j + dx[k]] == inf) {
                                return true;
                            }
                        }
                    }
                }
            }

            return false;
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (is_root(i, j)) {
                    y = i;
                    x = j;
                    return;
                }
            }
        }

        y = 0;
        x = 0;
    }

    void run() {
        f = vector<int>(n * n);
        for (int i = 0; i < n * n; i++) {
            cin >> f[i];
        }

        p = vector<int>(n * n);
        int t = 0;

        vector<vector<int>> g(n, vector<int>(n, 0));

        for (; t < n * n && g[0][0] == 0; t++) {
            cin >> p[t];

            int y, x;
            pick(g, p[t], y, x);

            if (f[t] == f[0]) {
                g[y][x] = f[t];
                move_f(g);

                cout << "F" << endl;
            } else {
                g[y][x] = f[t];
                move_l(g);

                cout << "L" << endl;
            }
        }

        for (; t < n * n; t++) {
            cin >> p[t];

            int ry, rx;
            root(g, ry, rx);

            vector<vector<int>> d(n, vector<int>(n));
            distance(g, ry, rx, d);

            int y, x;
            pick(g, p[t], y, x);

            int yf, xf;
            pick_f(g, p[t], yf, xf);

            int yl, xl;
            pick_l(g, p[t], yl, xl);

            if (t <= 0.65 * n * n) {
                if ((f[t] == g[ry][rx] && d[yf][xf] <= d[yl][xl])
                        || (f[t] != g[ry][rx] && d[yf][xf] > d[yl][xl])) {
                    g[y][x] = f[t];
                    move_f(g);

                    cout << "F" << endl;
                } else {
                    g[y][x] = f[t];
                    move_l(g);

                    cout << "L" << endl;
                }
            } else {
                vector<vector<int>> gb(g), gf(g), gl(g), gr(g);
                move_b(gb);
                move_f(gf);
                move_l(gl);
                move_r(gr);

                int vb = evaluate(gb);
                int vf = evaluate(gf);
                int vl = evaluate(gl);
                int vr = evaluate(gr);

                if (vb == max({ vb, vf, vl, vr })) {
                    g[y][x] = f[t];
                    move_b(g);
                    cout << "B" << endl;
                } else if (vf == max({ vb, vf, vl, vr })) {
                    g[y][x] = f[t];
                    move_f(g);
                    cout << "F" << endl;
                } else if (vl == max({ vb, vf, vl, vr })) {
                    g[y][x] = f[t];
                    move_l(g);
                    cout << "L" << endl;
                } else {
                    g[y][x] = f[t];
                    move_r(g);
                    cout << "R" << endl;
                }
            }
        }
    }

    int time_limit_ms() {
        return 1900;
    }
};

int main() {
    application().run();
}
