#include <stdexcept>
#include <tabularasa/Table.hpp>

namespace Tabularasa
{

Table::Table(void)
{
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

std::string Table::formattedCell(int width, const std::string& text, bool compact)
{
    if (width <= 0)
    {
        throw std::domain_error("invalid column width " + std::to_string(width));
    }

    auto textLength = text.size();
    std::string cell;

    if (textLength < width)
    {
        cell = text;
        cell += std::string(width - textLength, ' ');
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
        line += formattedCell(*widthIt, columnIt->title, compact);
    }
    line += '|';

    return line;
}

} /* namespace Tabularasa */
