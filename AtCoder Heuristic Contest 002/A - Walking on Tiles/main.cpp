#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <set>
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
    int n = 50;

    int si, sj;
    vector<vector<int>> t;
    vector<vector<int>> p;

    string res;

public:
    bool in(int i, int j) {
        return 0 <= i && i < n && 0 <= j && j < n;
    }

    void input() {
        cin >> si >> sj;

        t = vector<vector<int>>(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> t[i][j];
            }
        }

        p = vector<vector<int>>(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> p[i][j];
            }
        }
    }

    void output() {
        cout << res << endl;
    }

    void perform() {
        int state_limit = 3072;

        int di[] = { -1, 1, 0, 0 };
        int dj[] = { 0, 0, -1, 1 };
        string ds[] = { "U", "D", "L", "R" };

        vector<bool> state_v(n * n, false);
        state_v[t[si][sj]] = true;

        set<tuple<int, int, int, string, vector<bool>>> state;
        state.insert(make_tuple(p[si][sj], si, sj, "", state_v));

        while (time_elapsed_ms() < time_limit_ms()) {
            vector<tuple<int, int, int, string, vector<bool>>> next(0);
            for (set<tuple<int, int, int, string, vector<bool>>>::iterator i = state.begin(); i != state.end(); i++) {
                for (int j = 0; j < 4; j++) {
                    if (in(get<1>(*i) + di[j], get<2>(*i) + dj[j])
                            && !get<4>(*i)[t[get<1>(*i) + di[j]][get<2>(*i) + dj[j]]]) {
                        vector<bool> v(get<4>(*i));
                        v[t[get<1>(*i) + di[j]][get<2>(*i) + dj[j]]] = true;

                        next.push_back(make_tuple(get<0>(*i) + p[get<1>(*i) + di[j]][get<2>(*i) + dj[j]],
                                get<1>(*i) + di[j], get<2>(*i) + dj[j], get<3>(*i) + ds[j], v));
                    }
                }
            }

            if (next.size() == 0) {
                break;
            }

            sort(next.begin(), next.end(), greater<tuple<int, int, int, string, vector<bool>>>());

            state.clear();

            int next_size = next.size();
            if (next_size < state_limit) {
                for (int i = 0; i < next_size; i++) {
                    state.insert(next[i]);
                }
            } else {
                for (int i = 0; i < state_limit; i++) {
                    state.insert(next[i * next_size / state_limit]);
                }
            }
        }

        int res_val = 0;
        for (set<tuple<int, int, int, string, vector<bool>>>::iterator i = state.begin(); i != state.end(); i++) {
            if (res_val < get<0>(*i)) {
                res_val = get<0>(*i);
                res = get<3>(*i);
            }
        }
    }

    void run() {
        input();
        perform();
        output();
    }

    int time_limit_ms() {
        return 1980;
    }
};

int main() {
    application().run();
}
