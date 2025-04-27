//=============================
// sort.cpp   (改寫版，不同寫法)
//=============================
#include "sorts.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*-------------------------------------------------
  1. Insertion Sort
-------------------------------------------------*/
void insertionSort(vector<int> arr)
{
    int len = arr.size();
    for (int idx = 1; idx < len; ++idx) {
        int temp = arr[idx];
        int pos = idx;
        while (pos > 0 && arr[pos - 1] > temp) {
            arr[pos] = arr[pos - 1];
            --pos;
        }
        arr[pos] = temp;
    }
}

/*-------------------------------------------------
  2. Quick Sort（簡單版，pivot = 中間）
-------------------------------------------------*/
namespace {
    void quickSortHelper(vector<int>& data, int low, int high)
    {
        if (low >= high) return;

        int pivotVal = data[(low + high) / 2];
        int left = low, right = high;

        while (left <= right) {
            while (data[left] < pivotVal) ++left;
            while (data[right] > pivotVal) --right;
            if (left <= right) {
                swap(data[left], data[right]);
                ++left;
                --right;
            }
        }
        if (low < right) quickSortHelper(data, low, right);
        if (left < high) quickSortHelper(data, left, high);
    }
}

void quickSort(vector<int> arr)
{
    if (arr.empty()) return;
    quickSortHelper(arr, 0, arr.size() - 1);
}

/*-------------------------------------------------
  3. Merge Sort（Top-down）
-------------------------------------------------*/
namespace {
    void mergeParts(vector<int>& arr, int left, int mid, int right)
    {
        vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

        int idxL = 0, idxR = 0, idxMerge = left;

        while (idxL < leftArr.size() && idxR < rightArr.size()) {
            if (leftArr[idxL] <= rightArr[idxR]) {
                arr[idxMerge++] = leftArr[idxL++];
            } else {
                arr[idxMerge++] = rightArr[idxR++];
            }
        }
        while (idxL < leftArr.size()) arr[idxMerge++] = leftArr[idxL++];
        while (idxR < rightArr.size()) arr[idxMerge++] = rightArr[idxR++];
    }

    void mergeSortHelper(vector<int>& arr, int left, int right)
    {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        mergeParts(arr, left, mid, right);
    }
}

void mergeSort(vector<int> arr)
{
    if (arr.size() > 1)
        mergeSortHelper(arr, 0, arr.size() - 1);
}

/*-------------------------------------------------
  4. Heap Sort（STL實作）
-------------------------------------------------*/
void heapSort(vector<int> arr)
{
    if (arr.empty()) return;
    push_heap(arr.begin(), arr.end());
    sort_heap(arr.begin(), arr.end());
}

/*-------------------------------------------------
  5. Composite Sort（IntroSort）
-------------------------------------------------*/
namespace {
    const int INSERTION_LIMIT = 16;

    void insertionSortSection(vector<int>& arr, int left, int right)
    {
        for (int i = left + 1; i <= right; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    void introSortHelper(vector<int>& arr, int left, int right, int maxDepth)
    {
        if (right - left + 1 <= INSERTION_LIMIT) {
            insertionSortSection(arr, left, right);
            return;
        }
        if (maxDepth == 0) {
            make_heap(arr.begin() + left, arr.begin() + right + 1);
            sort_heap(arr.begin() + left, arr.begin() + right + 1);
            return;
        }

        int mid = left + (right - left) / 2;
        if (arr[left] > arr[mid]) swap(arr[left], arr[mid]);
        if (arr[left] > arr[right]) swap(arr[left], arr[right]);
        if (arr[mid] > arr[right]) swap(arr[mid], arr[right]);
        int pivot = arr[mid];
        swap(arr[mid], arr[right - 1]);

        int i = left, j = right - 1;
        while (true) {
            while (arr[++i] < pivot);
            while (arr[--j] > pivot);
            if (i >= j) break;
            swap(arr[i], arr[j]);
        }
        swap(arr[i], arr[right - 1]);

        introSortHelper(arr, left, i - 1, maxDepth - 1);
        introSortHelper(arr, i + 1, right, maxDepth - 1);
    }
}

void compositeSort(vector<int> arr)
{
    if (arr.size() <= 1) return;
    int maxDepth = 2 * log2(arr.size());
    introSortHelper(arr, 0, arr.size() - 1, maxDepth);
}