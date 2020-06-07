#include <stdexcept>
#include <tabularasa/Table.hpp>

namespace Tabularasa
{

Table::Table(void):
    compact(false),
    useColors(false)
{
}

Table::ColumnWidths Table::getColumnWidths(void) const
{
    ColumnWidths widths;

    for (auto& column: columns)
    {
        widths.push_back(getColumnWidth(column, rows));
    }

    return widths;
}

void Table::toStream(std::ostream& stream) const
{
    auto columnWidths = getColumnWidths();
    auto separator = separatorLine(columnWidths, compact);

    if (!compact)
        stream << separator << std::endl;
    stream << formattedHeaderRow(columnWidths, columns, compact, useColors) << std::endl;
    stream << separator << std::endl;
    for (auto& row: rows)
    {
        stream << formattedRow(columnWidths, columns, row, compact, useColors) << std::endl;
    }
    if (!compact)
        stream << separator << std::endl;
}

std::string Table::separatorLine(const Table::ColumnWidths& widths, bool compact)
{
    std::string line;

    for (auto width: widths)
    {
        if (width <= 0)
        {
            throw std::domain_error("invalid column width " + std::to_string(width));
        }

        line += '+';
        line += std::string(compact ? width : width + 2, '-');
    }
    line += '+';

    return line;
}

std::string Table::formattedCell(int width, const TableCell& cell, bool compact, bool useColors)
{
    if (width <= 0)
    {
        throw std::domain_error("invalid column width " + std::to_string(width));
    }

    auto textLength = cell.text.size();
    auto centerPadding = (width - textLength) / 2;
    std::string paddedCell;

    if (textLength < width)
    {
        switch (cell.hAlignment)
        {
            case HorizontalAlignment::DEFAULT:
            case HorizontalAlignment::LEFT:
                paddedCell = cell.text;
                paddedCell += std::string(width - textLength, ' ');
                break;
            case HorizontalAlignment::CENTER:
                paddedCell = std::string(centerPadding, ' ');
                paddedCell += cell.text;
                paddedCell += std::string(width - textLength - centerPadding, ' ');
                break;
            case HorizontalAlignment::RIGHT:
                paddedCell = std::string(width - textLength, ' ');
                paddedCell += cell.text;
                break;
        }
    }
    else
    {
        paddedCell = cell.text.substr(0, width);
    }

    if (!compact)
    {
        paddedCell = ' ' + paddedCell + ' ';
    }

    if (useColors && !cell.color.isDefault())
    {
        paddedCell = cell.color.setSequence() + paddedCell + cell.color.resetSequence();
    }

    return paddedCell;
}

TableCell Table::getRowCell(const TableRow& row, const std::string& id)
{
    auto it = row.find(id);
    if (it != row.cend())
    {
        return it->second;
    }
    return std::string();
}

std::string Table::formattedHeaderRow(
    const ColumnWidths& widths,
    const TableColumns& columns,
    bool compact,
    bool useColors)
{
    if (columns.size() != widths.size())
    {
        throw std::invalid_argument(
            "column count and column width count does not match "
            "(" + std::to_string(columns.size()) + "!=" + std::to_string(widths.size()) + ")");
    }

    std::string line;

    auto columnIt = columns.cbegin();
    auto widthIt = widths.cbegin();
    for (; columnIt != columns.cend(); ++columnIt, ++widthIt)
    {
        line += '|';
        TableCell cell { columnIt->title, columnIt->hAlignment, columnIt->color };
        line += formattedCell(*widthIt, cell, compact, useColors);
    }
    line += '|';

    return line;
}

std::string Table::formattedRow(
    const ColumnWidths& widths,
    const TableColumns& columns,
    const TableRow& row,
    bool compact,
    bool useColors)
{
    if (columns.size() != widths.size())
    {
        throw std::invalid_argument(
            "column count and column width count does not match "
            "(" + std::to_string(columns.size()) + "!=" + std::to_string(widths.size()) + ")");
    }

    std::string line;

    auto columnIt = columns.cbegin();
    auto widthIt = widths.cbegin();
    for (; columnIt != columns.cend(); ++columnIt, ++widthIt)
    {
        line += '|';
        auto cell = getRowCell(row, columnIt->id);
        if (cell.hAlignment == HorizontalAlignment::DEFAULT)
        {
            cell.hAlignment = columnIt->hAlignment;
        }
        line += formattedCell(*widthIt, cell, compact, useColors);
    }
    line += '|';

    return line;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int Table::getColumnWidth(const TableColumn& column, const TableRows& rows)
{
    int width = max(column.minWidth, column.title.size());

    for (auto& row: rows)
    {
        width = max(width, getRowCell(row, column.id).text.size());
    }

    if (column.maxWidth > 0)
    {
        width = min(column.maxWidth, width);
    }

    return width;
}

} /* namespace Tabularasa */
