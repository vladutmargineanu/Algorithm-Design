#include <map>
#include <algorithm>
#include <iostream>
#include <algorithm>

using namespace std;


using namespace std;

template<typename KeyType, typename ValueType>
    std::pair<KeyType, ValueType> get_max(const std::map<KeyType, ValueType> &x)
{
    using pairtype = std::pair<KeyType, ValueType>;
    return *std::max_element(x.begin(), x.end(), [](const pairtype &p1, const pairtype &p2) {
        return p1.second < p2.second;
    });
}
int main(){


std::map<char, int> x = {{'a', 1}, {'b', 2}, {'c', 0}};
auto max = get_max(x);
std::cout << max.first << "=>" << max.second << std::endl;

}