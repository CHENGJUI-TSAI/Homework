# Homework Sorting Project
## 組員

41243204 張品薰
41243205 黃詩方

---

此報告展示對多種排序算法進行的實作與性能分析。包括對以下排序算法的討論與實作：

- **Insertion Sort**
- **Quick Sort** (使用 median-of-three 方法選擇樞軸)
- **Merge Sort** (使用迭代方法)
- **Heap Sort**
- **Composite Sort** (綜合多種排序法)

## 1. 分析與討論

### Worst-case 與 Average-case 討論

- **Insertion Sort:**
  - **Worst-case**: 當數列逆序時，最差情況下需要進行 n*(n-1)/2 次比較與交換。其時間複雜度為 O(n²)。
  - **Average-case**: 當數列是隨機排列時，平均情況下時間複雜度也是 O(n²)。
  
- **Quick Sort:**
  - **Worst-case**: Quick Sort將排序邏輯反轉，逆推出 worst-case的時間複雜度為 O(n²)。
  - **Average-case**: 在隨機數列中，Quick Sort 的時間複雜度為 O(n log n)。

- **Merge Sort:**
  - **Worst-case**: Merge Sort 的時間複雜度為 O(n log n)，無論數列如何排列。
  - **Average-case**: 由於 Merge Sort 每次都將數列分成兩半並進行合併，時間複雜度始終為 O(n log n)。

- **Heap Sort:**
  - **Worst-case**: Heap Sort 的時間複雜度為 O(n log n)，無論數列如何排列。
  - **Average-case**: Heap Sort 也保持在 O(n log n) 的時間複雜度。

- **Composite Sort**: 綜合了多種排序法，針對不同的輸入資料使用最合適的排序方法，以達到最短的排序時間。
