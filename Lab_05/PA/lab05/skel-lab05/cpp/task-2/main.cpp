#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	void bkt(vector<int>& current,
			vector<vector<int> >& all) {
		// Am construit o submultime, deci o adaugam.
		all.push_back(current);

		// Incercam sa extindem submultimea curenta, plecand de la cel mai mare
		// element din submultime + 1.
		int last = 0;
		if (!current.empty())
			last = current.back();
		for (int i = last + 1; i <= n; i++) {
			// Luam numarul in submultime.
			current.push_back(i);
			// Apelam recursiv bkt.
			bkt(current, all);
			// Scoatem numarul pus mai sus din submultime.
			current.pop_back();
		}
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;

		/*
		TODO: Construiti toate submultimile multimii {1, ..., N}.

		Pentru a adauga o noua submultime:
			vector<int> submultime;
			all.push_back(submultime);
		*/

		vector<int> current;
		bkt(current, all);

		return all;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					(j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
