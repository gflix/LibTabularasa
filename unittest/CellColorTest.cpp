#include <gtest/gtest.h>
#include <tabularasa/CellColor.hpp>

using namespace Tabularasa;

TEST(CellColorTest, defaultConstructorsGetsDefault)
{
    CellColor test;

    EXPECT_TRUE(test.isDefault());
}

TEST(CellColorTest, setForegroundColorIsNotDefault)
{
    CellColor test { AnsiColor::BLUE };

    EXPECT_FALSE(test.isDefault());
}

TEST(CellColorTest, setBackgroundColorIsNotDefault)
{
    CellColor test { AnsiColor::DEFAULT, AnsiColor::GREEN };

    EXPECT_FALSE(test.isDefault());
}

TEST(CellColorTest, boldIsNotDefault)
{
    CellColor test { AnsiColor::DEFAULT, AnsiColor::DEFAULT, true };

    EXPECT_FALSE(test.isDefault());
}

TEST(CellColorTest, throwsWhenGettingSetSequenceForDefaultColors)
{
    CellColor test;

    EXPECT_THROW(test.setSequence(), std::runtime_error);
}

TEST(CellColorTest, getsSetSequenceForForegroundColor)
{
    CellColor test { AnsiColor::BLUE };
    std::string expected { "\033[34m" };

    EXPECT_EQ(expected, test.setSequence());
}

TEST(CellColorTest, getsSetSequenceForBackgroundColor)
{
    CellColor test { AnsiColor::DEFAULT, AnsiColor::YELLOW };
    std::string expected { "\033[43m" };

    EXPECT_EQ(expected, test.setSequence());
}

TEST(CellColorTest, getsSetSequenceForBold)
{
    CellColor test { AnsiColor::DEFAULT, AnsiColor::DEFAULT, true };
    std::string expected { "\033[1m" };

    EXPECT_EQ(expected, test.setSequence());
}

TEST(CellColorTest, getsSetSequenceForColorCombinationsI)
{
    CellColor test { AnsiColor::BLACK, AnsiColor::GREEN };
    std::string expected { "\033[30;42m" };

    EXPECT_EQ(expected, test.setSequence());
}

TEST(CellColorTest, getsSetSequenceForColorCombinationsII)
{
    CellColor test { AnsiColor::WHITE, AnsiColor::RED, true };
    std::string expected { "\033[37;41;1m" };

    EXPECT_EQ(expected, test.setSequence());
}

TEST(CellColorTest, getsResetSequence)
{
    std::string expected { "\033[0m" };

    EXPECT_EQ(expected, CellColor::resetSequence());
}
