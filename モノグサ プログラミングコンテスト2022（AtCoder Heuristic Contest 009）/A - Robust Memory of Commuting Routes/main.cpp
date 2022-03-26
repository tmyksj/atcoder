#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <string>
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
    int inf = 1 << 29;

    int size = 20;
    int res_limit = 200;

    int si, sj, ti, tj;
    double p;
    vector<string> h, v;

    vector<vector<tuple<int, int>>> graph;

public:
    int abs(int a) {
        return a >= 0 ? a : -a;
    }

    int idx_i(int idx) {
        return idx / size;
    }

    int idx_j(int idx) {
        return idx % size;
    }

    int ij_idx(int i, int j) {
        return i * size + j;
    }

    void input() {
        cin >> si >> sj >> ti >> tj >> p;

        h = vector<string>(size);
        for (int i = 0; i < size; i++) {
            cin >> h[i];
        }

        v = vector<string>(size - 1);
        for (int i = 0; i < size - 1; i++) {
            cin >> v[i];
        }
    }

    void run() {
        input();
        setup();

        vector<int> distance(size * size, inf);
        vector<int> prev(size * size, -1);

        priority_queue<tuple<int, int>,
                vector<tuple<int, int>>,
                greater<tuple<int, int>>> que;

        distance[ij_idx(si, sj)] = 0;
        que.push(make_tuple(0, ij_idx(si, sj)));

        while (!que.empty()) {
            tuple<int, int> q = que.top();
            que.pop();

            int dist = get<0>(q);
            int idx = get<1>(q);

            for (int i = 0; i < static_cast<int>(graph[idx].size()); i++) {
                int next_idx = get<0>(graph[idx][i]);
                int d = get<1>(graph[idx][i]);

                if (distance[next_idx] > dist + d) {
                    distance[next_idx] = dist + d;
                    prev[next_idx] = idx;

                    que.push(make_tuple(distance[next_idx], next_idx));
                }
            }
        }

        string res = "";
        for (int i = 0; i < res_limit ;) {
            if (i < res_limit) { res += "D"; i++; }
            if (i < res_limit) { res += "R"; i++; }
            if (i < res_limit) { res += "D"; i++; }
            if (i < res_limit) { res += "R"; i++; }
            if (i < res_limit) { res += "U"; i++; }
            if (i < res_limit) { res += "L"; i++; }
        }

        double res_score = score(res);

        for (double p1 = 1.0; p1 <= 4.5; p1 += 0.015625) {
            for (int p2 = 0; p2 <= 10; p2++) {
                string r = "";

                vector<int> path(0);
                for (int i = ij_idx(ti, tj); i != -1; i = prev[i]) {
                    path.push_back(i);
                }

                reverse(path.begin(), path.end());

                for (int i = 1; i < static_cast<int>(path.size()); i++) {
                    int prev_i = idx_i(path[i - 1]), prev_j = idx_j(path[i - 1]);
                    int cur_i = idx_i(path[i]), cur_j = idx_j(path[i]);
                    int d = abs(prev_i - cur_i) + abs(prev_j - cur_j);

                    for (int j = 0; j < p1 * d / (1 - p) + p2; j++) {
                        if (prev_i > cur_i) { r += "U"; }
                        if (prev_i < cur_i) { r += "D"; }
                        if (prev_j > cur_j) { r += "L"; }
                        if (prev_j < cur_j) { r += "R"; }
                    }
                }

                double r_score = score(r);

                if (res_score < r_score) {
                    res_score = r_score;
                    res = r;
                }
            }
        }

        for (int i = res.size(); i < res_limit; ) {
            if (i < res_limit) { res += "D"; i++; }
            if (i < res_limit) { res += "R"; i++; }
        }

        cout << res << endl;
    }

    double score(string out) {
        if (static_cast<int>(out.size()) > res_limit) {
            return 0;
        }

        double ret = 0;

        vector<vector<double>> cur(size, vector<double>(size, 0));
        cur[si][sj] = 1;

        for (int i = 0; i < static_cast<int>(out.size()); i++) {
            vector<vector<double>> next(size, vector<double>(size, 0));

            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    switch (out[i]) {
                        case 'U':
                            if (j > 0 && v[j - 1][k] == '0') {
                                next[j - 1][k] += cur[j][k] * (1 - p);
                                next[j][k] += cur[j][k] * p;
                            } else {
                                next[j][k] += cur[j][k];
                            }

                            break;
                        case 'D':
                            if (j < size - 1 && v[j][k] == '0') {
                                next[j + 1][k] += cur[j][k] * (1 - p);
                                next[j][k] += cur[j][k] * p;
                            } else {
                                next[j][k] += cur[j][k];
                            }

                            break;
                        case 'L':
                            if (k > 0 && h[j][k - 1] == '0') {
                                next[j][k - 1] += cur[j][k] * (1 - p);
                                next[j][k] += cur[j][k] * p;
                            } else {
                                next[j][k] += cur[j][k];
                            }

                            break;
                        case 'R':
                            if (k < size - 1 && h[j][k] == '0') {
                                next[j][k + 1] += cur[j][k] * (1 - p);
                                next[j][k] += cur[j][k] * p;
                            } else {
                                next[j][k] += cur[j][k];
                            }

                            break;
                    }
                }
            }

            cur = next;
            ret += cur[ti][tj] * (2 * res_limit - i);

            cur[ti][tj] = 0;
        }

        return ret;
    }

    void setup() {
        graph = vector<vector<tuple<int, int>>>(size * size, vector<tuple<int, int>>(0));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int cur_i = i - 1;
                while (cur_i >= 0 && v[cur_i][j] == '0') {
                    cur_i--;
                }

                if (cur_i < i - 1) {
                    graph[ij_idx(i, j)].push_back(make_tuple(ij_idx(cur_i + 1, j), abs(cur_i - i + 1)));

                    if (i == ti && j == tj) {
                        graph[ij_idx(cur_i + 1, j)].push_back(make_tuple(ij_idx(i, j), abs(cur_i - i + 1)));
                    }
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int cur_i = i;
                while (cur_i < size - 1 && v[cur_i][j] == '0') {
                    cur_i++;
                }

                if (cur_i > i) {
                    graph[ij_idx(i, j)].push_back(make_tuple(ij_idx(cur_i, j), abs(cur_i - i)));

                    if (i == ti && j == tj) {
                        graph[ij_idx(cur_i, j)].push_back(make_tuple(ij_idx(i, j), abs(cur_i - i)));
                    }
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int cur_j = j - 1;
                while (cur_j >= 0 && h[i][cur_j] == '0') {
                    cur_j--;
                }

                if (cur_j < j - 1) {
                    graph[ij_idx(i, j)].push_back(make_tuple(ij_idx(i, cur_j + 1), abs(cur_j - j + 1)));

                    if (i == ti && j == tj) {
                        graph[ij_idx(i, cur_j + 1)].push_back(make_tuple(ij_idx(i, j), abs(cur_j - j + 1)));
                    }
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int cur_j = j;
                while (cur_j < size - 1 && h[i][cur_j] == '0') {
                    cur_j++;
                }

                if (cur_j > j) {
                    graph[ij_idx(i, j)].push_back(make_tuple(ij_idx(i, cur_j), abs(cur_j - j)));

                    if (i == ti && j == tj) {
                        graph[ij_idx(i, cur_j)].push_back(make_tuple(ij_idx(i, j), abs(cur_j - j)));
                    }
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
