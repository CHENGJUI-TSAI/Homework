#pragma once
#ifndef SORTS_H
#define SORTS_H

#include <vector>

// 不要在 header 裡用 using namespace std;
// 函式宣告改用 std::vector<int> 全名。

void insertionSort(std::vector<int> arr);
void quickSort(std::vector<int> arr);
void mergeSort(std::vector<int> arr);
void heapSort(std::vector<int> arr);
void compositeSort(std::vector<int> arr);

#endif // SORTS_H
