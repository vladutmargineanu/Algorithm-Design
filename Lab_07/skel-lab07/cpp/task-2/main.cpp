#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

const int kNmax = 100005;
/* Sortare TOPOLOGICA iterativa !! DFS iterativ */
class Task
{
  public:
	void solve()
	{
		read_input();
		print_output(get_result());
	}

  private:
	int n;
	int m;
	vector<int> adj[kNmax];
	int time;
	vector<int> finTime;
	int numConnectedComp;
	vector<vector<int>> components;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++)
		{
			fin >> x >> y;
			adj[x].push_back(y);
		}
		fin.close();
	}

	/*
	Comparator for finTime used in topologicalSort
*/

     	struct comp {
		vector<int> finTime;
		comp(vector<int>& finTime) {
			this->finTime = finTime;
		}
		bool operator()(int i, int j) const {
			return finTime[i] > finTime[j];
		}
    }; 

	vector<int> get_result()
	{
		/*
			 Facem sortarea topologica a grafului stocat cu liste de
			adiacenta in adj.
			*******
			ATENTIE: nodurile sunt indexate de la 1 la n.
			*******
			*/
		stack<int> Stack;
		vector<bool> visited;
		vector<int> topSortOrder;
		int numNodes = n;

		//finTime.resize(numNodes);
		visited.resize(numNodes + 1);

		for (int i = 1; i <= numNodes; i++)
		{
			/*
				Initialize visited
				// Funcţie de vizitare a nodului
			*/
			visited[i] = false;
		}

		 this->time = 0;
		/*
		Call dfsTopSort for each unvisited node
		*/
		/* Parcurgere noduri și calculare tDesc și tFin pentru fiecare nod */
		for (int i = 1; i <= numNodes; i++)
		{
			if (!visited[i])
			{
				dfsTopSort(i, visited, Stack);
			}
		}
		while (Stack.empty() == false)
		{
			topSortOrder.push_back(Stack.top());
			Stack.pop();
		}

		comp c(finTime);
		/*  Sortare topologica
          sortează nodurile din V descrescător în funcție de tFin[nod] */
		// Nodes sorted in descending order by finTime
		return topSortOrder;
	}

	 void connectedComponents()
	{
		int numNodes = n;
		/* Initializations */
	    vector<bool> visited = std::vector<bool>(numNodes + 1, false);
	/* 
		 Call dfs for all unvisited nodes
		
		Use: components.push_back(vector<int>());
			to create new component
	*/

		for (int i = 0; i < numNodes; i++)
		{
			if (!visited[i])
			{
				this->components.push_back(vector<int>());
				dfsTopSort(i, visited);
				this->numConnectedComp++;
			}
		}
	}

	void dfsTopSort(int node, vector<bool> &visited, stack<int> &Stack)
	{

		// Mark the current node as visited.
		visited[node] = true;
		// dfs recursiv
		for (auto v : adj[node])
		{
			if (!visited[v])
			{
				dfsTopSort(v, visited, Stack);
			}
		}
		// Push current vertex to stack which stores result
		Stack.push(node);
	}

	// Parcurgere în adâncime
	 void dfsTopSort(int n, vector<bool> &visited) {
		/* 
		Perform DFS keeping track of finTime
	*/

		std::stack<int> s;

		visited[n] = true;
		s.push(n);

		while (!s.empty())
		{
			int currNode = s.top();

			int unvisited_neigh = -1;
			for (auto v : adj[currNode])
			{
				if (!visited[v])
				{
					unvisited_neigh = v;
					break;
				}
			}

			if (unvisited_neigh != -1)
			{
				visited[unvisited_neigh] = true;
				s.push(unvisited_neigh);
			}
			else
			{
				this->time++;
				this->finTime[currNode] = this->time;
				s.pop();
			}
	}
}

	void print_output(vector<int> result)
	{
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++)
		{
			fout << result[i] << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main()
{
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
