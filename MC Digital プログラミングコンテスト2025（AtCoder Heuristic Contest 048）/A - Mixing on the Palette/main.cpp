#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

using namespace std;

class heuristics {
public:
    chrono::system_clock::time_point clock_zero;

    random_device device;
    mt19937 engine;

    heuristics() :
        clock_zero(chrono::system_clock::now()),
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

    double random_uniform_real(double a, double b) {
        return uniform_real_distribution<double>(a, b)(engine);
    }

    double random_weibull(double a, double b) {
        return weibull_distribution<double>(a, b)(engine);
    }

    int time_elapsed_ms() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - clock_zero).count();
    }

    bool time_limit_exceeded() {
        return time_elapsed_ms() > time_limit_ms();
    }

    virtual int time_limit_ms() {
        return 0;
    }

    bool time_limit_within() {
        return time_elapsed_ms() <= time_limit_ms();
    }
};

class color {
public:
    double C, M, Y;

    double e(color& c1) {
        return sqrt((C - c1.C) * (C - c1.C)
                + (M - c1.M) * (M - c1.M)
                + (Y - c1.Y) * (Y - c1.Y));
    }
};

class well {
public:
    double C, M, Y;
    double v, w;
    int y, x;

    void add(color& c1) {
        C = (v * C + c1.C) / (v + 1);
        M = (v * M + c1.M) / (v + 1);
        Y = (v * Y + c1.Y) / (v + 1);
        v++;
    }

    void sub() {
        v--;
    }

    double e(color& c1) {
        return sqrt((C - c1.C) * (C - c1.C)
                + (M - c1.M) * (M - c1.M)
                + (Y - c1.Y) * (Y - c1.Y));
    }

    double e(color& c1, color& c2) {
        return sqrt(((v * C + c1.C) / (v + 1) - c2.C) * ((v * C + c1.C) / (v + 1) - c2.C)
                + ((v * M + c1.M) / (v + 1) - c2.M) * ((v * M + c1.M) / (v + 1) - c2.M)
                + ((v * Y + c1.Y) / (v + 1) - c2.Y) * ((v * Y + c1.Y) / (v + 1) - c2.Y));
    }
};

class application : public heuristics {
    int N, K, H, T, D;
    vector<color> own, tgt;

public:
    application() :
        heuristics() {
    }

    void run() {
        cin >> N >> K >> H >> T >> D;

        own.resize(K);

        for (int i = 0; i < K; i++) {
            cin >> own[i].C >> own[i].M >> own[i].Y;
        }

        tgt.resize(H);

        for (int i = 0; i < H; i++) {
            cin >> tgt[i].C >> tgt[i].M >> tgt[i].Y;
        }

        vector<tuple<double, vector<vector<int>>>> ret(0);

        solve1(ret);

        vector<int> seed(N * N);

        for (int i = 0; i < N * N; i++) {
            seed[i] = i % K;
        }

        while (time_limit_within()) {
            for (int i = 2; i <= 12 && time_limit_within(); i++) {
                for (int j = 1; j <= N * N / i && 2 * H + i * j - 1 <= T && time_limit_within(); j++) {
                    solve2(ret, seed, i, j);
                }
            }

            shuffle(seed.begin(), seed.end(), engine);
        }

        sort(ret.begin(), ret.end(), [](const auto& a, const auto& b) {
            return get<0>(a) < get<0>(b);
        });

        for (int i = 0; i < static_cast<int>(get<1>(ret[0]).size()); i++) {
            cout << get<1>(ret[0])[i][0];
            for (int j = 1; j < static_cast<int>(get<1>(ret[0])[i].size()); j++) {
                cout << " " << get<1>(ret[0])[i][j];
            }
            cout << endl;
        }
    }

    void solve1(vector<tuple<double, vector<vector<int>>>>& ret) {
        ret.push_back(make_tuple(1, vector<vector<int>>(0)));

        double E = 0;

        for (int i = 0; i < N; i++) {
            get<1>(ret[ret.size() - 1]).push_back(vector<int>(N - 1, 0));
        }

        for (int i = 0; i < N - 1; i++) {
            get<1>(ret[ret.size() - 1]).push_back(vector<int>(N, 0));
        }

        for (int i = 0; i < H; i++) {
            double e1 = 1e18;
            int idx = 0;

            for (int j = 0; j < K; j++) {
                if (e1 > own[j].e(tgt[i])) {
                    e1 = own[j].e(tgt[i]);
                    idx = j;
                }
            }

            E += e1;

            get<1>(ret[ret.size() - 1]).push_back({ 1, 0, 0, idx });
            get<1>(ret[ret.size() - 1]).push_back({ 2, 0, 0 });
        }

        get<0>(ret[ret.size() - 1]) += 10000 * E;
    }

    void solve2(vector<tuple<double, vector<vector<int>>>>& ret, vector<int> seed, int cell, int cnt) {
        ret.push_back(make_tuple(1, vector<vector<int>>(0)));

        int V = 0;
        double E = 0;

        for (int i = 0, j = 1; i < N; i++, j++) {
            get<1>(ret[ret.size() - 1]).push_back(vector<int>(0));

            if (i % 2 == 0) {
                for (int k = 0; k < N - 1; j++, k++) {
                    if (j % cell == 0) {
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].push_back(1);
                    } else {
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].push_back(0);
                    }
                }
            } else {
                for (int k = N - 2; k >= 0; j++, k--) {
                    if (j % cell == 0) {
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].push_back(1);
                    } else {
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].push_back(0);
                    }
                }

                reverse(get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].begin(),
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].end());
            }
        }

        for (int i = 0, j = 1; i < N - 1; i++) {
            get<1>(ret[ret.size() - 1]).push_back(vector<int>(0));

            if (i % 2 == 0) {
                for (int k = 0; k < N; j++, k++) {
                    if (j % cell == 0 || k != N - 1) {
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].push_back(1);
                    } else {
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].push_back(0);
                    }
                }
            } else {
                for (int k = N - 1; k >= 0; j++, k--) {
                    if (j % cell == 0 || k != 0) {
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].push_back(1);
                    } else {
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].push_back(0);
                    }
                }

                reverse(get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].begin(),
                        get<1>(ret[ret.size() - 1])[get<1>(ret[ret.size() - 1]).size() - 1].end());
            }
        }

        vector<well> wel(0);

        for (int i = 0, j = 0, flag = 1; i < N && flag == 1; i++) {
            if (i % 2 == 0) {
                for (int k = 0; k < N; j++, k++) {
                    if (j % cell == 0) {
                        if (static_cast<int>(wel.size()) == cnt) {
                            flag = 0;
                            break;
                        }

                        wel.push_back(well());
                        wel[wel.size() - 1].C = own[seed[j]].C;
                        wel[wel.size() - 1].M = own[seed[j]].M;
                        wel[wel.size() - 1].Y = own[seed[j]].Y;
                        wel[wel.size() - 1].v = 1;
                        wel[wel.size() - 1].w = cell;
                        wel[wel.size() - 1].y = i;
                        wel[wel.size() - 1].x = k;
                    } else {
                        wel[wel.size() - 1].add(own[seed[j]]);
                    }

                    V++;

                    get<1>(ret[ret.size() - 1]).push_back({ 1, wel[wel.size() - 1].y, wel[wel.size() - 1].x, seed[j] });
                }
            } else {
                for (int k = N - 1; k >= 0; j++, k--) {
                    if (j % cell == 0) {
                        if (static_cast<int>(wel.size()) == cnt) {
                            flag = 0;
                            break;
                        }

                        wel.push_back(well());
                        wel[wel.size() - 1].C = own[seed[j]].C;
                        wel[wel.size() - 1].M = own[seed[j]].M;
                        wel[wel.size() - 1].Y = own[seed[j]].Y;
                        wel[wel.size() - 1].v = 1;
                        wel[wel.size() - 1].w = cell;
                        wel[wel.size() - 1].y = i;
                        wel[wel.size() - 1].x = k;
                    } else {
                        wel[wel.size() - 1].add(own[seed[j]]);
                    }

                    V++;

                    get<1>(ret[ret.size() - 1]).push_back({ 1, wel[wel.size() - 1].y, wel[wel.size() - 1].x, seed[j] });
                }
            }
        }

        for (int i = 0; i < H; i++) {
            double e1 = 1e18;
            int idx = 0;

            for (int j = 0; j < cnt; j++) {
                if (e1 > wel[j].e(tgt[i])) {
                    e1 = wel[j].e(tgt[i]);
                    idx = j;
                }
            }

            E += e1;

            wel[idx].sub();
            get<1>(ret[ret.size() - 1]).push_back({ 2, wel[idx].y, wel[idx].x });

            for (int j = i + 1; j < H; j++) {
                double e2 = 1e18;
                int jdx = -1;

                for (int k = 0; k < cnt; k++) {
                    if (k == idx) {
                        for (int l = 0; l < K; l++) {
                            if (e2 > wel[k].e(own[l], tgt[j])) {
                                e2 = wel[k].e(own[l], tgt[j]);
                                jdx = l;
                            }
                        }
                    } else if (e2 > wel[k].e(tgt[j])) {
                        e2 = wel[k].e(tgt[j]);
                        jdx = -1;
                    }
                }

                if (jdx >= 0) {
                    V++;

                    wel[idx].add(own[jdx]);
                    get<1>(ret[ret.size() - 1]).push_back({ 1, wel[idx].y, wel[idx].x, jdx });

                    break;
                } else if (j == H - 1) {
                    double e3 = 1e18;
                    int kdx = 0;

                    for (int j = 0; j < K; j++) {
                        if (e3 > wel[idx].e(own[j], tgt[i + 1])) {
                            e3 = wel[idx].e(own[j], tgt[i + 1]);
                            kdx = j;
                        }
                    }

                    V++;

                    wel[idx].add(own[kdx]);
                    get<1>(ret[ret.size() - 1]).push_back({ 1, wel[idx].y, wel[idx].x, kdx });
                }
            }
        }

        get<0>(ret[ret.size() - 1]) += D * (V - H) + 10000 * E;
    }

    int time_limit_ms() {
        return 2700;
    }
};

int main() {
    application().run();
}
