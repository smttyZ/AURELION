#include <gtest/gtest.h>
#include <cmath>
#include "include/Vector3.h"

class Vector3TestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        v1 = math::Vector3(1.0f, 2.0f, 3.0f);
        v2 = math::Vector3(4.0f, 5.0f, 6.0f);
        zero = math::Vector3(0.0f, 0.0f, 0.0f);
        unit_x = math::Vector3(1.0f, 0.0f, 0.0f);
        unit_y = math::Vector3(0.0f, 1.0f, 0.0f);
        unit_z = math::Vector3(0.0f, 0.0f, 1.0f);
    }

    math::Vector3 v1, v2, zero, unit_x, unit_y, unit_z;
    const float EPSILON = 1e-6f;
};

// ============================================================================
// CONSTRUCTOR TESTS
// ============================================================================

TEST_F(Vector3TestFixture, DefaultConstructor) {
    math::Vector3 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST_F(Vector3TestFixture, ParameterizedConstructor) {
    math::Vector3 v(1.5f, -2.3f, 4.7f);
    EXPECT_FLOAT_EQ(v.x, 1.5f);
    EXPECT_FLOAT_EQ(v.y, -2.3f);
    EXPECT_FLOAT_EQ(v.z, 4.7f);
}

TEST_F(Vector3TestFixture, CopyConstructor) {
    math::Vector3 original(1.0f, 2.0f, 3.0f);
    math::Vector3 copy(original);

    EXPECT_FLOAT_EQ(copy.x, original.x);
    EXPECT_FLOAT_EQ(copy.y, original.y);
    EXPECT_FLOAT_EQ(copy.z, original.z);

    // Ensure they're separate objects
    copy.x = 10.0f;
    EXPECT_FLOAT_EQ(original.x, 1.0f);
}

TEST_F(Vector3TestFixture, AssignmentOperator) {
    math::Vector3 v(7.0f, 8.0f, 9.0f);
    v1 = v;

    EXPECT_FLOAT_EQ(v1.x, 7.0f);
    EXPECT_FLOAT_EQ(v1.y, 8.0f);
    EXPECT_FLOAT_EQ(v1.z, 9.0f);
}

TEST_F(Vector3TestFixture, SelfAssignment) {
    math::Vector3 original_v1 = v1;
    v1 = v1; // Self-assignment

    EXPECT_FLOAT_EQ(v1.x, original_v1.x);
    EXPECT_FLOAT_EQ(v1.y, original_v1.y);
    EXPECT_FLOAT_EQ(v1.z, original_v1.z);
}

// ============================================================================
// ARITHMETIC OPERATOR TESTS
// ============================================================================

TEST_F(Vector3TestFixture, Addition) {
    math::Vector3 result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST_F(Vector3TestFixture, AdditionWithZero) {
    math::Vector3 result = v1 + zero;
    EXPECT_FLOAT_EQ(result.x, v1.x);
    EXPECT_FLOAT_EQ(result.y, v1.y);
    EXPECT_FLOAT_EQ(result.z, v1.z);
}

TEST_F(Vector3TestFixture, Subtraction) {
    math::Vector3 result = v2 - v1;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST_F(Vector3TestFixture, SubtractionFromSelf) {
    math::Vector3 result = v1 - v1;
    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 0.0f);
}

TEST_F(Vector3TestFixture, ScalarMultiplication) {
    math::Vector3 result = v1 * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST_F(Vector3TestFixture, ScalarMultiplicationByZero) {
    math::Vector3 result = v1 * 0.0f;
    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 0.0f);
}

TEST_F(Vector3TestFixture, ScalarMultiplicationByNegative) {
    math::Vector3 result = v1 * -1.5f;
    EXPECT_FLOAT_EQ(result.x, -1.5f);
    EXPECT_FLOAT_EQ(result.y, -3.0f);
    EXPECT_FLOAT_EQ(result.z, -4.5f);
}

TEST_F(Vector3TestFixture, ScalarDivision) {
    math::Vector3 result = v1 / 2.0f;
    EXPECT_FLOAT_EQ(result.x, 0.5f);
    EXPECT_FLOAT_EQ(result.y, 1.0f);
    EXPECT_FLOAT_EQ(result.z, 1.5f);
}

TEST_F(Vector3TestFixture, ScalarDivisionByOne) {
    math::Vector3 result = v1 / 1.0f;
    EXPECT_FLOAT_EQ(result.x, v1.x);
    EXPECT_FLOAT_EQ(result.y, v1.y);
    EXPECT_FLOAT_EQ(result.z, v1.z);
}

// ============================================================================
// COMPOUND ASSIGNMENT TESTS
// ============================================================================

TEST_F(Vector3TestFixture, CompoundAddition) {
    math::Vector3 result = v1;
    result += v2;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST_F(Vector3TestFixture, CompoundSubtraction) {
    math::Vector3 result = v2;
    result -= v1;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST_F(Vector3TestFixture, CompoundScalarMultiplication) {
    math::Vector3 result = v1;
    result *= 3.0f;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST_F(Vector3TestFixture, CompoundScalarDivision) {
    math::Vector3 result = math::Vector3(6.0f, 8.0f, 12.0f);
    result /= 2.0f;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}


// ============================================================================
// LENGTH AND NORMALIZATION TESTS
// ============================================================================

TEST_F(Vector3TestFixture, Length) {
    float expected_length = std::sqrt(1.0f + 4.0f + 9.0f); // sqrt(14)
    EXPECT_NEAR(v1.length(), expected_length, EPSILON);
}

TEST_F(Vector3TestFixture, Normalized) {
    math::Vector3 normalized = v1.normalized();
    EXPECT_NEAR(normalized.length(), 1.0f, EPSILON);

    // Check direction is preserved
    float original_length = v1.length();
    EXPECT_NEAR(normalized.x, v1.x / original_length, EPSILON);
    EXPECT_NEAR(normalized.y, v1.y / original_length, EPSILON);
    EXPECT_NEAR(normalized.z, v1.z / original_length, EPSILON);

    // Original vector should be unchanged
    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f);
    EXPECT_FLOAT_EQ(v1.z, 3.0f);
}


// ============================================================================
// DOT PRODUCT TESTS
// ============================================================================

TEST_F(Vector3TestFixture, DotProduct) {
    float result = v1.dot(v2);
    float expected = 1.0f*4.0f + 2.0f*5.0f + 3.0f*6.0f; // 4 + 10 + 18 = 32
    EXPECT_FLOAT_EQ(result, expected);
}


// ============================================================================
// CROSS PRODUCT TESTS
// ============================================================================

TEST_F(Vector3TestFixture, CrossProduct) {
    math::Vector3 result = v1.cross(v2);
    // v1 = (1,2,3), v2 = (4,5,6)
    // cross = (2*6-3*5, 3*4-1*6, 1*5-2*4) = (12-15, 12-6, 5-8) = (-3, 6, -3)
    EXPECT_FLOAT_EQ(result.x, -3.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
    EXPECT_FLOAT_EQ(result.z, -3.0f);
}