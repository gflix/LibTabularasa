#ifndef TABULARASA_TABLECOLUMN_HPP_
#define TABULARASA_TABLECOLUMN_HPP_

#include <string>
#include <vector>
#include <tabularasa/CellColor.hpp>
#include <tabularasa/HorizontalAlignment.hpp>

namespace Tabularasa
{

struct TableColumn
{
    TableColumn(
        const std::string& id,
        const std::string& title = std::string(),
        int minWidth = 0,
        int maxWidth = 0,
        HorizontalAlignment hAlignment = HorizontalAlignment::LEFT,
        CellColor color = CellColor(AnsiColor::DEFAULT, AnsiColor::DEFAULT, true));

    std::string id;
    std::string title;
    int minWidth;
    int maxWidth;
    HorizontalAlignment hAlignment;
    CellColor color;
};

typedef std::vector<TableColumn> TableColumns;

} /* namespace Tabularasa */

#endif /* TABULARASA_TABLECOLUMN_HPP_ */
