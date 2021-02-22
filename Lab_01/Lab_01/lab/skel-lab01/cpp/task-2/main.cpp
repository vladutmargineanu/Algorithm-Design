// (C) Copyright 2019

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using std::setprecision;
using std::fixed;
using std::ifstream;
using std::ofstream;
using std::cout;

class Task {
 public:
    void solve() {
        read_input();
        print_output(compute_sqrt());
    }

 private:
    double n;
    double err = 0.001;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    double compute_sqrt() {
        double start = 1;
        double end = (n + 1) / 2;
        double mid;

        while (start <= end) {
            mid = (start + end) / 2;

            if (fabs(mid * mid - n) <= err) {
                return mid;
            }

            if (mid * mid < n) {
                start = mid;
            } else {
                end = mid;
            }
        }

        return mid;
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
        fout.close();
    }
};

int main() {
    Task task;
    task.solve();
    return 0;
}
