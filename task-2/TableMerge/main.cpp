#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
void mergeSortedTables(vector<T>& a, vector<T>&& b);

int main() {
	// given
	typedef int TestType;
	vector<TestType> a{ 1,3,5,7,9,11,13,15 };
	vector<TestType> b{ 2,4,6,8,10,12,14 };
	a.reserve(a.size() + b.size());
	// when
	mergeSortedTables<TestType>(a, std::move(b));
	// then
	cout << "Values:";
	for (const auto& v : a)
		cout << ' ' << v;
	cout << endl;
}

template<typename T>
void mergeSortedTables(vector<T>& a, vector<T>&& b) {
	std::move(b.begin(), b.end(), std::back_inserter(a));
	std::inplace_merge(a.begin(), a.begin() + (a.size() - b.size()), a.end());
};
