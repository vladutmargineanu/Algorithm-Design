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
	int N,board[100][100];

	void read_input() {
		ifstream fin("in");
		fin >> N;
		fin.close();
	}
int is_attack(int i,int j)
{
    int k,l;
    //checking if there is a queen in row or column
    for(k=0;k<N;k++)
    {
        if((board[i][k] == 1) || (board[k][j] == 1))
            return 1;
    }
    //checking for diagonals
    for(k=0;k<N;k++)
    {
        for(l=0;l<N;l++)
        {
            if(((k+l) == (i+j)) || ((k-l) == (i-j)))
            {
                if(board[k][l] == 1)
                    return 1;
            }
        }
    }
    return 0;
}

int N_queen(int n)
{
    int i,j;

    if(n==0)
        return 1;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
           
            if((!is_attack(i,j)) && (board[i][j]!=1))
            {
                board[i][j] = 1;
                
                if(N_queen(n-1)==1)
                {
                    return 1;
                }
                board[i][j] = 0;
            }
        }
    }
    return 0;
}

	vector<int> get_result() {
		vector<int> sol(N + 1, 0);

		/*
		TODO: Gasiti o solutie pentru problema damelor pe o tabla de dimensiune
		n x n.

		Pentru a plasa o dama pe randul i, coloana j:
			sol[i] = j.
		Randurile si coloanele se indexeaza de la 1 la n.

		De exemplu, configuratia (n = 5)
		X----
		--X--
		----X
		-X---
		---X-
		se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.
		*/
        int i,j;	
        for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++)
                {
                    board[i][j]=0;
                }
            }

        N_queen(N);
        for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++)
                    if(board[i][j] != 0 ) sol[i+1] = j;
            }
                return sol;
            }

            void print_output(vector<int> result) {
                ofstream fout("out");
                for (int i = 1; i <= N; i++) {
                    fout << result[i] << (i != N ? ' ' : '\n');
                }
                fout.close();
            }
};

int main() {
	Task task;
	task.solve();
	return 0;
}
