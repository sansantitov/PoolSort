#include "quickSort.h"
#include <future>
#include "requestHandler.h"
//#include <iostream>

void QuickSort::swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void QuickSort::quicksort_f(std::vector<int>& vec, int left, int right, std::shared_ptr<std::promise<void>> promise) {
    std::future<void> f = std::async(std::launch::async, [&]() { quicksort(vec, left, right); });
    f.wait();
    promise->set_value();
}

void QuickSort::quicksort(std::vector<int>& vec, int left, int right) {
    if (left >= right) return;
    RequestHandler rh;
    auto promise = std::make_shared<std::promise<void>>();
    int pi = partition(vec, left, right);
    if (multithread && (pi - left > diffPiLeft)) {
        //std::cout << "Yes quicksort_f" << std::endl;
        rh.push_task(&QuickSort::quicksort_f, this, std::ref(vec), left, pi - 1, promise);
        quicksort(vec, pi + 1, right);
    } else {
        quicksort(vec, left, pi - 1);
        quicksort(vec, pi + 1, right);
    }
}

int QuickSort::partition(std::vector<int>& vec, int left, int right) {
    int pivot = vec[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (vec[j] < pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[right]);
    return i + 1;
}

void QuickSort::make_multithread(bool l) {
    multithread = l;
}

