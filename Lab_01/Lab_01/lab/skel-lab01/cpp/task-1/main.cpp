// (C) Copyright 2019

#include <iostream>
#include <fstream>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::vector;


using std::cout;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, x;
    vector<int> v;

    void read_input() {
        ifstream fin("in");

        fin >> n;

        for (int i = 0; i < n; ++i) {
            int e;
            fin >> e;
            v.push_back(e);
        }

        fin >> x;

        fin.close();
    }

    int find_first() {
        int start = 0;
        int end = v.size() - 1;

        while (start <= end) {
            int mid = (start + end) / 2;

            if ((v[mid] == x) && ((mid == 0) || (x > v[mid - 1]))) {
                return mid;
            }

            if (v[mid] < x) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }

        return -1;
    }

    int find_last() {
        int start = 0;
        int end = v.size() - 1;

        while (start <= end) {
            int mid = (start + end) / 2;

            if ((v[mid] == x) && ((mid == v.size() - 1) || (x < v[mid + 1]))) {
                return mid;
            }

            if (v[mid] > x) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        return -1;
    }

    int get_result() {
        int first = find_first();

        return (first == -1) ? 0 : (find_last() - first + 1);
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
        fout.close();
    }
};

int main() {
    Task task;
    task.solve();
    return 0;
}
