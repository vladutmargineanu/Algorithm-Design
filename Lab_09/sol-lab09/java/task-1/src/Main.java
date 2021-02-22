import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public class Main {
	static class Task {
		public static final String INPUT_FILE = "in";
		public static final String OUTPUT_FILE = "out";
		public static final int NMAX = 50005;

		int n;
		int m;
		int source;

		public class Edge {
			public int node;
			public int cost;

			Edge(int _node, int _cost) {
				node = _node;
				cost = _cost;
			}
		}

		@SuppressWarnings("unchecked")
		ArrayList<Edge> adj[] = new ArrayList[NMAX];

		private void readInput() {
			try {
				Scanner sc = new Scanner(new BufferedReader(new FileReader(
								INPUT_FILE)));
				n = sc.nextInt();
				m = sc.nextInt();
				source = sc.nextInt();

				for (int i = 1; i <= n; i++) {
					adj[i] = new ArrayList<>();
				}
				for (int i = 1; i <= m; i++) {
					int x, y, w;
					x = sc.nextInt();
					y = sc.nextInt();
					w = sc.nextInt();
					adj[x].add(new Edge(y, w));
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(ArrayList<Integer> result) {
			try {
				BufferedWriter bw = new BufferedWriter(new FileWriter(
								OUTPUT_FILE));
				StringBuilder sb = new StringBuilder();
				for (int i = 1; i <= n; i++) {
					sb.append(result.get(i)).append(' ');
				}
				sb.append('\n');
				bw.write(sb.toString());
				bw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		class DijkstraNode implements Comparable<DijkstraNode> {
			int dist;
			int node;

			public DijkstraNode(int _dist, int _node) {
				dist = _dist;
				node = _node;
			}

			public int compareTo(DijkstraNode other) {
				if (dist == other.dist) return Integer.compare(node, other.node);
				return Integer.compare(dist, other.dist);
			}
		}

		public static int INF = 0x3f3f3f3f;

		private ArrayList<Integer> getResult() {
			// TODO: Gasiti distantele minime de la nodul source la celelalte noduri
			// folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
			//	d[node] = costul minim / lungimea minima a unui drum de la source la
			//	nodul node;
			//	d[source] = 0;
			//	d[node] = -1, daca nu se poate ajunge de la source la node.
			// Atentie:
			// O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			//	adj[x].get(i).node = nodul adiacent lui x,
			//	adj[x].get(i).cost = costul.
			ArrayList<Integer> d = new ArrayList<>();
			for (int i = 0; i <= n; i++)
				d.add(INF);

			// In loc de un priority_queue folosim tree set, cu elemente tupluri de
			// tipul (distanta pana la nod, nod). Setul tine elementele ordonate, deci
			// mereum in q.begin() vom avea tuplul care ii corespunde nodului cu
			// distanta minima.
			TreeSet<DijkstraNode> q = new TreeSet<>();
			d.set(source, 0);
			q.add(new DijkstraNode(d.get(source), source));

			while (!q.isEmpty()) {
				DijkstraNode dnode = q.pollFirst();
				int x = dnode.node;

				for (Edge e : adj[x]) {
					int y = e.node;
					int c = e.cost;

					// Se imbunatateste distanta?
					if (d.get(y) > d.get(x) + c) {
						// Scot vechea pereche (distanta, nod) din q.
						//
						q.remove(new DijkstraNode(d.get(y), y));
						// Updatez distanta si inserez noua pereche.
						d.set(y, d.get(x) + c);
						q.add(new DijkstraNode(d.get(y), y));
					}
				}
			}

			// Toate distantele INF (unreachable) sunt setate pe -1.
			for (int i = 1; i <= n; i++) {
				if (d.get(i) == INF)
					d.set(i, -1);
			}

      return d;
		}

		public void solve() {
			readInput();
			writeOutput(getResult());
		}
	}

	public static void main(String[] args) {
		new Task().solve();
	}
}
