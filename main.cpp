#include <bits/stdc++.h>
#include "FenwickTree.h"
#include "PrefixTree.h"

using namespace std;

void test() {
    int n = 8;
    vector <int> ar(n, 0);
    fenwick <int> f(8);
    for(int i = 0 ; i < (int) ar.size() ; ++i) f.modify(i + 1 ,ar[i]);
    f.modify(6, 3);

    cout << "Update 1: ";
    for (int i = 0; i < n; ++i) cout << f.get(i) - f.get(i - 1) << " ";
    cout << endl;

    cout << "Query 1: " << f.get(6 + 1) - f.get(0) << endl;

    f.modify(3, 2);
    f.modify(8, -2);

    cout << "Update 2: ";
    for (int i = 0; i < n; ++i) cout << f.get(i) - f.get(i - 1) << " ";
    cout << endl;

    cout << "Query 2:" << f.get(5 + 1) - f.get(1) << endl;

}

int main(){
    test();
    return 0;
}