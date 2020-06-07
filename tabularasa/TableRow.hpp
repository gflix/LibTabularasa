#ifndef TABULARASA_TABLEROW_HPP_
#define TABULARASA_TABLEROW_HPP_

#include <map>
#include <string>
#include <vector>
#include <tabularasa/TableCell.hpp>

namespace Tabularasa
{

typedef std::map<std::string, TableCell> TableRow;
typedef std::vector<TableRow> TableRows;

} /* namespace Tabularasa */

#endif /* TABULARASA_TABLEROW_HPP_ */
