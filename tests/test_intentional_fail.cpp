#include "test_utils.h"
#include "Vector3.hpp"
#include <iostream>

/**
 * Ce test échoue intentionnellement pour démontrer que le framework
 * peut détecter les échecs et les régressions.
 */

void test_intentional_failure() {
    Vector3 v(1.0, 2.0, 3.0);

    // Cette assertion échouera intentionnellement
    ASSERT_DOUBLE_EQ(999.0, v.x, "INTENTIONAL FAILURE: x should be 1.0, not 999.0");

    std::cout << "  This test demonstrates regression detection." << std::endl;
}

void test_another_intentional_failure() {
    Vector3 a(1.0, 0.0, 0.0);
    Vector3 b(1.0, 0.0, 0.0);

    double dot = a.dot(b);

    // Ceci échouera aussi
    ASSERT_DOUBLE_EQ(0.0, dot, "INTENTIONAL FAILURE: dot product should be 1.0");
}

int main() {
    std::cout << "\n=== Intentional Failure Test ===" << std::endl;
    std::cout << "This test suite is designed to FAIL to demonstrate" << std::endl;
    std::cout << "that the testing framework can detect regressions." << std::endl;
    std::cout << std::endl;

    RUN_TEST("IntentionalFailure1", test_intentional_failure);
    RUN_TEST("IntentionalFailure2", test_another_intentional_failure);

    std::cout << std::endl;
    std::cout << "Note: This test is marked as WILL_FAIL in CMake" << std::endl;
    std::cout << std::endl;

    return TEST_SUMMARY();
}
