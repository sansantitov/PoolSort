#pragma once
#include <vector>
#include <future>

class QuickSort {
public:
    void swap(int& x, int& y);
    void quicksort_f(std::vector<int>& vec, int left, int right, std::shared_ptr<std::promise<void>> promise);
    void quicksort(std::vector<int>& vec, int left, int right);
    int partition(std::vector<int>& vec, int left, int right);
    void make_multithread(bool);
private:
    bool multithread;
    //const int diffPiLeft = 100000;
    const int diffPiLeft = 10000;

};


