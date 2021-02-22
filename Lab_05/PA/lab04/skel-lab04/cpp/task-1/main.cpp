#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int kMod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result() {
		
		return solve_dp1_nn(); 
	}

	int solve_dp1_nn() {
		
        vector<int> dp_even(n + 1);
        vector<int> dp_odd(n + 1);
       
        dp_even[0] = 0;
        dp_odd[0] = 0;

		for (int i = 1; i <= n; ++i) {
			if (v[i] % 2 == 0) { 
				dp_even[i] = 1; 
				dp_odd[i]  = 0; 
				
				
				for (int j = 1; j < i; ++j) {
					dp_even[i] = (dp_even[i] + dp_even[j]) % kMod;
					dp_odd[i]  = (dp_odd[i] + dp_odd[j]) % kMod;
				}
			} else {              
				dp_even[i] = 0;   
				dp_odd[i]  = 1;   
				
				 
				for (int j = 1; j < i; ++j) {
					dp_even[i] = (dp_even[i] + dp_odd[j]) % kMod;
					dp_odd[i]  = (dp_odd[i] + dp_even[j]) % kMod;
				}
			}
		}

		
		int sol = 0;
		for (int i = 1; i <= n; ++i) {
			sol = (sol + dp_even[i]) % kMod;
		}

		return sol;
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
