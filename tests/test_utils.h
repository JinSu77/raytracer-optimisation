#ifndef TEST_UTILS_H
#define TEST_UTILS_H

extern int test_failures;

void ASSERT_TRUE(bool condition, const char* message);
void ASSERT_FALSE(bool condition, const char* message);
void ASSERT_DOUBLE_EQ(double expected, double actual, const char* message);
void ASSERT_NEAR(double expected, double actual, double epsilon, const char* message);
void RUN_TEST(const char* test_name, void (*test_func)());
int TEST_SUMMARY();

#endif // TEST_UTILS_H
