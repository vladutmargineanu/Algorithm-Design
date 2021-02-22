#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

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
		/*
		TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune
		2^n x 2^n
		*/
	
		if (n == 0) {
			return 1;
		}
		
		int aux = pow(2, n - 1);

		if (x > aux && y > aux) {
			//cadran 4
			return get_result(n - 1, x - aux, y - aux) + 3 * aux * aux;
		}
		if (x > aux && y <= aux) {
			//cadran 3
			return get_result(n - 1, x - aux, y) + 2 * aux * aux;
		}
		if (x <= aux && y > aux) {
			//cadran 2
			return get_result(n - 1, x, y - aux) + aux * aux;
		}
		if (x <= aux && y <= aux) {
			//cadran 1
			return get_result(n - 1, x, y);
		}
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
