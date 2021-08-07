#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <tuple>
#include <vector>
#include <string>

using namespace std;

class heuristics {
    random_device device;
    mt19937 engine;
    chrono::system_clock::time_point time_zero;

public:
    heuristics() {
        engine = mt19937(device());
        time_zero = chrono::system_clock::now();
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

    virtual void run() = 0;

    int time_elapsed_ms() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - time_zero).count();
    }

    bool time_limit_exceeded() {
        return time_elapsed_ms() > time_limit_ms();
    }

    virtual int time_limit_ms() = 0;
};

class application : public heuristics {
    int n, si, sj;
    vector<string> c;

    string res;
    int res_cost = 1 << 29;

public:
    int cost(int i, int j) {
        return c[i][j] - '0';
    }

    bool is_road(int i, int j) {
        return 0 <= i && i < n && 0 <= j && j < n && c[i][j] != '#';
    }

    void input() {
        cin >> n >> si >> sj;

        c = vector<string>(n);
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
    }

    void output() {
        cout << res << endl;
    }

    void perform() {
        while (!time_limit_exceeded()) {
            string ret_path = "";
            int ret_cost = 0;
            perform_each(ret_path, ret_cost);

            if (res_cost > ret_cost) {
                res = ret_path;
                res_cost = ret_cost;
            }
        }
    }

    void perform_each(string& ret_path, int& ret_cost) {
        ret_path = "";
        ret_cost = 0;

        int dy[] = { -1, 1, 0, 0 };
        int dx[] = { 0, 0, -1, 1 };

        vector<vector<bool>> dfs_u(n, vector<bool>(n, true));
        vector<vector<bool>> dfs_v(n, vector<bool>(n, true));
        string dfs_path = "";
        int dfs_cnt = 0;
        perform_fun_dfs(dfs_u, dfs_v, si, sj, "", dfs_path, dfs_cnt);

        int road_cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (is_road(i, j)) {
                    road_cnt++;
                }
            }
        }

        int trace_cnt = 0;
        vector<vector<bool>> trace_v(n, vector<bool>(n, true));
        string trace_path = "";
        for (int i = 0, y = si, x = sj; i < static_cast<int>(dfs_path.size()); i++) {
            for (int j = 0; j < 4; j++) {
                for (int a = y, b = x; is_road(a, b); a += dy[j], b += dx[j]) {
                    if (trace_v[a][b]) {
                        trace_v[a][b] = false;
                        trace_cnt++;
                    }
                }
            }

            if (trace_cnt == road_cnt) {
                string dijkstra_path = "";
                perform_fun_dijkstra(y, x, si, sj, dijkstra_path);

                trace_path += dijkstra_path;
                break;
            }

            trace_path += dfs_path[i];

            if (dfs_path[i] == 'U') {
                y--;
            } else if (dfs_path[i] == 'D') {
                y++;
            } else if (dfs_path[i] == 'L') {
                x--;
            } else {
                x++;
            }
        }

        ret_path = trace_path;
        for (int i = 0, y = si, x = sj; i < static_cast<int>(ret_path.size()) - 1; i++) {
            if (ret_path[i] == 'U') {
                ret_cost += cost(y - 1, x);
                y--;
            } else if (ret_path[i] == 'D') {
                ret_cost += cost(y + 1, x);
                y++;
            } else if (ret_path[i] == 'L') {
                ret_cost += cost(y, x - 1);
                x--;
            } else {
                ret_cost += cost(y, x + 1);
                x++;
            }
        }
    }

    void perform_fun_dfs(vector<vector<bool>>& u, vector<vector<bool>>& v, int i, int j, string prev,
            string& ret_path, int& ret_cnt) {
        ret_path = "";
        ret_cnt = 0;

        int di[] = { -1, 1, 0, 0 };
        int dj[] = { 0, 0, -1, 1 };
        string ds[] = { "U", "D", "L", "R" };
        string dt[] = { "D", "U", "R", "L" };

        u[i][j] = false;
        v[i][j] = false;
        for (int k = 0; k < 4; k++) {
            for (int y = i + di[k], x = j + dj[k]; is_road(y, x); y += di[k], x += dj[k]) {
                if (v[y][x]) {
                    v[y][x] = false;
                    ret_cnt++;
                }
            }
        }

        vector<int> tbl_next(0);
        for (int k = 0; k < 4; k++) {
            tbl_next.push_back(k);

            if (prev == ds[k]) {
                tbl_next.push_back(k);
                tbl_next.push_back(k);
                tbl_next.push_back(k);
            }
        }

        vector<bool> checked(4, false);
        for (int k = 0; k < 4; k++) {
            int next = tbl_next[random_uniform_int(0, tbl_next.size() - 1)];
            while (checked[next]) {
                next = tbl_next[random_uniform_int(0, tbl_next.size() - 1)];
            }

            checked[next] = true;

            if (is_road(i + di[next], j + dj[next]) && u[i + di[next]][j + dj[next]]) {
                string rp = "";
                int rc = 0;
                perform_fun_dfs(u, v, i + di[next], j + dj[next], ds[next], rp, rc);

                if (rc > 0) {
                    ret_path += ds[next] + rp + dt[next];
                    ret_cnt += rc;
                }
            }
        }
    }

    void perform_fun_dijkstra(int y0, int x0, int y1, int x1, string& ret_path) {
        ret_path = "";

        long long inf = 1LL << 61;

        int dy[] = { -1, 1, 0, 0 };
        int dx[] = { 0, 0, -1, 1 };
        string ds[] = { "U", "D", "L", "R" };

        vector<vector<string>> p(n, vector<string>(n, ""));
        vector<vector<long long>> d(n, vector<long long>(n, inf));
        d[y0][x0] = 0;

        priority_queue<tuple<long long, int, int>,
                vector<tuple<long long, int, int>>,
                greater<tuple<long long, int, int>>> que;
        que.push(make_tuple(0, y0, x0));
        while (!que.empty()) {
            tuple<long long, int, int> q = que.top();
            que.pop();

            int py = get<1>(q);
            int px = get<2>(q);

            for (int i = 0; i < 4; i++) {
                if (is_road(py + dy[i], px + dx[i])
                        && d[py + dy[i]][px + dx[i]] > d[py][px] + cost(py + dy[i], px + dx[i])) {
                    p[py + dy[i]][px + dx[i]] = ds[i];
                    d[py + dy[i]][px + dx[i]] = d[py][px] + cost(py + dy[i], px + dx[i]);
                    que.push(make_tuple(d[py + dy[i]][px + dx[i]], py + dy[i], px + dx[i]));
                }
            }
        }

        for (int y = y1, x = x1; y != y0 || x != x0; ) {
            ret_path += p[y][x];

            if (p[y][x] == "U") {
                y++;
            } else if (p[y][x] == "D") {
                y--;
            } else if (p[y][x] == "L") {
                x++;
            } else {
                x--;
            }
        }

        reverse(ret_path.begin(), ret_path.end());
    }

    void run() {
        input();
        perform();
        output();
    }

    int time_limit_ms() {
        return 2900;
    }
};

int main() {
    application().run();
}
