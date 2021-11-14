#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
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
    int order = 1000;
    int size = 50;

    int width = 801, height = 801;
    int x0 = 400, y0 = 400;
    int xn = 400, yn = 400;

    vector<int> a, b, c, d;
    vector<int> r, x, y;

public:
    int absolute_value(int a) {
        return a >= 0 ? a : -a;
    }

    void input() {
        a = vector<int>(order);
        b = vector<int>(order);
        c = vector<int>(order);
        d = vector<int>(order);
        for (int i = 0; i < order; i++) {
            cin >> a[i] >> b[i] >> c[i] >> d[i];
        }
    }

    void output() {
        cout << r.size();
        for (int i = 0; i < static_cast<int>(r.size()); i++) {
            cout << " " << r[i] + 1;
        }
        cout << endl;

        cout << x.size();
        for (int i = 0; i < static_cast<int>(x.size()); i++) {
            cout << " " << x[i] << " " << y[i];
        }
        cout << endl;
    }

    void run() {
        input();
        setup();
        solve();
        output();
    }

    void setup() {
        r = vector<int>(0);
        x = vector<int>(0);
        y = vector<int>(0);
    }

    void solve() {
        pick_subset(r);
        find_path(r, x, y);
    }

    int distance(int x0, int y0, int x1, int y1) {
        return absolute_value(x0 - x1) + absolute_value(y0 - y1);
    }

    void pick_subset(vector<int>& ret_subset) {
        vector<tuple<int, int, int, int, int>> point(order);
        for (int i = 0; i < order; i++) {
            point[i] = make_tuple(i, a[i], b[i], c[i], d[i]);
        }

        auto sort_by_distance = [&](tuple<int, int, int, int, int>& a, tuple<int, int, int, int, int>& b) {
            int distance_a = max(distance(get<1>(a), get<2>(a), x0, y0), distance(get<3>(a), get<4>(a), x0, y0));
            int distance_b = max(distance(get<1>(b), get<2>(b), x0, y0), distance(get<3>(b), get<4>(b), x0, y0));
            return distance_a < distance_b;
        };

        sort(point.begin(), point.end(), sort_by_distance);

        for (int i = 0; i < size; i++) {
            ret_subset.push_back(get<0>(point[i]));
        }
    }

    void find_path(vector<int>& subset, vector<int>& ret_x, vector<int>& ret_y) {
        int ret_cost = 1 << 29;

        for (double priority = 0.25; priority <= 1.75; priority += 0.015625) {
            vector<int> rx(0), ry(0);

            rx.push_back(x0);
            ry.push_back(y0);

            vector<int> point_x(0), point_y(0), point_z(0);
            for (int i = 0; i < size; i++) {
                point_x.push_back(a[subset[i]]);
                point_y.push_back(b[subset[i]]);
                point_z.push_back(subset[i]);
            }

            for (int cx = x0, cy = y0; !point_x.empty(); ) {
                int idx = 0;
                for (int i = 1; i < static_cast<int>(point_x.size()); i++) {
                    if (distance(point_x[idx], point_y[idx], cx, cy) * (point_z[idx] >= 0 ? priority : 1.0)
                            > distance(point_x[i], point_y[i], cx, cy) * (point_z[i] >= 0 ? priority : 1.0)) {
                        idx = i;
                    }
                }

                cx = point_x[idx];
                cy = point_y[idx];

                rx.push_back(point_x[idx]);
                ry.push_back(point_y[idx]);

                if (point_z[idx] >= 0) {
                    point_x.push_back(c[point_z[idx]]);
                    point_y.push_back(d[point_z[idx]]);
                    point_z.push_back(-1);
                }

                point_x.erase(point_x.begin() + idx);
                point_y.erase(point_y.begin() + idx);
                point_z.erase(point_z.begin() + idx);
            }

            rx.push_back(xn);
            ry.push_back(yn);

            int cost = 0;
            for (int i = 1; i < static_cast<int>(rx.size()); i++) {
                cost += distance(rx[i - 1], ry[i - 1], rx[i], ry[i]);
            }

            if (ret_cost > cost) {
                ret_cost = cost;

                ret_x.clear();
                ret_x.insert(ret_x.begin(), rx.begin(), rx.end());

                ret_y.clear();
                ret_y.insert(ret_y.begin(), ry.begin(), ry.end());
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
