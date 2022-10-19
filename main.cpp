#include <algorithm>
#include <iostream>

struct Heap {
    int a[100000] = {};
    int size;
     Heap() { size = 0; }

     void Insert(int x) {
       a[size++] = x;
       SiftUp(size);
     }

     void SiftUp(int n) {
       while ((n - 1) / 2 != 0 && a[(n - 1) / 2] > a[n]) {
         std::swap(a[n], a[(n - 1) / 2]);
         n = (n - 1) / 2;
       }
     }

     void SiftDown(int n) {
       while (2 * n + 1 <= size) {
         if (2 * n + 2 <= n && a[2 * n + 2] < a[2 * n + 1] && a[n] > a[2 * n + 2]) {
           std::swap(a[n], a[2 * n + 2]);
           n = 2 * n + 2;
         } else if (a[n] > a[2 * n + 1]) {
           std::swap(a[n], a[2 * n + 1]);
           n = 2 * n + 1;
         } else {
           break;
         }
       }
     }

     int GetMin() {
       return a[0];
     }

     int ExtractMin() {
       int min_val = a[0];
       std::swap(a[0], a[size--]);
       SiftDown(0);
       return min_val;
     }

     void DecreaseKey(int i, int delta) {}
};