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
    int size;
    vector<vector<int>> t;

    int gen_size = 20;
    int gen_i_p0 = 2400;
    int gen_e_p0 = 4;
    int gen_s_p0 = 20;
    int gen_s_p1 = 20;
    int gen_m_p0 = 8;
    double gen_m_p1 = 4.0;
    double gen_m_p2 = 0.08;

public:
    void run() {
        size = 30;

        t = vector<vector<int>>(size, vector<int>(size));
        for (int i = 0; i < size; i++) {
            string s;
            cin >> s;

            for (int j = 0; j < size; j++) {
                t[i][j] = s[j] - '0';
            }
        }

        auto gen_comp = [](const tuple<long long, string>& a, const tuple<long long, string>&b) {
            return get<0>(a) > get<0>(b);
        };

        vector<tuple<long long, string>> gen(0);
        for (int i = 0; i < gen_i_p0; i++) {
            string r(size * size, '0');
            for (int j = 0; j < size * size; j++) {
                r[j] += random_uniform_int(0, 3);
            }

            gen.push_back(make_tuple(score(r, 0), r));
        }

        sort(gen.begin(), gen.end(), gen_comp);
        gen.resize(gen_size);

        string ret = get<1>(gen[0]);
        long long ret_s = score(ret);

        while (time_limit_within()) {
            vector<tuple<long long, string>> next(0);

            for (int i = 0; i < gen_e_p0; i++) {
                next.push_back(gen[i]);
            }

            for (int i = 0; i < gen_s_p0; i++) {
                for (int j = 0; j < gen_s_p0; j++) {
                    if (i == j) {
                        continue;
                    }

                    int p0 = random_uniform_int(0, size * size - 1);
                    int p1 = random_uniform_int(0, size * size - 1);
                    while (p0 == p1) {
                        p1 = random_uniform_int(0, size * size - 1);
                    }

                    if (p0 > p1) {
                        swap(p0, p1);
                    }

                    string s0 = get<1>(gen[i]);
                    string s1 = get<1>(gen[j]);

                    string r(s0);
                    for (int k = p0; k < p1; k++) {
                        r[k] = s1[k];
                    }

                    next.push_back(make_tuple(score(r), r));
                }
            }

            for (int i = 0; i < gen_s_p1; i++) {
                for (int j = 0; j < gen_s_p1; j++) {
                    if (i == j) {
                        continue;
                    }

                    string s0 = get<1>(gen[i]);
                    string s1 = get<1>(gen[j]);

                    string r(s0);
                    for (int k = 0; k < size * size; k++) {
                        if (random_uniform_int(0, 1) == 1) {
                            r[k] = s1[k];
                        }
                    }

                    next.push_back(make_tuple(score(r), r));
                }
            }

            for (int i = 0; i < gen_m_p0; i++) {
                int j = static_cast<int>(random_poisson(gen_m_p1));
                while (j >= gen_size) {
                    j = static_cast<int>(random_poisson(gen_m_p1));
                }

                string r(get<1>(gen[j]));
                for (int k = 0; k < size * size; k++) {
                    if (random_uniform(0, 1.0) <= gen_m_p2) {
                        r[k] = random_uniform_int(0, 3) + '0';
                    }
                }

                next.push_back(make_tuple(score(r), r));
            }

            sort(next.begin(), next.end(), gen_comp);

            for (int i = 0; i < gen_size; i++) {
                gen[i] = next[i];
            }

            if (ret_s < get<0>(gen[0])) {
                ret_s = get<0>(gen[0]);
                ret = get<1>(gen[0]);
            }
        }

        cout << ret << endl;
    }

    long long score(string r, int mode = 1) {
        int rotate[8][4] = {
            { 0, 1, 2, 3 },
            { 1, 2, 3, 0 },
            { 2, 3, 0, 1 },
            { 3, 0, 1, 2 },
            { 4, 5, 4, 5 },
            { 5, 4, 5, 4 },
            { 6, 7, 6, 7 },
            { 7, 6, 7, 6 },
        };

        int dy[4] = { -1, 0, 0, 1 };
        int dx[4] = { 0, -1, 1, 0 };

        int to[8][4] = {
            { 1, 0, -1, -1 },
            { -1, 3, -1, 1 },
            { -1, -1, 3, 2 },
            { 2, -1, 0, -1 },
            { 1, 0, 3, 2 },
            { 2, 3, 0, 1 },
            { -1, 2, 1, -1 },
            { 3, -1, -1, 0 },
        };

        vector<vector<int>> u(size, vector<int>(size));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                u[i][j] = rotate[t[i][j]][r[i * size + j] - '0'];
            }
        }

        vector<vector<vector<bool>>> v(size, vector<vector<bool>>(size, vector<bool>(4, true)));

        vector<long long> s(0);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < 4; k++) {
                    int y = i, x = j, z = k, dist = 0;
                    while (v[y][x][z]) {
                        v[y][x][z] = false;

                        int d = to[u[y][x]][z];
                        if (d == -1) {
                            break;
                        }

                        v[y][x][d] = false;

                        y += dy[d];
                        x += dx[d];
                        if (y < 0 || size <= y || x < 0 || size <= x) {
                            break;
                        }

                        z = 3 - d;
                        dist++;

                        if (y == i && x == j && z == k) {
                            s.push_back(dist);
                            break;
                        }
                    }
                }
            }
        }

        sort(s.begin(), s.end(), greater<long long>());

        if (mode == 0) {
            return s.size() >= 1 ? s[0] : 0;
        } else {
            return s.size() >= 2 ? s[0] * s[1] : 0;
        }
    }

    int time_limit_ms() {
        return 1900;
    }
};

int main() {
    application().run();
}
