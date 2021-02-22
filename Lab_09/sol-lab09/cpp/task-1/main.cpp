#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
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
		folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.
		*/

		// Initializam vectorul de distante cu distante infinite.
		vector<int> d(n + 1, kInf);
		// In loc de un priority_queue<> folosim set<>, cu elemente tupluri de
		// tipul (distanta pana la nod, nod). Setul tine elementele ordonate, deci
		// mereum in q.begin() vom avea tuplul care ii corespunde nodului cu
		// distanta minima.
		set<pair<int, int>> q;

		// Inseram nodul de plecare in coada si ii actualizam distanta.
		d[source] = 0;
		q.insert(make_pair(d[source], source));

		while (!q.empty()) {
			// Scoatem nodul x din coada.
			int x = q.begin()->second;
			q.erase(q.begin());

			// Ii parcurgem toti vecinii.
			for (const pair<int, int>& yc : adj[x]) {
				int y = yc.first;
				int c = yc.second;

				// Se imbunatateste distanta?
				if (d[y] > d[x] + c) {
					// Scoatem vechea pereche din set.
					q.erase(make_pair(d[y], y));
					// Actualizam distanta si inseram din nou in set.
					d[y] = d[x] + c;
					q.insert(make_pair(d[y], y));
				}
			}
		}

		// Toate nodurile catre care distanta este inca kInf nu pot fi atinse din
		// nodul source, deci le setam pe -1.
		for (int i = 1; i <= n; i++)
			if (d[i] == kInf) d[i] = -1;

		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << " ";
		}
		fout << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
