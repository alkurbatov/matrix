#include <iostream>
#include <gtest/gtest.h>

#include "Errors.h"
#include "Matrix.h"

void test_creation()
{
    Matrix<int> case1(3, 3);
    ASSERT_EQ(case1.to_string(), "|0 0 0|\n|0 0 0|\n|0 0 0|\n");

    Matrix<double> case2(3, 3);
    ASSERT_EQ(case2.to_string(),
              "|0.000000 0.000000 0.000000|\n|0.000000 0.000000 0.000000|\n|0.000000 0.000000 0.000000|\n");

    Matrix<int> case3(1, 5);
    ASSERT_EQ(case3.to_string(), "|0 0 0 0 0|\n");

    Matrix<int> case4(7, 1);
    ASSERT_EQ(case4.to_string(), "|0|\n|0|\n|0|\n|0|\n|0|\n|0|\n|0|\n");

    Matrix<int> case5(1, 1);
    ASSERT_EQ(case5.to_string(), "|0|\n");
}

void test_get_set()
{
    Matrix<int> case1(3, 3);
    ASSERT_EQ(case1[0][1], 0);

    case1[0][1] = 5;
    ASSERT_EQ(case1[0][1], 5);

    Matrix<double> case2(1, 1);
    case2[0][0] = 0.2;
    ASSERT_EQ(case2.to_string(), "|0.200000|\n");
}

void test_deep_copy()
{
    Matrix<int> src(3, 3);
    Matrix<int> dst(src);
    ASSERT_EQ(src.to_string(), "|0 0 0|\n|0 0 0|\n|0 0 0|\n");

    ASSERT_EQ(src.rows(), 3);
    ASSERT_EQ(src.cols(), 3);

    dst[2][2] = 100;
    ASSERT_EQ(src.to_string(), "|0 0 0|\n|0 0 0|\n|0 0 0|\n");
    ASSERT_EQ(dst.to_string(), "|0 0 0|\n|0 0 0|\n|0 0 100|\n");
}

void test_move()
{
    Matrix<int> src(2, 2);
    src[0][0] = 1;
    src[0][1] = 2;
    src[1][0] = 3;
    src[1][1] = 4;

    Matrix<int> dst = std::move(src);

    ASSERT_EQ(src.rows(), 0);
    ASSERT_EQ(src.cols(), 0);
    ASSERT_EQ(src.to_string(), "");

    ASSERT_EQ(dst.rows(), 2);
    ASSERT_EQ(dst.cols(), 2);
    ASSERT_EQ(dst.to_string(), "|1 2|\n|3 4|\n");
}

void test_range_based_loop()
{
    Matrix<int> matrix(2, 2);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;
    matrix[1][1] = 4;

    unsigned i = 0;
    unsigned j = 0;
    for (auto val : matrix)
    {
        ASSERT_EQ(val, matrix[i][j]);

        if (j == matrix.cols() - 1)
        {
            j = 0;
            ++i;
            continue;
        }

        ++j;
    }
}

void test_sum()
{
    Matrix<int> left(2, 2);
    left[0][0] = 1;
    left[0][1] = 2;
    left[1][0] = 3;
    left[1][1] = 4;

    Matrix<int> right(2, 2);
    right[0][0] = 5;
    right[0][1] = 6;
    right[1][0] = 7;
    right[1][1] = 8;

    Matrix<int> res = left + right;
    ASSERT_EQ(res.rows(), 2);
    ASSERT_EQ(res.cols(), 2);
    ASSERT_EQ(res.to_string(), "|6 8|\n|10 12|\n");

    ASSERT_EQ(left.to_string(), "|1 2|\n|3 4|\n");
    ASSERT_EQ(right.to_string(), "|5 6|\n|7 8|\n");
}

void test_sum_on_wrong_dimensions()
{
    Matrix<int> left1(2, 2);
    Matrix<int> right1(3, 4);
    EXPECT_THROW(left1 + right1, DimensionsDontMatch);

    Matrix<int> left2(2, 2);
    Matrix<int> right2(2, 4);
    EXPECT_THROW(left2 + right2, DimensionsDontMatch);

    Matrix<int> left3(3, 2);
    Matrix<int> right3(4, 2);
    EXPECT_THROW(left3 + right3, DimensionsDontMatch);
}

void test_concat()
{
    Matrix<int> left(2, 2);
    left[0][0] = 1;
    left[0][1] = 2;
    left[1][0] = 3;
    left[1][1] = 4;

    Matrix<int> right(2, 2);
    right[0][0] = 5;
    right[0][1] = 6;
    right[1][0] = 7;
    right[1][1] = 8;

    Matrix<int> res = left | right;
    ASSERT_EQ(res.rows(), 4);
    ASSERT_EQ(res.cols(), 2);
    ASSERT_EQ(res.to_string(), "|1 2|\n|3 4|\n|5 6|\n|7 8|\n");

    ASSERT_EQ(left.to_string(), "|1 2|\n|3 4|\n");
    ASSERT_EQ(right.to_string(), "|5 6|\n|7 8|\n");
}

void test_concat_on_wrong_dimensions()
{
    Matrix<int> left(2, 2);
    Matrix<int> right(3, 4);
    EXPECT_THROW(left | right, DimensionsDontMatch);
}

int main()
{
    test_creation();
    test_get_set();
    test_deep_copy();
    test_move();
    test_range_based_loop();
    test_sum();
    test_sum_on_wrong_dimensions();
    test_concat();
    test_concat_on_wrong_dimensions();

    return 0;
}
