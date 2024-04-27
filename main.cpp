#include "weighted_bag.h"
#include <string>
#include <cassert>

template <typename T>
void test(const std::string& testname, const WeightedBag<std::string, T>& wb, int repetitions, double allowed_error, const std::map<std::string, int>& expectation) {
    std::cout << "====" << testname << "====" << std::endl;

    std::map<std::string, int> counts;
    for (int i = 0; i < repetitions; ++i) {
        ++counts[wb.get()];
    }

    int total = 0;
    for (const auto& [_, i] : expectation) {
        total += i;
    }

    for (const auto& [key, expected] : expectation) {
        double expected_rate = static_cast<double>(expected) / total;
        double actual_rate = static_cast<double>(counts[key]) / repetitions;
        std::cout << key << ": Expected=" << expected_rate * 100 << " %, Actual=" << actual_rate * 100 << "%\n";
        assert(abs(expected_rate - actual_rate) < allowed_error);
    }

    std::cout << std::endl;
}


int main() {
    // int weights
    WeightedBag<std::string, int> wb_int;
    wb_int.put("apple", 10);
    wb_int.put("orange", 5);
    test("wb_int initial", wb_int, 1000000, 0.05, {{"apple", 10}, {"orange", 5}});

    wb_int.put("apple", 5);
    wb_int.put("apple", 2);
    wb_int.put("apple", 1);
    wb_int.put("apple", 2);
    wb_int.put("peach", 1);
    test("wb_int after recreate", wb_int, 1000000, 0.05, {{"apple", 20}, {"orange", 5}, {"peach", 1}});

    for (int i = 0; i < 495; ++i) {
        wb_int.put("apple", 1);
        wb_int.put("orange", 1);
        wb_int.put("peach", 1);
    }
    for (int i = 0; i < 4; ++i) {
        wb_int.put("apple", 1);
        wb_int.put("peach", 1);
    }
    for (int i = 0; i < 481; ++i) {
        wb_int.put("apple", 1);
    }
    test("wb_int after lots of puts", wb_int, 1000000, 0.05, {{"apple", 1000}, {"orange", 500}, {"peach", 500}});

    // double weights
    WeightedBag<std::string, double> wb_double;
    wb_double.put("apple", 10);
    wb_double.put("orange", 5);
    test("wb_double initial", wb_double, 1000000, 0.05, {{"apple", 10}, {"orange", 5}});

    wb_double.put("apple", 5);
    wb_double.put("apple", 2);
    wb_double.put("apple", 1);
    wb_double.put("apple", 2);
    wb_double.put("peach", 1);
    test("wb_double after recreate", wb_double, 1000000, 0.05, {{"apple", 20}, {"orange", 5}, {"peach", 1}});

    for (int i = 0; i < 495; ++i) {
        wb_double.put("apple", 1);
        wb_double.put("orange", 1);
        wb_double.put("peach", 1);
    }
    for (int i = 0; i < 4; ++i) {
        wb_double.put("apple", 1);
        wb_double.put("peach", 1);
    }
    for (int i = 0; i < 481; ++i) {
        wb_double.put("apple", 1);
    }
    test("wb_double after lots of puts", wb_double, 1000000, 0.05, {{"apple", 1000}, {"orange", 500}, {"peach", 500}});

    wb_double.put("banana", 1234.1234);
    wb_double.put("mango", 3.141592);
    test("wb_double with fractional weights", wb_double, 1000000, 0.05, {{"apple", 1000}, {"orange", 500}, {"peach", 500}, {"banana", 1234.1234}, {"mango", 3.141592}});

    return 0;
}