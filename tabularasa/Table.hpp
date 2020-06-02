#ifndef TABULARASA_TABLE_HPP_
#define TABULARASA_TABLE_HPP_

#include <tabularasa/TableColumn.hpp>
#include <tabularasa/TableRow.hpp>

namespace Tabularasa
{

struct Table
{
    typedef std::vector<int> ColumnWidths;

    Table(void);

    static std::string separatorLine(const ColumnWidths& widths, bool compact = false);

    TableColumns columns;
    TableRows rows;
};

} /* namespace Tabularasa */

#endif /* TABULARASA_TABLE_HPP_ */
