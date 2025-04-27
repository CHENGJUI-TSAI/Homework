#include "sorts.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;
using Clock = chrono::high_resolution_clock;

//--------------------------------------------------
// 隨機打亂 Permute
//--------------------------------------------------
template <class T>
void Permute(T* a, int n)
{
    for (int i = n - 1; i >= 1; --i) {
        int j = rand() % (i + 1);  // j in [0, i]
        swap(a[j], a[i]);
    }
}

//--------------------------------------------------
// 印出記憶體使用量
//--------------------------------------------------
void printMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS memInfo{};
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));

    cout << "----------------------------------------------------------\n";
    cout << "Memory Usage Information:\n";
    cout << "Working Set Size:      " << memInfo.WorkingSetSize / 1024 << " KB\n";
    cout << "Peak Working Set Size: " << memInfo.PeakWorkingSetSize / 1024 << " KB\n";
    cout << "Pagefile Usage:        " << memInfo.PagefileUsage / 1024 << " KB\n";
    cout << "----------------------------------------------------------\n";
}

//--------------------------------------------------
// 測試排序
//--------------------------------------------------
void runAndMeasure(void (*sortFunc)(vector<int>), const vector<int>& original)
{
    const int REPEAT = 10;
    long long total = 0, worst = 0;

    for (int i = 0; i < REPEAT; ++i) {
        auto t1 = Clock::now();
        sortFunc(original);  // 傳 original，sortFunc 會自己 copy
        auto t2 = Clock::now();
        long long us = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        total += us;
        worst = max(worst, us);
    }

    cout << "Avg   " << total / double(REPEAT) / 1000.0
        << " ms | Worst "
        << worst / 1000.0 << " ms\n";
    printMemoryUsage();
}

//--------------------------------------------------
// main
//--------------------------------------------------
int main()
{
    srand(unsigned(time(nullptr)));

    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };

    for (int n : sizes) {
        cout << "== n = " << n << " ==\n";
        vector<int> data(n);
        for (int i = 0; i < n; ++i)
            data[i] = i + 1;
        Permute(data.data(), n);

        cout << "[Insertion]  "; runAndMeasure(insertionSort, data);
        cout << "[Quick]      "; runAndMeasure(quickSort, data);
        cout << "[Merge]      "; runAndMeasure(mergeSort, data);
        cout << "[Heap]       "; runAndMeasure(heapSort, data);
        cout << "[Composite]  "; runAndMeasure(compositeSort, data);
        cout << "===========================\n";
    }

    cout << "按 Enter 結束...";
    cin.ignore();
    cin.get();
    return 0;
}
