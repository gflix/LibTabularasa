#ifndef TABULARASA_TABLECOLUMN_HPP_
#define TABULARASA_TABLECOLUMN_HPP_

#include <string>

namespace Tabularasa
{

struct TableColumn
{
    TableColumn(
        const std::string title = std::string(),
        int minWidth = 0);

    std::string title;
    int minWidth;
};

} /* namespace Tabularasa */

#endif /* TABULARASA_TABLECOLUMN_HPP_ */
