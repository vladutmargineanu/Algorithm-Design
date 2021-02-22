// Kosaraju - O(n + m)
#include <bits/stdc++.h>
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
  vector<int> adj_trans[kNmax];

  void read_input() {
    ifstream fin("in");
    fin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
      fin >> x >> y;
      adj[x].push_back(y);
      adj_trans[y].push_back(x);
    }
    fin.close();
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
    vector<vector<int>> sol;
    // visited[i] = retine daca nodul a fost vizitat sau nu
    // initial visited[i] = 0
    // - cand fac DFS pe graful normal, marchez cu 1 nodurile vizitate
    // - obtin toate nodurile vizitate
    // - cand fac DFS pe graful transpus, le am deja marcate cu 1,
    //   cand vizitez un nod il marchez cu 0
    vector<int> visited;

    // retin nodurile crescator dupa timpul de finalizare
    // reverse(finish_sort.begin(), finish_sort.end()) reprezinta sortarea
    // topologica
    vector<int> finish_sort;

    visited.resize(n + 1);
    finish_sort.push_back(-1); // indexare de la 1
    // parcugere pe graful initial
    for (int i = 1; i <= n; ++i) {
      if (!visited[i]) { // nevizitat pe adj => visited[i] == 0
        dfs(i, visited, finish_sort);
      }
    }

    // parcurgere pe graful transpus dat de sortarea topologica
    for (int i = n; i >= 1; --i) {
      if (visited[finish_sort[i]]) { // nevizitat pe adj => visited[i] == 1
        // construiesc o noua ctc
        vector<int> current_ctc;

        dfs_t(finish_sort[i], visited, current_ctc);

        // o salvez
        sol.push_back(current_ctc);
      }
    }
    return sol;
  }

  // dfs pe graful normal (folosesc adj)
  void dfs(int node, vector<int> &visited, vector<int> &finish_sort) {
    visited[node] = 1;

    for (auto &vecin : adj[node]) {
      if (!visited[vecin]) {
        dfs(vecin, visited, finish_sort);
      }
    }

    // adaug nodul la sortarea topologica
    finish_sort.push_back(node);
  }

  // dfs pe graful transpus (folosesc adj_t)
  void dfs_t(int node, vector<int> &visited, vector<int> &current_ctc) {
    // vizitarea pe graful transpus, inseamna
    visited[node] = 0;
    current_ctc.push_back(node);

    for (auto &vecin : adj_trans[node]) {
      if (visited[vecin]) {
        dfs_t(vecin, visited, current_ctc);
      }
    }
  }

  void print_output(vector<vector<int>> result) {
    ofstream fout("out");
    fout << result.size() << '\n';
    for (const auto &ctc : result) {
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
