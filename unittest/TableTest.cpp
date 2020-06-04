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

TEST(TableTest, throwsWhenGeneratingSeparatorLineWithInvalidColumnWidth)
{
    Table::ColumnWidths widths { 4, 3, 0, 5 };
    EXPECT_THROW(Table::separatorLine(widths), std::domain_error);
}

TEST(TableTest, generatedRegularCellWithEmptyText)
{
    int width = 4;
    std::string text;
    std::string expected { "      " };
    EXPECT_EQ(expected, Table::formattedCell(width, text));
}

TEST(TableTest, generatedCompactCellWithEmptyText)
{
    int width = 4;
    std::string text;
    std::string expected { "    " };
    EXPECT_EQ(expected, Table::formattedCell(width, text, true));
}

TEST(TableTest, generatedRegularCellWithShorterText)
{
    int width = 6;
    std::string text { "foo" };
    std::string expected { " foo    " };
    EXPECT_EQ(expected, Table::formattedCell(width, text));
}

TEST(TableTest, generatedCompactCellWithShorterText)
{
    int width = 6;
    std::string text { "foo" };
    std::string expected { "foo   " };
    EXPECT_EQ(expected, Table::formattedCell(width, text, true));
}

TEST(TableTest, generatedRegularCellWithExactText)
{
    int width = 6;
    std::string text { "foobar" };
    std::string expected { " foobar " };
    EXPECT_EQ(expected, Table::formattedCell(width, text));
}

TEST(TableTest, generatedCompactCellWithExactText)
{
    int width = 6;
    std::string text { "foobar" };
    std::string expected { "foobar" };
    EXPECT_EQ(expected, Table::formattedCell(width, text, true));
}

TEST(TableTest, generatedRegularCellWithLongerText)
{
    int width = 6;
    std::string text { "foozbarbaz" };
    std::string expected { " foozba " };
    EXPECT_EQ(expected, Table::formattedCell(width, text));
}

TEST(TableTest, generatedCompactCellWithLongerText)
{
    int width = 6;
    std::string text { "foozbarbaz" };
    std::string expected { "foozba" };
    EXPECT_EQ(expected, Table::formattedCell(width, text, true));
}

TEST(TableTest, throwsWhenGeneratingCellWithInvalidWidth)
{
    int width = 0;
    std::string text { "foozbarbaz" };
    EXPECT_THROW(Table::formattedCell(width, text), std::domain_error);
}
