//=============================
// sort.cpp   (簡約版，效仿範例迴圈寫法)
//=============================
#include "sorts.h"
#include <algorithm>
#include <vector>
#include <cmath>   // log2
using std::swap;
using std::vector;

/*-------------------------------------------------
  1. Insertion Sort
-------------------------------------------------*/
void insertionSort(vector<int> arr)
{
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

/*-------------------------------------------------
  2. Quick Sort（median-of-three 版留給 Composite）
-------------------------------------------------*/
namespace {
    void quickRec(vector<int>& arr, int left, int right)
    {
        if (left >= right) return;

        int pivot = arr[(left + right) / 2];
        int i = left, j = right;

        while (i <= j) {
            while (arr[i] < pivot) ++i;
            while (arr[j] > pivot) --j;
            if (i <= j) swap(arr[i++], arr[j--]);
        }
        quickRec(arr, left, j);
        quickRec(arr, i, right);
    }
}

void quickSort(vector<int> arr)
{
    if (!arr.empty())
        quickRec(arr, 0, static_cast<int>(arr.size()) - 1);
}

/*-------------------------------------------------
  3. Merge Sort（Top-down）
-------------------------------------------------*/
namespace {
    void merge(vector<int>& a, int l, int m, int r)
    {
        vector<int> L(a.begin() + l, a.begin() + m + 1);
        vector<int> R(a.begin() + m + 1, a.begin() + r + 1);

        int i = 0, j = 0, k = l;
        while (i < (int)L.size() && j < (int)R.size())
            a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        while (i < (int)L.size()) a[k++] = L[i++];
        while (j < (int)R.size()) a[k++] = R[j++];
    }

    void mergeRec(vector<int>& a, int l, int r)
    {
        if (l >= r) return;
        int m = (l + r) / 2;
        mergeRec(a, l, m);
        mergeRec(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void mergeSort(vector<int> arr)
{
    if (arr.size() > 1)
        mergeRec(arr, 0, static_cast<int>(arr.size()) - 1);
}

/*-------------------------------------------------
  4. Heap Sort（STL make_heap / sort_heap）
-------------------------------------------------*/
void heapSort(vector<int> arr)
{
    std::make_heap(arr.begin(), arr.end());
    std::sort_heap(arr.begin(), arr.end());
}

/*-------------------------------------------------
  5. Composite Sort ＝ IntroSort
     - 小區段改插入
     - 遞迴深度用 2*log2(n)，超過時改 Heap
-------------------------------------------------*/
namespace {
    const int CUTOFF = 16;

    void insertionSmall(vector<int>& a, int l, int r)
    {
        for (int i = l + 1; i <= r; ++i) {
            int key = a[i], j = i - 1;
            while (j >= l && a[j] > key) a[j + 1] = a[j--];
            a[j + 1] = key;
        }
    }

    void introRec(vector<int>& a, int l, int r, int depth)
    {
        if (r - l + 1 <= CUTOFF) {          // 小陣列直接插入
            insertionSmall(a, l, r);
            return;
        }
        if (depth == 0) {                   // 超深度 -> Heap
            std::make_heap(a.begin() + l, a.begin() + r + 1);
            std::sort_heap(a.begin() + l, a.begin() + r + 1);
            return;
        }
        /* median-of-three pivot */
        int m = (l + r) / 2;
        if (a[l] > a[m]) swap(a[l], a[m]);
        if (a[l] > a[r]) swap(a[l], a[r]);
        if (a[m] > a[r]) swap(a[m], a[r]);
        int pivot = a[m];
        swap(a[m], a[r - 1]);               // pivot 到 r-1

        int i = l, j = r - 1;
        while (true) {
            while (a[++i] < pivot) {}
            while (a[--j] > pivot) {}
            if (i >= j) break;
            swap(a[i], a[j]);
        }
        swap(a[i], a[r - 1]);               // 還原 pivot

        introRec(a, l, i - 1, depth - 1);
        introRec(a, i + 1, r, depth - 1);
    }
}

void compositeSort(vector<int> arr)
{
    if (arr.size() <= 1) return;
    int depthLimit = static_cast<int>(2 * std::log2(arr.size()));
    introRec(arr, 0, static_cast<int>(arr.size()) - 1, depthLimit);
}
