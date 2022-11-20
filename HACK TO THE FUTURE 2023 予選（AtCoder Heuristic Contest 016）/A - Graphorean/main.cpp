#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class heuristics_core {
protected:
    random_device device;
    mt19937 engine;

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

public:
    heuristics_core() :
        engine(mt19937(device())) {
    }
};

class heuristics_application : public heuristics_core {
protected:
    chrono::system_clock::time_point time_zero;

    int time_elapsed_ms() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - time_zero).count();
    }

    bool time_limit_exceeded() {
        return time_elapsed_ms() > time_limit_ms();
    }

    bool time_limit_within() {
        return time_elapsed_ms() <= time_limit_ms();
    }

    virtual int time_limit_ms() = 0;

public:
    heuristics_application() :
        heuristics_core(),
        time_zero(chrono::system_clock::now()) {
    }

    virtual void run() = 0;
};

class application : public heuristics_application {
    int m, q;
    double epsilon;

    double emulate(int n, const vector<string>& g, const function<int(string)>& predictor) {
        int edge = n * (n - 1) / 2;

        int loop = 2400, e = 0;
        for (int i = 0; i < loop; i++) {
            int idx = random_uniform_int(0, m - 1);

            vector<int> jdx(n);
            for (int j = 0; j < n; j++) {
                jdx[j] = j;
            }

            shuffle(jdx.begin(), jdx.end(), engine);

            vector<vector<bool>> g1(n, vector<bool>(n, false));
            for (int j = 0, p = 0; j < n; j++) {
                for (int k = j + 1; k < n; k++, p++) {
                    g1[j][k] = g1[k][j] =
                            (g[idx][p] == '1') ^ (random_uniform_real(0, 1) <= epsilon);
                }
            }

            string g2(edge, '0');
            for (int j = 0, p = 0; j < n; j++) {
                for (int k = j + 1; k < n; k++, p++) {
                    if (g1[jdx[j]][jdx[k]]) {
                        g2[p] = '1';
                    }
                }
            }

            if (predictor(g2) != idx) {
                e++;
            }
        }

        return pow(0.9, e * q / static_cast<double>(loop)) / n;
    }

    void strategy_a(vector<tuple<double, int, vector<string>, function<int(string)>>>& ret) {
        if (epsilon != 0) {
            return;
        }

        int n = ceil((sqrt(8 * (m - 1) + 1) + 1) / 2);
        int edge = n * (n - 1) / 2;

        vector<string> g(m, string(edge, '0'));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < i; j++) {
                g[i][j] = '1';
            }
        }

        auto predictor = [=](string h) {
            return count(h.begin(), h.end(), '1');
        };

        ret.push_back(make_tuple(1.0 / n, n, g, predictor));
    }

    void strategy_b(vector<tuple<double, int, vector<string>, function<int(string)>>>& ret) {
        if (epsilon == 0) {
            return;
        }

        for (int n = 4; n <= 100; n += 4) {
            int edge = n * (n - 1) / 2;
            int step = edge / (m + 1);

            vector<int> a1(m);
            vector<double> a2(m);

            vector<vector<int>> b1(m, vector<int>(n));
            vector<vector<double>> b2(m, vector<double>(n));

            vector<string> g(m, string(edge, '0'));
            for (int i = 0; i < m; i++) {
                a1[i] = step * (i + 1);
                a2[i] = a1[i] * (1 - epsilon) + (edge - a1[i]) * epsilon;

                vector<vector<bool>> g1(n, vector<bool>(n, false));

                if (i % 2 == 0) {
                    for (int j = 0, p = 0; j < n && p < a1[i]; j++) {
                        for (int k = j + 1; k < n && p < a1[i]; k++, p++) {
                            g1[j][k] = g1[k][j] = true;
                        }
                    }
                } else {
                    for (int j = 0, p = 0; j < n && p < a1[i]; j++) {
                        for (int k = 0; j + k + 1 < n && p < a1[i]; k++, p++) {
                            g1[k][j + k + 1] = g1[j + k + 1][k] = true;
                        }
                    }
                }

                for (int j = 0; j < n; j++) {
                    b1[i][j] = count(g1[j].begin(), g1[j].end(), true);
                    b2[i][j] = b1[i][j] * (1 - epsilon) + (n - b1[i][j]) * epsilon;
                }

                sort(b2[i].begin(), b2[i].end());

                for (int j = 0, p = 0; j < n; j++) {
                    for (int k = j + 1; k < n; k++, p++) {
                        if (g1[j][k]) {
                            g[i][p] = '1';
                        }
                    }
                }
            }

            auto predictor = [=](string h) {
                int a3 = count(h.begin(), h.end(), '1');

                vector<int> b3(n, 0);
                for (int i = 0, p = 0; i < n; i++) {
                    for (int j = i + 1; j < n; j++, p++) {
                        if (h[p] == '1') {
                            b3[i]++;
                            b3[j]++;
                        }
                    }
                }

                sort(b3.begin(), b3.end());

                vector<tuple<double, int>> v(m);
                for (int i = 0; i < m; i++) {
                    v[i] = make_tuple(abs(a2[i] - a3), i);
                }

                sort(v.begin(), v.end());

                vector<tuple<double, int>> w(2);
                for (int i = 0; i < 2; i++)  {
                    double x = 0, y = 0, z = 0;
                    for (int j = 0; j < n; j++) {
                        x += b2[get<1>(v[i])][j] * b3[j];
                        y += b2[get<1>(v[i])][j] * b2[get<1>(v[i])][j];
                        z += b3[j] * b3[j];
                    }

                    w[i] = make_tuple(x / (sqrt(y) * sqrt(z)), get<1>(v[i]));
                }

                return get<1>(*max_element(w.begin(), w.end()));
            };

            ret.push_back(make_tuple(emulate(n, g, predictor), n, g, predictor));
        }
    }

    int time_limit_ms() {
        return 4800;
    }

public:
    void run() {
        cin >> m >> epsilon;
        q = 100;

        vector<tuple<double, int, vector<string>, function<int(string)>>> ret(0);
        strategy_a(ret);
        strategy_b(ret);

        tuple<double, int, vector<string>, function<int(string)>> strategy =
                *max_element(ret.begin(), ret.end(), [](const auto& a, const auto& b) {
                    return get<0>(a) < get<0>(b);
                });

        cout << get<1>(strategy) << endl;
        for (int i = 0; i < m; i++) {
            cout << get<2>(strategy)[i] << endl;
        }

        for (int i = 0; i < q; i++) {
            string h;
            cin >> h;

            cout << get<3>(strategy)(h) << endl;
        }
    }
};

int main() {
    application().run();
}
