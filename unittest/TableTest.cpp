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

TEST(TableTest, getsExistingRowCell)
{
    TableRow row;
    row["foo"] = "bar";
    row["123"] = "456";
    std::string id { "foo" };
    std::string expected { "bar" };
    EXPECT_EQ(expected, Table::getRowCell(row, id));
}

TEST(TableTest, getsNonExistingRowCell)
{
    TableRow row;
    row["foo"] = "bar";
    row["123"] = "456";
    std::string id { "nonexisting" };
    std::string expected;
    EXPECT_EQ(expected, Table::getRowCell(row, id));
}

TEST(TableTest, getsRegularFormattedHeaderRow)
{
    TableColumns columns;
    columns.push_back(TableColumn("A", "Foo"));
    columns.push_back(TableColumn("B", "bAr"));
    columns.push_back(TableColumn("C", "1234"));
    Table::ColumnWidths widths { 3, 2, 5 };
    std::string expected { "| Foo | bA | 1234  |" };
    EXPECT_EQ(expected, Table::formattedHeaderRow(widths, columns));
}

TEST(TableTest, getsCompactFormattedHeaderRow)
{
    TableColumns columns;
    columns.push_back(TableColumn("A", "Foo"));
    columns.push_back(TableColumn("B", "bAr"));
    columns.push_back(TableColumn("C", "1234"));
    Table::ColumnWidths widths { 3, 2, 5 };
    std::string expected { "|Foo|bA|1234 |" };
    EXPECT_EQ(expected, Table::formattedHeaderRow(widths, columns, true));
}

TEST(TableTest, throwsWhenFormattingHeaderRowWithNonMatchingColumnsAndWidths)
{
    TableColumns columns;
    columns.push_back(TableColumn("A", "Foo"));
    columns.push_back(TableColumn("B", "bAr"));
    columns.push_back(TableColumn("C", "1234"));
    Table::ColumnWidths widths { 3, 2, 5, 100 };
    EXPECT_THROW(Table::formattedHeaderRow(widths, columns), std::invalid_argument);
}
