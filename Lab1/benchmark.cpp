#include <iostream>
#include <chrono>
#include <algorithm>

#include <cstdio>
#include <string.h>


using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

template <typename T>
class TVector{
public:
	TVector() = default;
	~TVector() {
		delete[] arr;
	}
	TVector(const size_t len){
		arr = new T[len];
		size = len;
		capecity = len;
	}
	TVector(const size_t len, const T value){
		arr = new T[len];
		size = len;
		capecity = len;
		for (size_t i = 0; i < size; i++) {
			arr[i] = value;
		}
	}
	void PushBack(const T& elem){
		if (size == capecity) {
			capecity++;
			capecity = capecity*2;
			size_t new_size = capecity;
			T* tmp = new T[new_size];
			std::copy(begin(), end(), tmp);
			delete[] arr;
			arr = tmp;
		}
		arr[size] = elem;
		size++;
	}
	void swap(TVector& b){
		T* c = arr;
		arr = b.arr;
		b.arr = c;
	}
	T& operator[] (const int i){
		return arr[i];
	}
	TVector& operator=(TVector& other) {
		if (&other == this) {
			return *this;
		}
		if (other.size <= capecity) {
			std::copy(other.begin(), other.end(), begin());
			size = other.size;
		}
		else {
			TVector<T> tmp(other);
			std::swap(tmp.arr, arr);
			std::swap(tmp.size, size);
			std::swap(tmp.capecity, capecity);
		}
		return *this;
	}
	size_t Size() const {
		return size;
	}
	T* begin(){
		return arr;
	}
	T* end(){
		return arr + size;
	}

private:
	size_t size = 0;
	size_t capecity = 0;
	T* arr = nullptr;
};

struct TPair{
    int znacheniye[3] = {0};
    char stroka[11] = {'\0'};
    char val[65];
};

int RadixSort(TVector<TPair> &elems, const int (&max)[3]) {
	size_t N = elems.Size();
    if (N == 0) {
        return 0;
	}
	for (int i = 0; i < 3; ++i) {
		TVector<int> tmp((max[i] + 1),0);
		for (size_t j = 0; j < N; ++j) {
			tmp[elems[j].znacheniye[i]]++;
		}

		for (size_t j = 1; j < tmp.Size(); ++j) {
			tmp[j] += tmp[j-1];
		}

		TVector<TPair> res(N);
		for (int j = N-1; j > (-1); j--) {
			res[tmp[elems[j].znacheniye[i]] - 1] = elems[j];
			--tmp[elems[j].znacheniye[i]];
		}
		
		elems.swap(res);
	}
	return 0;
}

bool cmp(TPair lhs, TPair rhs) {
    int l = lhs.znacheniye[0] + lhs.znacheniye[1]*12 + lhs.znacheniye[2]*365;
    int r = rhs.znacheniye[0] + rhs.znacheniye[1]*12 + rhs.znacheniye[2]*365;
    return l < r;
}

int main(){
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
	int max[3] = {0};
	
	TVector<TPair> elems;
    TVector<TPair> elems2;
	TPair x;

	while (scanf("%s %s", x.stroka, x.val)>0) {
		sscanf(x.stroka, "%d.%d.%d", &x.znacheniye[0], &x.znacheniye[1], &x.znacheniye[2]);
        elems.PushBack(x);
		elems2.PushBack(x);
		if(x.znacheniye[0] > max[0]) max[0] = x.znacheniye[0];
		if(x.znacheniye[1] > max[1]) max[1] = x.znacheniye[1];
		if(x.znacheniye[2] > max[2]) max[2] = x.znacheniye[2];
    }

    std::cout << "Count of lines is " << elems.Size() << std::endl;

    // Измеряем время работы сортировки подсчётом.
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
    RadixSort(elems, max);
    std::chrono::time_point<std::chrono::system_clock> end_ts = std::chrono::system_clock::now();
    uint64_t RadixSortTime = std::chrono::duration_cast<std::chrono::microseconds>( end_ts - start_ts ).count();

    // Измеряем время работы stl сортировки.
    start_ts = std::chrono::system_clock::now();
    std::stable_sort(elems2.begin(), elems2.end(), cmp);
    end_ts = std::chrono::system_clock::now();

    uint64_t stl_sort_ts = std::chrono::duration_cast<std::chrono::microseconds>( end_ts - start_ts ).count();
    std::cout << "Counting sort time: " << RadixSortTime << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << std::endl;
}

