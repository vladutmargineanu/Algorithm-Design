#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, k;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin.close();
	}
bool check(std::vector<int> solution) {
    for(int i = 0; i < solution.size()-1; i++ )
	for(int j = 0; j < solution.size(); j++)
		if(i!=j && solution[i]==solution[j])
			return false;
return true;
	
}
 

 
void back(std::vector<int> &domain, std::vector<int> &solution,vector<vector<int> > &all) {
 
    if (domain.size() == n-k ) {
        if(check(solution)) {
	    all.push_back(solution);
        }
        return;
    }
 

    for (unsigned int i = 0; i < domain.size(); ++i) {
        
        int tmp = domain[i];
 
        
        solution.push_back(domain[i]);
      
        domain.erase(domain.begin() + i);
 
       
        back(domain, solution,all);
 
       
        domain.insert(domain.begin() + i, tmp);
        solution.pop_back();
    }
}
	vector<vector<int> > get_result() {
		vector<vector<int> > all;

		/*
		TODO: Construiti toate aranjamentele de N luate cate K ale
		multimii {1, ..., N}.

		Pentru a adauga un nou aranjament:
			vector<int> aranjament;
			all.push_back(aranjament);
		*/

		std::vector<int> domain(n), solution;
		for (int i = 0; i < n; ++i)
		{
			domain[i] = i + 1;
		}
 
    /* apelam backtracking pe domeniul nostru, cautand solutia in vectorul solution */
    back(domain, solution,all);
		
		return all;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					(j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
