// Tarjan - O(n + m)

#include <bits/stdc++.h>
using namespace std;

const int kNmax = 100005;
#define edge pair<int, int>
#define MIN(x, y) ((x) < (y) ? (x) : (y))

class Task {
public:
  void solve() {
    read_input();
    print_output(get_result());
  }

private:
  // n = numar de noduri, m = numar de muchii
  int n, m;

  // adj[node] lista de adiacenta a nodului node pentru graful initial
  vector<int> adj[kNmax];

  // bcc[i] = componenta biconexa cu indicele i
  vector<vector<int>> bcc;

  // ordinea de vizitare
  // found[node] = timpul de start a lui node in parcurgerea DFS
  // in laborator found se numeste idx
  vector<int> found;

  // low_link[node] = min { found[x] | x este accesibil din node }
  // adica timpul minim al unui nou
  vector<int> low_link;

  // vector in care retin punctele de articulatie
  vector<int> cut_vertex;
  vector<int> is_cv;

  // parent[i] = parintele nodului i
  vector<int> parent;

  void read_input() {
    ifstream fin("in");
    fin >> n >> m;

    found = vector<int>(n + 1, -1);
    low_link = vector<int>(n + 1, 0);
    parent = vector<int>(n + 1, 0);
    is_cv = vector<int>(n + 1, 0);

    for (int i = 1, x, y; i <= m; i++) {
      fin >> x >> y;
      adj[x].push_back(y);
      adj[y].push_back(x);
    }
    fin.close();
  }

  vector<int> get_result() {
    /*
    TODO: Gasiti nodurile critice ale grafului neorientat stocat cu liste
    de adiacenta in adj.
    */
    tarjan();

    return cut_vertex;
  }

  void tarjan() {
    // momentul curent de start
    // pe masura ce vizita nodurile el va creste (++)
    int current_start = 0;

    for (int i = 1; i <= n; ++i) {
      if (found[i] == -1) {
        // acest nod nu a fost descoperit, deci il putem folosi
        // marcam nodul i ca fiind radacina
        parent[i] = 0;

        // pornim o noua cautare din nodul respectiv
        dfs(i, current_start);
      }
    }
  }

  void dfs(int node, int &current_start) {
    // incep un nou nod, deci un nod timp de start
    ++current_start;  // numarul nodului 

    // atat found, cat si low_link vor primi valoarea lui current_start
    found[node] = current_start;
    low_link[node] = current_start;

    // initializez numarul de copii al nodului curent cu 0
    int children = 0;

    for (auto &vecin : adj[node]) {
      if (found[vecin] == -1) { // deci il pot vizita
        // parintele nodului in care ma duc este chiar nodul curent
        parent[vecin] = node;

        // cresc numarul de copii
        ++children;

        // pornesc un nou dfs
        dfs(vecin, current_start);

        // updatez low_link:
        // - low_link[node]  = timpul de start cel mai mic pe care NODE  il
        // cunoaste
        // - low_link[vecin] = timpul de start cel mai mic pe care VECIN il
        // cunoaste
        // Tot ce acceseaza vecin (Ex. vecin - ... - x) poate accesa si node
        // (ex. node - vecin - ... - x)
        low_link[node] = MIN(low_link[node], low_link[vecin]);

        // CUT VERTEX - caz 2:
        // daca nu au existat muchii de intoarcere spre un STRAMOS al lui node
        // inseamna ca nodul curent este punct de articulatie
        // adica VECIN nu a putut sa sara inapoi in arbore PESTE node
        if (low_link[vecin] >= found[node]) {
          // radacina este tratata separat (adica conditia de mai sus nu este
          // pentru radacina)
          if (parent[node] != 0) {
            // deci node este CV
            // il daugat la solutie doar daca nu a fost deja adaugat
            if (!is_cv[node]) {
              cut_vertex.push_back(node);
              is_cv[node] = 1;
            }
          }
        }
      } else {
        if (vecin != parent[node]) {
          // am gasit o muchie de intoarcere
          low_link[node] = MIN(low_link[node], found[vecin]);
        }
      }
    }

    // CUT VERTEX - caz 1:
    // daca nodul curent este radacina si are mai mult de 2 copii
    if (parent[node] == 0 && children >= 2) {
      // salvez pe node doar daca nu l-am salvat deja
      if (!is_cv[node]) {
        is_cv[node] = 1;
        cut_vertex.push_back((node));
      }
    }
  }

  void print_output(vector<int> result) {
    ofstream fout("out");
    for (int i = 0; i < int(result.size()); i++) {
      fout << result[i] << ' ';
    }
    fout << '\n';
    fout.close();
  }
};

int main() {
  Task *task = new Task();
  task->solve();
  delete task;
  return 0;
}
