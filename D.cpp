#include <cmath>
#include <iostream>

void siftDown(unsigned int* a, int v, int size) {
  while (2 * v + 1 < size) {
    int u = 2 * v + 1;
    if (u + 1 < size && a[u] > a[u + 1]) {
      ++u;
    }
    if (a[v] <= a[u]) {
      break;
    }
    std::swap(a[v], a[u]);
    v = u;
  }
}

void reverse(unsigned int* a, int size) {
  for (int i = 0; i < size / 2; ++i) {
    std::swap(a[i], a[size - i - 1]);
  }
}

void heapify(unsigned int* a, int size) {
  for (int i = size - 1; i >= 0; --i) {
    siftDown(a, i, size);
  }
}

int extractMin(unsigned int* a, int size) {
  size--;
  int min_val = a[0];
  std::swap(a[0], a[size--]);
  siftDown(a, 0, size);
  return min_val;
}

void MyHeapSort(unsigned int* a, int size) {
  int cur = size;
  heapify(a, size);
  for (int i = 0; i < size; ++i) {
    extractMin(a,cur--);
  }
  reverse(a, size);
}

unsigned int* Merge(unsigned int* a, unsigned int* b, int k, int size_a, int size_b) {
  unsigned int* d = new unsigned int[k];
  int i = 0, j = 0;
  for (int id = 0; id < k; ++id) {
    if (i < size_a && j < size_b) {
      if (a[i] <= b[j]) {
        d[id] = a[i];
        ++i;
      } else {
        d[id] = b[j];
        ++j;
      }
    } else if (i < size_a) {
      d[id] = a[i];
      ++i;
    } else if (j < size_b) {
      d[id] = b[j];
      ++j;
    }
  }
  return d;
}

int main() {
  int n, k;
  unsigned int a0, x, y;
  std::cin >> n >> k >> a0 >> x >> y;
  unsigned int a[10000];
  a[0] = (x * a0 + y) % static_cast<long long>(std::pow(2, 30));;
  for (int i = 1; i < n; ++i) {
    a[i] = (x * a[i - 1] + y) % static_cast<long long>(std::pow(2, 30));
  }
  for (int i = 0; i <= (n - 1) / k; ++i) {
    MyHeapSort(a + i * k, std::min(k, n - i * k));
  }
  unsigned int* c = Merge(a, a + k, k, k, std::min(k, n - k));
  for (int i = 2; i <= (n - 1) / k; ++i) {
    c = Merge(c, a + i * k, k, k, std::min(k, n - i * k));
  }
  for (int i = 0; i < k; ++i) {
    std::cout << c[i] << ' ';
  }
  delete[] c;
  return 0;
}