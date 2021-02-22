#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

#define eps 0.0001

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(compute_sqrt());
	}

private:
	double n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	double compute_sqrt() {
		/*
		TODO: Calculati sqrt(n) cu o precizie de 0.001
		Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x
		*/
		double left = (2 * n) / (n + 1);
		double right = (n + 1) / 2;
		double mid = 0.0;

		while (left <= right) {
			mid = (left + right) / 2;

			if (fabs(mid * mid - n) < eps) {
				return mid;
			}

			if (mid * mid < n) {
				left = mid;
			} else {
				right = mid;
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
