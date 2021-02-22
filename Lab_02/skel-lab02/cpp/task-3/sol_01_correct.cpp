#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<Homework> hws;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.push_back(Homework(deadline, score));
		}
		fin.close();
	}
    // Sortam descrescator dupa score, sa punem temele cu score max prima data
	static bool score_comparator(Homework ob1, Homework ob2)
	{
		return (ob1.score > ob2.score);
	}

	// Verificam daca am fixat vreo tema in sapmana respectiva de la dreapta la stg
	static bool check(Homework ob, vector<int>& timp) {

		for (int t = ob.deadline; t > 0; --t) {
			if (timp[t] == 0){
				timp[t] = 1; // am fixat tema

				return true;
			}
		}
		return false;
	}

	int get_result() {
		/*
		TODO: Aflati punctajul maxim pe care il puteti obtine planificand
		optim temele.
		*/

		sort(hws.begin(), hws.end(), score_comparator);

		// Aflam deadline-ul maxim
		int dead_m = 0;
		for(auto homework : hws) {
			if(homework.deadline > dead_m){
				dead_m = homework.deadline;
			}
		}

		// la fel ca la problema cuielor, fixam temele in saptamana deadline ului
		vector<int> timp(dead_m + 1, 0); // tinem evidenta temelor fixate in funtie de saptamani
		int score_max = 0;

			for (auto homework : hws) {
				if (check(homework, timp)) {
					score_max += homework.score;
			}
		}

		return score_max;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}