#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

const int kNmax = 100005;

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
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	vector<int> get_result() {
		vector<int> d(n + 1);

		/*
		TODO: Faceti un BFS care sa construiasca in d valorile d[i] = numarul
		minim de muchii de parcurs de la nodul source la nodul i.
		d[source] = 0
		d[x] = -1 daca nu exista drum de la source la x.
		*******
		ATENTIE: nodurile sunt indexate de la 1 la n.
		*******
		*/
		int numNodes = n;  // numarul de noduri
		int currNode;
		vector<bool> visited;
		std::queue<int> q;
		vector<int> parent(numNodes);
		/*  Initializations */
		// Initializam toate distantele cu inf (INT_MAX)
		d.resize(numNodes + 1, INT_MAX);
		visited.resize(numNodes + 1, false);
		parent.resize(numNodes + 1, -1);

		/*
		 Perform BFS from source, keeping track of distance and parent
	*/
	for (int i = 1; i <= n; i++) {
			d[i] = -1;
	}
	q.push(source);
	d[source] = 0; // distanta pana la sursa este 0
	visited[source] = true;
   
	while (!q.empty()) {
		currNode = q.front(); // se determina nodul din varful cozii
		q.pop();
       //  pentru fiecare v dintre vecinii lui currNode
		for (auto v : adj[currNode]) {
			
			if (!visited[v]) {
				// daca nu a fost vizitat
				d[v] = d[currNode] + 1;
				parent[v] = currNode;
				visited[v] = true;
				// Adăugăm nodul u în coadă
				q.push(v);
			}
		}
	}

		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i == n ? '\n' : ' ');
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
