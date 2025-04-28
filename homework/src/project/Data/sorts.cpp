#include "sorts.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Insertion Sort

void insertionSort(vector<int> arr)
{
    int len = int(arr.size());
    for (int i = 1; i < len; ++i) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

//Quick Sort

namespace {
    void quickRec(vector<int>& a, int l, int r)
    {
        if (l >= r) return;
        int pivot = a[(l + r) / 2];
        int i = l, j = r;
        while (i <= j) {
            while (a[i] < pivot) ++i;
            while (a[j] > pivot) --j;
            if (i <= j) swap(a[i++], a[j--]);
        }
        quickRec(a, l, j);
        quickRec(a, i, r);
    }
}

void quickSort(vector<int> arr)
{
    if (!arr.empty()) {
        quickRec(arr, 0, int(arr.size()) - 1);
    }
}

//Merge Sort

namespace {
    void mergeParts(vector<int>& a, int l, int m, int r)
    {
        vector<int> L(a.begin() + l, a.begin() + m + 1),
            R(a.begin() + m + 1, a.begin() + r + 1);
        int i = 0, j = 0, k = l;
        while (i < int(L.size()) && j < int(R.size()))
            a[k++] = (L[i] <= R[j] ? L[i++] : R[j++]);
        while (i < int(L.size())) a[k++] = L[i++];
        while (j < int(R.size())) a[k++] = R[j++];
    }

    void mergeRec(vector<int>& a, int l, int r)
    {
        if (l >= r) return;
        int m = l + (r - l) / 2;
        mergeRec(a, l, m);
        mergeRec(a, m + 1, r);
        mergeParts(a, l, m, r);
    }
}

void mergeSort(vector<int> arr)
{
    if (arr.size() > 1) {
        mergeRec(arr, 0, int(arr.size()) - 1);
    }
}

// Heap Sort

void heapSort(vector<int> arr)
{
    if (arr.empty()) return;
    make_heap(arr.begin(), arr.end());
    sort_heap(arr.begin(), arr.end());
}

//Composite Sort

namespace {
    const int INSERTION_LIMIT = 16;

    void insertionSection(vector<int>& a, int l, int r)
    {
        for (int i = l + 1; i <= r; ++i) {
            int key = a[i], j = i - 1;
            while (j >= l && a[j] > key)
                a[j + 1] = a[j--];
            a[j + 1] = key;
        }
    }

    void introRec(vector<int>& a, int l, int r, int depth)
    {
        if (r - l + 1 <= INSERTION_LIMIT) {
            insertionSection(a, l, r);
            return;
        }
        if (depth == 0) {
            make_heap(a.begin() + l, a.begin() + r + 1);
            sort_heap(a.begin() + l, a.begin() + r + 1);
            return;
        }
        int m = l + (r - l) / 2;
        if (a[l] > a[m]) swap(a[l], a[m]);
        if (a[l] > a[r]) swap(a[l], a[r]);
        if (a[m] > a[r]) swap(a[m], a[r]);
        int pivot = a[m];
        swap(a[m], a[r - 1]);
        int i = l, j = r - 1;
        while (true) {
            while (a[++i] < pivot);
            while (a[--j] > pivot);
            if (i >= j) break;
            swap(a[i], a[j]);
        }
        swap(a[i], a[r - 1]);
        introRec(a, l, i - 1, depth - 1);
        introRec(a, i + 1, r, depth - 1);
    }
}

void compositeSort(vector<int> arr)
{
    if (arr.size() <= 1) return;
    int maxDepth = 2 * log2(arr.size());
    introRec(arr, 0, int(arr.size()) - 1, maxDepth);
}
