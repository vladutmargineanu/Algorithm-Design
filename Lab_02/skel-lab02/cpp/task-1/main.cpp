#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;
/*
1. De ce folosim biblioteca iomanip?
 Pentru clasa setprecision.(rand 52)


*/
struct Object {
	int weight;
	int price;
// Constructor
	Object(int _weight, int _price) : weight(_weight), price(_price) {}
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, w;
	// vector de obiecte Object (struct) cu campuri weight si price
	vector<Object> objs;

	void read_input() {
		ifstream fin("in");
		// w = greuteatea pe care o poate baga in rucsac
		// n = numarul de obiecte
		fin >> n >> w;
		for (int i = 0, weight, price; i < n; i++) {
			fin >> weight >> price;
			objs.push_back(Object(weight, price));
		}
		fin.close();
	}
    // comparator, sortam in ordine descrescatoare 
	static bool ratio_comparator(Object ob1, Object ob2){
		return ((double)ob1.price) / ob1.weight > ((double)ob2.price) / ob2.weight;
	}

	double get_result() {
		/*
		TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
		*/
		// 1.Sortam
		sort(objs.begin(), objs.end(), ratio_comparator);

		/* for (auto objects : objs) {
			cout << "Greutatea = " << objects.weight 
					<< " " << "Pretul = " << objects.price << "\n";
	 	}  */

		int contor_weight = 0; //cat bagam pe parcurs in sac
		double value = 0;

		for (auto objects : objs) {
			if(contor_weight >= w)
					break;
			if (objects.weight + contor_weight <= w) {
				contor_weight += objects.weight;
				value += objects.price;
			} else {
				value += (double)objects.price * (w - contor_weight) / objects.weight;
				contor_weight = w; //pt oprire
			}
		}

			return value;
	}

	void print_output(double result) {
		ofstream fout("out");
		fout << setprecision(4) << fixed << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
''