#include <gtest/gtest.h>
#include <tabularasa/Table.hpp>

using namespace Tabularasa;

TEST(TableTest, getsColumnWidths)
{
    Table table;
    table.columns.push_back(TableColumn("A", "Foo"));
    table.columns.push_back(TableColumn("B", "Bar"));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({
        {"A", TableCell("12345")},
        {"B", TableCell("X")},
        {"C", TableCell("y")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("123")},
        {"B", TableCell("12345-relevant")},
        {"C", TableCell("n")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("2345")},
        {"B", TableCell("Y")},
        {"C", TableCell("n")}
    }));
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
    table.rows.push_back(TableRow({
        {"A", TableCell("12345")},
        {"B", TableCell("X")},
        {"C", TableCell("y")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("123")},
        {"B", TableCell("12345-relevant")},
        {"C", TableCell("n")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("2345")},
        {"B", TableCell("Y")},
        {"C", TableCell("n")}
    }));
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
    table.rows.push_back(TableRow({
        {"A", TableCell("12345")},
        {"B", TableCell("X")},
        {"C", TableCell("y")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("123")},
        {"B", TableCell("12345-relevant")},
        {"C", TableCell("n")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("2345")},
        {"B", TableCell("Y")},
        {"C", TableCell("n")}
    }));
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

TEST(TableTest, putsRegularTableToStreamIII)
{
    Table table;
    table.columns.push_back(TableColumn("A", "Foo", 0, 0, HorizontalAlignment::RIGHT));
    table.columns.push_back(TableColumn("B", "Bar", 0, 0, HorizontalAlignment::CENTER));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({
        {"A", TableCell("12345")},
        {"B", TableCell("X", HorizontalAlignment::LEFT)},
        {"C", TableCell("y")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("123", HorizontalAlignment::CENTER)},
        {"B", TableCell("12345-relevant")},
        {"C", TableCell("n")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("2345")},
        {"B", TableCell("Y", HorizontalAlignment::RIGHT)},
        {"C", TableCell("n")}
    }));
    std::string expected {
        "+-------+----------------+---+\n"
        "|   Foo |      Bar       | - |\n"
        "+-------+----------------+---+\n"
        "| 12345 | X              | y |\n"
        "|  123  | 12345-relevant | n |\n"
        "|  2345 |              Y | n |\n"
        "+-------+----------------+---+\n"
    };

    std::stringstream actual;
    table.toStream(actual);

    EXPECT_EQ(expected, actual.str());
}

TEST(TableTest, putsRegularTableToStreamIV)
{
    Table table;
    table.useColors = true;
    table.columns.push_back(TableColumn("A", "Foo"));
    table.columns.push_back(TableColumn("B", "Bar"));
    table.columns.push_back(TableColumn("C", "-"));
    table.rows.push_back(TableRow({
        {"A", TableCell("12345")},
        {"B", TableCell("X")},
        {"C", TableCell("y", HorizontalAlignment::DEFAULT, CellColor(AnsiColor::GREEN))}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("123")},
        {"B", TableCell("12345-relevant")},
        {"C", TableCell("n", HorizontalAlignment::DEFAULT, CellColor(AnsiColor::RED))}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("2345")},
        {"B", TableCell("Y")},
        {"C", TableCell("n", HorizontalAlignment::DEFAULT, CellColor(AnsiColor::RED))}
    }));
    std::string expected {
        "+-------+----------------+---+\n"
        "| Foo   | Bar            | - |\n"
        "+-------+----------------+---+\n"
        "| 12345 | X              |\033[32m y \033[0m|\n"
        "| 123   | 12345-relevant |\033[31m n \033[0m|\n"
        "| 2345  | Y              |\033[31m n \033[0m|\n"
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
    table.rows.push_back(TableRow({
        {"A", TableCell("12345")},
        {"B", TableCell("X")},
        {"C", TableCell("y")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("123")},
        {"B", TableCell("12345-relevant")},
        {"C", TableCell("n")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("2345")},
        {"B", TableCell("Y")},
        {"C", TableCell("n")}
    }));
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
    table.rows.push_back(TableRow({
        {"A", TableCell("12345")},
        {"B", TableCell("X")},
        {"C", TableCell("y")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("123")},
        {"B", TableCell("12345-relevant")},
        {"C", TableCell("n")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("2345")},
        {"B", TableCell("Y")},
        {"C", TableCell("n")}
    }));
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
    table.rows.push_back(TableRow({
        {"A", TableCell("12345")},
        {"B", TableCell("X")},
        {"C", TableCell("y")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("123")},
        {"B", TableCell("12345-relevant")},
        {"C", TableCell("n")}
    }));
    table.rows.push_back(TableRow({
        {"A", TableCell("2345")},
        {"B", TableCell("Y")},
        {"C", TableCell("n")}
    }));
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
    TableCell cell { "foo", HorizontalAlignment::CENTER };
    std::string expected { "  foo   " };
    EXPECT_EQ(expected, Table::formattedCell(width, cell, false));
}

TEST(TableTest, generatedRegularCellWithShorterTextCenterAlignedII)
{
    int width = 6;
    TableCell cell { "fo", HorizontalAlignment::CENTER };
    std::string expected { "   fo   " };
    EXPECT_EQ(expected, Table::formattedCell(width, cell, false));
}

TEST(TableTest, generatedRegularCellWithShorterTextRightAligned)
{
    int width = 6;
    TableCell cell { "foo", HorizontalAlignment::RIGHT };
    std::string expected { "    foo " };
    EXPECT_EQ(expected, Table::formattedCell(width, cell, false));
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

TEST(TableTest, generatedRegularCellWithEnabledColor)
{
    int width = 6;
    TableCell cell { "foo", HorizontalAlignment::DEFAULT, CellColor(AnsiColor::WHITE, AnsiColor::YELLOW, true) };
    std::string expected { "\033[37;43;1m foo    \033[0m" };
    EXPECT_EQ(expected, Table::formattedCell(width, cell, false, true));
}

TEST(TableTest, generatedRegularCellWithDisabledColor)
{
    int width = 6;
    TableCell cell { "foo", HorizontalAlignment::DEFAULT, CellColor(AnsiColor::WHITE, AnsiColor::YELLOW, true) };
    std::string expected { " foo    " };
    EXPECT_EQ(expected, Table::formattedCell(width, cell, false, false));
}

TEST(TableTest, getsExistingRowCell)
{
    TableRow row;
    row["foo"] = TableCell("bar");
    row["123"] = TableCell("456");
    std::string id { "foo" };
    std::string expected { "bar" };
    EXPECT_EQ(expected, Table::getRowCell(row, id).text);
}

TEST(TableTest, getsNonExistingRowCell)
{
    TableRow row;
    row["foo"] = TableCell("bar");
    row["123"] = TableCell("456");
    std::string id { "nonexisting" };
    std::string expected;
    EXPECT_EQ(expected, Table::getRowCell(row, id).text);
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
    row["D"] = TableCell("not used");
    row["A"] = TableCell("fOO");
    row["B"] = TableCell("X");
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
    row["D"] = TableCell("not used");
    row["A"] = TableCell("fOO");
    row["B"] = TableCell("X");
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
    row["D"] = TableCell("not used");
    row["A"] = TableCell("fOO");
    row["B"] = TableCell("X");
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
    rows.push_back(TableRow({
        {"A", TableCell("1234")}
    }));
    int expected = 4;
    EXPECT_EQ(expected, Table::getColumnWidth(column, rows));
}

TEST(TableTest, getsColumnWidthIII)
{
    TableColumn column { "A", "Foo" };
    TableRows rows;
    rows.push_back(TableRow({
        {"A", TableCell("12345")}
    }));
    rows.push_back(TableRow({
        {"B", TableCell("12345-not-relevant")}
    }));
    rows.push_back(TableRow({
        {"A", TableCell("2345")}
    }));
    int expected = 5;
    EXPECT_EQ(expected, Table::getColumnWidth(column, rows));
}

TEST(TableTest, getsColumnWidthIV)
{
    TableColumn column { "A", "Foo", 0, 4 };
    TableRows rows;
    rows.push_back(TableRow({
        {"A", TableCell("12345")}
    }));
    rows.push_back(TableRow({
        {"B", TableCell("12345-not-relevant")}
    }));
    rows.push_back(TableRow({
        {"A", TableCell("2345")}
    }));
    int expected = 4;
    EXPECT_EQ(expected, Table::getColumnWidth(column, rows));
}
