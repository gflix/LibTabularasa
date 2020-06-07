#include <stdexcept>
#include <tabularasa/TableColumn.hpp>

namespace Tabularasa
{

TableColumn::TableColumn(
    const std::string& id,
    const std::string& title,
    int minWidth,
    int maxWidth,
    HorizontalAlignment hAlignment,
    CellColor color):
    id(id),
    title(title),
    minWidth(minWidth),
    maxWidth(maxWidth),
    hAlignment(hAlignment),
    color(color)
{
    if (maxWidth > 0 && maxWidth < minWidth)
    {
        throw std::domain_error("maxWidth shall not be less than minWidth");
    }
    if (title.size() > minWidth)
    {
        this->minWidth = title.size();
    }
}

} /* namespace Tabularasa */
