#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

int main(){
    auto start = high_resolution_clock::now();

    cout << "Hello, World2!\n";
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Execution time: " << duration.count() << " microseconds\n";
    return 0;
}