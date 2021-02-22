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
		@SuppressWarnings("unchecked")
		ArrayList<Integer> adjt[] = new ArrayList[NMAX];

		private void readInput() {
			try {
				Scanner sc = new Scanner(new BufferedReader(new FileReader(
								INPUT_FILE)));
				n = sc.nextInt();
				m = sc.nextInt();

				for (int i = 1; i <= n; i++) {
					adj[i] = new ArrayList<>();
					adjt[i] = new ArrayList<>();
				}
				for (int i = 1; i <= m; i++) {
					int x, y;
					x = sc.nextInt();
					y = sc.nextInt();
					adj[x].add(y);
					adjt[y].add(x);
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(ArrayList<ArrayList<Integer>> result) {
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
								OUTPUT_FILE)));
				pw.printf("%d\n", result.size());
				for (ArrayList<Integer> ctc : result) {
					for (int nod : ctc) {
						pw.printf("%d ", nod);
					}
					pw.printf("\n");
				}
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private ArrayList<ArrayList<Integer>> getResult() {
			// TODO: Gasiti componentele tare conexe ale grafului orientat cu
			// n noduri, stocat in adj. Rezultatul se va returna sub forma
			// unui ArrayList, ale carui elemente sunt componentele tare conexe
			// detectate. Nodurile si componentele tare conexe pot fi puse in orice
			// ordine in arraylist.
			//
			// Atentie: graful transpus este stocat in adjt.
			ArrayList<ArrayList<Integer>> sol = new ArrayList<>();
			boolean visited[] = new boolean[n + 1];
			ArrayList<Integer> finish_sort = new ArrayList<>();
			finish_sort.add(-1);
			for (int i = 1; i <= n; i++)
				visited[i] = false;

			// Sortez nodurile dupa timpii de finish din dfs.
			for (int i = 1; i <= n; i++)
				if (!visited[i])
					dfs(i, visited, finish_sort);

			// Resetez visited pentru dfs-urile pe graful transpus.
			for (int i = 1; i <= n; i++)
				visited[i] = false;

			// Parcurg nodurile in ordinea inversa a timpilor de finish.
			for (int i = n; i >= 1; --i) {
				int x = finish_sort.get(i);
				if (visited[x]) continue;

				// Fac dfs pe graful transpus si toate nodurile atinse fac parte din
				// aceeasi ctc.
				ArrayList<Integer> current_ctc = new ArrayList<Integer>();
				dfs_t(x, visited, current_ctc);
				sol.add(current_ctc);
			}
			return sol;
		}

		private void dfs(int node, boolean visited[], ArrayList<Integer> finish_sort) {
			visited[node] = true;

			for (int neighbor : adj[node]) {
				if (visited[neighbor])
					continue;
				dfs(neighbor, visited, finish_sort);
			}

			// Iesire nod, il adaug la finish_sort.
			finish_sort.add(node);
		}

		private void dfs_t(int node, boolean visited[], ArrayList<Integer> ctc) {
			visited[node] = true;
			ctc.add(node);

			for (int neighbor : adjt[node]) {
				if (visited[neighbor])
					continue;
				dfs_t(neighbor, visited, ctc);
			}
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
