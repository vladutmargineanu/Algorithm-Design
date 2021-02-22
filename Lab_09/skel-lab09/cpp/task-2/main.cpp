#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

#define INF 0x3f3f3f3f

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
		folosind BellmanFord pe adjul orientat cu n noduri, m arce stocat in adj.
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
		vector<int> d(n + 1, INF);
		vector<int> v;
		queue<int> coada;
		int viz[kNmax];
		int esteincoada[kNmax];

		for (int i = 1; i <= n; i++)
		{
			viz[i] = 0;
			esteincoada[i] = 0;
			d[i] = INF;
		}
		d[source] = 0;
		coada.push(source);
		esteincoada[source] = 1;

		//  minimizează drumul de la nodul de start  la oricare vârf x până la obținerea costului minim
		while (!coada.empty())
		{
			int nodcurent = coada.front();
			viz[nodcurent]++;
			// găsește însă un circuit negativ, atunci nu există 
			// soluție (pentru că drumul ar fi minimizat la maxim)
			if (viz[nodcurent] >= n)
			   return vector<int>();
			coada.pop();
			esteincoada[nodcurent] = 0;
			// relaxari succesive
			// cum in initializare se face o relaxare (daca exista drum direct de la sursa la nod =>
			// d[nod] = w[sursa, nod]) mai sunt necesare |V-2| relaxari
			// Ii parcurgem toti vecinii.
			for (size_t i = 0; i < adj[nodcurent].size(); i++)
			{
				int vecin = adj[nodcurent][i].first;
				int cost = adj[nodcurent][i].second;
				//  se verifică dacă minimizează distanța de la nodul de start la nodul x
				if (d[nodcurent] + cost < d[vecin])
				{
					d[vecin] = d[nodcurent] + cost;
					// îmbunătăţirea costului nodurilor vecine  se face 
					// introducându-le într-o coadă în cazul scăderii costului, dacă nu apar deja
					if (!esteincoada[vecin])
						coada.push(vecin);
				}
			}
		}
		// Toate nodurile catre care distanta este inca kInf nu pot fi atinse din
		// nodul source, deci le setam pe -1.
		for (int i = 1; i <= n; i++)
			if (d[i] == kInf)
				d[i] = -1;

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
