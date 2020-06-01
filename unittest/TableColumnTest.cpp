#include <gtest/gtest.h>
#include <tabularasa/TableColumn.hpp>

using namespace Tabularasa;

TEST(TableColumnTest, keepsMinWidthWithShorterTitle)
{
    TableColumn test { "foo", 4 };
    int expected = 4;
    EXPECT_EQ(expected, test.minWidth);
}

TEST(TableColumnTest, adjustsMinWidthWithLongerTitle)
{
    TableColumn test { "foobar", 4 };
    int expected = 6;
    EXPECT_EQ(expected, test.minWidth);
}
