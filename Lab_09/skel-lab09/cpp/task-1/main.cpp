#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
using namespace std;

const int kNmax = 50005;
const int kInf = 0x3f3f3f3f;
const int NMax = 50005;
vector<int> d;

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
	// verificam daca nodurile sunt deja in coada
	bool InCoada[NMax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
		}
		fin.close();
	}

	struct compara
	{
		bool operator()(int x, int y)
		{
			return d[x] > d[y];
		}
	};
	// creeam o coada de prioritate (priority queue / heap-uri) ce o vom folosii pentru acest algoritm.
	priority_queue <int, vector<int>, compara> Coada;

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
		// vector<int> d(n + 1, kInf);
		// Initializam vectorul de distante cu distante infinite.
		d = vector<int>(n + 1, kInf);
		d[source] = 0;
		// Punem nodul de start in coada.
		Coada.push(source);
		// Luam nodul – cu valoarea D[nod] minima – din coada si il marcam ca vizitat.
		InCoada[source] = true;
		// relaxari succesive
		// Se actualizeaza distantele minime ale vecinilor nodului curent.
		while (!Coada.empty())
		{ // Scoatem nodul x din coada.
			int nodCurent = Coada.top();
			// Eliminam nodul curent din coada
			Coada.pop();
			// marcam nodul ca nefiind in coada
			InCoada[nodCurent] = false;
			// Ii parcurgem toti vecinii.
			for (size_t i = 0; i < adj[nodCurent].size(); i++)
			{
				int Vecin = adj[nodCurent][i].first;
				int Cost = adj[nodCurent][i].second;
				// Se imbunatateste distanta?
				if (d[nodCurent] + Cost < d[Vecin])
				{ // Actualizam distanta si inseram din nou in coada
					d[Vecin] = d[nodCurent] + Cost;
					if (InCoada[Vecin] == false)
					{
						Coada.push(Vecin);
						InCoada[Vecin] = true;
					}
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
