#ifndef TABULARASA_CELLCOLOR_HPP_
#define TABULARASA_CELLCOLOR_HPP_

#include <string>
#include <tabularasa/AnsiColor.hpp>

namespace Tabularasa
{

struct CellColor
{
    CellColor(
        AnsiColor foreground = AnsiColor::DEFAULT,
        AnsiColor background = AnsiColor::DEFAULT,
        bool bold = false
    );

    AnsiColor foreground;
    AnsiColor background;
    bool bold;

    bool isDefault(void) const;
    std::string setSequence(void) const;
    static std::string resetSequence(void);

protected:
    static const std::string escapeSequence;
};

} /* namespace Tabularasa */

#endif /* TABULARASA_CELLCOLOR_HPP_ */
