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

} /* namespace Tabularasa */
