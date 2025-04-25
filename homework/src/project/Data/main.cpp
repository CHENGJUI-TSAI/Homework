//=============================
// main.cpp － 單一檔案版
//=============================
#include "sorts.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;
using Clock = chrono::high_resolution_clock;

//--------------------------------------------------
// 印出目前行程的記憶體使用量
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
// 重複 REPEAT 次排序並量測時間＋記憶體
//--------------------------------------------------
void runAndMeasure(void (*sortFunc)(vector<int>), const vector<int>& original)
{
    const int REPEAT = 10;
    long long total = 0, worst = 0;

    for (int i = 0; i < REPEAT; ++i) {
        vector<int> data = original;          // 每回合用 copy 保持資料一致
        auto t1 = Clock::now();
        sortFunc(data);
        auto t2 = Clock::now();
        long long us = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        total += us;
        worst = max(worst, us);
    }

    double avg_ms = total / double(REPEAT) / 1000.0;
    double worst_ms = worst / 1000.0;

    cout << "Avg " << avg_ms << " ms | "
        << "Worst " << worst_ms << " ms\n";

    printMemoryUsage();                     // 直接輸出你要的區塊
}

//--------------------------------------------------
// 入口
//--------------------------------------------------
int main()
{
    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };
    mt19937 gen(random_device{}());
    uniform_int_distribution<> dist(0, 1'000'000);

    for (int n : sizes) {
        cout << "== n = " << n << " ==\n";
        vector<int> data(n);
        for (auto& x : data) x = dist(gen);

        cout << "[Insertion]  "; runAndMeasure(insertionSort, data);
        cout << "[Quick]      "; runAndMeasure(quickSort, data);
        cout << "[Merge]      "; runAndMeasure(mergeSort, data);
        cout << "[Heap]       "; runAndMeasure(heapSort, data);
        cout << "[Composite]  "; runAndMeasure(compositeSort, data);
        cout << "===========================\n";
    }

    cout << "按 Enter 結束..."; cin.get();
    return 0;
}
