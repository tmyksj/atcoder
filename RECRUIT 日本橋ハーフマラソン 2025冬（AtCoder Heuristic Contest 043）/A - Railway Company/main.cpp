#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
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
    int y, x;
};

class peer {
    int abs(int a) const {
        return a >= 0 ? a : -a;
    }

public:
    point s, t;

    int d() const {
        return abs(s.y - t.y) + abs(s.x - t.x);
    }
};

class grid {
public:
    int N, M, K, T;
    vector<peer>* p;

    vector<vector<int>> model_a;
    vector<vector<int>> model_b;
    vector<vector<vector<tuple<point, int>>>> model_c;

    vector<tuple<int, peer>> p_init_a;
    vector<tuple<int, peer>> p_init_b;

    int ds = 13;
    int dy[13] = { -2, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 2 };
    int dx[13] = { 0, -1, 0, 1, -2, -1, 0, 1, 2, -1, 0, 1, 0 };

    grid(int N, int M, int K, int T, vector<peer>* p) :
        N(N),
        M(M),
        K(K),
        T(T),
        p(p),
        model_a(vector<vector<int>>(N, vector<int>(N, 0))),
        model_b(vector<vector<int>>(N, vector<int>(N, 0))),
        model_c(N, vector<vector<tuple<point, int>>>(N, vector<tuple<point, int>>(0))),
        p_init_a(0),
        p_init_b(0) {

        for (int i = 0; i < M; i++) {
            model_a[(*p)[i].s.y][(*p)[i].s.x]++;
            model_a[(*p)[i].t.y][(*p)[i].t.x]++;

            for (int j = 0; j < ds; j++) {
                if (0 <= (*p)[i].s.y + dy[j] && (*p)[i].s.y + dy[j] < N
                        && 0 <= (*p)[i].s.x + dx[j] && (*p)[i].s.x + dx[j] < N) {
                    model_b[(*p)[i].s.y + dy[j]][(*p)[i].s.x + dx[j]]++;
                }

                if (0 <= (*p)[i].t.y + dy[j] && (*p)[i].t.y + dy[j] < N
                        && 0 <= (*p)[i].t.x + dx[j] && (*p)[i].t.x + dx[j] < N) {
                    model_b[(*p)[i].t.y + dy[j]][(*p)[i].t.x + dx[j]]++;
                }
            }
        }

        for (int i = 0; i < M; i++) {
            model_c[(*p)[i].s.y][(*p)[i].s.x].push_back(make_tuple((*p)[i].t, (*p)[i].d()));
            model_c[(*p)[i].t.y][(*p)[i].t.x].push_back(make_tuple((*p)[i].s, (*p)[i].d()));
        }

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < ds; j++) {
                for (int k = 0; k < ds; k++) {
                    peer q;
                    q.s.y = (*p)[i].s.y + dy[j];
                    q.s.x = (*p)[i].s.x + dx[j];
                    q.t.y = (*p)[i].t.y + dy[k];
                    q.t.x = (*p)[i].t.x + dx[k];

                    if (0 <= q.s.y && q.s.y < N
                            && 0 <= q.s.x && q.s.x < N
                            && 0 <= q.t.y && q.t.y < N
                            && 0 <= q.t.x && q.t.x < N
                            && 100 * q.d() + 9900 <= K && q.d() + 1 <= T) {
                        p_init_a.push_back(make_tuple(model_b[q.s.y][q.s.x] * model_b[q.t.y][q.t.x], q));

                        int acc = 0;

                        for (int l = 0; l < ds; l++) {
                            if (0 <= q.s.y + dy[l] && q.s.y + dy[l] < N
                                    && 0 <= q.s.x + dx[l] && q.s.x + dx[l] < N) {
                                for (int m = 0;
                                        m < static_cast<int>(model_c[q.s.y + dy[l]][q.s.x + dx[l]].size()); m++) {
                                    for (int n = 0; n < ds; n++) {
                                        if (get<0>(model_c[q.s.y + dy[l]][q.s.x + dx[l]][m]).y == q.t.y + dy[n]
                                                && get<0>(model_c[q.s.y + dy[l]][q.s.x + dx[l]][m]).x
                                                        == q.t.x + dx[n]) {
                                            acc += get<1>(model_c[q.s.y + dy[l]][q.s.x + dx[l]][m]);
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        p_init_b.push_back(make_tuple(acc, q));
                    }
                }
            }
        }

        sort(p_init_a.begin(), p_init_a.end(),
                [](const auto& a, const auto& b) {
                    return get<0>(a) > get<0>(b);
                });

        sort(p_init_b.begin(), p_init_b.end(),
                [](const auto& a, const auto& b) {
                    return get<0>(a) > get<0>(b);
                });
    }
};

class state {
    int inf = 1 << 29;

    heuristics* h;
    grid* g;

public:
    int type;

    int current_k;
    int current_t;
    int current_s;

    vector<vector<int>> current_a;
    vector<vector<int>> current_g;
    union_find current_u;

    state(heuristics* h, grid* g, int type) :
        h(h),
        g(g),
        type(type),
        current_k(g->K),
        current_t(0),
        current_s(0),
        current_a(0),
        current_g(g->N, vector<int>(g->N, -1)),
        current_u(g->N * g->N + 1) {
    }

    vector<vector<int>> action() {
        vector<vector<int>> ret(current_a);
        for (int i = ret.size(); i < g->T; i++) {
            ret.push_back(vector<int>(1, -1));
        }

        return ret;
    }

    int evaluate() {
        return current_k + (g->T - current_t) * current_s;
    }

    void init() {
        peer p;

        if (type == 0) {
            p = get<1>(g->p_init_a[min(static_cast<int>(h->random_exponential(0.04)),
                    static_cast<int>(g->p_init_a.size() - 1))]);
        } else {
            p = get<1>(g->p_init_b[min(static_cast<int>(h->random_exponential(0.4)),
                    static_cast<int>(g->p_init_b.size() - 1))]);
        }

        current_k -= 100 * p.d() + 9900;
        current_t += p.d() + 1;

        current_a.push_back({ 0, p.s.y, p.s.x });
        current_g[p.s.y][p.s.x] = 0;

        if (p.s.y < p.t.y) {
            for (int i = p.s.y + 1; i < p.t.y; i++) {
                current_a.push_back({ 2, i, p.s.x });
                current_g[i][p.s.x] = 2;
            }

            if (p.s.x < p.t.x) {
                current_a.push_back({ 5, p.t.y, p.s.x });
                current_g[p.t.y][p.s.x] = 5;

                for (int i = p.s.x + 1; i < p.t.x; i++) {
                    current_a.push_back({ 1, p.t.y, i });
                    current_g[p.t.y][i] = 1;
                }
            } else if (p.s.x > p.t.x) {
                current_a.push_back({ 4, p.t.y, p.s.x });
                current_g[p.t.y][p.s.x] = 4;

                for (int i = p.s.x - 1; i > p.t.x; i--) {
                    current_a.push_back({ 1, p.t.y, i });
                    current_g[p.t.y][i] = 1;
                }
            }
        } else if (p.s.y == p.t.y) {
            if (p.s.x < p.t.x) {
                for (int i = p.s.x + 1; i < p.t.x; i++) {
                    current_a.push_back({ 1, p.t.y, i });
                    current_g[p.t.y][i] = 1;
                }
            } else if (p.s.x > p.t.x) {
                for (int i = p.s.x - 1; i > p.t.x; i--) {
                    current_a.push_back({ 1, p.t.y, i });
                    current_g[p.t.y][i] = 1;
                }
            }
        } else {
            for (int i = p.s.y - 1; i > p.t.y; i--) {
                current_a.push_back({ 2, i, p.s.x });
                current_g[i][p.s.x] = 2;
            }

            if (p.s.x < p.t.x) {
                current_a.push_back({ 6, p.t.y, p.s.x });
                current_g[p.t.y][p.s.x] = 6;

                for (int i = p.s.x + 1; i < p.t.x; i++) {
                    current_a.push_back({ 1, p.t.y, i });
                    current_g[p.t.y][i] = 1;
                }
            } else if (p.s.x > p.t.x) {
                current_a.push_back({ 3, p.t.y, p.s.x });
                current_g[p.t.y][p.s.x] = 3;

                for (int i = p.s.x - 1; i > p.t.x; i--) {
                    current_a.push_back({ 1, p.t.y, i });
                    current_g[p.t.y][i] = 1;
                }
            }
        }

        current_a.push_back({ 0, p.t.y, p.t.x });
        current_g[p.t.y][p.t.x] = 0;

        for (int i = 0; i < g->ds; i++) {
            if (0 <= p.s.y + g->dy[i] && p.s.y + g->dy[i] < g->N
                    && 0 <= p.s.x + g->dx[i] && p.s.x + g->dx[i] < g->N) {
                current_u.unite(g->N * (p.s.y + g->dy[i]) + p.s.x + g->dx[i], g->N * g->N);
            }

            if (0 <= p.t.y + g->dy[i] && p.t.y + g->dy[i] < g->N
                    && 0 <= p.t.x + g->dx[i] && p.t.x + g->dx[i] < g->N) {
                current_u.unite(g->N * (p.t.y + g->dy[i]) + p.t.x + g->dx[i], g->N * g->N);
            }
        }

        update_current_s();
        current_k += current_s;
    }

    bool next() {
        vector<tuple<int, int, int, int, int, int>> idx(20, make_tuple(0, 0, 0, 0, 0, 0));

        for (int i = 0; i < static_cast<int>(idx.size()); i++) {
            peer p = (*g->p)[h->random_uniform_int(0, g->M - 1)];

            if (current_u.root(g->N * p.s.y + p.s.x) == current_u.root(g->N * g->N)) {
                if (current_u.root(g->N * p.t.y + p.t.x) == current_u.root(g->N * g->N)) {
                    get<0>(idx[i]) = 2;
                } else {
                    get<0>(idx[i]) = 0;
                    get<2>(idx[i]) = p.t.y;
                    get<3>(idx[i]) = p.t.x;

                    for (int j = 0; j < g->ds; j++) {
                        if (0 <= p.t.y + g->dy[j] && p.t.y + g->dy[j] < g->N
                                && 0 <= p.t.x + g->dx[j] && p.t.x + g->dx[j] < g->N
                                && current_u.root(g->N * (p.t.y + g->dy[j]) + p.t.x + g->dx[j])
                                        != current_u.root(g->N * g->N)) {
                            int acc = 0;

                            if (type == 0) {
                                for (int k = 0; k < g->ds; k++) {
                                    if (0 <= p.t.y + g->dy[j] + g->dy[k] && p.t.y + g->dy[j] + g->dy[k] < g->N
                                            && 0 <= p.t.x + g->dx[j] + g->dx[k] && p.t.x + g->dx[j] + g->dx[k] < g->N
                                            && current_u.root(g->N * (p.t.y + g->dy[j] + g->dy[k])
                                                    + p.t.x + g->dx[j] + g->dx[k]) != current_u.root(g->N * g->N)) {
                                        acc += g->model_a[p.t.y + g->dy[j] + g->dy[k]][p.t.x + g->dx[j] + g->dx[k]];
                                    }
                                }
                            } else {
                                for (int k = 0;
                                        k < static_cast<int>(g->model_c[p.t.y + g->dy[j]][p.t.x + g->dx[j]].size());
                                        k++) {
                                    if (current_u.root(g->N
                                            * get<0>(g->model_c[p.t.y + g->dy[j]][p.t.x + g->dx[j]][k]).y
                                            + get<0>(g->model_c[p.t.y + g->dy[j]][p.t.x + g->dx[j]][k]).x)
                                                    == current_u.root(g->N * g->N)) {
                                        acc += get<1>(g->model_c[p.t.y + g->dy[j]][p.t.x + g->dx[j]][k]);
                                    }
                                }
                            }

                            if (get<1>(idx[i]) < acc) {
                                get<1>(idx[i]) = acc;
                                get<2>(idx[i]) = p.t.y + g->dy[j];
                                get<3>(idx[i]) = p.t.x + g->dx[j];
                            }
                        }
                    }
                }
            } else {
                if (current_u.root(g->N * p.t.y + p.t.x) == current_u.root(g->N * g->N)) {
                    get<0>(idx[i]) = 0;
                    get<2>(idx[i]) = p.s.y;
                    get<3>(idx[i]) = p.s.x;

                    for (int j = 0; j < g->ds; j++) {
                        if (0 <= p.s.y + g->dy[j] && p.s.y + g->dy[j] < g->N
                                && 0 <= p.s.x + g->dx[j] && p.s.x + g->dx[j] < g->N
                                && current_u.root(g->N * (p.s.y + g->dy[j]) + p.s.x + g->dx[j])
                                        != current_u.root(g->N * g->N)) {
                            int acc = 0;

                            if (type == 0) {
                                for (int k = 0; k < g->ds; k++) {
                                    if (0 <= p.s.y + g->dy[j] + g->dy[k] && p.s.y + g->dy[j] + g->dy[k] < g->N
                                            && 0 <= p.s.x + g->dx[j] + g->dx[k] && p.s.x + g->dx[j] + g->dx[k] < g->N
                                            && current_u.root(g->N * (p.s.y + g->dy[j] + g->dy[k])
                                                    + p.s.x + g->dx[j] + g->dx[k]) != current_u.root(g->N * g->N)) {
                                        acc += g->model_a[p.s.y + g->dy[j] + g->dy[k]][p.s.x + g->dx[j] + g->dx[k]];
                                    }
                                }
                            } else {
                                for (int k = 0;
                                        k < static_cast<int>(g->model_c[p.s.y + g->dy[j]][p.s.x + g->dx[j]].size());
                                        k++) {
                                    if (current_u.root(g->N
                                            * get<0>(g->model_c[p.s.y + g->dy[j]][p.s.x + g->dx[j]][k]).y
                                            + get<0>(g->model_c[p.s.y + g->dy[j]][p.s.x + g->dx[j]][k]).x)
                                                    == current_u.root(g->N * g->N)) {
                                        acc += get<1>(g->model_c[p.s.y + g->dy[j]][p.s.x + g->dx[j]][k]);
                                    }
                                }
                            }

                            if (get<1>(idx[i]) < acc) {
                                get<1>(idx[i]) = acc;
                                get<2>(idx[i]) = p.s.y + g->dy[j];
                                get<3>(idx[i]) = p.s.x + g->dx[j];
                            }
                        }
                    }
                } else {
                    get<0>(idx[i]) = 1;
                    get<2>(idx[i]) = p.s.y;
                    get<3>(idx[i]) = p.s.x;
                    get<4>(idx[i]) = p.t.y;
                    get<5>(idx[i]) = p.t.x;

                    for (int j = 0; j < g->ds; j++) {
                        if (0 <= p.s.y + g->dy[j] && p.s.y + g->dy[j] < g->N
                                && 0 <= p.s.x + g->dx[j] && p.s.x + g->dx[j] < g->N
                                && current_u.root(g->N * (p.s.y + g->dy[j]) + p.s.x + g->dx[j])
                                        != current_u.root(g->N * g->N)) {
                            int acc = 0;

                            if (type == 0) {
                                for (int k = 0; k < g->ds; k++) {
                                    if (0 <= p.s.y + g->dy[j] + g->dy[k] && p.s.y + g->dy[j] + g->dy[k] < g->N
                                            && 0 <= p.s.x + g->dx[j] + g->dx[k] && p.s.x + g->dx[j] + g->dx[k] < g->N
                                            && current_u.root(g->N * (p.s.y + g->dy[j] + g->dy[k])
                                                    + p.s.x + g->dx[j] + g->dx[k]) != current_u.root(g->N * g->N)) {
                                        acc += g->model_a[p.s.y + g->dy[j] + g->dy[k]][p.s.x + g->dx[j] + g->dx[k]];
                                    }
                                }
                            } else {
                                for (int k = 0;
                                        k < static_cast<int>(g->model_c[p.s.y + g->dy[j]][p.s.x + g->dx[j]].size());
                                        k++) {
                                    if (current_u.root(g->N
                                            * get<0>(g->model_c[p.s.y + g->dy[j]][p.s.x + g->dx[j]][k]).y
                                            + get<0>(g->model_c[p.s.y + g->dy[j]][p.s.x + g->dx[j]][k]).x)
                                                    == current_u.root(g->N * g->N)) {
                                        acc += get<1>(g->model_c[p.s.y + g->dy[j]][p.s.x + g->dx[j]][k]);
                                    }
                                }
                            }

                            if (get<1>(idx[i]) < acc) {
                                get<1>(idx[i]) = acc;
                                get<2>(idx[i]) = p.s.y + g->dy[j];
                                get<3>(idx[i]) = p.s.x + g->dx[j];
                            }
                        }
                    }

                    int w = get<1>(idx[i]);

                    for (int j = 0; j < g->ds; j++) {
                        if (0 <= p.t.y + g->dy[j] && p.t.y + g->dy[j] < g->N
                                && 0 <= p.t.x + g->dx[j] && p.t.x + g->dx[j] < g->N
                                && current_u.root(g->N * (p.t.y + g->dy[j]) + p.t.x + g->dx[j])
                                        != current_u.root(g->N * g->N)) {
                            int acc = 0;

                            if (type == 0) {
                                for (int k = 0; k < g->ds; k++) {
                                    if (0 <= p.t.y + g->dy[j] + g->dy[k] && p.t.y + g->dy[j] + g->dy[k] < g->N
                                            && 0 <= p.t.x + g->dx[j] + g->dx[k] && p.t.x + g->dx[j] + g->dx[k] < g->N
                                            && current_u.root(g->N * (p.t.y + g->dy[j] + g->dy[k])
                                                    + p.t.x + g->dx[j] + g->dx[k]) != current_u.root(g->N * g->N)) {
                                        acc += g->model_a[p.t.y + g->dy[j] + g->dy[k]][p.t.x + g->dx[j] + g->dx[k]];
                                    }
                                }
                            } else {
                                for (int k = 0;
                                        k < static_cast<int>(g->model_c[p.t.y + g->dy[j]][p.t.x + g->dx[j]].size());
                                        k++) {
                                    if (current_u.root(g->N
                                            * get<0>(g->model_c[p.t.y + g->dy[j]][p.t.x + g->dx[j]][k]).y
                                            + get<0>(g->model_c[p.t.y + g->dy[j]][p.t.x + g->dx[j]][k]).x)
                                                    == current_u.root(g->N * g->N)) {
                                        acc += get<1>(g->model_c[p.t.y + g->dy[j]][p.t.x + g->dx[j]][k]);
                                    }
                                }
                            }

                            if (get<1>(idx[i]) < acc + w) {
                                get<1>(idx[i]) = acc + w;
                                get<4>(idx[i]) = p.t.y + g->dy[j];
                                get<5>(idx[i]) = p.t.x + g->dx[j];
                            }
                        }
                    }
                }
            }
        }

        sort(idx.begin(), idx.end(),
                [](const auto& a, const auto& b) {
                    return get<0>(a) != get<0>(b)
                            ? get<0>(a) < get<0>(b)
                            : get<1>(a) > get<1>(b);
                });

        if (type == 0 && current_s >= 4000) {
            for (int i = 0; i < min(static_cast<int>(idx.size()), 5) && get<0>(idx[i]) == 0; i++) {
                point a;
                a.y = get<2>(idx[i]);
                a.x = get<3>(idx[i]);

                if (unite(a, 8)) {
                    return true;
                }
            }
        }

        point a;
        a.y = get<2>(idx[0]);
        a.x = get<3>(idx[0]);

        point b;
        b.y = get<4>(idx[0]);
        b.x = get<5>(idx[0]);

        switch (get<0>(idx[0])) {
            case 0:
                return unite(a, inf);
            case 1:
                return unite(a, inf)
                        && (current_u.root(g->N * b.y + b.x) == current_u.root(g->N * g->N) || unite(b, inf));
            default:
                return false;
        }
    }

    bool unite(const point& p, int d_max) {
        if (current_g[p.y][p.x] > 0) {
            int wait = max((4999 - current_k + current_s) / current_s, 0);

            if (current_t + wait + 1 > g->T) {
                return false;
            }

            current_k += current_s * wait - 5000;
            current_t += wait + 1;

            for (int i = 0; i < wait; i++) {
                current_a.push_back(vector<int>(1, -1));
            }

            current_a.push_back({ 0, p.y, p.x });
            current_g[p.y][p.x] = 0;

            for (int i = 0; i < g->ds; i++) {
                if (0 <= p.y + g->dy[i] && p.y + g->dy[i] < g->N
                        && 0 <= p.x + g->dx[i] && p.x + g->dx[i] < g->N) {
                    current_u.unite(g->N * (p.y + g->dy[i]) + p.x + g->dx[i], g->N * g->N);
                }
            }

            update_current_s();
            current_k += current_s;

            return true;
        }

        vector<vector<tuple<int, int, int>>> d(g->N,
                vector<tuple<int, int, int>>(g->N, make_tuple(inf, -1, -1)));
        get<0>(d[p.y][p.x]) = 0;

        priority_queue<tuple<int, int, int>,
                vector<tuple<int, int, int>>,
                greater<tuple<int, int, int>>> que;
        que.push(make_tuple(0, p.y, p.x));

        point t;
        t.y = -1;

        while (!que.empty()) {
            tuple<int, int, int> q = que.top();
            que.pop();

            if (get<0>(q) > d_max) {
                return false;
            }

            int cy = get<1>(q);
            int cx = get<2>(q);

            if (get<0>(q) > get<0>(d[cy][cx])) {
                continue;
            }

            int dy[] = { -1, 0, 0, 1 };
            int dx[] = { 0, -1, 1, 0 };

            for (int i = 0; i < 4; i++) {
                int ny = cy + dy[i];
                int nx = cx + dx[i];

                if (ny < 0 || g->N <= ny || nx < 0 || g->N <= nx) {
                    continue;
                }

                if (current_g[ny][nx] == 0) {
                    get<0>(d[ny][nx]) = get<0>(d[cy][cx]) + 1;
                    get<1>(d[ny][nx]) = cy;
                    get<2>(d[ny][nx]) = cx;

                    t.y = ny;
                    t.x = nx;
                    goto out;
                }

                if (current_g[ny][nx] == -1 && get<0>(d[ny][nx]) > get<0>(d[cy][cx]) + 1) {
                    get<0>(d[ny][nx]) = get<0>(d[cy][cx]) + 1;
                    get<1>(d[ny][nx]) = cy;
                    get<2>(d[ny][nx]) = cx;
                    que.push(make_tuple(get<0>(d[ny][nx]), ny, nx));
                }
            }
        }

    out:
        if (t.y == -1) {
            return false;
        }

        int wait = max((100 * get<0>(d[t.y][t.x]) - current_k + current_s + 4899)
                / current_s - get<0>(d[t.y][t.x]) + 1, 0);

        if (current_t + get<0>(d[t.y][t.x]) + wait > g->T) {
            return false;
        }

        current_k += current_s * (get<0>(d[t.y][t.x]) + wait - 1) - 100 * get<0>(d[t.y][t.x]) - 4900;
        current_t += get<0>(d[t.y][t.x]) + wait;

        for (int i = 0; i < wait; i++) {
            current_a.push_back(vector<int>(1, -1));
        }

        int py = t.y;
        int px = t.x;

        int cy = get<1>(d[py][px]);
        int cx = get<2>(d[py][px]);

        int ny = get<1>(d[cy][cx]);
        int nx = get<2>(d[cy][cx]);

        while (cy != p.y || cx != p.x) {
            if ((px + 1 == cx && cx + 1 == nx) || (px - 1 == cx && cx - 1 == nx)) {
                current_a.push_back({ 1, cy, cx });
                current_g[cy][cx] = 1;
            } else if ((py + 1 == cy && cy + 1 == ny) || (py - 1 == cy && cy - 1 == ny)) {
                current_a.push_back({ 2, cy, cx });
                current_g[cy][cx] = 2;
            } else if ((px + 1 == cx && cy + 1 == ny) || (py - 1 == cy && cx - 1 == nx)) {
                current_a.push_back({ 3, cy, cx });
                current_g[cy][cx] = 3;
            } else if ((px + 1 == cx && cy - 1 == ny) || (py + 1 == cy && cx - 1 == nx)) {
                current_a.push_back({ 4, cy, cx });
                current_g[cy][cx] = 4;
            } else if ((py + 1 == cy && cx + 1 == nx) || (px - 1 == cx && cy - 1 == ny)) {
                current_a.push_back({ 5, cy, cx });
                current_g[cy][cx] = 5;
            } else {
                current_a.push_back({ 6, cy, cx });
                current_g[cy][cx] = 6;
            }

            py = cy;
            px = cx;

            cy = ny;
            cx = nx;

            ny = get<1>(d[cy][cx]);
            nx = get<2>(d[cy][cx]);
        }

        current_a.push_back({ 0, cy, cx });
        current_g[cy][cx] = 0;

        for (int i = 0; i < g->ds; i++) {
            if (0 <= cy + g->dy[i] && cy + g->dy[i] < g->N
                    && 0 <= cx + g->dx[i] && cx + g->dx[i] < g->N) {
                current_u.unite(g->N * (cy + g->dy[i]) + cx + g->dx[i], g->N * g->N);
            }
        }

        update_current_s();
        current_k += current_s;

        return true;
    }

    void update_current_s() {
        current_s = 0;

        for (int i = 0; i < g->M; i++) {
            if (current_u.root(g->N * (*g->p)[i].s.y + (*g->p)[i].s.x)
                    == current_u.root(g->N * (*g->p)[i].t.y + (*g->p)[i].t.x)) {
                current_s += (*g->p)[i].d();
            }
        }
    }
};

class application : public heuristics {
    int N, M, K, T;
    vector<peer> p;

public:
    application() :
        heuristics() {
    }

    void run() {
        cin >> N >> M >> K >> T;

        p.resize(M);

        for (int i = 0; i < M; i++) {
            cin >> p[i].s.y >> p[i].s.x >> p[i].t.y >> p[i].t.x;
        }

        grid g(N, M, K, T, &p);

        state result(this, &g, 0);

        for (int i = 0; i < 100 && time_limit_within(); i++) {
            state s(this, &g, i % 2);

            s.init();

            if (result.evaluate() < s.evaluate()) {
                result = s;
            }

            while (s.next()) {
                if (result.evaluate() < s.evaluate()) {
                    result = s;
                }
            }
        }

        while (time_limit_within()) {
            state s(this, &g, result.type);

            s.init();

            if (result.evaluate() < s.evaluate()) {
                result = s;
            }

            while (s.next()) {
                if (result.evaluate() < s.evaluate()) {
                    result = s;
                }
            }
        }

        vector<vector<int>> action(result.action());

        for (int i = 0; i < static_cast<int>(action.size()); i++) {
            cout << action[i][0];

            for (int j = 1; j < static_cast<int>(action[i].size()); j++) {
                cout << " " << action[i][j];
            }

            cout << endl;
        }
    }

    int time_limit_ms() {
        return 2950;
    }
};

int main() {
    application().run();
}
