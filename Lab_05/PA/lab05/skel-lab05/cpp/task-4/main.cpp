#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, k;
	string caractere;
	vector<int> freq;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin >> caractere;
		caractere = " " + caractere; // Adaugare element fictiv -
									 // indexare de la 1.
		freq.push_back(-1); // Adaugare element fictiv - indexare de la 1.
		for (int i = 1, f; i <= n; i++) {
			fin >> f;
			freq.push_back(f);
		}
		fin.close();
	}

	void bkt(vector<char>& current,		// Sirul curent
			int consec,					// Numarul de caractere consecutive de
										// la sfarsit
			vector<vector<char> >& all) {
		// Daca sunt peste K aparitii ale aceluiasi caracter consecutiv,
		// ne oprim.
		if (consec > k)
			return;

		// Verificam daca nu mai e nimic de pus.
		bool found = true;
		for (int i = 1; i <= n; i++) {
			if (freq[i] != 0)
				found = false;
		}

		if (found) {
			// Am construit un sir, deci il adaugam.
			all.push_back(current);
			return;
		}

		// Incercam sa extindem sirul.
		for (int i = 1; i <= n; i++) {
			// Sarim peste caracterul i, daca nu mai avem de pus din el.
			if (freq[i] == 0)
				continue;

			int new_consec = 1;
			// Daca extindem cu acelasi caracter, actualizam new_consec la
			// valoarea veche + 1, altfel il setam pe 1.
			if (!current.empty() && current.back() == caractere[i])
				new_consec = consec + 1;

			// Incercam sa extindem sirul cu caracterul i, scazand frecventa.
			freq[i]--;
			current.push_back(caractere[i]);
			// Apelam recursiv.
			bkt(current, new_consec, all);

			// Refacem freq si current.
			freq[i]++;
			current.pop_back();
	
		}
	}

	vector<vector<char>> get_result() {
		vector<vector<char>> all;

		/*
		TODO: Construiti toate sirurile cu caracterele in stringul caractere
		(indexat de la 1 la n), si frecventele in vectorul freq (indexat de la
		1 la n), stiind ca nu pot fi mai mult de K aparitii consecutive ale
		aceluiasi caracter.

		Pentru a adauga un nou sir:
			vector<char> sir;
			all.push_back(sir);
		*/

		vector<char> current;
		bkt(current, 0, all);

		return all;
	}

	void print_output(vector<vector<char> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j];
			}
			fout << '\n';
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
