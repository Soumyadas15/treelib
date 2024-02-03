#include <iostream>
#include <vector>
  using namespace std;

template <typename T>
class fenwick {
  public:
    vector<T> fenw;
    int n;
    fenwick(int _n) : n(_n + 1) fenw.resize(n);

    void modify(int x, T v) {
        while (x <= n) {
            fenw[x] += v;
            x += (x & -x);
        }
    }

    T get(int x) {
        T v{};
        while (x > 0) {
            v += fenw[x];
            x -= (x & -x);
        }
        return v;
    }
};
