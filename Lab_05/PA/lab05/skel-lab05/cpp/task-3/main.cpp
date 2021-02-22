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

	bool bkt(vector<int>& current, vector<int>& used, vector<int>& sol) {
		int current_row = current.size();
		if (current_row == n + 1) {
			// Am gasit o solutie, o punem in sol si returnam true.
			sol = current;
			return true;
		}

		// Incercam sa extindem solutia curenta, punand urmatoarea dama pe
		// orice coloana neluata.
		for (int i = 1; i <= n; i++) {
			if (used[i]) continue;

			// Doua din cele 3 conditii sunt satisfacute acum:
			// - nu se ataca pe acelasi rand (pentru ca le plasam pe randuri
			// diferite din constructie: sol[i] nu are mai multe valori).
			// - nu se ataca pe aceeasi coloana (pentru ca avem grija ca sol[i]
			// != sol[j], orice i != j).
			// Verificam daca se ataca cumva pe diagonala cu o dama deja pusa:
			bool diagonal_ok = true;
			for (int j = 1; j < current_row; j++) {
				// Doua dame cu coordonatele (x1, y1) si (x2, y2) se ataca pe
				// diagonala <==> abs(x1 - x2) == abs(y1 - y2).
				// In cazul nostru, damele sunt (j, current[j]) si cea pe care
				// vrem sa o punem acum: (current_row, i).
				if (abs(j - current_row) == abs(current[j] - i))
					diagonal_ok = false;
			}

			if (!diagonal_ok) continue;
			
			// Marcam coloana ca fiind luata.
			used[i] = 1;
			current.push_back(i);

			// Apelam recursiv backtracking.
			if (bkt(current, used, sol)) {
				// Am gasit solutie, ne intoarcem pe recursivitate.
				return true;
			}

			// Marcam coloana ca fiind neluata.
			used[i] = 0;
			current.pop_back();
		}

		return false;
	}

	vector<int> get_result() {
		vector<int> sol(n + 1, 0);

		/*
		TODO: Gasiti o solutie pentru problema damelor pe o tabla de dimensiune
		n x n.

		Pentru a plasa o dama pe randul i, coloana j:
			sol[i] = j.
		Randurile si coloanele se indexeaza de la 1 la n.

		De exemplu, configuratia (n = 5)
		X----
		--X--
		----X
		-X---
		---X-
		se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.
		*/

		vector<int> current(1, 0);
		vector<int> used(n + 1, 0);
		bkt(current, used, sol);

		return sol;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i != n ? ' ' : '\n');
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
