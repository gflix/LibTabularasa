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
        line += '+';
        line += std::string(compact ? width : width + 2, '-');
    }
    line += '+';

    return line;
}

std::string Table::formattedCell(int width, const std::string& text, bool compact)
{
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
