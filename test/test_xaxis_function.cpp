/***************************************************************************
* Copyright (c) 2017, Johan Mabille, Sylvain Corlay Wolf Vollprecht and    *
* Martin Renou                                                             *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xframe/xnamed_axis.hpp"

namespace xf
{
    TEST(xaxis_function, plus_operator)
    {
        auto axis1 = named_axis("abs", axis(16));
        auto axis2 = named_axis("ord", axis(10, 20, 1));

        auto func1 = axis1 + axis2;
        EXPECT_EQ(func1({{"abs", 10}, {"ord", 5}}), 25);
        EXPECT_EQ(func1({{"abs", 15}, {"ord", 9}}), 34);
    }

    TEST(xaxis_function, pow_operator)
    {
        auto axis1 = named_axis("abs", axis(15));
        auto axis2 = named_axis("ord", axis(10, 20, 1));

        auto func1 = pow(axis2, axis1);
        EXPECT_EQ(func1({{"abs", 2}, {"ord", 5}}), 225);

        auto func2 = axis1 + axis2 + pow(axis2, axis1);
        EXPECT_EQ(func2({{"abs", 2}, {"ord", 5}}), 242);
    }

    TEST(xaxis_function, bool_operator)
    {
        auto axis1 = named_axis("abs", axis(15));
        auto axis2 = named_axis("ord", axis(10, 20, 1));
        auto axis3 = named_axis("alt", axis('b', 'j'));

        auto func1 = axis1 < 13u;
        EXPECT_EQ(func1({{"abs", 10}}), true);
        EXPECT_EQ(func1({{"abs", 14}}), false);

        auto func2 = axis1 > axis2;
        EXPECT_EQ(func2({{"abs", 10}, {"ord", 3}}), false);
        EXPECT_EQ(func2({{"abs", 14}, {"ord", 3}}), true);

        auto func3 = equal(axis3, 'b') || axis3 >= 'g' && not_equal(axis3, 'i');
        EXPECT_EQ(func3({{"alt", 0}}), true);  // b
        EXPECT_EQ(func3({{"alt", 1}}), false); // c
        EXPECT_EQ(func3({{"alt", 2}}), false); // d
        EXPECT_EQ(func3({{"alt", 3}}), false); // e
        EXPECT_EQ(func3({{"alt", 4}}), false); // f
        EXPECT_EQ(func3({{"alt", 5}}), true);  // g
        EXPECT_EQ(func3({{"alt", 6}}), true);  // h
        EXPECT_EQ(func3({{"alt", 7}}), false); // i
    }

    TEST(xaxis_function, xaxis_scalar)
    {
        auto axis1 = named_axis("abs", axis(15));
        auto axis2 = named_axis("ord", axis(10, 20, 1));

        auto func1 = axis1 < 13u;
        EXPECT_EQ(func1({{"abs", 10}}), true);
        EXPECT_EQ(func1({{"abs", 14}}), false);

        auto func2 = axis1 + axis2 + 4u;
        EXPECT_EQ(func2({{"abs", 10}, {"ord", 5}}), 29);
    }
}