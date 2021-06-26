#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <string>
#include <vector>

using namespace std;

class heuristics {
protected:
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
    string genome = "ABCDEFGH";

    int n, m;
    vector<string> s;

    vector<string> res;
    double res_value;

    vector<string> t;

public:
    bool in(vector<string>& out, string g) {
        bool ret = false;
        for (int i = 0; i < n && !ret; i++) {
            for (int j = 0; j < n && !ret; j++) {
                bool ret_row = true, ret_col = true;
                for (int k = 0; k < static_cast<int>(g.size()); k++) {
                    ret_row = ret_row && out[i][(j + k) % n] == g[k];
                    ret_col = ret_col && out[(i + k) % n][k] == g[k];
                }

                ret = ret_row || ret_col;
            }
        }

        return ret;
    }

    void input() {
        cin >> n >> m;

        s = vector<string>(m);
        for (int i = 0; i < m; i++) {
            cin >> s[i];
        }
    }

    void output() {
        for (int i = 0; i < n; i++) {
            cout << res[i] << endl;
        }
    }

    void perform() {
        perform_step0();
        perform_step1();
    }

    void perform_step0() {
        vector<string> t_base(0);

        int s_size_max = 0;
        for (int i = 0; i < m; i++) {
            s_size_max = max(s_size_max, static_cast<int>(s[i].size()));
        }

        vector<bool> pick(m, true);
        for (int k = s_size_max; k > 6; k--) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    if (pick[i] && pick[j]
                            && min(static_cast<int>(s[i].size()), static_cast<int>(s[j].size())) >= k
                            && s[i].size() + s[j].size() - k <= n) {
                        bool partial_match = true;
                        for (int p = 0; p < k && partial_match; p++) {
                            partial_match = s[i][p] == s[j][p - k + s[j].size()];
                        }

                        if (partial_match) {
                            t_base.push_back(s[i] + s[j].substr(k));
                            pick[i] = false;
                            pick[j] = false;
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            if (pick[i]) {
                t_base.push_back(s[i]);
                pick[i] = false;
            }
        }

        t = vector<string>(0);
        for (int i = 0; i < static_cast<int>(t_base.size()); i++) {
            bool uniq = true;
            for (int j = 0; j < static_cast<int>(t_base.size()) && uniq; j++) {
                uniq = uniq && (i == j || t_base[j].find(t_base[i]) == string::npos);
            }

            if (uniq) {
                t.push_back(t_base[i]);
            }
        }
    }

    void perform_step1() {
        res_value = 0;
        while (!time_limit_exceeded()) {
            vector<string> out;
            perform_step1_each(out);

            double out_value = value(out);
            if (res_value < out_value) {
                res = out;
                res_value = out_value;
            }
        }
    }

    void perform_step1_each(vector<string>& out) {
        shuffle(t.begin(), t.end(), engine);

        out.resize(n);
        for (int i = 0, k = 0; i < n; i++) {
            out[i] = "";

            int j = 0;
            for (; j + static_cast<int>(t[k].size()) <= n; j += t[k].size(), k++) {
                out[i] += t[k];
            }

            for (; j < n; j++) {
                out[i] += ".";
            }
        }

        map<int, queue<string>> t_mq;
        for (int i = 0; i < static_cast<int>(t.size()); i++) {
            if (!in(out, t[i])) {
                t_mq[t[i].size()].push(t[i]);
            }
        }

        for (int i = 0; i < n; i++) {
            int j = 0;
            for (; j < n; j++) {
                if (out[i][j] == '.') {
                    break;
                }
            }

            if (j < n && t_mq[n - j].empty()) {
                for (; j < n; j++) {
                    out[i][j] = genome[random_uniform_int(0, genome.size() - 1)];
                }
            } else if (j < n) {
                string g = t_mq[n - j].front();
                t_mq[n - j].pop();
                for (int k = 0; j < n; j++, k++) {
                    out[i][j] = g[k];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            string prev = out[i];
            for (int j = 0, delta = random_uniform_int(0, n - 1); j < n; j++) {
                out[i][j] = prev[(j + delta) % n];
            }
        }
    }

    void run() {
        input();
        perform();
        output();
    }

    int time_limit_ms() {
        return 2980;
    }

    double value(vector<string>& out) {
        double c = 0;
        for (int i = 0; i < m; i++) {
            if (in(out, s[i])) {
                c++;
            }
        }

        double d = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (out[i][j] == '.') {
                    d++;
                }
            }
        }

        return c < m ? c / m : 2 * n * n / (2 * n * n - d);
    }
};

int main() {
    application().run();
}
