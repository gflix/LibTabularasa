#ifndef TABULARASA_TABLECOLUMN_HPP_
#define TABULARASA_TABLECOLUMN_HPP_

#include <string>
#include <vector>

namespace Tabularasa
{

struct TableColumn
{
    TableColumn(
        const std::string& id,
        const std::string& title = std::string(),
        int minWidth = 0,
        int maxWidth = 0);

    std::string id;
    std::string title;
    int minWidth;
    int maxWidth;
};

typedef std::vector<TableColumn> TableColumns;

} /* namespace Tabularasa */

#endif /* TABULARASA_TABLECOLUMN_HPP_ */
