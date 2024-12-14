/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#ifndef LIBDWG_DIMENSIONSTYLE_H
#define LIBDWG_DIMENSIONSTYLE_H

#include <dwg/tables/TableEntry.h>

namespace dwg {
namespace tables {

/// Represents the dimension text background color.
enum DimensionTextBackgroundFillMode : short
{
    /// No background color is used.
    NoBackground,
    /// In this mode the drawing background color is used.
    DrawingBackgroundColor,
    /// This mode is used as the dimension text background.
    DimensionTextBackgroundColor,
};

/// Controls the vertical placement of dimension text in relation to the dimension line.
enum DimensionTextHorizontalAlignment : unsigned char
{
    /// Centers the dimension text along the dimension line between the
    /// extension lines.
    Centered = 0,
    /// Left-justifies the text with the first extension line along the
    /// dimension line.
    Left = 1,
    /// Right-justifies the text with the second extension line along the
    /// dimension line.
    Right = 2,
    /// Positions the text over or along the first extension line.
    OverFirstExtLine = 3,
    /// Positions the text over or along the second extension line.
    OverSecondExtLine = 4
};

/// Controls the placement of dimension text.
enum DimensionTextVerticalAlignment
{
    /// Centers the dimension text between the two parts of the dimension line.
    Centered = 0,
    /// Places the dimension text above the dimension line except when the
    /// dimension line is not horizontal and text inside the extension lines is
    /// forced horizontal
    /// (<see cref="DimensionStyle.TextInsideHorizontal"/> = true). The distance
    /// from the dimension line to the baseline of the lowest line of text is
    /// the current <see cref="DimensionStyle.DimensionLineGap" /> value.
    Above = 1,
    /// Places the dimension text on the side of the dimension line farthest
    /// away from the first defining point.
    Outside = 2,
    /// Places the dimension text to conform to a Japanese Industrial Standards
    /// (JIS) representation.
    JIS = 3,
    /// Places the dimension text under the dimension line.
    Below = 4
};

/// Controls the arc length symbol position in an arc length dimension.
enum ArcLengthSymbolPosition : short
{
    /// Before the dimension text (default).
    BeforeDimensionText,
    /// Above the dimension text.
    AboveDimensionText,
    /// Don't display the arc length symbol.
    None,
};


/// Represents the fraction format when the linear unit format is set to
/// architectural or fractional.
enum FractionFormat : short
{
    /// Horizontal stacking.
    Horizontal,
    /// Diagonal stacking.
    Diagonal,
    /// Not stacked.
    None,
};


/// How dimension text and arrows are arranged when space is not sufficient to
/// place both within the extension lines.
enum TextArrowFitType : unsigned char
{
    /// Places both text and arrows outside extension lines
    Both = 0,
    /// Moves arrows first, then text
    ArrowsFirst = 1,
    /// Moves text first, then arrows
    TextFirst = 2,
    /// Moves either text or arrows, whichever fits best
    BestFit = 3
};


/// Represents the text direction (left-to-right or right-to-left).
enum TextDirection : unsigned char
{
    /// Display text left-to-right.</summary>
    LeftToRight = 0,
    /// Display text right-to-left.</summary>
    RightToLeft = 1,
};


/// Text movement rules.
enum TextMovement : short
{
    /// Moves the dimension line with dimension text.
    MoveLineWithText,
    /// Adds a leader when dimension text is moved.
    AddLeaderWhenTextMoved,
    /// Allows text to be moved freely without a leader.
    FreeTextPosition,
};

/// Tolerance alignment.
enum ToleranceAlignment : unsigned char
{
    /// Aligns the tolerance text with the bottom of the main dimension text.
    Bottom = 0,
    /// Aligns the tolerance text with the middle of the main dimension text.
    Middle = 1,
    /// Aligns the tolerance text with the top of the main dimension text.
    Top = 2
};

/// Represents supression of zeros in displaying decimal numbers.
enum ZeroHandling : unsigned char
{
    /// Suppress zero feet and exactly zero inches.
    SuppressZeroFeetAndInches = 0,
    /// Show zero feet and exactly zero inches.
    ShowZeroFeetAndInches = 1,
    /// Show zero feet and suppress zero inches.
    ShowZeroFeetSuppressZeroInches = 2,
    /// Suppress zero feet and show zero inches.
    SuppressZeroFeetShowZeroInches = 3,
    /// Suppress leading zeroes in decimal numbers.
    SuppressDecimalLeadingZeroes = 4,
    /// Suppress trailing zeroes in decimal numbers.
    SuppressDecimalTrailingZeroes = 8,
    /// Suppress both leading and trailing zeroes in decimal numbers
    SuppressDecimalLeadingAndTrailingZeroes = 12,
};

class DimensionStyle : TableEntry
{
};

class DimensionStylesTable : public Table<DimensionStyle>
{
};

}// namespace tables
}// namespace dwg

#endif// LIBDWG_DIMENSIONSTYLE_H