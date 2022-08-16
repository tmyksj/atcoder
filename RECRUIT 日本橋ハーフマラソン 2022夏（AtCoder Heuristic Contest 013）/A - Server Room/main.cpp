#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <string>
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
    int size, type;
    vector<int> grid;

public:
    inline int in(int i, int j) {
        return 0 <= i && i < size
                && 0 <= j && j < size;
    }

    inline int ops_limit() {
        return 100 * type;
    }

    inline int p(int i, int j) {
        return i * size + j;
    }

    inline int px(int q) {
        return q % size;
    }

    inline int py(int q) {
        return q / size;
    }

    int evaluate(const vector<int>& move_src, const vector<int>& move_dst,
            const vector<int>& conn_src, const vector<int>& conn_dst) {
        vector<int> g(grid);
        for (int i = 0; i < static_cast<int>(move_src.size()); i++) {
            swap(g[move_src[i]], g[move_dst[i]]);
        }

        union_find uf(size * size);
        for (int i = 0; i < static_cast<int>(conn_src.size()); i++) {
            uf.unite(conn_src[i], conn_dst[i]);
        }

        vector<vector<int>> sum(size * size, vector<int>(type + 1, 0));
        for (int i = 0; i < size * size; i++) {
            sum[uf.root(i)][g[i]]++;
        }

        int ret = 0;
        for (int i = 0; i < size * size; i++) {
            for (int acc = accumulate(sum[i].begin(), sum[i].end(), 0), j = 0; j <= type; j++) {
                acc -= sum[i][j];
                ret -= sum[i][j] * acc;
                ret += sum[i][j] * (sum[i][j] - 1) / 2;
            }
        }

        return ret;
    }

    void run() {
        cin >> size >> type;

        grid = vector<int>(size * size);
        for (int i = 0; i < size; i++) {
            string s;
            cin >> s;

            for (int j = 0; j < size; j++) {
                grid[p(i, j)] = s[j] - '0';
            }
        }

        int prop1 = 40;
        int prop2 = type <= 3 ? 5 : type;
        int prop3 = 15;
        double prop4 = 0.8;
        int prop5 = 2 * type;

        int ret_val = 0;
        vector<int> ret_move_src(0), ret_move_dst(0);
        vector<int> ret_conn_src(0), ret_conn_dst(0);

        vector<vector<tuple<int, vector<int>, vector<int>>>> search(
                prop1, vector<tuple<int, vector<int>, vector<int>>>(0));
        if (type <= 3) {
            for (int i = 0; i < prop2; i++) {
                search[0].push_back(make_tuple(0, vector<int>(0), vector<int>(0)));
            }
        } else {
            for (int i = 0; i < prop2; i++) {
                vector<int> move_src(0), move_dst(0);
                vector<int> conn_src(0), conn_dst(0);

                step1(move_src, move_dst, i + 1);
                step3(move_src, move_dst, conn_src, conn_dst);

                if (static_cast<int>(move_src.size()) <= prop4 * ops_limit()) {
                    search[0].push_back(make_tuple(0, move_src, move_dst));
                } else {
                    search[0].push_back(make_tuple(0, vector<int>(0), vector<int>(0)));
                }

                int val = evaluate(move_src, move_dst, conn_src, conn_dst);
                if (ret_val < val) {
                    ret_val = val;
                    ret_move_src = move_src;
                    ret_move_dst = move_dst;
                    ret_conn_src = conn_src;
                    ret_conn_dst = conn_dst;
                }
            }
        }

        while (time_limit_within()) {
            for (int i = 1; i < prop1 && time_limit_within(); i++) {
                for (int j = 0; j < prop2; j++) {
                    for (int k = 0; k < prop3; k++) {
                        vector<int> move_src(get<1>(search[i - 1][j])), move_dst(get<2>(search[i - 1][j]));
                        vector<int> conn_src(0), conn_dst(0);

                        step2(move_src, move_dst, prop5);
                        step3(move_src, move_dst, conn_src, conn_dst);

                        int val = evaluate(move_src, move_dst, conn_src, conn_dst);
                        search[i].push_back(make_tuple(val, move_src, move_dst));

                        if (ret_val < val) {
                            ret_val = val;
                            ret_move_src = move_src;
                            ret_move_dst = move_dst;
                            ret_conn_src = conn_src;
                            ret_conn_dst = conn_dst;
                        }
                    }
                }

                sort(search[i].begin(), search[i].end(), [](const auto& a, const auto& b) {
                    return get<0>(a) > get<0>(b);
                });

                search[i].resize(prop2);
            }
        }

        while (true) {
            vector<int> move_src(ret_move_src), move_dst(ret_move_dst);
            vector<int> conn_src(ret_conn_src), conn_dst(ret_conn_dst);
            step4(move_src, move_dst, conn_src, conn_dst);

            int val = evaluate(move_src, move_dst, conn_src, conn_dst);
            if (ret_val < val) {
                ret_val = val;
                ret_move_src = move_src;
                ret_move_dst = move_dst;
                ret_conn_src = conn_src;
                ret_conn_dst = conn_dst;
            } else {
                break;
            }
        }

        cout << ret_move_src.size() << endl;
        for (int i = 0; i < static_cast<int>(ret_move_src.size()); i++) {
            cout << py(ret_move_src[i]) << " " << px(ret_move_src[i]) << " "
                    << py(ret_move_dst[i]) << " " << px(ret_move_dst[i]) << endl;
        }

        cout << ret_conn_src.size() << endl;
        for (int i = 0; i < static_cast<int>(ret_conn_src.size()); i++) {
            cout << py(ret_conn_src[i]) << " " << px(ret_conn_src[i]) << " "
                    << py(ret_conn_dst[i]) << " " << px(ret_conn_dst[i]) << endl;
        }
    }

    void step1(vector<int>& move_src, vector<int>& move_dst, int mtype) {
        if (static_cast<int>(move_src.size()) >= ops_limit()) {
            return;
        }

        int gap = 2;
        vector<vector<int>> route_y = {
            {},
            { -1 },
            { 0 },
            { 0 },
            { 1 },
            { -1, -1 },
            { -1, 0 },
            { 0, -1 },
            { -1, 0 },
            { 0, -1 },
            { 0, 0 },
            { 0, 0 },
            { 0, 1 },
            { 1, 0 },
            { 0, 1 },
            { 1, 0 },
            { 1, 1 },
        };
        vector<vector<int>> route_x = {
            {},
            { 0 },
            { -1 },
            { 1 },
            { 0 },
            { 0, 0 },
            { 0, -1 },
            { -1, 0 },
            { 0, 1 },
            { 1, 0 },
            { -1, -1 },
            { 1, 1 },
            { -1, 0 },
            { 0, -1 },
            { 1, 0 },
            { 0, 1 },
            { 0, 0 },
        };

        vector<int> g(grid);
        for (int i = 0; i < static_cast<int>(move_src.size()); i++) {
            swap(g[move_src[i]], g[move_dst[i]]);
        }

        for (int i = 0; i < size * size; i++) {
            if (g[i] == 0) {
                continue;
            }

            int src_y = py(i);
            int src_x = px(i);

            int idx = -1;
            for (int j = 0; j < static_cast<int>(route_y.size()); j++) {
                int dst_y = src_y, dst_x = src_x;
                for (int k = 0; k < static_cast<int>(route_y[j].size()); k++) {
                    dst_y += route_y[j][k];
                    dst_x += route_x[j][k];

                    if (!in(dst_y, dst_x) || g[p(dst_y, dst_x)] != 0) {
                        dst_y = -1;
                        break;
                    }
                }

                if (dst_y >= 0 && ((g[i] == mtype && dst_y % gap == 0 && dst_x % gap == 0)
                        || (g[i] != mtype && (dst_y % gap != 0 || dst_x % gap != 0)))) {
                    idx = j;
                    break;
                }
            }

            if (idx >= 0 && static_cast<int>(move_src.size() + route_y[idx].size()) <= ops_limit()) {
                for (int j = 0, sy = src_y, sx = src_x, dy = src_y, dx = src_x;
                        j < static_cast<int>(route_y[idx].size()); j++) {
                    dy += route_y[idx][j];
                    dx += route_x[idx][j];

                    int s = p(sy, sx), d = p(dy, dx);
                    swap(g[s], g[d]);
                    move_src.push_back(s);
                    move_dst.push_back(d);

                    sy = dy;
                    sx = dx;
                }
            }
        }
    }

    void step2(vector<int>& move_src, vector<int>& move_dst, int ops) {
        if (static_cast<int>(move_src.size()) >= ops_limit()) {
            return;
        }

        int dy[] = { -1, 0, 0, 1 };
        int dx[] = { 0, -1, 1, 0 };

        vector<int> g(grid);
        for (int i = 0; i < static_cast<int>(move_src.size()); i++) {
            swap(g[move_src[i]], g[move_dst[i]]);
        }

        for (int i = 0; i < ops; ) {
            int src_y = random_uniform_int(0, size - 1);
            int src_x = random_uniform_int(0, size - 1);

            int src = p(src_y, src_x);
            if (g[src] == 0) {
                continue;
            }

            vector<int> src_dy(0), src_dx(0);
            for (int j = 0; j < 4; j++) {
                if (in(src_y + dy[j], src_x + dx[j])
                        && g[p(src_y + dy[j], src_x + dx[j])] == 0) {
                    src_dy.push_back(dy[j]);
                    src_dx.push_back(dx[j]);
                }
            }

            if (src_dy.size() == 0) {
                continue;
            }

            int dir = random_uniform_int(0, src_dy.size() - 1);
            int dst = p(src_y + src_dy[dir], src_x + src_dx[dir]);

            swap(g[src], g[dst]);
            move_src.push_back(src);
            move_dst.push_back(dst);
            i++;

            if (static_cast<int>(move_src.size()) >= ops_limit()) {
                return;
            }
        }
    }

    void step3(const vector<int>& move_src, const vector<int>& move_dst,
            vector<int>& conn_src, vector<int>& conn_dst) {
        if (static_cast<int>(move_src.size()) >= ops_limit()) {
            return;
        }

        int conn = -1;

        vector<int> g(grid);
        for (int i = 0; i < static_cast<int>(move_src.size()); i++) {
            swap(g[move_src[i]], g[move_dst[i]]);
        }

        union_find uf(size * size);
        map<int, vector<int>> candidate;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                int src = p(i, j);
                if (g[src] <= 0) {
                    continue;
                }

                for (; j < size - 1; j++) {
                    int dst = p(i, j + 1);
                    if (g[dst] == g[src] && uf.root(src) != uf.root(dst)) {
                        for (int k = px(src) + 1; k < j + 1; k++) {
                            g[p(i, k)] = conn;
                        }

                        uf.unite(src, dst);
                        candidate[src].push_back(dst);

                        break;
                    }

                    if (g[dst] != 0) {
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                int src = p(j, i);
                if (g[src] <= 0) {
                    continue;
                }

                for (; j < size - 1; j++) {
                    int dst = p(j + 1, i);
                    if (g[dst] == g[src] && uf.root(src) != uf.root(dst)) {
                        for (int k = py(src) + 1; k < j + 1; k++) {
                            g[p(k, i)] = conn;
                        }

                        uf.unite(src, dst);
                        candidate[src].push_back(dst);

                        break;
                    }

                    if (g[dst] != 0) {
                        break;
                    }
                }
            }
        }

        vector<tuple<int, int>> vt(0);
        for (int i = 0; i < size * size; i++) {
            if (uf.size(i) >= 2) {
                vt.push_back(make_tuple(uf.size(i), i));
            }
        }

        sort(vt.begin(), vt.end(), [](const auto& a, const auto& b) {
            return get<0>(a) != get<0>(b) ? get<0>(a) > get<0>(b) : get<1>(a) < get<1>(b);
        });

        for (int i = 0; i < static_cast<int>(vt.size()); i++) {
            int src = get<1>(vt[i]);

            for (int j = 0; j < static_cast<int>(candidate[src].size()); j++) {
                conn_src.push_back(src);
                conn_dst.push_back(candidate[src][j]);

                if (static_cast<int>(move_src.size() + conn_src.size()) >= ops_limit()) {
                    return;
                }
            }
        }
    }

    void step4(vector<int>& move_src, vector<int>& move_dst,
            vector<int>& conn_src, vector<int>& conn_dst) {
        int dy[] = { -1, 0, 0, 1 };
        int dx[] = { 0, -1, 1, 0 };

        vector<vector<int>> route_y = {
            {},
            { -1 },
            { 0 },
            { 0 },
            { 1 },
            { -1, -1 },
            { -1, 0 },
            { 0, -1 },
            { -1, 0 },
            { 0, -1 },
            { 0, 0 },
            { 0, 0 },
            { 0, 1 },
            { 1, 0 },
            { 0, 1 },
            { 1, 0 },
            { 1, 1 },
        };
        vector<vector<int>> route_x = {
            {},
            { 0 },
            { -1 },
            { 1 },
            { 0 },
            { 0, 0 },
            { 0, -1 },
            { -1, 0 },
            { 0, 1 },
            { 1, 0 },
            { -1, -1 },
            { 1, 1 },
            { -1, 0 },
            { 0, -1 },
            { 1, 0 },
            { 0, 1 },
            { 0, 0 },
        };

        vector<int> g(grid);
        for (int i = 0; i < static_cast<int>(move_src.size()); i++) {
            swap(g[move_src[i]], g[move_dst[i]]);
        }

        union_find uf(size * size);
        for (int i = 0; i < static_cast<int>(conn_src.size()); i++) {
            uf.unite(conn_src[i], conn_dst[i]);
        }

        for (int i = 0; i < static_cast<int>(conn_src.size()); i++) {
            int src_y = py(conn_src[i]), src_x = px(conn_src[i]);
            int dst_y = py(conn_dst[i]), dst_x = px(conn_dst[i]);

            for (int j = min(src_y, dst_y) + 1; j < max(src_y, dst_y); j++) {
                g[p(j, src_x)] = -uf.root(conn_src[i]);
            }

            for (int j = min(src_x, dst_x) + 1; j < max(src_x, dst_x); j++) {
                g[p(src_y, j)] = -uf.root(conn_src[i]);
            }
        }

        int idx_val = 1, idx = -1, jdx = -1;
        for (int i = 0; i < size * size; i++) {
            if (g[i] <= 0 || uf.size(i) >= 2) {
                continue;
            }

            int src_y = py(i);
            int src_x = px(i);

            for (int j = 0; j < static_cast<int>(route_y.size()); j++) {
                int dst_y = src_y, dst_x = src_x;
                for (int k = 0; k < static_cast<int>(route_y[j].size()); k++) {
                    dst_y += route_y[j][k];
                    dst_x += route_x[j][k];

                    if (!in(dst_y, dst_x) || g[p(dst_y, dst_x)] > 0) {
                        dst_y = -1;
                        break;
                    }
                }

                if (dst_y == -1) {
                    continue;
                }

                int dst = p(dst_y, dst_x);

                if (g[i] == g[-g[dst]] && idx_val < uf.size(g[-g[dst]])) {
                    idx_val = uf.size(g[-g[dst]]);
                    idx = i;
                    jdx = j;
                }

                for (int k = 0; k < 4; k++) {
                    if (in(dst_y + dy[k], dst_x + dx[k])
                            && g[i] == g[p(dst_y + dy[k], dst_x + dx[k])]
                            && idx_val < uf.size(p(dst_y + dy[k], dst_x + dx[k]))) {
                        idx_val = uf.size(p(dst_y + dy[k], dst_x + dx[k]));
                        idx = i;
                        jdx = j;
                    }
                }
            }
        }

        if (idx >= 0) {
            for (int i = 0, sy = py(idx), sx = px(idx), dy = py(idx), dx = px(idx);
                    i < static_cast<int>(route_y[jdx].size()); i++) {
                dy += route_y[jdx][i];
                dx += route_x[jdx][i];

                move_src.push_back(p(sy, sx));
                move_dst.push_back(p(dy, dx));

                sy = dy;
                sx = dx;

                if (static_cast<int>(move_src.size()) >= ops_limit()) {
                    break;
                }
            }
        }

        conn_src.clear();
        conn_dst.clear();
        step3(move_src, move_dst, conn_src, conn_dst);
    }

    int time_limit_ms() {
        return 2900;
    }
};

int main() {
    application().run();
}
