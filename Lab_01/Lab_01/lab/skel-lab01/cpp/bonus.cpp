#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int inversiuni(const vector<int> &v, int start, int end) {
    return 0;
}

int main() {
    vector<int> v;
    int size;

    cin >> size;
    v.resize(size);

    for (int i = 0; i < size; ++i) {
        cin >> v[i];
    }

    cout << inversiuni(v, 0, size - 1) << '\n';
    return 0;
}