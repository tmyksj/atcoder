#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
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
    int d = 10, r = 10000;

    int n, k;
    vector<int> a, x, y;

public:
    int evaluate(const vector<int>& px, const vector<int>& py, const vector<int>& qx, const vector<int>& qy) {
        vector<vector<int>> current(1, vector<int>(n));
        for (int i = 0; i < n; i++) {
            current[0][i] = i;
        }

        for (int i = 0; i < static_cast<int>(px.size()); i++) {
            vector<vector<int>> next(0);

            for (int j = 0; j < static_cast<int>(current.size()); j++) {
                vector<int> left(0), right(0);

                for (int k = 0; k < static_cast<int>(current[j].size()); k++) {
                    long long bx = px[i] - qx[i];
                    long long by = py[i] - qy[i];

                    long long cx = x[current[j][k]] - px[i];
                    long long cy = y[current[j][k]] - py[i];

                    long long d = bx * cy - by * cx;

                    if (d < 0) {
                        left.push_back(current[j][k]);
                    }

                    if (d > 0) {
                        right.push_back(current[j][k]);
                    }
                }

                if (left.size() > 0) {
                    next.push_back(left);
                }

                if (right.size() > 0) {
                    next.push_back(right);
                }
            }

            current = next;
        }

        vector<int> b(d, 0);
        for (int i = 0; i < static_cast<int>(current.size()); i++) {
            if (0 < current[i].size() && static_cast<int>(current[i].size()) <= d) {
                b[current[i].size() - 1]++;
            }
        }

        int ret = 0;
        for (int i = 0; i < d; i++) {
            ret += min(a[i], b[i]);
        }

        return ret;
    }

    void run() {
        cin >> n >> k;

        a = vector<int>(d);
        for (int i = 0; i < d; i++) {
            cin >> a[i];
        }

        x = vector<int>(n);
        y = vector<int>(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }

        int prop1 = 12;
        int prop2 = 40;
        int prop3 = 12;
        int prop4 = 40;

        vector<int> ux(x);
        sort(ux.begin(), ux.end());
        ux.erase(unique(ux.begin(), ux.end()), ux.end());

        vector<int> uy(x);
        sort(uy.begin(), uy.end());
        uy.erase(unique(uy.begin(), uy.end()), uy.end());

        int ret_val = 0;
        vector<int> ret_px, ret_py, ret_qx, ret_qy;

        while (time_limit_within()) {
            vector<int> px(k), py(k), qx(k), qy(k);

            int idx = 0;

            int v_size = random_uniform_int(prop1, prop2), v_diff = ux.size() / v_size;
            for (int i = v_diff; idx < k && i < static_cast<int>(ux.size()); idx++, i += v_diff) {
                px[idx] = (ux[i - 1] + ux[i]) / 2;
                py[idx] = 0;
                qx[idx] = px[idx] + random_uniform_int(ux[i - v_diff] - ux[i], ux[i] - ux[i - v_diff]) / 2;
                qy[idx] = r;
            }

            int h_size = random_uniform_int(prop3, prop4), h_diff = uy.size() / h_size;
            for (int i = h_diff; idx < k && i < static_cast<int>(uy.size()); idx++, i += h_diff) {
                px[idx] = 0;
                py[idx] = (uy[i - 1] + uy[i]) / 2;
                qx[idx] = r;
                qy[idx] = py[idx] + random_uniform_int(uy[i - h_diff] - uy[i], uy[i] - uy[i - h_diff]) / 2;
            }

            px.resize(idx);
            py.resize(idx);
            qx.resize(idx);
            qy.resize(idx);

            int val = evaluate(px, py, qx, qy);
            if (ret_val < val) {
                ret_val = val;
                ret_px = px;
                ret_py = py;
                ret_qx = qx;
                ret_qy = qy;
            }
        }

        cout << ret_px.size() << endl;
        for (int i = 0; i < static_cast<int>(ret_px.size()); i++) {
            cout << ret_px[i] << " " << ret_py[i] << " " << ret_qx[i] << " " << ret_qy[i] << endl;
        }
    }

    int time_limit_ms() {
        return 2900;
    }
};

int main() {
    application().run();
}
