#include "test_utils.h"
#include "Vector3.hpp"
#include <cmath>

const double EPSILON = 1e-6;

// Test basique: création et accès
void test_vector_creation() {
    Vector3 v(1.0, 2.0, 3.0);
    ASSERT_DOUBLE_EQ(1.0, v.x, "Vector x component");
    ASSERT_DOUBLE_EQ(2.0, v.y, "Vector y component");
    ASSERT_DOUBLE_EQ(3.0, v.z, "Vector z component");
}

// Test addition
void test_vector_addition() {
    Vector3 a(1.0, 2.0, 3.0);
    Vector3 b(4.0, 5.0, 6.0);
    Vector3 result = a + b;

    ASSERT_DOUBLE_EQ(5.0, result.x, "Addition x");
    ASSERT_DOUBLE_EQ(7.0, result.y, "Addition y");
    ASSERT_DOUBLE_EQ(9.0, result.z, "Addition z");
}

// Test soustraction
void test_vector_subtraction() {
    Vector3 a(10.0, 8.0, 6.0);
    Vector3 b(1.0, 2.0, 3.0);
    Vector3 result = a - b;

    ASSERT_DOUBLE_EQ(9.0, result.x, "Subtraction x");
    ASSERT_DOUBLE_EQ(6.0, result.y, "Subtraction y");
    ASSERT_DOUBLE_EQ(3.0, result.z, "Subtraction z");
}

// Test multiplication scalaire
void test_vector_scalar_multiply() {
    Vector3 v(2.0, 3.0, 4.0);
    Vector3 result = v * 3.0;

    ASSERT_DOUBLE_EQ(6.0, result.x, "Multiply x");
    ASSERT_DOUBLE_EQ(9.0, result.y, "Multiply y");
    ASSERT_DOUBLE_EQ(12.0, result.z, "Multiply z");
}

// Test longueur
void test_vector_length() {
    Vector3 v(3.0, 4.0, 0.0);
    double length = v.length();
    ASSERT_DOUBLE_EQ(5.0, length, "Length of (3,4,0) should be 5");
}

// Test normalisation
void test_vector_normalize() {
    Vector3 v(3.0, 4.0, 0.0);
    Vector3 normalized = v.normalize();
    double length = normalized.length();

    ASSERT_NEAR(1.0, length, EPSILON, "Normalized vector has length 1");
}

// Test produit scalaire
void test_vector_dot_product() {
    Vector3 a(1.0, 2.0, 3.0);
    Vector3 b(4.0, 5.0, 6.0);
    double dot = a.dot(b);

    ASSERT_DOUBLE_EQ(32.0, dot, "Dot product (1*4 + 2*5 + 3*6 = 32)");
}

// Test produit vectoriel
void test_vector_cross_product() {
    Vector3 a(1.0, 0.0, 0.0);
    Vector3 b(0.0, 1.0, 0.0);
    Vector3 result = a.cross(b);

    ASSERT_DOUBLE_EQ(0.0, result.x, "Cross product x");
    ASSERT_DOUBLE_EQ(0.0, result.y, "Cross product y");
    ASSERT_DOUBLE_EQ(1.0, result.z, "Cross product z");
}

int main() {
    std::cout << "\n=== Vector3 Unit Tests ===" << std::endl;

    RUN_TEST("VectorCreation", test_vector_creation);
    RUN_TEST("VectorAddition", test_vector_addition);
    RUN_TEST("VectorSubtraction", test_vector_subtraction);
    RUN_TEST("VectorScalarMultiply", test_vector_scalar_multiply);
    RUN_TEST("VectorLength", test_vector_length);
    RUN_TEST("VectorNormalize", test_vector_normalize);
    RUN_TEST("VectorDotProduct", test_vector_dot_product);
    RUN_TEST("VectorCrossProduct", test_vector_cross_product);

    return TEST_SUMMARY();
}
