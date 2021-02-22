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
	int n, k;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin.close();
	}

	void bkt(vector<int>& current,
			vector<int>& used,
			vector<vector<int> >& all) {
		if (current.size() == k) {
			// Daca am construit un aranjament de dimensiune k, il adaugam.
			all.push_back(current);

			// Si ne oprim.
			return;
		}

		// Incercam sa extindem solutia curenta.
		for (int i = 1; i <= n; i++) {
			// Sarim peste orice numar deja luat in aranjament.
			if (used[i]) continue;
			
			// Luam numarul in aranjament (adaugandu-l la sfarsit).
			current.push_back(i);
			// Marcam numarul ca fiind folosit.
			used[i] = 1;
			// Apelam recursiv bkt.
			bkt(current, used, all);
			// Scoatem numarul pus mai sus din aranjament.
			current.pop_back();
			// Marcam numarul ca fiind nefolosit.
			used[i] = 0;
		}
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;

		/*
		TODO: Construiti toate aranjamentele de N luate cate K ale
		multimii {1, ..., N}.

		Pentru a adauga un nou aranjament:
			vector<int> aranjament;
			all.push_back(aranjament);
		*/
		vector<int> used(n + 1);
		vector<int> current;

		bkt(current, used, all);

	
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
