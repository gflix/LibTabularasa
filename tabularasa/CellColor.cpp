#include <stdexcept>
#include <vector>
#include <tabularasa/CellColor.hpp>

namespace Tabularasa
{

const std::string CellColor::escapeSequence = "\033[";

CellColor::CellColor(
    AnsiColor foreground,
    AnsiColor background,
    bool bold):
    foreground(foreground),
    background(background),
    bold(bold)
{
}

bool CellColor::isDefault(void) const
{
    return
        foreground == AnsiColor::DEFAULT &&
        background == AnsiColor::DEFAULT &&
        !bold;
}

std::string CellColor::setSequence(void) const
{
    if (isDefault())
    {
        throw std::runtime_error("no ANSI sequence available when colors are set to default");
    }

    std::vector<int> codes;
    if (foreground != AnsiColor::DEFAULT)
    {
        codes.push_back(static_cast<int>(foreground) + 30);
    }
    if (background != AnsiColor::DEFAULT)
    {
        codes.push_back(static_cast<int>(background) + 40);
    }
    if (bold)
    {
        codes.push_back(1);
    }

    std::string sequence;
    for (auto it = codes.cbegin(); it != codes.cend(); ++it)
    {
        if (it != codes.cbegin())
            sequence += ';';

        sequence += std::to_string(*it);
    }
    return escapeSequence + sequence + "m";
}

std::string CellColor::resetSequence(void)
{
    return escapeSequence + "0m";
}

} /* namespace Tabularasa */
