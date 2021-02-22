#include <fstream>
#include <vector>
#include <string>
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
	string expr;

	void read_input() {
		ifstream fin("in");
		fin >> n >> expr;
		expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
		fin.close();
	}

	int get_result() {
		return bool_expression();
	}

	bool is_operator(char op) {
        return op == '&' || op == '|' || op == '^';    
    }

    bool is_operand(char op) {
        return op == 'T' || op == 'F';    
    }

    bool evaluate(char op, int L, int R) {
        if (op == '&') return L & R;
        if (op == '|') return L | R;
        if (op == '^') return L ^ R;
    }

    
    int bool_expression() {
         
        vector<vector<vector<int>>>  dp(n + 1, vector<vector<int>> (n + 1, vector<int> (2, 0) ) );
         
        for (int i = 1; i <= n; i += 2) {
            dp[i][i][0] = (expr[i] == 'F');
            dp[i][i][1] = (expr[i] == 'T');
        }

         
        for (int len = 2; len <= n; ++len) {             
            for (int i = 1; i + len - 1 <= n; ++i) {     
                int j = i + len - 1;                     
                for (int k = i + 1; k < j; ++k) {       
                    if (!is_operator(expr[k])) {
                        continue;
                    }
                    char op = expr[k];                  
                    for (int lv = 0; lv <= 1; ++lv) {
                        for (int rv = 0; rv <= 1; ++rv) {
                             
                            bool v = evaluate(op, lv, rv);

                            
                            int add = (1LL * dp[i][k - 1][lv] * dp[k + 1][j][rv]) % kMod;


                             
                            dp[i][j][v] = (dp[i][j][v] + add) % kMod;
                        }
                    } 
                }
            }
        }

         
        return dp[1][n][1];
 
    }


	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
