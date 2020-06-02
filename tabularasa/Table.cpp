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

} /* namespace Tabularasa */
