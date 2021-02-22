#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Task
{
  public:
    void solve()
    {
        read_input();
        get_result();
    }

  private:
    int N, k;
    int m = N - k; // vom genera submultimi de N-k elemente
    std::vector<long long> sir;
    // Vectorul care va contine submultimea de m elemente
    std::vector<long long> subsir;
    void read_input()
    {
        std::ifstream fin("p1.in");
        fin >> N;
        long long n;
        for (int i = 0; i < N; i++)
        {
            fin >> n;
            sir.push_back(n);
        }
        fin.close();
    }
    // comparator, sortam in ordine crescatoare
    static bool comparator(long long ob1, long long ob2)
    {
        return (ob1 < ob2);
    }

    void initial(int p)
    {
        if (p == 0)
        {
            subsir[p] = sir[p];
        }
        else
        {
            subsir[p] = subsir[p - 1];
        }
    }

    int successor(int p)
    {
        if (subsir.size() < N - k + p - 1)
        {
            subsir[p] = sir[p + 1];
            return 1;
        }
        else{
            return 0;
        }
    }

    int validity()
    {
        return 1;
    }
    int solution(int p) {
        return p - 1 == m - 1;
    }

    void write () {
        std::ofstream fout("p1.out");
        for(unsigned i = 0; i < subsir.size(); i++) {
            fout << subsir[i] << " ";
        }
        fout << "\n";
        fout.close();
    }

    void bt(int p)
    {
        initial(p);
        while (successor(p))
        {
            if (validity())
            {
                if (solution(p))
                {
                    // aflam diferenta pentru submultimea generata
                    write();
                }
                else
                {
                    bt(p + 1);
                }
            }
        }
    }

    void get_result()
    {
        // Sortam in ordine descrescatoare
        sort(sir.begin(), sir.end(), comparator);
        bt(0);

    }

    void print_output(long long result)
    {
        std::ofstream fout("p1.out");
        fout << result;
        fout.close();
    }
};

int main()
{
    Task task;
    task.solve();
    return 0;
}