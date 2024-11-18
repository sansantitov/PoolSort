#include <vector>
#include <iostream>
#include <chrono>
#include "quickSort.h"


int main() {

    QuickSort sort;
    bool res = true;

    srand(0);
    int size = 100000;

    std::vector<int> arr;

    for (int i = 0; i < size; i++) arr.push_back(rand() % 5000);

    sort.make_multithread(true);
    auto start = std::chrono::high_resolution_clock::now();
    sort.quicksort(arr, 0, size - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Multithread: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << ".";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " sec" << std::endl;
    for(int i=0; i<size-1; i++) {
        if (arr[i] > arr[i + 1]) {
            std::cout << "Unsorted" << std::endl;
            res = false;
            break;
        }
    }
    if (res) printf("Check: Ok!\n");

    arr.clear();
    for (int i = 0; i < size; i++) arr.push_back(rand() % 5000);
    sort.make_multithread(false);
    auto start1 = std::chrono::high_resolution_clock::now();
    sort.quicksort(arr, 0, size - 1);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Single thread: " << std::chrono::duration_cast<std::chrono::seconds>(end1 - start1).count() << ".";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " sec"<< std::endl;


    res = true;
    for(int i=0; i<size-1; i++) {
        if (arr[i] > arr[i + 1]) {
            std::cout << "Unsorted" << std::endl;
            res = false;
            break;
        }
    }
    if (res) printf("Check: Ok!\n");

    return 0;

 }
