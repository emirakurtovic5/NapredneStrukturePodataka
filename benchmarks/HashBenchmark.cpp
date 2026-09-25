#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

#include "HashTable.h"

using namespace std;
using namespace chrono;

void runBenchmark(const vector<int>& values, const string& scenario) {
    int n = static_cast<int>(values.size());

    HashTable<int> table;

    // INSERT
    auto start = high_resolution_clock::now();

    for (int value : values) {
        table.insert(value);
    }

    auto end = high_resolution_clock::now();

    double insertTime =
        duration_cast<duration<double, milli>>(end - start).count();

    // SEARCH
    start = high_resolution_clock::now();

    for (int value : values) {
        table.contains(value);
    }

    end = high_resolution_clock::now();

    double searchTime =
        duration_cast<duration<double, milli>>(end - start).count();

    // REMOVE
    start = high_resolution_clock::now();

    for (int value : values) {
        table.remove(value);
    }

    end = high_resolution_clock::now();

    double removeTime =
        duration_cast<duration<double, milli>>(end - start).count();

    cout << scenario
         << " | N = " << n
         << " | Insert: " << insertTime << " ms"
         << " | Search: " << searchTime << " ms"
         << " | Remove: " << removeTime << " ms"
         << endl;
}

int main() {

    vector<int> sizes = {
        1000,
        10000,
        100000,
        1000000
    };

    random_device rd;
    mt19937 generator(rd());

    // NASUMIČAN REDOSLIJED
    cout << "Random order:" << endl;

    for (int n : sizes) {
        vector<int> values;

        for (int i = 1; i <= n; ++i) {
            values.push_back(i);
        }

        shuffle(values.begin(), values.end(), generator);

        runBenchmark(values, "Random");
    }

    cout << endl;

    // SORTIRAN RASTUĆI REDOSLIJED
    cout << "Sorted increasing order:" << endl;

    for (int n : sizes) {
        vector<int> values;

        for (int i = 1; i <= n; ++i) {
            values.push_back(i);
        }

        runBenchmark(values, "Sorted");
    }

    return 0;
}