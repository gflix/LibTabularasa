#include <gtest/gtest.h>
#include <tabularasa/Table.hpp>

using namespace Tabularasa;

TEST(TableTest, getsColumnWidths)
{
    Table table;
    table.columns.push_back(TableColumn("A", "Foo"));
    table.columns.push_back(TableColumn("B", "Bar"));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({ {"A", "12345"}, {"B", "X"}, {"C", "y"} }));
    table.rows.push_back(TableRow({ {"A", "123"}, {"B", "12345-relevant"}, {"C", "n"} }));
    table.rows.push_back(TableRow({ {"A", "2345"}, {"B", "Y"}, {"C", "n"} }));
    int expectedSize = 3;
    Table::ColumnWidths expectedWidths { 5, 14, 1 };

    auto actual = table.getColumnWidths();

    EXPECT_EQ(expectedSize, actual.size());
    auto expectedIt = expectedWidths.cbegin();
    auto actualIt = actual.cbegin();
    for(; expectedIt != expectedWidths.cend(); ++expectedIt, ++actualIt)
    {
        EXPECT_EQ(*expectedIt, *actualIt);
    }
}

TEST(TableTest, putsRegularTableToStreamI)
{
    Table table;
    table.columns.push_back(TableColumn("A", "Foo"));
    table.columns.push_back(TableColumn("B", "Bar"));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({ {"A", "12345"}, {"B", "X"}, {"C", "y"} }));
    table.rows.push_back(TableRow({ {"A", "123"}, {"B", "12345-relevant"}, {"C", "n"} }));
    table.rows.push_back(TableRow({ {"A", "2345"}, {"B", "Y"}, {"C", "n"} }));
    std::string expected {
        "+-------+----------------+---+\n"
        "| Foo   | Bar            | - |\n"
        "+-------+----------------+---+\n"
        "| 12345 | X              | y |\n"
        "| 123   | 12345-relevant | n |\n"
        "| 2345  | Y              | n |\n"
        "+-------+----------------+---+\n"
    };

    std::stringstream actual;
    table.toStream(actual);

    EXPECT_EQ(expected, actual.str());
}

TEST(TableTest, putsRegularTableToStreamII)
{
    Table table;
    table.columns.push_back(TableColumn("A", "Foo", 0, 0, HorizontalAlignment::RIGHT));
    table.columns.push_back(TableColumn("B", "Bar", 0, 0, HorizontalAlignment::CENTER));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({ {"A", "12345"}, {"B", "X"}, {"C", "y"} }));
    table.rows.push_back(TableRow({ {"A", "123"}, {"B", "12345-relevant"}, {"C", "n"} }));
    table.rows.push_back(TableRow({ {"A", "2345"}, {"B", "Y"}, {"C", "n"} }));
    std::string expected {
        "+-------+----------------+---+\n"
        "|   Foo |      Bar       | - |\n"
        "+-------+----------------+---+\n"
        "| 12345 |       X        | y |\n"
        "|   123 | 12345-relevant | n |\n"
        "|  2345 |       Y        | n |\n"
        "+-------+----------------+---+\n"
    };

    std::stringstream actual;
    table.toStream(actual);

    EXPECT_EQ(expected, actual.str());
}

TEST(TableTest, putsCompactTableToStream)
{
    Table table;
    table.compact = true;
    table.columns.push_back(TableColumn("A", "Foo"));
    table.columns.push_back(TableColumn("B", "Bar"));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({ {"A", "12345"}, {"B", "X"}, {"C", "y"} }));
    table.rows.push_back(TableRow({ {"A", "123"}, {"B", "12345-relevant"}, {"C", "n"} }));
    table.rows.push_back(TableRow({ {"A", "2345"}, {"B", "Y"}, {"C", "n"} }));
    std::string expected {
        "|Foo  |Bar           |-|\n"
        "+-----+--------------+-+\n"
        "|12345|X             |y|\n"
        "|123  |12345-relevant|n|\n"
        "|2345 |Y             |n|\n"
    };

    std::stringstream actual;
    table.toStream(actual);

    EXPECT_EQ(expected, actual.str());
}

TEST(TableTest, putsRegularTableWithMaxWidthToStreamI)
{
    Table table;
    table.columns.push_back(TableColumn("A", "Foo"));
    table.columns.push_back(TableColumn("B", "Bar", 0, 7));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({ {"A", "12345"}, {"B", "X"}, {"C", "y"} }));
    table.rows.push_back(TableRow({ {"A", "123"}, {"B", "12345-relevant"}, {"C", "n"} }));
    table.rows.push_back(TableRow({ {"A", "2345"}, {"B", "Y"}, {"C", "n"} }));
    std::string expected {
        "+-------+---------+---+\n"
        "| Foo   | Bar     | - |\n"
        "+-------+---------+---+\n"
        "| 12345 | X       | y |\n"
        "| 123   | 12345-r | n |\n"
        "| 2345  | Y       | n |\n"
        "+-------+---------+---+\n"
    };

    std::stringstream actual;
    table.toStream(actual);

    EXPECT_EQ(expected, actual.str());
}

TEST(TableTest, putsRegularTableWithMaxWidthToStreamII)
{
    Table table;
    table.columns.push_back(TableColumn("A", "Foo", 0, 0, HorizontalAlignment::CENTER));
    table.columns.push_back(TableColumn("B", "Bar", 0, 7, HorizontalAlignment::RIGHT));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({ {"A", "12345"}, {"B", "X"}, {"C", "y"} }));
    table.rows.push_back(TableRow({ {"A", "123"}, {"B", "12345-relevant"}, {"C", "n"} }));
    table.rows.push_back(TableRow({ {"A", "2345"}, {"B", "Y"}, {"C", "n"} }));
    std::string expected {
        "+-------+---------+---+\n"
        "|  Foo  |     Bar | - |\n"
        "+-------+---------+---+\n"
        "| 12345 |       X | y |\n"
        "|  123  | 12345-r | n |\n"
        "| 2345  |       Y | n |\n"
        "+-------+---------+---+\n"
    };

    std::stringstream actual;
    table.toStream(actual);

    EXPECT_EQ(expected, actual.str());
}

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

TEST(TableTest, generatedRegularCellWithShorterTextCenterAlignedI)
{
    int width = 6;
    std::string text { "foo" };
    std::string expected { "  foo   " };
    EXPECT_EQ(expected, Table::formattedCell(width, text, false, HorizontalAlignment::CENTER));
}

TEST(TableTest, generatedRegularCellWithShorterTextCenterAlignedII)
{
    int width = 6;
    std::string text { "fo" };
    std::string expected { "   fo   " };
    EXPECT_EQ(expected, Table::formattedCell(width, text, false, HorizontalAlignment::CENTER));
}

TEST(TableTest, generatedRegularCellWithShorterTextRightAligned)
{
    int width = 6;
    std::string text { "foo" };
    std::string expected { "    foo " };
    EXPECT_EQ(expected, Table::formattedCell(width, text, false, HorizontalAlignment::RIGHT));
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

TEST(TableTest, getsRegularFormattedRow)
{
    TableColumns columns;
    columns.push_back(TableColumn("A", "Foo"));
    columns.push_back(TableColumn("B", "bAr"));
    columns.push_back(TableColumn("C", "1234"));
    Table::ColumnWidths widths { 3, 2, 5 };
    TableRow row;
    row["D"] = "not used";
    row["A"] = "fOO";
    row["B"] = "X";
    std::string expected { "| fOO | X  |       |" };
    EXPECT_EQ(expected, Table::formattedRow(widths, columns, row));
}

TEST(TableTest, getsCompactFormattedRow)
{
    TableColumns columns;
    columns.push_back(TableColumn("A", "Foo"));
    columns.push_back(TableColumn("B", "bAr"));
    columns.push_back(TableColumn("C", "1234"));
    Table::ColumnWidths widths { 3, 2, 5 };
    TableRow row;
    row["D"] = "not used";
    row["A"] = "fOO";
    row["B"] = "X";
    std::string expected { "|fOO|X |     |" };
    EXPECT_EQ(expected, Table::formattedRow(widths, columns, row, true));
}

TEST(TableTest, throwsWhenFormattingRowWithNonMatchingColumnsAndWidths)
{
    TableColumns columns;
    columns.push_back(TableColumn("A", "Foo"));
    columns.push_back(TableColumn("B", "bAr"));
    columns.push_back(TableColumn("C", "1234"));
    Table::ColumnWidths widths { 100, 3, 2, 5 };
    TableRow row;
    row["D"] = "not used";
    row["A"] = "fOO";
    row["B"] = "X";
    EXPECT_THROW(Table::formattedRow(widths, columns, row), std::invalid_argument);
}

TEST(TableTest, getsColumnWidthI)
{
    TableColumn column { "A", "Foo" };
    TableRows rows;
    int expected = 3;
    EXPECT_EQ(expected, Table::getColumnWidth(column, rows));
}

TEST(TableTest, getsColumnWidthII)
{
    TableColumn column { "A", "Foo" };
    TableRows rows;
    rows.push_back(TableRow({ {"A", "1234"} }));
    int expected = 4;
    EXPECT_EQ(expected, Table::getColumnWidth(column, rows));
}

TEST(TableTest, getsColumnWidthIII)
{
    TableColumn column { "A", "Foo" };
    TableRows rows;
    rows.push_back(TableRow({ {"A", "12345"} }));
    rows.push_back(TableRow({ {"B", "12345-not-relevant"} }));
    rows.push_back(TableRow({ {"A", "2345"} }));
    int expected = 5;
    EXPECT_EQ(expected, Table::getColumnWidth(column, rows));
}

TEST(TableTest, getsColumnWidthIV)
{
    TableColumn column { "A", "Foo", 0, 4 };
    TableRows rows;
    rows.push_back(TableRow({ {"A", "12345"} }));
    rows.push_back(TableRow({ {"B", "12345-not-relevant"} }));
    rows.push_back(TableRow({ {"A", "2345"} }));
    int expected = 4;
    EXPECT_EQ(expected, Table::getColumnWidth(column, rows));
}
