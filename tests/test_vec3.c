#include "unity.h"
#include "vec3.h"

void test_vec3_add(void) {
    Vec3 a = {1.0f, 2.0f, 3.0f};
    Vec3 b = {4.0f, 5.0f, 6.0f};
    Vec3 res = vec3_add(a, b);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, res.x);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, res.y);
    TEST_ASSERT_EQUAL_FLOAT(9.0f, res.z);
}

void test_vec3_sub(void) {
    Vec3 a = {4.0f, 5.0f, 6.0f};
    Vec3 b = {1.0f, 2.0f, 3.0f};
    Vec3 res = vec3_sub(a, b);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, res.x);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, res.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, res.z);
}

void test_vec3_mul(void) {
    Vec3 v = {1.0f, 2.0f, 3.0f};
    Vec3 res = vec3_mul(v, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, res.x);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, res.y);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, res.z);
}

void test_vec3_dot(void) {
    Vec3 a = {1.0f, 2.0f, 3.0f};
    Vec3 b = {4.0f, 5.0f, 6.0f};
    float res = vec3_dot(a, b);
    TEST_ASSERT_EQUAL_FLOAT(32.0f, res);
}

void test_vec3_cross(void) {
    Vec3 x_axis = {1.0f, 0.0f, 0.0f};
    Vec3 y_axis = {0.0f, 1.0f, 0.0f};
    Vec3 res = vec3_cross(x_axis, y_axis); 
    TEST_ASSERT_EQUAL_FLOAT(0.0f, res.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, res.y);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, res.z);
}

void test_vec3_length(void) {
    Vec3 v = {3.0f, 4.0f, 0.0f};
    TEST_ASSERT_EQUAL_FLOAT(25.0f, vec3_length_squared(v));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, vec3_length(v));
}

void test_vec3_normalize(void) {
    Vec3 v = {3.0f, 0.0f, 0.0f};
    Vec3 res = vec3_normalize(v);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, res.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, res.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, res.z);
    
    // Test vecteur nul
    Vec3 zero = {0.0f, 0.0f, 0.0f};
    Vec3 res_zero = vec3_normalize(zero);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, res_zero.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, res_zero.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, res_zero.z);
}