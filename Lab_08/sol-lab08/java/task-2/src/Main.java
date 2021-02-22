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

		private void writeOutput(ArrayList<Integer> result) {
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
								OUTPUT_FILE)));
				for (int node : result) {
					pw.printf("%d ", node);
				}
				pw.printf("\n");
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private int depth[];
		private int low[];

		private void dfs(int x, int f, ArrayList<Integer> sol) {
			depth[x] = depth[f] + 1;
			low[x] = depth[x];
			boolean ok = false;
			// Cnt = numarul de copii al lui x in arborele DFS.
			int cnt = 0;
			for (int y : adj[x]) {
				if (y == f) continue;
				if (depth[y] == 0) {
					dfs(y, x, sol);
					cnt++;
					if (low[y] >= depth[x]) {
						// Acest nod este posibil sa fie punct critic (caz particular
						// - radacina), deoarece nu au existat muchii de intoarcere catre
						// vreun stramos al lui x.
						ok = true;
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

			// Daca e radacina si are cel putin 2 copii e punct critic
			if (f == 0 && cnt > 1) sol.add(x);
			// Sau daca nu e radacina si ok == true.
			else if (f != 0 && ok) sol.add(x);
		}

		private ArrayList<Integer> getResult() {
			// TODO: Gasiti nodurile critice ale grafului neorientat stocat cu liste
			// de adiacenta in adj.
			ArrayList<Integer> sol = new ArrayList<>();
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
