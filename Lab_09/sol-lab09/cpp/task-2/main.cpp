#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
using namespace std;

const int kNmax = 50005;
const int kInf = 0x3f3f3f3f;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	int source;
	vector<pair<int, int> > adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti distantele minime de la nodul source la celelalte noduri
		folosind BellmanFord pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.

		In cazul in care exista ciclu de cost negativ, returnati un vector gol:
			return vector<int>();
		*/
		// Initializez vectorul de distante la inf.
		vector<int> d(n + 1, kInf);

		// Setez sursa la distanta 0.
		d[source] = 0;

		// Construiesc un vector de muchii.
		vector<pair<pair<int, int>, int>> edges;

		for (int x = 1; x <= n; x++) {
			for (const pair<int, int>& yc : adj[x]) {
				int y = yc.first;
				int c = yc.second;
				edges.push_back(make_pair(make_pair(x, y), c));
			}
		}

		// Fac N - 1 relaxari.
		for (int i = 1; i <= n - 1; i++) {
			// Parcurg toate muchiile:
			for (int j = 0; j < edges.size(); j++) {
				int x = edges[j].first.first;
				int y = edges[j].first.second;
				int c = edges[j].second;

				// Incerc sa updatez distanta.
				if (d[y] > d[x] + c)
					d[y] = d[x] + c;
			}
		}

		// Verific daca mai poate fi updatata distanta
		for (int j = 0; j < edges.size(); j++) {
			int x = edges[j].first.first;
			int y = edges[j].first.second;
			int c = edges[j].second;

			if (d[y] > d[x] + c)
				return vector<int>();
		}

		// Toate nodurile catre care distanta este inca kInf nu pot fi atinse din
		// nodul source, deci le setam pe -1.
		for (int i = 1; i <= n; i++)
			if (d[i] == kInf) d[i] = -1;

		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		if (result.size() == 0) {
			fout << "Ciclu negativ!\n";
		} else {
			for (int i = 1; i <= n; i++) {
				fout << result[i] << ' ';
			}
			fout << '\n';
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
