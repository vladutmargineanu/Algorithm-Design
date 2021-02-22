import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	static class Task {
		public final static String INPUT_FILE = "in";
		public final static String OUTPUT_FILE = "out";

		int n;
		int[] v;

		private final static int MOD = 1000000007;

		private void readInput() {
			try {
				Scanner sc = new Scanner(new File(INPUT_FILE));
				n = sc.nextInt();
				v = new int[n + 1];
				for (int i = 1; i <= n; i++) {
					v[i] = sc.nextInt();
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(int result) {
			try {
				PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
				pw.printf("%d\n", result);
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private int getResult() {
			// TODO: Aflati numarul de subsiruri (ale sirului stocat in v,
			// indexat de la 1 la n), nevide cu suma numerelor para.
			// Rezultatul se va intoarce modulo MOD (1000000007).

			// dp[i][p] = Numarul de subsiruri formate cu elemente din {v[1],
			// ..., v[i]}, cu paritatea sumei p.
			int[][] dp = new int[n + 1][2];
			
			// cazuri de baza
			dp[0][0] = 0;
			dp[0][1] = 0;

			for (int i = 1; i <= n; i++) {
				dp[i][0] = dp[i][1] = 0;

				// Putem lua elementul v[i] singur in subsir (deci paritatea va
				// fi v[i] % 2):
				dp[i][v[i] % 2] = 1;

				for (int p = 0; p < 2; p++) {
					// dp[i] in functie de dp[i - 1]:
					// Fie nu luam elementul v[i] in subsir, si atunci se
					// pastreaza paritatea:
					dp[i][p] = (dp[i][p] + dp[i - 1][p]) % MOD;

					// Fie luam elementul v[i] in subsir, si atunci se modifica
					// paritatea in (paritate veche + numar curent) % 2.
					int np = (v[i] + p) % 2;
					dp[i][np] = (dp[i][np] + dp[i - 1][p]) % MOD;
				}
			}

			// dp[n][0] = Numarul de subsiruri formate cu elemente din {v[1],
			// ..., v[n]}, cu paritate 0.
			return dp[n][0];
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
