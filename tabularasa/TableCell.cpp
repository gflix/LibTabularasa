#include <tabularasa/TableCell.hpp>

namespace Tabularasa
{

TableCell::TableCell(
    const std::string& text,
    HorizontalAlignment hAlignment):
    text(text),
    hAlignment(hAlignment)
{
}

} /* namespace Tabularasa */
