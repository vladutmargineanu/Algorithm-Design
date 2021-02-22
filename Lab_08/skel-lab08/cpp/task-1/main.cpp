#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <iterator>

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
	vector<int> adj[kNmax];
	vector<int> adjt[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}

	void timeOrder(int v, bool visited[], stack<int> &Stack)
	{
		// Mark the current node as visited and print it
		visited[v] = true;

		// Recur for all the vertices adjacent to this vertex
		for (auto i : adj[v])
			if (!visited[i])
				timeOrder(i, visited, Stack);

		// All vertices reachable from v are processed by now, push v
		Stack.push(v);
	}

	void dfs(int v, bool visited[], vector<vector<int>>& sol)
	{
		// Mark the current node as visited and print it
		visited[v] = true;
		// Recur for all the vertices adjacent to this vertex
	    //sol[v].push_back(v);


		for (auto i : adjt[v]) {
			if (!visited[i]){
				dfs(i, visited, sol);
			}
		}
		sol[sol.size()].push_back(v);
	}

	vector<vector<int>> get_result() {
		/*
		TODO: Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.
		
		Atentie: graful transpus este stocat in adjt.
		*/

		/* o stivă pentru a reţine ordinea terminării
		 parcurgerii nodurilor grafului original */
		stack<int> Stack;
		vector<vector<int>> sol;

		// Mark all the vertices as not visited (For first DFS)
		bool *visited = new bool[n];
		for (int i = 0; i < n; i++)
			visited[i] = false;

		for (int i = 0; i < n; i++)
			if (visited[i] == false)
				timeOrder(i, visited, Stack);

		// Mark all the vertices as not visited (For second DFS)
		for (int i = 0; i < n; i++)
			visited[i] = false;
		// cat timp stiva nu e vida
		while (Stack.empty() == false)
		{
			// Pop a vertex from stack
			int v = Stack.top();
			Stack.pop();

			// find Strongly connected component of the popped vertex
			if (visited[v] == false)
			{
				sol.push_back(vector<int> ());
				dfs(v, visited, sol);
				//sol.push_back(v);
				
			}
		}

		return sol;
	}

	void print_output(vector<vector<int>> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
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
