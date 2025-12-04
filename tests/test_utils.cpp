#include "test_utils.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

int test_failures = 0;

void ASSERT_TRUE(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAILED: " << message << std::endl;
        test_failures++;
    }
}

void ASSERT_FALSE(bool condition, const char* message) {
    if (condition) {
        std::cerr << "FAILED: " << message << std::endl;
        test_failures++;
    }
}

void ASSERT_DOUBLE_EQ(double expected, double actual, const char* message) {
    if (std::abs(expected - actual) > 1e-9) {
        std::cerr << "FAILED: " << message
                  << " (expected: " << expected
                  << ", got: " << actual << ")" << std::endl;
        test_failures++;
    }
}

void ASSERT_NEAR(double expected, double actual, double epsilon, const char* message) {
    if (std::abs(expected - actual) > epsilon) {
        std::cerr << "FAILED: " << message
                  << " (expected: " << expected
                  << ", got: " << actual
                  << ", epsilon: " << epsilon << ")" << std::endl;
        test_failures++;
    }
}

void RUN_TEST(const char* test_name, void (*test_func)()) {
    std::cout << "Running: " << test_name << "... ";
    int before = test_failures;
    test_func();
    if (test_failures == before) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
}

int TEST_SUMMARY() {
    if (test_failures == 0) {
        std::cout << "\nAll tests passed!" << std::endl;
        return 0;
    } else {
        std::cout << "\n" << test_failures << " test(s) failed!" << std::endl;
        return 1;
    }
}
