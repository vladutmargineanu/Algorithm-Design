#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 105;

class Task {
 public:
	void solve() {
		read_input();
		compute();
		print_output();
	}

 private:
	int n;
	int d[kNmax][kNmax];
	int a[kNmax][kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fin >> a[i][j];
			}
		}
		fin.close();
	}

	void compute() {
		/*
		TODO: Gasiti distantele minime intre oricare doua noduri, folosind RoyFloyd
		pe graful orientat cu n noduri, m arce stocat in matricea ponderilor a
		(declarata mai sus).

		Atentie:
		O muchie (x, y, w) este reprezentata astfel in matricea ponderilor:
			a[x][y] = w;
		Daca nu exista o muchie intre doua noduri x si y, in matricea ponderilor
		se va afla valoarea 0:
			a[x][y] = 0;

		Trebuie sa populati matricea d[][] (declarata mai sus):
			d[x][y] = distanta minima intre nodurile x si y, daca exista drum.
			d[x][y] = 0 daca nu exista drum intre x si y.
			d[x][x] = 0.
		*/

		int i, j, k;
		// putem spune că valorile inițiale ale celor mai scurte distanțe se bazează
		//  pe cele mai scurte căi, având în vedere că nu există un vertex intermediar.
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				d[i][j] = a[i][j]; // costul muchiei, sau infinit

		for (k = 1; k <= n; k++)
		{
			// Pick all vertices as source one by one
			for (i = 1; i <= n; i++)
			{
				// Pick all vertices as destination for the
				// above picked source
				for (j = 1; j <= n; j++)
				{

					if (i == j)
						continue;

					// Daca nu exista drum de la i la k sau de la k la j, sarim peste.
					if (!d[i][k] || !d[k][j])
						continue;
					// If vertex k is on the shortest path from
					// i to j, then update the value of dist[i][j]

					// // Daca nu exista drum de la i la k sau de la k la j, sarim peste
					if (!d[i][j] || d[i][k] + d[k][j] < d[i][j])
						d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}

	void print_output() {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fout << d[i][j] << ' ';
			}
			fout << '\n';
		}
		fout.close();

		// ofstream ferr("err");
		// for (int i = 1; i <= n; i++)
		// {
		// 	for (int j = 1; j <= n; j++)
		// 	{
		// 		ferr << d[i][j] << ' ';
		// 	}
		// 	ferr << '\n';
		// }
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
