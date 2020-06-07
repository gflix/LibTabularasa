#ifndef TABULARASA_TABLE_HPP_
#define TABULARASA_TABLE_HPP_

#include <ostream>
#include <tabularasa/TableColumn.hpp>
#include <tabularasa/TableRow.hpp>

namespace Tabularasa
{

struct Table
{
    typedef std::vector<int> ColumnWidths;

    Table(void);

    ColumnWidths getColumnWidths(void) const;
    void toStream(std::ostream& stream) const;

    static std::string separatorLine(const ColumnWidths& widths, bool compact = false);
    static std::string formattedCell(
        int width,
        const TableCell& cell,
        bool compact = false,
        bool useColors = false);
    static TableCell getRowCell(const TableRow& row, const std::string& id);
    static std::string formattedHeaderRow(
        const ColumnWidths& widths,
        const TableColumns& columns,
        bool compact = false,
        bool useColors = false);
    static std::string formattedRow(
        const ColumnWidths& widths,
        const TableColumns& columns,
        const TableRow& row,
        bool compact = false,
        bool useColors = false);
    static int getColumnWidth(const TableColumn& column, const TableRows& rows);

    TableColumns columns;
    TableRows rows;
    bool compact;
    bool useColors;
};

} /* namespace Tabularasa */

#endif /* TABULARASA_TABLE_HPP_ */
