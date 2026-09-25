#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "RedBlackTree.h"

using namespace std;
using namespace std::chrono;

vector<int> createData(int n) {
    vector<int> data(n);

    for (int i = 0; i < n; ++i) {
        data[i] = i + 1;
    }

    return data;
}

double benchmarkInsert(const vector<int>& data) {
    RedBlackTree<int> tree;

    auto start = high_resolution_clock::now();

    for (int value : data) {
        tree.insert(value);
    }

    auto end = high_resolution_clock::now();

    return duration<double, milli>(end - start).count();
}

double benchmarkSearch(const vector<int>& data) {
    RedBlackTree<int> tree;

    for (int value : data) {
        tree.insert(value);
    }

    auto start = high_resolution_clock::now();

    for (int value : data) {
        tree.contains(value);
    }

    auto end = high_resolution_clock::now();

    return duration<double, milli>(end - start).count();
}

double benchmarkRemove(const vector<int>& data) {
    RedBlackTree<int> tree;

    for (int value : data) {
        tree.insert(value);
    }

    auto start = high_resolution_clock::now();

    for (int value : data) {
        tree.remove(value);
    }

    auto end = high_resolution_clock::now();

    return duration<double, milli>(end - start).count();
}

void runBenchmark(int n, mt19937& generator) {
    vector<int> sortedData = createData(n);
    vector<int> randomData = sortedData;

    shuffle(
        randomData.begin(),
        randomData.end(),
        generator
    );

    cout << "N = " << n << endl;

    double insertRandom = benchmarkInsert(randomData);
    double searchRandom = benchmarkSearch(randomData);
    double removeRandom = benchmarkRemove(randomData);

    cout << "Nasumican redoslijed:" << endl;
    cout << "insert: " << insertRandom << " ms" << endl;
    cout << "search: " << searchRandom << " ms" << endl;
    cout << "remove: " << removeRandom << " ms" << endl;

    double insertSorted = benchmarkInsert(sortedData);
    double searchSorted = benchmarkSearch(sortedData);
    double removeSorted = benchmarkRemove(sortedData);

    cout << "Sortiran rastuci redoslijed:" << endl;
    cout << "insert: " << insertSorted << " ms" << endl;
    cout << "search: " << searchSorted << " ms" << endl;
    cout << "remove: " << removeSorted << " ms" << endl;

    cout << endl;
}

int main() {
    vector<int> sizes = {
        1000,
        10000,
        100000,
        1000000
    };

    mt19937 generator(42);

    cout << "=== Red-Black Tree Benchmark ===" << endl;
    cout << endl;

    for (int n : sizes) {
        runBenchmark(n, generator);
    }

    return 0;
}