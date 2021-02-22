#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result(n, x, y));
    }

private:
    int n, x, y;

    void read_input() {
        ifstream fin("in");
        fin >> n >> x >> y;
        fin.close();
    }

    int get_result(int n, int x, int y) {
        int doi_la_n = 1 << n;
        int left_row = 1;
        int left_col = 1;
        int right_row = doi_la_n;
        int right_col = doi_la_n;
        int start = 1;
        int end = doi_la_n * doi_la_n;

        while (start < end) {
            int offset = (end - start + 1) / 4;
            int mid_row = (left_row + right_row) / 2;
            int mid_col = (left_col + right_col) / 2;

            if ((x <= mid_row) && (y <= mid_col)) {
                end = offset + start - 1;
                right_row = mid_row;
                right_col = mid_col;
            } else if ((x <= mid_row) && (y > mid_col)) {
                end = 2 * offset + start - 1;
                start = offset + start;
                left_col = mid_col + 1;
                right_row = mid_row;
            } else if ((x > mid_row) && (y <= mid_col)) {
                end = 3 * offset + start - 1;
                start = 2 * offset + start;
                left_row = mid_row + 1;
                right_col = mid_col;
            } else {
                start = 3 * offset + start;
                left_row = mid_row + 1;
                left_col = mid_col + 1;
            }
        }

        return start;
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
