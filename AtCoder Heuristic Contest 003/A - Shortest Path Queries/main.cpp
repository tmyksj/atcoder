#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <tuple>
#include <vector>

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
    long long infinity = 1LL << 61;

    int grid_size = 30;
    int query_size = 1000;
    long long distance_average = 5000;

    int query_i;
    vector<int> s_i, s_j, t_i, t_j;
    vector<long long> b;
    vector<string> res;

    int strategy_switching_point = 80;
    int edge_leak = 10;
    double edge_leak_base = 1.4;

    vector<vector<long long>> distance_horizontal;
    vector<vector<long long>> distance_vertical;

    vector<vector<vector<long long>>> distance_horizontal_log;
    vector<vector<vector<long long>>> distance_vertical_log;

    vector<vector<vector<double>>> distance_horizontal_weight;
    vector<vector<vector<double>>> distance_vertical_weight;

public:
    template <class T>
    T abs(T a) {
        return a > 0 ? a : -a;
    }

    bool is_inclusive(int i, int j) {
        return 0 <= i && i < grid_size && 0 <= j && j < grid_size;
    }

    void run() {
        setup();

        for (; query_i < query_size; query_i++) {
            cin >> s_i[query_i] >> s_j[query_i] >> t_i[query_i] >> t_j[query_i];

            solve();
            cout << res[query_i] << endl;

            cin >> b[query_i];
            update();
        }
    }

    void setup() {
        query_i = 0;

        s_i = vector<int>(query_size);
        s_j = vector<int>(query_size);
        t_i = vector<int>(query_size);
        t_j = vector<int>(query_size);
        b = vector<long long>(query_size);

        res = vector<string>(query_size);

        distance_horizontal = vector<vector<long long>>(grid_size, vector<long long>(grid_size - 1, distance_average));
        distance_vertical = vector<vector<long long>>(grid_size - 1, vector<long long>(grid_size, distance_average));

        distance_horizontal_log = vector<vector<vector<long long>>>(grid_size, vector<vector<long long>>(grid_size - 1, vector<long long>(0)));
        distance_vertical_log = vector<vector<vector<long long>>>(grid_size - 1, vector<vector<long long>>(grid_size, vector<long long>(0)));

        distance_horizontal_weight = vector<vector<vector<double>>>(grid_size, vector<vector<double>>(grid_size - 1, vector<double>(0)));
        distance_vertical_weight = vector<vector<vector<double>>>(grid_size - 1, vector<vector<double>>(grid_size, vector<double>(0)));
    }

    void solve() {
        if (query_i < strategy_switching_point) {
            solve_a();
        } else {
            solve_b();
        }
    }

    void solve_a() {
        string res_a = "";
        for (int i = s_i[query_i]; i < t_i[query_i]; i++) { res_a += 'D'; }
        for (int i = s_i[query_i]; i > t_i[query_i]; i--) { res_a += 'U'; }
        for (int i = s_j[query_i]; i < t_j[query_i]; i++) { res_a += 'R'; }
        for (int i = s_j[query_i]; i > t_j[query_i]; i--) { res_a += 'L'; }

        string res_b = "";
        for (int i = s_j[query_i]; i < t_j[query_i]; i++) { res_b += 'R'; }
        for (int i = s_j[query_i]; i > t_j[query_i]; i--) { res_b += 'L'; }
        for (int i = s_i[query_i]; i < t_i[query_i]; i++) { res_b += 'D'; }
        for (int i = s_i[query_i]; i > t_i[query_i]; i--) { res_b += 'U'; }

        string res_c = "";
        if (s_j[query_i] < t_j[query_i]) { res_c += 'R'; }
        if (s_j[query_i] > t_j[query_i]) { res_c += 'L'; }
        for (int i = s_i[query_i]; i < t_i[query_i]; i++) { res_c += 'D'; }
        for (int i = s_i[query_i]; i > t_i[query_i]; i--) { res_c += 'U'; }
        for (int i = s_j[query_i] + 1; i < t_j[query_i]; i++) { res_c += 'R'; }
        for (int i = s_j[query_i] - 1; i > t_j[query_i]; i--) { res_c += 'L'; }

        string res_d = "";
        if (s_i[query_i] < t_i[query_i]) { res_d += 'D'; }
        if (s_i[query_i] > t_i[query_i]) { res_d += 'U'; }
        for (int i = s_j[query_i]; i < t_j[query_i]; i++) { res_d += 'R'; }
        for (int i = s_j[query_i]; i > t_j[query_i]; i--) { res_d += 'L'; }
        for (int i = s_i[query_i] + 1; i < t_i[query_i]; i++) { res_d += 'D'; }
        for (int i = s_i[query_i] - 1; i > t_i[query_i]; i--) { res_d += 'U'; }

        string res_e = "";
        for (int i = s_i[query_i]; i < t_i[query_i] - 1; i++) { res_e += 'D'; }
        for (int i = s_i[query_i]; i > t_i[query_i] + 1; i--) { res_e += 'U'; }
        for (int i = s_j[query_i]; i < t_j[query_i]; i++) { res_e += 'R'; }
        for (int i = s_j[query_i]; i > t_j[query_i]; i--) { res_e += 'L'; }
        if (s_i[query_i] < t_i[query_i]) { res_e += 'D'; }
        if (s_i[query_i] > t_i[query_i]) { res_e += 'U'; }

        string res_f = "";
        for (int i = s_j[query_i]; i < t_j[query_i] - 1; i++) { res_f += 'R'; }
        for (int i = s_j[query_i]; i > t_j[query_i] + 1; i--) { res_f += 'L'; }
        for (int i = s_i[query_i]; i < t_i[query_i]; i++) { res_f += 'D'; }
        for (int i = s_i[query_i]; i > t_i[query_i]; i--) { res_f += 'U'; }
        if (s_j[query_i] < t_j[query_i]) { res_f += 'R'; }
        if (s_j[query_i] > t_j[query_i]) { res_f += 'L'; }

        vector<tuple<int, string>> res_opt(6);
        res_opt[0] = make_tuple(solve_a_value(res_a), res_a);
        res_opt[1] = make_tuple(solve_a_value(res_b), res_b);
        res_opt[2] = make_tuple(solve_a_value(res_c), res_c);
        res_opt[3] = make_tuple(solve_a_value(res_d), res_d);
        res_opt[4] = make_tuple(solve_a_value(res_e), res_e);
        res_opt[5] = make_tuple(solve_a_value(res_f), res_f);

        sort(res_opt.begin(), res_opt.end());

        res[query_i] = get<1>(res_opt[5]);
    }

    int solve_a_value(string path) {
        int ret = 0;
        for (int i = 0, current_i = s_i[query_i], current_j = s_j[query_i]; i < static_cast<int>(path.size()); i++) {
            if (path[i] == 'U') {
                ret += (distance_vertical_log[current_i - 1][current_j].size() == 0 ? 1 : 0);
                current_i--;
            } else if (path[i] == 'L') {
                ret += (distance_horizontal_log[current_i][current_j - 1].size() == 0 ? 1 : 0);
                current_j--;
            } else if (path[i] == 'R') {
                ret += (distance_horizontal_log[current_i][current_j].size() == 0 ? 1 : 0);
                current_j++;
            } else if (path[i] == 'D') {
                ret += (distance_vertical_log[current_i][current_j].size() == 0 ? 1 : 0);
                current_i++;
            }
        }

        return ret;
    }

    void solve_b() {
        vector<vector<long long>> grid(grid_size, vector<long long>(grid_size, infinity));
        vector<vector<int>> grid_path(grid_size, vector<int>(grid_size, 0));
        grid[s_i[query_i]][s_j[query_i]] = 0;

        priority_queue<tuple<long long, int, int>,
                vector<tuple<long long, int, int>>,
                greater<tuple<long long, int, int>>> que;
        que.push(make_tuple(0, s_i[query_i], s_j[query_i]));
        while (!que.empty()) {
            tuple<long long, int, int> q = que.top();
            que.pop();

            int current_i = get<1>(q);
            int current_j = get<2>(q);

            if (is_inclusive(current_i - 1, current_j)
                    && grid[current_i - 1][current_j] > grid[current_i][current_j] + distance_vertical[current_i - 1][current_j]) {
                grid[current_i - 1][current_j] = grid[current_i][current_j] + distance_vertical[current_i - 1][current_j];
                grid_path[current_i - 1][current_j] = 'U';
                que.push(make_tuple(grid[current_i - 1][current_j], current_i - 1, current_j));
            }
            if (is_inclusive(current_i, current_j - 1)
                    && grid[current_i][current_j - 1] > grid[current_i][current_j] + distance_horizontal[current_i][current_j - 1]) {
                grid[current_i][current_j - 1] = grid[current_i][current_j] + distance_horizontal[current_i][current_j - 1];
                grid_path[current_i][current_j - 1] = 'L';
                que.push(make_tuple(grid[current_i][current_j - 1], current_i, current_j - 1));
            }
            if (is_inclusive(current_i, current_j + 1)
                    && grid[current_i][current_j + 1] > grid[current_i][current_j] + distance_horizontal[current_i][current_j]) {
                grid[current_i][current_j + 1] = grid[current_i][current_j] + distance_horizontal[current_i][current_j];
                grid_path[current_i][current_j + 1] = 'R';
                que.push(make_tuple(grid[current_i][current_j + 1], current_i, current_j + 1));
            }
            if (is_inclusive(current_i + 1, current_j)
                    && grid[current_i + 1][current_j] > grid[current_i][current_j] + distance_vertical[current_i][current_j]) {
                grid[current_i + 1][current_j] = grid[current_i][current_j] + distance_vertical[current_i][current_j];
                grid_path[current_i + 1][current_j] = 'D';
                que.push(make_tuple(grid[current_i + 1][current_j], current_i + 1, current_j));
            }
        }

        res[query_i] = "";
        for (int current_i = t_i[query_i], current_j = t_j[query_i]; grid_path[current_i][current_j] != 0; ) {
            res[query_i] += grid_path[current_i][current_j];

            if (grid_path[current_i][current_j] == 'U') {
                current_i++;
            } else if (grid_path[current_i][current_j] == 'L') {
                current_j++;
            } else if (grid_path[current_i][current_j] == 'R') {
                current_j--;
            } else if (grid_path[current_i][current_j] == 'D') {
                current_i--;
            }
        }

        reverse(res[query_i].begin(), res[query_i].end());
    }

    int time_limit_ms() {
        return 1980;
    }

    void update() {
        update_distance();
        update_leak();
    }

    void update_distance() {
        long long sum_distance = 0;
        for (int i = 0, current_i = s_i[query_i], current_j = s_j[query_i]; i < static_cast<int>(res[query_i].size()); i++) {
            if (res[query_i][i] == 'U') {
                sum_distance += distance_vertical[current_i - 1][current_j];
                current_i--;
            } else if (res[query_i][i] == 'L') {
                sum_distance += distance_horizontal[current_i][current_j - 1];
                current_j--;
            } else if (res[query_i][i] == 'R') {
                sum_distance += distance_horizontal[current_i][current_j];
                current_j++;
            } else if (res[query_i][i] == 'D') {
                sum_distance += distance_vertical[current_i][current_j];
                current_i++;
            }
        }

        double q_i = query_i + 1, q_s = query_size;
        q_i *= q_i; q_s *= q_s;
        q_i *= q_i; q_s *= q_s;
        q_i *= q_i; q_s *= q_s;
        q_i *= q_i;

        double penalty = abs(1.0 - static_cast<double>(b[query_i]) / sum_distance) + 1.0;
        penalty *= penalty;
        penalty *= penalty;
        penalty *= penalty;

        double weight = q_i / q_s / res[query_i].size() * penalty;
        for (int i = 0, current_i = s_i[query_i], current_j = s_j[query_i]; i < static_cast<int>(res[query_i].size()); i++) {
            if (res[query_i][i] == 'U') {
                distance_vertical_log[current_i - 1][current_j].push_back(b[query_i] * distance_vertical[current_i - 1][current_j] / sum_distance);
                distance_vertical_weight[current_i - 1][current_j].push_back(weight);

                double sum = 0, sum_weight = 0;
                for (int j = 0; j < static_cast<int>(distance_vertical_log[current_i - 1][current_j].size()); j++) {
                    sum += distance_vertical_log[current_i - 1][current_j][j] * distance_vertical_weight[current_i - 1][current_j][j];
                    sum_weight += distance_vertical_weight[current_i - 1][current_j][j];
                }

                distance_vertical[current_i - 1][current_j] = sum / sum_weight;
                current_i--;
            } else if (res[query_i][i] == 'L') {
                distance_horizontal_log[current_i][current_j - 1].push_back(b[query_i] * distance_horizontal[current_i][current_j - 1] / sum_distance);
                distance_horizontal_weight[current_i][current_j - 1].push_back(weight);

                double sum = 0, sum_weight = 0;
                for (int j = 0; j < static_cast<int>(distance_horizontal_log[current_i][current_j - 1].size()); j++) {
                    sum += distance_horizontal_log[current_i][current_j - 1][j] * distance_horizontal_weight[current_i][current_j - 1][j];
                    sum_weight += distance_horizontal_weight[current_i][current_j - 1][j];
                }

                distance_horizontal[current_i][current_j - 1] = sum / sum_weight;
                current_j--;
            } else if (res[query_i][i] == 'R') {
                distance_horizontal_log[current_i][current_j].push_back(b[query_i] * distance_horizontal[current_i][current_j] / sum_distance);
                distance_horizontal_weight[current_i][current_j].push_back(weight);

                double sum = 0, sum_weight = 0;
                for (int j = 0; j < static_cast<int>(distance_horizontal_log[current_i][current_j].size()); j++) {
                    sum += distance_horizontal_log[current_i][current_j][j] * distance_horizontal_weight[current_i][current_j][j];
                    sum_weight += distance_horizontal_weight[current_i][current_j][j];
                }

                distance_horizontal[current_i][current_j] = sum / sum_weight;
                current_j++;
            } else if (res[query_i][i] == 'D') {
                distance_vertical_log[current_i][current_j].push_back(b[query_i] * distance_vertical[current_i][current_j] / sum_distance);
                distance_vertical_weight[current_i][current_j].push_back(weight);

                double sum = 0, sum_weight = 0;
                for (int j = 0; j < static_cast<int>(distance_vertical_log[current_i][current_j].size()); j++) {
                    sum += distance_vertical_log[current_i][current_j][j] * distance_vertical_weight[current_i][current_j][j];
                    sum_weight += distance_vertical_weight[current_i][current_j][j];
                }

                distance_vertical[current_i][current_j] = sum / sum_weight;
                current_i++;
            }
        }
    }

    void update_leak() {
        update_leak_horizontal();
        update_leak_vertical();
    }

    void update_leak_horizontal() {
        vector<vector<vector<long long>>> leak(grid_size, vector<vector<long long>>(grid_size - 1, vector<long long>(0)));
        vector<vector<vector<double>>> weight(grid_size, vector<vector<double>>(grid_size - 1, vector<double>(0)));

        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size - 1; j++) {
                if (distance_horizontal_log[i][j].size() > 0) {
                    for (int k = -edge_leak; k <= edge_leak; k++) {
                        if (0 <= j + k && j + k < grid_size - 1) {
                            leak[i][j + k].push_back(distance_horizontal[i][j]);
                            weight[i][j + k].push_back(edge_leak_base - static_cast<double>(abs(k)) / edge_leak);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size - 1; j++) {
                if (distance_horizontal_log[i][j].size() == 0 && leak[i][j].size() > 0) {
                    double sum = 0, sum_weight = 0;
                    for (int k = 0; k < static_cast<int>(leak[i][j].size()); k++) {
                        sum += leak[i][j][k] * weight[i][j][k];
                        sum_weight += weight[i][j][k];
                    }

                    distance_horizontal[i][j] = sum / sum_weight;
                }
            }
        }
    }

    void update_leak_vertical() {
        vector<vector<vector<long long>>> leak(grid_size - 1, vector<vector<long long>>(grid_size, vector<long long>(0)));
        vector<vector<vector<double>>> weight(grid_size - 1, vector<vector<double>>(grid_size, vector<double>(0)));

        for (int i = 0; i < grid_size - 1; i++) {
            for (int j = 0; j < grid_size; j++) {
                if (distance_vertical_log[i][j].size() > 0) {
                    for (int k = -edge_leak; k <= edge_leak; k++) {
                        if (0 <= i + k && i + k < grid_size - 1) {
                            leak[i + k][j].push_back(distance_vertical[i][j]);
                            weight[i + k][j].push_back(edge_leak_base - static_cast<double>(abs(k)) / edge_leak);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < grid_size - 1; i++) {
            for (int j = 0; j < grid_size; j++) {
                if (distance_vertical_log[i][j].size() == 0 && leak[i][j].size() > 0) {
                    double sum = 0, sum_weight = 0;
                    for (int k = 0; k < static_cast<int>(leak[i][j].size()); k++) {
                        sum += leak[i][j][k] * weight[i][j][k];
                        sum_weight += weight[i][j][k];
                    }

                    distance_vertical[i][j] = sum / sum_weight;
                }
            }
        }
    }
};

int main() {
    application().run();
}
