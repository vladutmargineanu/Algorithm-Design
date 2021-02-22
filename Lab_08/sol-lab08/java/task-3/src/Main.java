import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Main {
	static class Task {
		public static final String INPUT_FILE = "in";
		public static final String OUTPUT_FILE = "out";
		public static final int NMAX = 100005; // 10^5

		int n;
		int m;

		@SuppressWarnings("unchecked")
		ArrayList<Integer> adj[] = new ArrayList[NMAX];

		class Edge {
			int x;
			int y;

			Edge(int _x, int _y) {
				x = _x;
				y = _y;
			}
		}

		private void readInput() {
			try {
				Scanner sc = new Scanner(new BufferedReader(new FileReader(
								INPUT_FILE)));
				n = sc.nextInt();
				m = sc.nextInt();

				for (int i = 1; i <= n; i++)
					adj[i] = new ArrayList<>();
				for (int i = 1; i <= m; i++) {
					int x, y;
					x = sc.nextInt();
					y = sc.nextInt();
					adj[x].add(y);
					adj[y].add(x);
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private int depth[];
		private int low[];

		private void dfs(int x, int f, ArrayList<Edge> sol) {
			depth[x] = depth[f] + 1;
			low[x] = depth[x];
			for (int y : adj[x]) {
				if (y == f) continue;
				if (depth[y] == 0) {
					dfs(y, x, sol);
					if (low[y] > depth[x]) {
						// Muchie critica (nu au existat muchii de intoarcere din
						// subarborele lui y spre x sau spre un stramos al lui x), deci
						// scoaterea muchiei (x, y) va deconecta sigur nodurile x si y.
						sol.add(new Edge(x, y));
					}
					// updatez low_link:
					// - low_link[x] = depth-ul cel mai mic pe care X il
					// cunoaste
					// - low_link[y] = depth-ul cel mai mic pe care Y il
					// cunoaste
					// Tot ce acceseaza y (Ex. y - ... - z) poate accesa si x
					// (ex. x - y - ... - z)
					low[x] = Math.min(low[x], low[y]);
				} else {
					// Muchie de intoarcere.
					low[x] = Math.min(low[x], depth[y]);
				}
			}
		}

		private void writeOutput(ArrayList<Edge> result) {
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
								OUTPUT_FILE)));
				pw.printf("%d\n", result.size());
				for (Edge e : result) {
					pw.printf("%d %d\n", e.x, e.y);
				}
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private ArrayList<Edge> getResult() {
			// TODO: Gasiti muchiile critice ale grafului neorientat stocat cu liste
			// de adiacenta in adj.
			ArrayList<Edge> sol = new ArrayList<>();
			depth = new int[n + 1];
			low = new int[n + 1];
			for (int i = 0; i <= n; i++) depth[i] = 0;
			for (int i = 1; i <= n; i++) {
				if (depth[i] != 0) continue;
				dfs(i, 0, sol);
			}
			return sol;
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
