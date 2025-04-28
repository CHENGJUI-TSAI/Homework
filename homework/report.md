# 41243252
# 41243249

作業一

## 解題說明

本題結合題目要求排序法，計算排序執行時間。

### 解題策略

1.Insertion Sort

將陣列分成「已排序區段」和「待排序區段」。
依序把每個新元素插入到前面已排序的正確位置。

2.Quick Sort

選一個 pivot（此版用區段中點元素）。
把陣列分成「小於 pivot」和「大於 pivot」兩部分，並遞迴排序這兩個子區段。

3.Merge Sort

不斷把陣列二分成左右兩半。
對左右半部各自遞迴排序，然後把兩個已排序序列「合併」成一個。

4.Heap Sort

先用 make_heap 建立最大（或最小）堆。
再用 sort_heap 逐步取出堆頂元素，完成排序。

5.Composite Sort (IntroSort)

對小區段（≤16 元素）直接用插入排序，減少遞迴開銷。
設定深度上限 2·log₂(n)：
當遞迴深度耗盡時，切換到堆排序，避免最壞情況退化。
否則，使用三取中法選 pivot，照快速排序流程繼續遞迴。
## 程式實作

以下為主要程式碼：

### Insertion Sort
```cpp
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
```


### Quick Sort 

```cpp
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
```


### Merge Sort 

```cpp
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
```


### Heap Sort

```cpp
void heapSort(vector<int> arr)
{
    if (arr.empty()) return;
    make_heap(arr.begin(), arr.end());
    sort_heap(arr.begin(), arr.end());
}
```



## 測試與驗證

#### 生成隨機數列
```cpp
template <class T>
void Permute(T* a, int n)
{
    for (int i = n - 1; i >= 1; --i) {
        int j = rand() % (i + 1);  
        swap(a[j], a[i]);
    }
}
```


#### 計算執行時間
```cpp
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

const char* names[] = { "Insertion Sort", "Quick Sort    ", "Merge Sort    ", "Heap Sort     " };
for (int i = 0; i < 4; ++i)
{
    double avg = 0;
    for (double x : times[i]) avg += x;
    avg /= times[i].size();
    printf("%s - Worst: %.2f microseconds, Avg: %.2f microseconds\n", names[i], worst[i], avg);
    printMemoryUsage();
}
```


#### 重複測量排序時間
```cpp
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
```
測量結果簡要驗證了各演算法的理論複雜度：

1.插入排序耗時隨資料規模呈二次增長（O(n²)）；

2.快速排序、合併排序、堆積排序的平均／最差時間均隨 n log n 緩增；

3.複合排序在所有規模下耗時最少，也符合其優化組合策略的高效性。

### 測試案例
```
== n = 500 ==
[Insertion]  Avg   0.5494 ms | Worst 0.578 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4544 KB
Peak Working Set Size: 4544 KB
Pagefile Usage:        696 KB
----------------------------------------------------------
[Quick]      Avg   0.0846 ms | Worst 0.098 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4560 KB
Peak Working Set Size: 4560 KB
Pagefile Usage:        696 KB
----------------------------------------------------------
[Merge]      Avg   1.5499 ms | Worst 2.122 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4572 KB
Peak Working Set Size: 4572 KB
Pagefile Usage:        696 KB
----------------------------------------------------------
[Heap]       Avg   0.0741 ms | Worst 0.155 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4572 KB
Peak Working Set Size: 4572 KB
Pagefile Usage:        696 KB
----------------------------------------------------------
[Composite]  Avg   0.0449 ms | Worst 0.139 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4580 KB
Peak Working Set Size: 4580 KB
Pagefile Usage:        696 KB
----------------------------------------------------------
===========================
== n = 1000 ==
[Insertion]  Avg   2.2429 ms | Worst 2.495 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4584 KB
Peak Working Set Size: 4584 KB
Pagefile Usage:        700 KB
----------------------------------------------------------
[Quick]      Avg   0.1095 ms | Worst 0.119 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4584 KB
Peak Working Set Size: 4584 KB
Pagefile Usage:        700 KB
----------------------------------------------------------
[Merge]      Avg   2.4799 ms | Worst 3.663 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4588 KB
Peak Working Set Size: 4588 KB
Pagefile Usage:        704 KB
----------------------------------------------------------
[Heap]       Avg   0.1461 ms | Worst 0.204 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4588 KB
Peak Working Set Size: 4588 KB
Pagefile Usage:        704 KB
----------------------------------------------------------
[Composite]  Avg   0.1037 ms | Worst 0.189 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4592 KB
Peak Working Set Size: 4592 KB
Pagefile Usage:        708 KB
----------------------------------------------------------
===========================
== n = 2000 ==
[Insertion]  Avg   9.3341 ms | Worst 10.522 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4600 KB
Peak Working Set Size: 4600 KB
Pagefile Usage:        716 KB
----------------------------------------------------------
[Quick]      Avg   0.2841 ms | Worst 0.377 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4600 KB
Peak Working Set Size: 4600 KB
Pagefile Usage:        716 KB
----------------------------------------------------------
[Merge]      Avg   5.1943 ms | Worst 5.851 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4608 KB
Peak Working Set Size: 4608 KB
Pagefile Usage:        724 KB
----------------------------------------------------------
[Heap]       Avg   0.388 ms | Worst 0.506 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4608 KB
Peak Working Set Size: 4608 KB
Pagefile Usage:        724 KB
----------------------------------------------------------
[Composite]  Avg   0.2126 ms | Worst 0.255 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4612 KB
Peak Working Set Size: 4612 KB
Pagefile Usage:        728 KB
----------------------------------------------------------
===========================
== n = 3000 ==
[Insertion]  Avg   25.7818 ms | Worst 30.662 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4620 KB
Peak Working Set Size: 4620 KB
Pagefile Usage:        740 KB
----------------------------------------------------------
[Quick]      Avg   0.4256 ms | Worst 0.45 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4620 KB
Peak Working Set Size: 4620 KB
Pagefile Usage:        740 KB
----------------------------------------------------------
[Merge]      Avg   7.6704 ms | Worst 8.524 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4632 KB
Peak Working Set Size: 4632 KB
Pagefile Usage:        748 KB
----------------------------------------------------------
[Heap]       Avg   0.4874 ms | Worst 0.531 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4632 KB
Peak Working Set Size: 4632 KB
Pagefile Usage:        748 KB
----------------------------------------------------------
[Composite]  Avg   0.3218 ms | Worst 0.35 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4632 KB
Peak Working Set Size: 4632 KB
Pagefile Usage:        748 KB
----------------------------------------------------------
===========================
== n = 4000 ==
[Insertion]  Avg   41.4422 ms | Worst 53.406 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4632 KB
Peak Working Set Size: 4632 KB
Pagefile Usage:        748 KB
----------------------------------------------------------
[Quick]      Avg   0.497 ms | Worst 0.509 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4632 KB
Peak Working Set Size: 4632 KB
Pagefile Usage:        748 KB
----------------------------------------------------------
[Merge]      Avg   9.5312 ms | Worst 10.125 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4640 KB
Peak Working Set Size: 4640 KB
Pagefile Usage:        756 KB
----------------------------------------------------------
[Heap]       Avg   0.6435 ms | Worst 0.71 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4640 KB
Peak Working Set Size: 4640 KB
Pagefile Usage:        756 KB
----------------------------------------------------------
[Composite]  Avg   0.4213 ms | Worst 0.509 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4640 KB
Peak Working Set Size: 4640 KB
Pagefile Usage:        756 KB
----------------------------------------------------------
===========================
== n = 5000 ==
[Insertion]  Avg   57.7066 ms | Worst 61.081 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4624 KB
Peak Working Set Size: 4668 KB
Pagefile Usage:        740 KB
----------------------------------------------------------
[Quick]      Avg   0.6752 ms | Worst 0.822 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4624 KB
Peak Working Set Size: 4668 KB
Pagefile Usage:        740 KB
----------------------------------------------------------
[Merge]      Avg   11.8603 ms | Worst 12.664 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4628 KB
Peak Working Set Size: 4668 KB
Pagefile Usage:        744 KB
----------------------------------------------------------
[Heap]       Avg   0.7793 ms | Worst 0.806 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4648 KB
Peak Working Set Size: 4668 KB
Pagefile Usage:        776 KB
----------------------------------------------------------
[Composite]  Avg   0.5395 ms | Worst 0.621 ms
----------------------------------------------------------
Memory Usage Information:
Working Set Size:      4628 KB
Peak Working Set Size: 4668 KB
Pagefile Usage:        744 KB
----------------------------------------------------------
===========================
```


平均時間
| n   | Insertion | Quick  | Merge  | Heap   | Composite |
|-----|-----------|--------|--------|--------|-----------|
| 500 | 0.5494    | 0.0846 | 1.5499 | 0.0741 | 0.0449    |
|1000 | 2.2429	  | 0.1095 | 2.4799	| 0.1461 | 0.1037    |
|2000 |	9.3341    |	0.2841 | 5.1943	| 0.3880 | 0.2126    |   
|3000 |	25.7818	  | 0.4256 | 7.6704	| 0.4874 | 0.3218    |
|4000 |	41.4422	  | 0.4970 | 9.5312	| 0.6435 | 0.4213    |
|5000 |	57.7066	  | 0.6752 | 11.8603| 0.7793 | 0.5395    |

最差時間
| n   | Insertion | Quick  | Merge  | Heap   | Composite |
|-----|-----------|--------|--------|--------|-----------|
| 500 | 0.578	  | 0.098  | 2.122	| 0.155	 | 0.139     |
| 1000|	2.495	  | 0.119  | 3.663	| 0.204	 | 0.189     |
| 2000|	10.522	  | 0.377  | 5.851	| 0.506	 | 0.255     |
| 3000|	30.662	  | 0.45   | 8.524	| 0.531	 | 0.35      |
| 4000|	53.406	  | 0.509  | 10.125	| 0.71	 | 0.509     |
| 5000|	61.081	  | 0.822  | 12.664	| 0.806	 | 0.621     |


## 效能分析

| 排序演算法     | 最佳時間複雜度     | 平均時間複雜度    | 最差時間複雜度     | 空間複雜度               |
|---------------|--------------------|-------------------|--------------------|--------------------------|
| 插入排序      | O(n)               | O(n²)             | O(n²)              | O(1)            |
| 快速排序      | O(n log n)         | O(n log n)        | O(n²)              | O(log n)       |
| 合併排序      | O(n log n)         | O(n log n)        | O(n log n)         | O(n)        |
| 堆積排序      | O(n log n)         | O(n log n)        | O(n log n)         | O(1)             |
| 複合排序      | O(n) / O(n log n)  | O(n log n)        | O(n log n)         | O(n) / O(log n)          |

![worst_time_chart 折線圖](https://github.com/CHENGJUI-TSAI/Homework/blob/main/homework/src/images/worst_time_chart.png)
![average_time_chart 折線圖](https://github.com/CHENGJUI-TSAI/Homework/blob/main/homework/src/images/average_time_chart.png)

## 結論

1. 測驗結果顯示，插入排序適合在小規模資料（n ≤ 500），但隨 n 增大，其執行時間快速惡化，完全符合 O(n²) 的二次增長特性。

2.快速排序、合併排序與堆積排序在中、大規模資料（n ≥ 1000）下均展現穩定的 O(n log n) 性能，其中快速排序因較低的常數而通常最快，但最差 
  情況下可能退化至 O(n²)；合併排序最差情況亦為 O(n log n)；堆積排序則在記憶體使用上最省。

3.複合排序透過切換至插入排序處理小區間，並在較大區塊中套用分治策略，實測平均與最差均優於單一演算法，驗證其在混合場景下的優越性。



## 應用建議

小資料量（n < 1000）：可優先考慮複合排序或插入排序，以簡單、低常數因子獲得最好效能。

中大型資料量（1000 ≤ n ≤ 10⁶）：可考慮快速排序與合併排序，若需最差時間保證，合併排序更為穩健；若記憶體受限，則考慮堆積排序。

極大規模（n ≫ 10⁶）或分散式場景：合併排序易於並行化分割，若有多執行緒／多核環境，可進一步採用多路合併或外部排序技術。

## 申論及開發報告

std::vector<int>
使用資料結構原因：

C++ 的 std::vector 提供動態陣列功能，可自動管理記憶體。

支援隨機存取（O(1)時間複雜度）與彈性大小調整，適合各種規模的排序測試。

內建與 STL 演算法（如 make_heap, sort_heap）相容，方便使用 STL 函式提升效率。


使用的演算法與原因

(1) Insertion Sort
適用小型資料。

時間複雜度 O(n²)，但在資料量小或幾乎有序時表現良好。

(2) Quick Sort
適合大部分一般資料。

平均時間複雜度 O(n log n)，遞迴實作，pivot 選中間元素。

簡單快速，但最差情況為 O(n²)。

(3) Merge Sort
穩定且適合大型資料。

時間複雜度穩定為 O(n log n)，但需要額外 O(n) 空間。

適合大量資料且需要穩定排序的情境。

(4) Heap Sort
不需要額外空間的 O(n log n) 排序。

使用 std::make_heap 和 std::sort_heap。

不穩定排序，但記憶體效率佳，適合空間受限情況。

(5) Composite Sort 
結合多種排序法的自適應排序。

初期使用 Quick Sort，當遞迴層數過深時切換為 Heap Sort。

小範圍內使用 Insertion Sort 優化。

兼具 Quick Sort 的快與 Heap Sort 的穩，避免 Quick Sort 最差情形。
