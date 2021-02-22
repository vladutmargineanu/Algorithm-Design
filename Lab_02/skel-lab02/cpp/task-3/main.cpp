#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct Homework
{
    int deadline;
    int score;

    Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

class Task
{
  public:
    void solve()
    {
        read_input();
        print_output(get_result());
    }

  private:
    int n;
    vector<Homework> hws;

    void read_input()
    {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, deadline, score; i < n; i++)
        {
            fin >> deadline >> score;
            hws.push_back(Homework(deadline, score));
        }
        fin.close();
    }
    // Sortam descrescator dupa deadline, sa punem temele cu score max prima data
     static bool deadline_comparator(Homework ob1, Homework ob2)
    {
         return (ob1.deadline > ob2.deadline);
    }


    int get_result()
    {
        /*
		TODO: Aflati punctajul maxim pe care il puteti obtine planificand
		optim temele.
		*/

        sort(hws.begin(), hws.end(), deadline_comparator);

        // // Aflam deadline-ul maxim
        int dead_m = 0;
        for (auto homework : hws)
        {
             if (homework.deadline > dead_m)
             {
                 dead_m = homework.deadline;
             }
        }

        priority_queue<int> mypq;
        int value = 0;

       while(dead_m != 0) {

            for(auto home: hws) {
                if(home.deadline == dead_m)
                mypq.push(home.score);
            }
          int aux = mypq.top();
          mypq.pop();
          value += aux; 
        dead_m --;
        }

      //   Rezolvare Heap
      //  1. Sortam crescator dupa deadline
        
    
       return value;
    }

    void print_output(int result)
    {
        ofstream fout("out");
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