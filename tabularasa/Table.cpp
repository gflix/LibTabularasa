#include <stdexcept>
#include <tabularasa/Table.hpp>

namespace Tabularasa
{

Table::Table(void):
    compact(false)
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
    stream << formattedHeaderRow(columnWidths, columns, compact) << std::endl;
    stream << separator << std::endl;
    for (auto& row: rows)
    {
        stream << formattedRow(columnWidths, columns, row, compact) << std::endl;
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

std::string Table::formattedCell(int width, const std::string& text, bool compact, HorizontalAlignment hAlignment)
{
    if (width <= 0)
    {
        throw std::domain_error("invalid column width " + std::to_string(width));
    }

    auto textLength = text.size();
    auto centerPadding = (width - textLength) / 2;
    std::string cell;

    if (textLength < width)
    {
        switch (hAlignment)
        {
            case HorizontalAlignment::LEFT:
                cell = text;
                cell += std::string(width - textLength, ' ');
                break;
            case HorizontalAlignment::CENTER:
                cell = std::string(centerPadding, ' ');
                cell += text;
                cell += std::string(width - textLength - centerPadding, ' ');
                break;
            case HorizontalAlignment::RIGHT:
                cell = std::string(width - textLength, ' ');
                cell += text;
                break;
        }
    }
    else
    {
        cell = text.substr(0, width);
    }

    if (!compact)
    {
        cell = ' ' + cell + ' ';
    }

    return cell;
}

std::string Table::getRowCell(const TableRow& row, const std::string& id)
{
    auto it = row.find(id);
    if (it != row.cend())
    {
        return it->second;
    }
    return std::string();
}

std::string Table::formattedHeaderRow(const ColumnWidths& widths, const TableColumns& columns, bool compact)
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
        line += formattedCell(*widthIt, columnIt->title, compact, columnIt->hAlignment);
    }
    line += '|';

    return line;
}

std::string Table::formattedRow(const ColumnWidths& widths, const TableColumns& columns, const TableRow& row, bool compact)
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
        line += formattedCell(*widthIt, getRowCell(row, columnIt->id), compact, columnIt->hAlignment);
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
        width = max(width, getRowCell(row, column.id).size());
    }

    if (column.maxWidth > 0)
    {
        width = min(column.maxWidth, width);
    }

    return width;
}

} /* namespace Tabularasa */
