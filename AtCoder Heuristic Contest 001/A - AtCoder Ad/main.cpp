#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

using namespace std;

const chrono::system_clock::time_point time_zero = chrono::system_clock::now();

const int time_limit_ms = 4980;
const long long x_max = 10000;
const long long x_min = 0;
const long long y_max = 10000;
const long long y_min = 0;

int elapsed_time_ms() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - time_zero).count();
}

bool is_time_limit_exceeded() {
    return elapsed_time_ms() > time_limit_ms;
}

bool is_valid(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        const vector<long long>& a,
        const vector<long long>& b,
        const vector<long long>& c,
        const vector<long long>& d) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (max(a[i], a[j]) < min(c[i], c[j]) && max(b[i], b[j]) < min(d[i], d[j])) {
                return false;
            }
        }
    }

    return true;
}

bool is_invalid(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        const vector<long long>& a,
        const vector<long long>& b,
        const vector<long long>& c,
        const vector<long long>& d) {
    return !is_valid(n, x, y, r, a, b, c, d);
}

double value(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        const vector<long long>& a,
        const vector<long long>& b,
        const vector<long long>& c,
        const vector<long long>& d) {
    double ret = 0;
    for (int i = 0; i < n; i++) {
        long long s = (c[i] - a[i]) * (d[i] - b[i]);
        double q = 1 - static_cast<double>(min(r[i], s)) / max(r[i], s);
        ret += 1 - q * q;
    }

    return ret;
}

void solve_step_0(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        vector<long long>& a,
        vector<long long>& b,
        vector<long long>& c,
        vector<long long>& d) {
    for (int i = 0; i < n; i++) {
        a[i] = x[i];
        b[i] = y[i];
        c[i] = x[i] + 1;
        d[i] = y[i] + 1;
    }
}

void solve_step_1(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        vector<long long>& a,
        vector<long long>& b,
        vector<long long>& c,
        vector<long long>& d) {
    int time_limit_ms_for_step_1 = 80 * time_limit_ms / 100;

    random_device device;
    mt19937 engine(device());

    uniform_int_distribution<int> dist_steps(1, 12);
    uniform_int_distribution<int> dist_n(0, n - 1);
    uniform_int_distribution<int> dist_m(0, 3);
    uniform_int_distribution<int> dist_d(-6, 16);

    vector<long long> ret_a(a), ret_b(b), ret_c(c), ret_d(d);
    double ret_value = value(n, x, y, r, ret_a, ret_b, ret_c, ret_d);

    for (vector<long long> current_a(ret_a), current_b(ret_b), current_c(ret_c), current_d(ret_d);
            elapsed_time_ms() < time_limit_ms_for_step_1; ) {
        vector<long long> next_a(current_a), next_b(current_b), next_c(current_c), next_d(current_d);

        int steps = dist_steps(engine);
        for (int i = 0; i < steps; i++) {
            int j = dist_n(engine);
            int m = dist_m(engine);
            int d = dist_d(engine);

            long long s = (next_c[j] - next_a[j]) * (next_d[j] - next_b[j]);

            if (m == 0) {
                if (s > r[j]) {
                    next_a[j] = min(max(x_min, next_a[j] + d), x[j]);
                } else {
                    next_a[j] = min(max(x_min, next_a[j] - d), x[j]);
                }
            } else if (m == 1) {
                if (s > r[j]) {
                    next_b[j] = min(max(y_min, next_b[j] + d), y[j]);
                } else {
                    next_b[j] = min(max(y_min, next_b[j] - d), y[j]);
                }
            } else if (m == 2) {
                if (s < r[j]) {
                    next_c[j] = max(min(x_max, next_c[j] + d), x[j] + 1);
                } else {
                    next_c[j] = max(min(x_max, next_c[j] - d), x[j] + 1);
                }
            } else {
                if (s < r[j]) {
                    next_d[j] = max(min(y_max, next_d[j] + d), y[j] + 1);
                } else {
                    next_d[j] = max(min(y_max, next_d[j] - d), y[j] + 1);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            while ((next_c[i] - next_a[i]) * (next_d[i] - next_b[i]) > 0.85 * r[i]) {
                int m = dist_m(engine);

                if (m == 0) {
                    next_a[i] = min(next_a[i] + 1, x[i]);
                } else if (m == 1) {
                    next_b[i] = min(next_b[i] + 1, y[i]);
                } else if (m == 2) {
                    next_c[i] = max(next_c[i] - 1, x[i] + 1);
                } else {
                    next_d[i] = max(next_d[i] - 1, y[i] + 1);
                }
            }
        }

        if (is_valid(n, x, y, r, next_a, next_b, next_c, next_d)) {
            current_a = next_a;
            current_b = next_b;
            current_c = next_c;
            current_d = next_d;

            double current_value = value(n, x, y, r, current_a, current_b, current_c, current_d);

            if (ret_value < current_value) {
                ret_a = current_a;
                ret_b = current_b;
                ret_c = current_c;
                ret_d = current_d;
                ret_value = current_value;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        a[i] = ret_a[i];
        b[i] = ret_b[i];
        c[i] = ret_c[i];
        d[i] = ret_d[i];
    }
}

void solve_step_2(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        vector<long long>& a,
        vector<long long>& b,
        vector<long long>& c,
        vector<long long>& d) {
    if (is_time_limit_exceeded()) {
        return;
    }

    random_device device;
    mt19937 engine(device());

    uniform_int_distribution<int> dist_m(0, 3);

    for (int i = 0; i < n; i++) {
        while ((c[i] - a[i]) * (d[i] - b[i]) > 0.8 * r[i]) {
            if (is_time_limit_exceeded()) {
                return;
            }

            int m = dist_m(engine);

            if (m == 0) {
                a[i] = min(a[i] + 1, x[i]);
            } else if (m == 1) {
                b[i] = min(b[i] + 1, y[i]);
            } else if (m == 2) {
                c[i] = max(c[i] - 1, x[i] + 1);
            } else {
                d[i] = max(d[i] - 1, y[i] + 1);
            }
        }
    }
}

void solve_step_3(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        vector<long long>& a,
        vector<long long>& b,
        vector<long long>& c,
        vector<long long>& d) {
    if (is_time_limit_exceeded()) {
        return;
    }

    random_device device;
    mt19937 engine(device());

    uniform_int_distribution<int> dist_m(0, 3);

    vector<tuple<double, int>> v_idx(n);
    for (int i = 0; i < n; i++) {
        long long s = (c[i] - a[i]) * (d[i] - b[i]);
        double q = 1 - static_cast<double>(min(r[i], s)) / max(r[i], s);
        v_idx[i] = make_tuple(1 - q * q, i);
    }

    sort(v_idx.begin(), v_idx.end());

    for (int i = 0; i < n; i++) {
        int j = get<1>(v_idx[i]);

        for (int state = (a[j] == x_min ? 0b0000 : 0b0001)
                + (b[j] == y_min ? 0b0000 : 0b0010)
                + (c[j] == x_max ? 0b0000 : 0b0100)
                + (d[j] == y_max ? 0b0000 : 0b1000); state > 0 && (c[j] - a[j]) * (d[j] - b[j]) < r[j]; ) {
            if (is_time_limit_exceeded()) {
                return;
            }

            int m = dist_m(engine);
            while ((state & (1 << m)) == 0) {
                m = dist_m(engine);
            }

            if (m == 0) {
                a[j]--;
                if (is_invalid(n, x, y, r, a, b, c, d)) {
                    a[j]++;
                    state &= 0b1110;
                } else if (a[j] == x_min) {
                    state &= 0b1110;
                }
            } else if (m == 1) {
                b[j]--;
                if (is_invalid(n, x, y, r, a, b, c, d)) {
                    b[j]++;
                    state &= 0b1101;
                } else if (b[j] == y_min) {
                    state &= 0b1101;
                }
            } else if (m == 2) {
                c[j]++;
                if (is_invalid(n, x, y, r, a, b, c, d)) {
                    c[j]--;
                    state &= 0b1011;
                } else if (c[j] == x_max) {
                    state &= 0b1011;
                }
            } else {
                d[j]++;
                if (is_invalid(n, x, y, r, a, b, c, d)) {
                    d[j]--;
                    state &= 0b0111;
                } else if (d[j] == y_max) {
                    state &= 0b0111;
                }
            }
        }
    }
}

void solve_step_4(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        vector<long long>& a,
        vector<long long>& b,
        vector<long long>& c,
        vector<long long>& d) {
    if (is_time_limit_exceeded()) {
        return;
    }

    vector<long long> ret_a(a), ret_b(b), ret_c(c), ret_d(d);
    double ret_value = value(n, x, y, r, ret_a, ret_b, ret_c, ret_d);

    vector<tuple<double, int>> v_idx(n);
    for (int i = 0; i < n; i++) {
        long long s = (c[i] - a[i]) * (d[i] - b[i]);
        double q = 1 - static_cast<double>(min(r[i], s)) / max(r[i], s);
        v_idx[i] = make_tuple(1 - q * q, i);
    }

    sort(v_idx.begin(), v_idx.end());

    for (int i = 0; i < n; i++) {
        int j = get<1>(v_idx[i]);

        for (vector<long long> current_a(ret_a), current_b(ret_b), current_c(ret_c), current_d(ret_d);
                current_a[j] > x_min; ) {
            if (is_time_limit_exceeded()) {
                goto out;
            }

            current_a[j]--;

            bool invalid = false;

            for (int k = 0; k < n; k++) {
                if (j != k
                        && max(current_a[j], current_a[k]) < min(current_c[j], current_c[k])
                        && max(current_b[j], current_b[k]) < min(current_d[j], current_d[k])) {
                    if (current_c[k] > x[k] + 1) {
                        current_c[k]--;
                    } else {
                        invalid = true;
                        break;
                    }
                }
            }

            if (invalid) {
                break;
            }

            double current_value = value(n, x, y, r, current_a, current_b, current_c, current_d);

            if (ret_value < current_value) {
                ret_a = current_a;
                ret_b = current_b;
                ret_c = current_c;
                ret_d = current_d;
                ret_value = current_value;
            } else {
                break;
            }
        }

        for (vector<long long> current_a(ret_a), current_b(ret_b), current_c(ret_c), current_d(ret_d);
                current_b[j] > y_min; ) {
            if (is_time_limit_exceeded()) {
                goto out;
            }

            current_b[j]--;

            bool invalid = false;

            for (int k = 0; k < n; k++) {
                if (j != k
                        && max(current_a[j], current_a[k]) < min(current_c[j], current_c[k])
                        && max(current_b[j], current_b[k]) < min(current_d[j], current_d[k])) {
                    if (current_d[k] > y[k] + 1) {
                        current_d[k]--;
                    } else {
                        invalid = true;
                        break;
                    }
                }
            }

            if (invalid) {
                break;
            }

            double current_value = value(n, x, y, r, current_a, current_b, current_c, current_d);

            if (ret_value < current_value) {
                ret_a = current_a;
                ret_b = current_b;
                ret_c = current_c;
                ret_d = current_d;
                ret_value = current_value;
            } else {
                break;
            }
        }

        for (vector<long long> current_a(ret_a), current_b(ret_b), current_c(ret_c), current_d(ret_d);
                current_c[j] < x_max; ) {
            if (is_time_limit_exceeded()) {
                goto out;
            }

            current_c[j]++;

            bool invalid = false;

            for (int k = 0; k < n; k++) {
                if (j != k
                        && max(current_a[j], current_a[k]) < min(current_c[j], current_c[k])
                        && max(current_b[j], current_b[k]) < min(current_d[j], current_d[k])) {
                    if (current_a[k] < x[k]) {
                        current_a[k]++;
                    } else {
                        invalid = true;
                        break;
                    }
                }
            }

            if (invalid) {
                break;
            }

            double current_value = value(n, x, y, r, current_a, current_b, current_c, current_d);

            if (ret_value < current_value) {
                ret_a = current_a;
                ret_b = current_b;
                ret_c = current_c;
                ret_d = current_d;
                ret_value = current_value;
            } else {
                break;
            }
        }

        for (vector<long long> current_a(ret_a), current_b(ret_b), current_c(ret_c), current_d(ret_d);
                current_d[j] < y_max; ) {
            if (is_time_limit_exceeded()) {
                goto out;
            }

            current_d[j]++;

            bool invalid = false;

            for (int k = 0; k < n; k++) {
                if (j != k
                        && max(current_a[j], current_a[k]) < min(current_c[j], current_c[k])
                        && max(current_b[j], current_b[k]) < min(current_d[j], current_d[k])) {
                    if (current_b[k] < y[k]) {
                        current_b[k]++;
                    } else {
                        invalid = true;
                        break;
                    }
                }
            }

            if (invalid) {
                break;
            }

            double current_value = value(n, x, y, r, current_a, current_b, current_c, current_d);

            if (ret_value < current_value) {
                ret_a = current_a;
                ret_b = current_b;
                ret_c = current_c;
                ret_d = current_d;
                ret_value = current_value;
            } else {
                break;
            }
        }
    }

out:
    for (int i = 0; i < n; i++) {
        a[i] = ret_a[i];
        b[i] = ret_b[i];
        c[i] = ret_c[i];
        d[i] = ret_d[i];
    }
}

void solve_step_5(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        vector<long long>& a,
        vector<long long>& b,
        vector<long long>& c,
        vector<long long>& d) {
    solve_step_3(n, x, y, r, a, b, c, d);
}

void solve(int n,
        const vector<long long>& x,
        const vector<long long>& y,
        const vector<long long>& r,
        vector<long long>& a,
        vector<long long>& b,
        vector<long long>& c,
        vector<long long>& d) {
    solve_step_0(n, x, y, r, a, b, c, d);
    solve_step_1(n, x, y, r, a, b, c, d);
    solve_step_2(n, x, y, r, a, b, c, d);
    solve_step_3(n, x, y, r, a, b, c, d);
    solve_step_4(n, x, y, r, a, b, c, d);
    solve_step_5(n, x, y, r, a, b, c, d);
}

int main() {
    int n;
    cin >> n;

    vector<long long> x(n), y(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }

    vector<long long> a(n), b(n), c(n), d(n);
    solve(n, x, y, r, a, b, c, d);

    for (int i = 0; i < n; i++) {
        cout << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << endl;
    }
}
