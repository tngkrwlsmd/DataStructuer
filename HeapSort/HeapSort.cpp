#include <iostream>
#include <iomanip> //formatting
#include <cstdlib>
#include <ctime>
#include <random> //random
#define N 100

void ConstructHeap(int data[], int n);
void HeapSort(int data[], int n);

int main(void) {

	int data[N];

	//srand(time(NULL));
	std::cout << "정렬 전 배열" << std::endl << std::endl;
	//방법 1
	/*for (int i = 0; i < N; i++) {
		data[i] = rand() % 1000;
		std::cout << std::setw(3) << data[i] << " ";
		if ((i + 1) % 10 == 0) std::cout << std::endl;
	}*/

	//방법 2
	/*int count = 0;
	for (auto& i : data) {
		i = rand() % 1000;
		std::cout << std::setw(3) << i << " ";
		count++;
		if (count % 10 == 0) std::cout << std::endl;
	}*/

	//방법 3
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 1000);

	int count = 0;
	for (auto& i : data) {
		i = dis(gen);
		std::cout << std::setw(3) << i << " ";
		count++;
		if (count % 10 == 0) std::cout << std::endl;
	}

	HeapSort(data, N);

	std::cout << std::endl << "정렬 후 배열" << std::endl << std::endl;

	for (int i = 0; i < N; i++) {
		std::cout << std::setw(3) << data[i] << " ";
		if ((i + 1) % 10 == 0) std::cout << std::endl;
	}

	return 0;
}

void ConstructHeap(int data[], int n) {
	int i, j, temp, left, right, imsi;
	for (i = n / 2; i >= 0; i--) {
		temp = data[i]; j = i;
		left = 2 * j + 1; right = 2 * j + 2;
		while (left < n) {
			if (right < n && data[left] < data[right]) imsi = right;
			else imsi = left;
			if (temp < data[imsi]) {
				data[j] = data[imsi]; j = imsi;
				left = 2 * j + 1; right = 2 * j + 2;
			}
			else break;
		}
		data[j] = temp;
	}
}

void HeapSort(int data[], int n) {
	int temp, i;
	ConstructHeap(data, n);
	for (i = n - 1; i > 0; i--) {
		temp = data[0]; data[0] = data[i]; data[i] = temp;
		ConstructHeap(data, i);
	}
}