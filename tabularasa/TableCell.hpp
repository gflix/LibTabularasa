#ifndef TABULARASA_TABLECELL_HPP_
#define TABULARASA_TABLECELL_HPP_

#include <string>
#include <tabularasa/HorizontalAlignment.hpp>

namespace Tabularasa
{

struct TableCell
{
    TableCell(
        const std::string& text = std::string(),
        HorizontalAlignment hAlignment = HorizontalAlignment::DEFAULT);

    std::string text;
    HorizontalAlignment hAlignment;
};

} /* namespace Tabularasa */

#endif /* TABULARASA_TABLECELL_HPP_ */
