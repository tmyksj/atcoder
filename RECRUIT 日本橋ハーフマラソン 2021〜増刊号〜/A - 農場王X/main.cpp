#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class heuristics_common {
    random_device device;
    mt19937 engine;

public:
    heuristics_common() :
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

class heuristics_application : public heuristics_common {
    chrono::system_clock::time_point time_zero;

public:
    heuristics_application() :
        heuristics_common(),
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
    int n, m, t;
    vector<int> r, c, s, e;
    vector<long long> v;

    vector<vector<vector<long long>>> farm;
    vector<vector<vector<int>>> id;

    vector<string> res;
    long long res_money;

    int prop_initial_machine_size = 28;

    int prop_delta_size = 13;
    int prop_delta_len[13] = { 81, 35, 35, 35, 35, 35, 35, 35, 35, 39, 39, 39, 39, };
    int prop_delta_row[13][81] = {
        {  0,  0, -1, -1, -1,  0,  1,  1,  1,  1,  0, -1, -2, -2, -2, -2, -2, -1,  0,  1,  2,  2,  2,  2,  2,  2,  1,  0, -1, -2, -3, -3, -3, -3, -3, -3, -3, -2, -1,  0,  1,  2,  3,  3,  3,  3,  3,  3,  3,  3,  2,  1,  0, -1, -2, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -2, -1,  0,  1,  2,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4, },
        {  0,  0,  0, -1, -1, -1, -1, -2, -2, -2, -2, -2, -3, -3, -3, -3, -4, -4, -4, -5, -5, -5, -5, -6, -6, -6, -6, -6, -7, -7, -7, -7, -8, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0, -1, -2,  0, -1, -2, -3,  0, -1, -2, -3, -4, -1, -2, -3, -4, -2, -3, -4, -2, -3, -4, -5, -2, -3, -4, -5, -6, -3, -4, -5, -6, -4, -5, -6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,  3,  3,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  1,  2,  0,  1,  2,  3,  0,  1,  2,  3,  4,  1,  2,  3,  4,  2,  3,  4,  2,  3,  4,  5,  2,  3,  4,  5,  6,  3,  4,  5,  6,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0, -1, -2,  0, -1, -2, -3,  0, -1, -2, -3, -4, -1, -2, -3, -4, -2, -3, -4, -2, -3, -4, -5, -2, -3, -4, -5, -6, -3, -4, -5, -6, -4, -5, -6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0, -1, -1, -1, -1, -2, -2, -2, -2, -2, -3, -3, -3, -3, -4, -4, -4, -5, -5, -5, -5, -6, -6, -6, -6, -6, -7, -7, -7, -7, -8, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  1,  2,  0,  1,  2,  3,  0,  1,  2,  3,  4,  1,  2,  3,  4,  2,  3,  4,  2,  3,  4,  5,  2,  3,  4,  5,  6,  3,  4,  5,  6,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,  3,  3,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0, -1, -1, -1, -1, -2, -2, -2, -2, -2, -3, -3, -3, -3, -3, -4, -4, -4, -4, -4, -5, -5, -5, -5, -5, -6, -6, -6, -6, -6, -7, -7, -7, -7, -8, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0, -1, -2,  0, -1, -2, -3,  0, -1, -2, -3, -4, -1, -2, -3, -4, -5, -2, -3, -4, -5, -6, -3, -4, -5, -6, -7, -4, -5, -6, -7, -8, -5, -6, -7, -8, -6, -7, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  1,  2,  0,  1,  2,  3,  0,  1,  2,  3,  4,  1,  2,  3,  4,  5,  2,  3,  4,  5,  6,  3,  4,  5,  6,  7,  4,  5,  6,  7,  8,  5,  6,  7,  8,  6,  7,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
    };
    int prop_delta_col[13][81] = {
        {  0, -1, -1,  0,  1,  1,  1,  0, -1, -2, -2, -2, -2, -1,  0,  1,  2,  2,  2,  2,  2,  1,  0, -1, -2, -3, -3, -3, -3, -3, -3, -2, -1,  0,  1,  2,  3,  3,  3,  3,  3,  3,  3,  2,  1,  0, -1, -2, -3, -4, -4, -4, -4, -4, -4, -4, -4, -3, -2, -1,  0,  1,  2,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  3,  2,  1,  0, -1, -2, -3, -4, },
        {  0,  1,  2,  0,  1,  2,  3,  0,  1,  2,  3,  4,  1,  2,  3,  4,  2,  3,  4,  2,  3,  4,  5,  2,  3,  4,  5,  6,  3,  4,  5,  6,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0, -1, -1, -1, -1, -2, -2, -2, -2, -2, -3, -3, -3, -3, -4, -4, -4, -5, -5, -5, -5, -6, -6, -6, -6, -6, -7, -7, -7, -7, -8, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0, -1, -2,  0, -1, -2, -3,  0, -1, -2, -3, -4, -1, -2, -3, -4, -2, -3, -4, -2, -3, -4, -5, -2, -3, -4, -5, -6, -3, -4, -5, -6, -4, -5, -6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,  3,  3,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,  3,  3,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0, -1, -2,  0, -1, -2, -3,  0, -1, -2, -3, -4, -1, -2, -3, -4, -2, -3, -4, -2, -3, -4, -5, -2, -3, -4, -5, -6, -3, -4, -5, -6, -4, -5, -6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0, -1, -1, -1, -1, -2, -2, -2, -2, -2, -3, -3, -3, -3, -4, -4, -4, -5, -5, -5, -5, -6, -6, -6, -6, -6, -7, -7, -7, -7, -8, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  1,  2,  0,  1,  2,  3,  0,  1,  2,  3,  4,  1,  2,  3,  4,  2,  3,  4,  2,  3,  4,  5,  2,  3,  4,  5,  6,  3,  4,  5,  6,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  1,  2,  0,  1,  2,  3,  0,  1,  2,  3,  4,  1,  2,  3,  4,  5,  2,  3,  4,  5,  6,  3,  4,  5,  6,  7,  4,  5,  6,  7,  8,  5,  6,  7,  8,  6,  7,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0, -1, -1, -1, -1, -2, -2, -2, -2, -2, -3, -3, -3, -3, -3, -4, -4, -4, -4, -4, -5, -5, -5, -5, -5, -6, -6, -6, -6, -6, -7, -7, -7, -7, -8, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0, -1, -2,  0, -1, -2, -3,  0, -1, -2, -3, -4, -1, -2, -3, -4, -5, -2, -3, -4, -5, -6, -3, -4, -5, -6, -7, -4, -5, -6, -7, -8, -5, -6, -7, -8, -6, -7, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
        {  0,  0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, },
    };

public:
    long long area_size(vector<vector<bool>>& v, int r, int c) {
        vector<vector<bool>> dfs(n, vector<bool>(n, true));
        dfs[r][c] = false;

        return area_size(v, r, c, dfs);
    }

    long long area_size(vector<vector<bool>>& v, int r, int c, vector<vector<bool>>& dfs) {
        if (v[r][c]) {
            long long ret = 1;
            int dr[] = { -1, 0, 0, 1 };
            int dc[] = { 0, -1, 1, 0 };
            for (int i = 0; i < 4; i++) {
                if (0 <= r + dr[i] && r + dr[i] < n
                        && 0 <= c + dc[i] && c + dc[i] < n
                        && dfs[r + dr[i]][c + dc[i]]) {
                    dfs[r + dr[i]][c + dc[i]] = false;
                    ret += area_size(v, r + dr[i], c + dc[i], dfs);
                }
            }

            return ret;
        } else {
            return 0;
        }
    }

    void input() {
        cin >> n >> m >> t;

        r = vector<int>(m);
        c = vector<int>(m);
        s = vector<int>(m);
        e = vector<int>(m);
        v = vector<long long>(m);
        for (int i = 0; i < m; i++) {
            cin >> r[i] >> c[i] >> s[i] >> e[i] >> v[i];
        }
    }

    void output() {
        for (int i = 0; i < t; i++) {
            cout << res[i] << endl;
        }
    }

    void run() {
        input();
        setup();
        solve();
        output();
    }

    void setup() {
        setup_farm();
        setup_id();
        setup_res();
    }

    void setup_farm() {
        farm = vector<vector<vector<long long>>>(t, vector<vector<long long>>(n, vector<long long>(n, 0)));
        for (int i = 0; i < m; i++) {
            for (int j = s[i]; j <= e[i]; j++) {
                farm[j][r[i]][c[i]] = v[i];
            }
        }
    }

    void setup_id() {
        id = vector<vector<vector<int>>>(t, vector<vector<int>>(n, vector<int>(n, -1)));
        for (int i = 0; i < m; i++) {
            for (int j = s[i]; j <= e[i]; j++) {
                id[j][r[i]][c[i]] = i;
            }
        }
    }

    void setup_res() {
        res = vector<string>(t, "-1");
        res_money = -1;
    }

    void solve() {
        for (int machine_size = prop_initial_machine_size; time_limit_within(); machine_size++) {
            vector<string> ret(t);
            long long money = 1;

            vector<bool> vegetable(m, true);
            vector<vector<bool>> machine(n, vector<bool>(n, false));
            vector<int> machine_row(0), machine_col(0);

            for (int time = 0; time < t; time++) {
                if (time_limit_exceeded()) {
                    return;
                }

                long long machine_price =
                        (machine_row.size() + 1) * (machine_row.size() + 1) * (machine_row.size() + 1);

                if (static_cast<int>(machine_row.size()) < machine_size && machine_price <= money) {
                    int new_row = -1, new_col = -1;
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            if (farm[time][i][j] > 0
                                    && vegetable[id[time][i][j]]
                                    && !machine[i][j]
                                    && (new_row == -1 || farm[time][i][j] > farm[time][new_row][new_col])) {
                                new_row = i;
                                new_col = j;
                            }
                        }
                    }

                    if (new_row == -1) {
                        ret[time] = "-1";
                    } else {
                        money -= machine_price;
                        machine[new_row][new_col] = true;
                        machine_row.insert(machine_row.begin(), new_row);
                        machine_col.insert(machine_col.begin(), new_col);
                        ret[time] = to_string(new_row) + " " + to_string(new_col);
                    }

                    for (int i = 0; i < static_cast<int>(machine_row.size()); i++) {
                        if (farm[time][machine_row[i]][machine_col[i]] > 0
                                && vegetable[id[time][machine_row[i]][machine_col[i]]]) {
                            vegetable[id[time][machine_row[i]][machine_col[i]]] = false;
                            money += farm[time][machine_row[i]][machine_col[i]]
                                    * area_size(machine, machine_row[i], machine_col[i]);
                        }
                    }
                } else {
                    int dst_delta = -1, dst_time = -1, dst_row = -1, dst_col = -1;
                    long long dst_val = -1;

                    for (int ds_idx = 0; ds_idx < prop_delta_size; ds_idx++) {
                        int d_len = prop_delta_len[ds_idx];
                        int* dr = prop_delta_row[ds_idx];
                        int* dc = prop_delta_col[ds_idx];

                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < n; j++) {
                                long long val = 0;

                                for (int m_idx = 0, d_idx = 0, k = 0; time + k < t; m_idx++, d_idx++, k++) {
                                    while (d_idx < d_len
                                            && m_idx < static_cast<int>(machine_row.size())
                                            && (i + dr[d_idx] < 0 || n <= i + dr[d_idx]
                                                    || j + dc[d_idx] < 0 || n <= j + dc[d_idx]
                                                    || machine[i + dr[d_idx]][j + dc[d_idx]])) {
                                        if (0 <= i + dr[d_idx] && i + dr[d_idx] < n
                                                && 0 <= j + dc[d_idx] && j + dc[d_idx] < n
                                                && machine[i + dr[d_idx]][j + dc[d_idx]]) {
                                            m_idx++;
                                        }

                                        d_idx++;
                                    }

                                    if (d_idx == d_len || m_idx == static_cast<int>(machine_row.size())) {
                                        break;
                                    } else if (farm[time + k][i + dr[d_idx]][j + dc[d_idx]] > 0
                                            && vegetable[id[time + k][i + dr[d_idx]][j + dc[d_idx]]]) {
                                        val += farm[time + k][i + dr[d_idx]][j + dc[d_idx]] * (m_idx + 1);
                                    }

                                    if (dst_val == -1
                                            || static_cast<double>(dst_val) / (dst_time + 1)
                                                    < static_cast<double>(val) / (k + 1)) {
                                        dst_delta = ds_idx;
                                        dst_val = val;
                                        dst_time = k;
                                        dst_row = i;
                                        dst_col = j;
                                    }
                                }
                            }
                        }
                    }

                    if (dst_delta == -1) {
                        ret[time] = "-1";
                    } else {
                        int d_len = prop_delta_len[dst_delta];
                        int* dr = prop_delta_row[dst_delta];
                        int* dc = prop_delta_col[dst_delta];

                        int m_idx = 0;
                        for (int d_idx = 0, k = 0; k <= dst_time; m_idx++, d_idx++, k++, time++) {
                            while (d_idx < d_len
                                    && m_idx < static_cast<int>(machine_row.size())
                                    && (dst_row + dr[d_idx] < 0 || n <= dst_row + dr[d_idx]
                                            || dst_col + dc[d_idx] < 0 || n <= dst_col + dc[d_idx]
                                            || machine[dst_row + dr[d_idx]][dst_col + dc[d_idx]])) {
                                if (0 <= dst_row + dr[d_idx] && dst_row + dr[d_idx] < n
                                        && 0 <= dst_col + dc[d_idx] && dst_col + dc[d_idx] < n
                                        && machine[dst_row + dr[d_idx]][dst_col + dc[d_idx]]) {
                                    for (int i = 0; i < static_cast<int>(machine_row.size()); i++) {
                                        if (machine_row[i] == dst_row + dr[d_idx]
                                                && machine_col[i] == dst_col + dc[d_idx]) {
                                            for (int j = i; j > m_idx; j--) {
                                                swap(machine_row[j], machine_row[j - 1]);
                                                swap(machine_col[j], machine_col[j - 1]);
                                            }

                                            break;
                                        }
                                    }

                                    m_idx++;
                                }

                                d_idx++;
                            }

                            if (d_idx == d_len || m_idx == static_cast<int>(machine_row.size())) {
                                ret[time] = "-1";
                            } else {
                                int src_row = machine_row[m_idx], src_col = machine_col[m_idx];
                                machine[src_row][src_col] = false;
                                machine[dst_row + dr[d_idx]][dst_col + dc[d_idx]] = true;
                                machine_row[m_idx] = dst_row + dr[d_idx];
                                machine_col[m_idx] = dst_col + dc[d_idx];
                                ret[time] = to_string(src_row)
                                        + " " + to_string(src_col)
                                        + " " + to_string(dst_row + dr[d_idx])
                                        + " " + to_string(dst_col + dc[d_idx]);
                            }

                            for (int i = 0; i < static_cast<int>(machine_row.size()); i++) {
                                if (farm[time][machine_row[i]][machine_col[i]] > 0
                                        && vegetable[id[time][machine_row[i]][machine_col[i]]]) {
                                    vegetable[id[time][machine_row[i]][machine_col[i]]] = false;
                                    money += farm[time][machine_row[i]][machine_col[i]]
                                            * area_size(machine, machine_row[i], machine_col[i]);
                                }
                            }
                        }

                        if (m_idx > static_cast<int>(machine_row.size()) / 2) {
                            reverse(machine_row.begin(), machine_row.begin() + m_idx);
                            reverse(machine_row.begin(), machine_row.end());
                            reverse(machine_col.begin(), machine_col.begin() + m_idx);
                            reverse(machine_col.begin(), machine_col.end());
                        }

                        time--;
                    }
                }
            }

            if (res_money < money) {
                res = ret;
                res_money = money;
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
