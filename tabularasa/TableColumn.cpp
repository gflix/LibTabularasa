#include <tabularasa/TableColumn.hpp>

namespace Tabularasa
{

TableColumn::TableColumn(
    const std::string& id,
    const std::string& title,
    int minWidth):
    id(id),
    title(title),
    minWidth(minWidth)
{
    if (title.size() > minWidth)
    {
        this->minWidth = title.size();
    }
}

} /* namespace Tabularasa */
