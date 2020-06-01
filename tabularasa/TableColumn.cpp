#include <tabularasa/TableColumn.hpp>

namespace Tabularasa
{

TableColumn::TableColumn(
    const std::string title,
    int minWidth):
    title(title),
    minWidth(minWidth)
{
    if (title.size() > minWidth)
    {
        this->minWidth = title.size();
    }
}

} /* namespace Tabularasa */
