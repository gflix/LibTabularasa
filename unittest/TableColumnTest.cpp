#include <gtest/gtest.h>
#include <tabularasa/TableColumn.hpp>

using namespace Tabularasa;


TEST(TableColumnTest, throwsWhenMaxWidthIsLessThanMinWidth)
{
    EXPECT_THROW(TableColumn("A", "foo", 4, 3), std::domain_error);
}

TEST(TableColumnTest, keepsMinWidthWithShorterTitle)
{
    TableColumn test { "A", "foo", 4 };
    int expected = 4;
    EXPECT_EQ(expected, test.minWidth);
}

TEST(TableColumnTest, adjustsMinWidthWithLongerTitle)
{
    TableColumn test { "B", "foobar", 4 };
    int expected = 6;
    EXPECT_EQ(expected, test.minWidth);
}
