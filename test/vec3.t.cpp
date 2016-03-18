#include <gtest/gtest.h>
#include "vec3.h"
#include <math.h>

TEST(Vec3f, Constructor)
{
    Vec3f n(1.0,-1.0,5.0);
    EXPECT_EQ(1.0, n.i());
    EXPECT_EQ(-1.0,n.j());
    EXPECT_EQ(5.0, n.k());
}

TEST(Vec3f, Add)
{
    Vec3f augend(1.0, 10., 20.);
    Vec3f addend(1.0, -1.0, 2.0);
    Vec3f sum = augend + addend;

    EXPECT_DOUBLE_EQ(2.0,sum.i());
    EXPECT_DOUBLE_EQ(9.0,sum.j());
    EXPECT_DOUBLE_EQ(22.,sum.k());
}

TEST(Vec3f, Subtract)
{
    Vec3f minuend(10, 50, 80);
    Vec3f subtrahend(1, 2, 10);
    Vec3f difference = minuend - subtrahend;

    EXPECT_DOUBLE_EQ(9,  difference.i());
    EXPECT_DOUBLE_EQ(48, difference.j());
    EXPECT_DOUBLE_EQ(70, difference.k());
}

TEST(Vec3f, CrossProductK)
{
    Vec3f a(1, 0, 0);
    Vec3f b(0, 1, 0);
    Vec3f product = a.cross_product(b);
    EXPECT_DOUBLE_EQ(0, product.i());
    EXPECT_DOUBLE_EQ(0, product.j());
    EXPECT_DOUBLE_EQ(1, product.k());
}

TEST(Vec3f, CrossProductJ)
{
    Vec3f a(0, 0, 1);
    Vec3f b(1, 0, 0);
    Vec3f product = a.cross_product(b);
    EXPECT_DOUBLE_EQ(0, product.i());
    EXPECT_DOUBLE_EQ(1, product.j());
    EXPECT_DOUBLE_EQ(0, product.k());
}

TEST(Vec3f, CrossProductI)
{
    Vec3f a(0, 1, 0);
    Vec3f b(0, 0, 1);
    Vec3f product = a.cross_product(b);
    EXPECT_DOUBLE_EQ(1, product.i());
    EXPECT_DOUBLE_EQ(0, product.j());
    EXPECT_DOUBLE_EQ(0, product.k());
}

TEST(Vec3f, CrossProductINeg)
{
    Vec3f a(0, 0, 1);
    Vec3f b(0, 1, 0);
    Vec3f product = a.cross_product(b);
    EXPECT_DOUBLE_EQ(-1, product.i());
    EXPECT_DOUBLE_EQ(0, product.j());
    EXPECT_DOUBLE_EQ(0, product.k());
}

TEST(Vec3f, Normalize)
{
    Vec3f a(24.61,3591,4683);
    Vec3f normalized = a.normalize();
    EXPECT_DOUBLE_EQ(1, normalized.magnitude());
}

TEST(Vec3f, Magnitude)
{
    Vec3f a(-1, 1.0, 3);
    EXPECT_DOUBLE_EQ(sqrt(11),a.magnitude());
}

TEST(Vec3f, Divide)
{
    Vec3f dividend(10, -50, 201);
    Vec3f quotient = dividend / 2;
    EXPECT_DOUBLE_EQ(5,    quotient.i());
    EXPECT_DOUBLE_EQ(-25,  quotient.j());
    EXPECT_DOUBLE_EQ(100.5,quotient.k());
}
