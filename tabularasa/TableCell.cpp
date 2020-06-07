#include <tabularasa/TableCell.hpp>

namespace Tabularasa
{

TableCell::TableCell(
    const std::string& text,
    HorizontalAlignment hAlignment,
    const CellColor& color):
    text(text),
    hAlignment(hAlignment),
    color(color)
{
}

} /* namespace Tabularasa */
