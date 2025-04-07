#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

using namespace std;

class heuristics {
public:
    chrono::system_clock::time_point clock_zero;

    random_device device;
    mt19937 engine;

    heuristics() :
        clock_zero(chrono::system_clock::now()),
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

    double random_uniform_real(double a, double b) {
        return uniform_real_distribution<double>(a, b)(engine);
    }

    double random_weibull(double a, double b) {
        return weibull_distribution<double>(a, b)(engine);
    }

    int time_elapsed_ms() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - clock_zero).count();
    }

    bool time_limit_exceeded() {
        return time_elapsed_ms() > time_limit_ms();
    }

    virtual int time_limit_ms() {
        return 0;
    }

    bool time_limit_within() {
        return time_elapsed_ms() <= time_limit_ms();
    }
};

class union_find {
    vector<int> p;
    vector<int> r;

public:
    union_find(int n) :
        p(n),
        r(n) {

        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 0;
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
        } else {
            p[rb] = ra;

            if (r[ra] == r[rb]) {
                r[ra]++;
            }
        }
    }
};

class point {
public:
    double lx, rx, dx;
    double ly, ry, dy;

    double d(const point& p) const {
        double x = abs((lx + rx) / 2 + dx - (p.lx + p.rx) / 2 - p.dx);
        double y = abs((ly + ry) / 2 + dy - (p.ly + p.ry) / 2 - p.dy);

        return sqrt(x * x + y * y);
    }

    double d_raw(const point& p) const {
        double x = abs((lx + rx) / 2 - (p.lx + p.rx) / 2);
        double y = abs((ly + ry) / 2 - (p.ly + p.ry) / 2);

        return sqrt(x * x + y * y);
    }
};

class subgroup {
public:
    vector<tuple<int, point>> p;
    vector<int> a, b;
};

class group {
public:
    vector<subgroup> sub;
};

class application : public heuristics {
    int N, M, Q, L, W;
    vector<int> G;
    vector<point> p;

public:
    application() :
        heuristics() {
    }

    void run() {
        cin >> N >> M >> Q >> L >> W;

        G.resize(M);

        for (int i = 0; i < M; i++) {
            cin >> G[i];
        }

        p.resize(N);

        for (int i = 0; i < N; i++) {
            cin >> p[i].lx >> p[i].rx >> p[i].ly >> p[i].ry;
        }

        vector<vector<int>> oracle(N, vector<int>(N, 0));

        int q = Q;

        for (int i = 0; i < M; i++) {
            if (G[i] % L <= 2) {
                q -= G[i] / L;
            } else {
                q -= G[i] / L + 1;
            }
        }

        for (int i = 0; i < q; i++) {
            vector<tuple<double, int>> p_d(0);

            for (int j = 0; j < N; j++) {
                p_d.push_back(make_tuple(p[i].d_raw(p[j]), j));
            }

            sort(p_d.begin(), p_d.end());

            cout << "? " << L;

            for (int j = 0; j < L; j++) {
                cout << " " << get<1>(p_d[j]);
            }

            cout << endl;

            for (int j = 0; j < L - 1; j++) {
                int a, b;
                cin >> a >> b;

                oracle[a][b] = 1;
                oracle[b][a] = 1;

                double ax = (p[a].lx + p[a].rx) / 2;
                double ay = (p[a].ly + p[a].ry) / 2;

                double bx = (p[b].lx + p[b].rx) / 2;
                double by = (p[b].ly + p[b].ry) / 2;

                double cx = (ax + bx) / 2;
                double cy = (ay + by) / 2;

                p[a].dx += (ax < cx ? 1 : (ax == cx ? 0 : -1)) * (0.0085 * W + 7.1147);
                p[a].dy += (ay < cy ? 1 : (ay == cy ? 0 : -1)) * (0.0085 * W + 7.1147);

                p[b].dx += (bx < cx ? 1 : (bx == cx ? 0 : -1)) * (0.0085 * W + 7.1147);
                p[b].dy += (by < cy ? 1 : (by == cy ? 0 : -1)) * (0.0085 * W + 7.1147);
            }

            for (int j = 0; j < L; j++) {
                for (int k = 0; k < L; k++) {
                    if (oracle[get<1>(p_d[j])][get<1>(p_d[k])] == 0
                            && p[get<1>(p_d[j])].d(p[get<1>(p_d[k])]) <= (-0.000077 * W + 0.38452) * W) {
                        oracle[get<1>(p_d[j])][get<1>(p_d[k])] = -1;
                        oracle[get<1>(p_d[k])][get<1>(p_d[j])] = -1;
                    }
                }
            }
        }

        vector<vector<int>> p_grp(0);
        vector<vector<group>> grp(0);

        int ox[] = { 0, 0, 10000, 10000 };
        int oy[] = { 0, 10000, 0, 10000 };

        for (int i = 0; i < 4; i++) {
            p_grp.push_back(vector<int>(N, -1));
            grp.push_back(vector<group>(M));

            point o;
            o.lx = o.rx = ox[i];
            o.ly = o.ry = oy[i];

            vector<tuple<double, int>> p_o(N);

            for (int j = 0; j < N; j++) {
                get<0>(p_o[j]) = o.d(p[j]);
                get<1>(p_o[j]) = j;
            }

            sort(p_o.begin(), p_o.end());

            for (int j = 0, k = 0; k < M; k++) {
                while (p_grp[p_grp.size() - 1][get<1>(p_o[j])] >= 0) {
                    j++;
                }

                vector<tuple<double, int>> p_d(0);

                for (int l = 0; l < N; l++) {
                    if (p_grp[p_grp.size() - 1][l] >= 0) {
                        continue;
                    }

                    p_d.push_back(make_tuple(p[get<1>(p_o[j])].d(p[l]), l));
                }

                sort(p_d.begin(), p_d.end());

                for (int j_sub = 0, k_sub = 0; k_sub < G[k]; ) {
                    while (p_grp[p_grp.size() - 1][get<1>(p_d[j_sub])] >= 0) {
                        j_sub++;
                    }

                    vector<tuple<double, int>> p_d_sub(0);

                    for (int l_sub = 0; l_sub < static_cast<int>(p_d.size()); l_sub++) {
                        if (p_grp[p_grp.size() - 1][get<1>(p_d[l_sub])] >= 0) {
                            continue;
                        }

                        p_d_sub.push_back(make_tuple(
                                p[get<1>(p_d[j_sub])].d(p[get<1>(p_d[l_sub])]), get<1>(p_d[l_sub])));
                    }

                    sort(p_d_sub.begin(), p_d_sub.end());

                    grp[grp.size() - 1][k].sub.push_back(subgroup());

                    for (int l = 0; k_sub < G[k] && l < L; k_sub++, l++) {
                        p_grp[p_grp.size() - 1][get<1>(p_d_sub[l])] = j;

                        grp[grp.size() - 1][k].sub[grp[grp.size() - 1][k].sub.size() - 1].p
                                .push_back(make_tuple(get<1>(p_d_sub[l]), p[get<1>(p_d_sub[l])]));
                    }
                }
            }
        }

        vector<tuple<int, int>> G_s(M);

        for (int i = 0; i < M; i++) {
            get<0>(G_s[i]) = G[i];
            get<1>(G_s[i]) = i;
        }

        sort(G_s.begin(), G_s.end(), greater<tuple<int, int>>());

        for (int i = 0; i < 4; i++) {
            p_grp.push_back(vector<int>(N, -1));
            grp.push_back(vector<group>(M));

            point o;
            o.lx = o.rx = ox[i];
            o.ly = o.ry = oy[i];

            vector<tuple<double, int>> p_o(N);

            for (int j = 0; j < N; j++) {
                get<0>(p_o[j]) = o.d(p[j]);
                get<1>(p_o[j]) = j;
            }

            sort(p_o.begin(), p_o.end());

            for (int j = 0, k = 0; k < M; k++) {
                while (p_grp[p_grp.size() - 1][get<1>(p_o[j])] >= 0) {
                    j++;
                }

                vector<tuple<double, int>> p_d(0);

                for (int l = 0; l < N; l++) {
                    if (p_grp[p_grp.size() - 1][l] >= 0) {
                        continue;
                    }

                    p_d.push_back(make_tuple(p[get<1>(p_o[j])].d(p[l]), l));
                }

                sort(p_d.begin(), p_d.end());

                for (int j_sub = 0, k_sub = 0; k_sub < G[get<1>(G_s[k])]; ) {
                    while (p_grp[p_grp.size() - 1][get<1>(p_d[j_sub])] >= 0) {
                        j_sub++;
                    }

                    vector<tuple<double, int>> p_d_sub(0);

                    for (int l_sub = 0; l_sub < static_cast<int>(p_d.size()); l_sub++) {
                        if (p_grp[p_grp.size() - 1][get<1>(p_d[l_sub])] >= 0) {
                            continue;
                        }

                        p_d_sub.push_back(make_tuple(
                                p[get<1>(p_d[j_sub])].d(p[get<1>(p_d[l_sub])]), get<1>(p_d[l_sub])));
                    }

                    sort(p_d_sub.begin(), p_d_sub.end());

                    grp[grp.size() - 1][get<1>(G_s[k])].sub.push_back(subgroup());

                    for (int l = 0; k_sub < G[get<1>(G_s[k])] && l < L; k_sub++, l++) {
                        p_grp[p_grp.size() - 1][get<1>(p_d_sub[l])] = j;

                        grp[grp.size() - 1][get<1>(G_s[k])].sub[grp[grp.size() - 1][get<1>(G_s[k])].sub.size() - 1].p
                                .push_back(make_tuple(get<1>(p_d_sub[l]), p[get<1>(p_d_sub[l])]));
                    }
                }
            }
        }

        vector<tuple<double, int>> idx(p_grp.size());

        for (int i = 0; i < static_cast<int>(idx.size()); i++) {
            union_find u(N);

            for (int j = 0; j < M; j++) {
                vector<int> C(0);

                for (int k = 0; k < static_cast<int>(grp[i][j].sub.size()); k++) {
                    for (int l = 0; l < static_cast<int>(grp[i][j].sub[k].p.size()); l++) {
                        C.push_back(get<0>(grp[i][j].sub[k].p[l]));
                    }
                }

                vector<tuple<double, int, int>> e;

                for (int k = 0; k < static_cast<int>(C.size()); k++) {
                    for (int l = k + 1; l < static_cast<int>(C.size()); l++) {
                        e.push_back(make_tuple(p[C[k]].d(p[C[l]]), C[k], C[l]));
                    }
                }

                sort(e.begin(), e.end());

                for (int k = 0; k < static_cast<int>(e.size()); k++) {
                    if (u.root(get<1>(e[k])) != u.root(get<2>(e[k]))) {
                        u.unite(get<1>(e[k]), get<2>(e[k]));
                        get<0>(idx[i]) += get<0>(e[k]);
                    }
                }
            }

            get<1>(idx[i]) = i;
        }

        sort(idx.begin(), idx.end());

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < static_cast<int>(grp[get<1>(idx[0])][i].sub.size()); j++) {
                if (grp[get<1>(idx[0])][i].sub[j].p.size() <= 2) {
                    continue;
                }

                cout << "? " << grp[get<1>(idx[0])][i].sub[j].p.size();

                for (int k = 0; k < static_cast<int>(grp[get<1>(idx[0])][i].sub[j].p.size()); k++) {
                    cout << " " << get<0>(grp[get<1>(idx[0])][i].sub[j].p[k]);
                }

                cout << endl;

                grp[get<1>(idx[0])][i].sub[j].a.resize(grp[get<1>(idx[0])][i].sub[j].p.size() - 1);
                grp[get<1>(idx[0])][i].sub[j].b.resize(grp[get<1>(idx[0])][i].sub[j].p.size() - 1);

                for (int k = 0; k < static_cast<int>(grp[get<1>(idx[0])][i].sub[j].p.size() - 1); k++) {
                    cin >> grp[get<1>(idx[0])][i].sub[j].a[k] >> grp[get<1>(idx[0])][i].sub[j].b[k];
                }
            }
        }

        cout << "!" << endl;

        union_find u(N);

        for (int i = 0; i < M; i++) {
            vector<int> C(0);

            for (int j = 0; j < static_cast<int>(grp[get<1>(idx[0])][i].sub.size()); j++) {
                for (int k = 0; k < static_cast<int>(grp[get<1>(idx[0])][i].sub[j].p.size()); k++) {
                    C.push_back(get<0>(grp[get<1>(idx[0])][i].sub[j].p[k]));
                }
            }

            cout << C[0];

            for (int j = 1; j < static_cast<int>(C.size()); j++) {
                cout << " " << C[j];
            }

            cout << endl;

            for (int j = 0; j < static_cast<int>(grp[get<1>(idx[0])][i].sub.size()); j++) {
                for (int k = 0; k < static_cast<int>(grp[get<1>(idx[0])][i].sub[j].a.size()); k++) {
                    u.unite(grp[get<1>(idx[0])][i].sub[j].a[k], grp[get<1>(idx[0])][i].sub[j].b[k]);

                    cout << grp[get<1>(idx[0])][i].sub[j].a[k] << " " << grp[get<1>(idx[0])][i].sub[j].b[k] << endl;
                }
            }

            vector<tuple<double, int, int>> e;

            for (int j = 0; j < static_cast<int>(C.size()); j++) {
                for (int k = j + 1; k < static_cast<int>(C.size()); k++) {
                    e.push_back(make_tuple(p[C[j]].d(p[C[k]]), C[j], C[k]));
                }
            }

            sort(e.begin(), e.end());

            for (int j = 0; j < static_cast<int>(e.size()); j++) {
                if (u.root(get<1>(e[j])) != u.root(get<2>(e[j]))
                        && oracle[get<1>(e[j])][get<2>(e[j])] >= 0) {
                    u.unite(get<1>(e[j]), get<2>(e[j]));

                    cout << get<1>(e[j]) << " " << get<2>(e[j]) << endl;
                }
            }

            for (int j = 0; j < static_cast<int>(e.size()); j++) {
                if (u.root(get<1>(e[j])) != u.root(get<2>(e[j]))) {
                    u.unite(get<1>(e[j]), get<2>(e[j]));

                    cout << get<1>(e[j]) << " " << get<2>(e[j]) << endl;
                }
            }
        }
    }

    int time_limit_ms() {
        return 1980;
    }
};

int main() {
    application().run();
}
