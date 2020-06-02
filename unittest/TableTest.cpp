#include <gtest/gtest.h>
#include <tabularasa/Table.hpp>

using namespace Tabularasa;

TEST(TableTest, generatedRegularSeparatorLine)
{
    Table::ColumnWidths widths { 4, 3, 5 };
    std::string expected { "+------+-----+-------+" };
    EXPECT_EQ(expected, Table::separatorLine(widths));
}

TEST(TableTest, generatedCompactSeparatorLine)
{
    Table::ColumnWidths widths { 4, 3, 5 };
    std::string expected { "+----+---+-----+" };
    EXPECT_EQ(expected, Table::separatorLine(widths, true));
}
