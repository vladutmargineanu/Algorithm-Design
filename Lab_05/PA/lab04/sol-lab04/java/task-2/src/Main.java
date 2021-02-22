import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	static class Task {
		public final static String INPUT_FILE = "in";
		public final static String OUTPUT_FILE = "out";

		private final static int MOD = 1000000007;

		int n;
		char[] v;

		private void readInput() {
			try {
				Scanner sc = new Scanner(new File(INPUT_FILE));
				n = sc.nextInt();
				String s = sc.next().trim();
				s = " " + s;
				v = s.toCharArray();
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

		private boolean isOperand(char c) {
			return c == 'T' || c == 'F';
		}

		private int getOperandValue(char c) {
			if (c == 'T') return 1;
			if (c == 'F') return 0;
			throw new RuntimeException();
		}

		private int evaluate(char op, int opd1, int opd2) {
			if (op == '&') return opd1 & opd2;
			if (op == '|') return opd1 | opd2;
			if (op == '^') return opd1 ^ opd2;
			throw new RuntimeException();
		}

		private int getResult() {
			// TODO: Calculati numarul de moduri in care se pot aseza
			// parantezele astfel incat rezultatul expresiei sa fie TRUE.

			// dp[L][R][V] = Numarul de moduri in care se pot aseza parantezele
			// pe subsecventa [v[L], ..., v[R]], astfel incat evaluarea
			// expresiei sa dea valoarea V.
			int[][][] dp = new int[n + 1][n + 1][2];
			
			// Initializare:
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= n; j++)
					dp[i][j][0] = dp[i][j][1] = 0;

			for (int i = 1; i <= n; i++) {
				if (isOperand(v[i])) {
					// Pe subsecventa [v[i]], exista un singur mod de a pune
					// parantezele: nu le punem, si obtinem valoarea
					// operandului v[i].
					dp[i][i][getOperandValue(v[i])] = 1;
				}
			}

			// Solutia se bazeaza pe faptul ca o subsecventa [i, j] poate fi
			// sparta in doua subsecvente [i, k - 1], [k + 1, j] + operandul
			// v[k] dintre ele.
			// Astfel, este necesar sa garantam ca atunci cand calculam
			// dp-ul unei subsecvente de lungime X, toate dp-urile pentru
			// subsecventele de lungime < X sunt calculate si ele.
			// Astfel, iteram prin lungime (de la 2 la n), am initializat
			// pentru lungime 1 mai sus.
			//
			// Daca avem X moduri in stanga, Y moduri in
			// dreapta, atunci se vor obtine X * Y moduri noi de a paranteza
			// subsecventa [i, j], deoarece parantezele din stanga si din
			// dreapta sunt independente.
			for (int len = 2; len <= n; len++) {
				// Iteram prin capatul stanga al subsecventei.
				for (int i = 1; i + len - 1 <= n; i++) {
					// Obtinem capatul dreapta din lungime si capatul stanga.
					int j = i + len - 1;
					// Iteram prin indicii dintre capete, cautand un loc unde
					// subsecventa poate fi "sparta" in 2 de un operator.
					for (int k = i + 1; k < j; k++) {
						if (isOperand(v[k]))
							continue;
						// Iteram prin valorile de adevar pentru subsecventa
						// stanga.
						for (int lv = 0; lv <= 1; lv++) {
							// Iteram prin valorile de adevar pentru subsecventa
							// dreapta.
							for (int rv = 0; rv <= 1; rv++) {
								// Evaluam valoarea intregii expresii, daca
								// parantezam aici.
								int nv = evaluate(v[k], lv, rv);
								// Calculam noul numar de moduri:
								// Adaugam numarul de moduri din stanga,
								// inmultit cu numarul de moduri din dreapta.
								int add = (int)((1L * dp[i][k - 1][lv]
										* dp[k + 1][j][rv]) % MOD);
								dp[i][j][nv] = (dp[i][j][nv] + add) % MOD;
							}
						}
					}
				}
			}

			// Rezultatul se afla in dp[1][n][1]: Numarul de parantezari pentru
			// intreg sirul cu valoarea de adevar 1 (TRUE).
			return dp[1][n][1];
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
