#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "AVLTree.h"

using Clock = std::chrono::high_resolution_clock;

// Vraća vrijeme izvršavanja funkcije f u milisekundama.
template <typename Func>
double measureMs(Func f) {
    auto start = Clock::now();
    f();
    auto end = Clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

std::vector<int> makeRandomValues(std::size_t n, unsigned seed) {
    std::vector<int> values(n);
    std::iota(values.begin(), values.end(), 0);

    std::mt19937 rng(seed);
    std::shuffle(values.begin(), values.end(), rng);

    return values;
}

std::vector<int> makeSortedValues(std::size_t n) {
    std::vector<int> values(n);
    std::iota(values.begin(), values.end(), 0);
    return values;
}

struct BenchmarkResult {
    std::size_t n;
    double insertMs;
    double searchMs;
    double removeMs;
};

BenchmarkResult runBenchmark(const std::vector<int>& insertOrder,
                              const std::vector<int>& searchOrder,
                              const std::vector<int>& removeOrder) {
    AVLTree<int> tree;

    BenchmarkResult result;
    result.n = insertOrder.size();

    result.insertMs = measureMs([&]() {
        for (int value : insertOrder) {
            tree.insert(value);
        }
    });

    // Sigurnosna provjera da benchmark mjeri stvarno popunjeno stablo.
    if (tree.size() != insertOrder.size()) {
        std::cerr << "UPOZORENJE: veličina stabla (" << tree.size()
                  << ") ne odgovara broju unesenih elemenata ("
                  << insertOrder.size() << ")\n";
    }

    volatile std::size_t foundCount = 0;
    result.searchMs = measureMs([&]() {
        for (int value : searchOrder) {
            bool found = tree.contains(value);
            foundCount += found ? 1 : 0;
        }
    });

    result.removeMs = measureMs([&]() {
        for (int value : removeOrder) {
            tree.remove(value);
        }
    });

    return result;
}

void printHeader(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
    std::cout << std::left
               << std::setw(12) << "N"
               << std::setw(16) << "insert (ms)"
               << std::setw(16) << "search (ms)"
               << std::setw(16) << "remove (ms)"
               << "\n";
    std::cout << std::string(60, '-') << "\n";
}

void printRow(const BenchmarkResult& r) {
    std::cout << std::left
               << std::setw(12) << r.n
               << std::setw(16) << std::fixed << std::setprecision(3) << r.insertMs
               << std::setw(16) << std::fixed << std::setprecision(3) << r.searchMs
               << std::setw(16) << std::fixed << std::setprecision(3) << r.removeMs
               << "\n";
}

int main() {
    const std::vector<std::size_t> sizes = {1000, 10000, 100000, 1000000};
    const unsigned seed = 42;

    printHeader("AVL Tree - nasumican redoslijed ubacivanja");
    for (std::size_t n : sizes) {
        std::vector<int> insertOrder = makeRandomValues(n, seed);

        std::vector<int> searchOrder = insertOrder;
        std::mt19937 rng(seed + 1);
        std::shuffle(searchOrder.begin(), searchOrder.end(), rng);

        std::vector<int> removeOrder = insertOrder;
        std::mt19937 rng2(seed + 2);
        std::shuffle(removeOrder.begin(), removeOrder.end(), rng2);

        BenchmarkResult result = runBenchmark(insertOrder, searchOrder, removeOrder);
        printRow(result);
    }

    printHeader("AVL Tree - sortiran (rastuci) redoslijed ubacivanja");
    for (std::size_t n : sizes) {
        std::vector<int> insertOrder = makeSortedValues(n);

        std::vector<int> searchOrder = insertOrder;
        std::mt19937 rng(seed + 3);
        std::shuffle(searchOrder.begin(), searchOrder.end(), rng);

        std::vector<int> removeOrder = insertOrder;
        std::mt19937 rng2(seed + 4);
        std::shuffle(removeOrder.begin(), removeOrder.end(), rng2);

        BenchmarkResult result = runBenchmark(insertOrder, searchOrder, removeOrder);
        printRow(result);
    }

    std::cout << "\nBenchmark zavrsen.\n";

    return 0;
}