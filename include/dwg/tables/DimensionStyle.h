

namespace dwg {
namespace Tables {

/// Represents the dimension text background color.
/// </summary>
enum DimensionTextBackgroundFillMode : short {
    /// <summary>
    /// No background color is used.
    /// </summary>
    NoBackground,
    /// <summary>
    /// In this mode the drawing background color is used.
    /// </summary>
    DrawingBackgroundColor,
    /// <summary>
    /// This mode is used as the dimension text background.
    /// </summary>
    DimensionTextBackgroundColor,
};

/// Controls the vertical placement of dimension text in relation to the
/// dimension line.
/// </summary>
enum DimensionTextHorizontalAlignment : unsigned char {
    /// <summary>
    /// Centers the dimension text along the dimension line between the
    /// extension lines.
    /// </summary>
    Centered = 0,

    /// <summary>
    /// Left-justifies the text with the first extension line along the
    /// dimension line.
    /// </summary>
    Left = 1,

    /// <summary>
    /// Right-justifies the text with the second extension line along the
    /// dimension line.
    /// </summary>
    Right = 2,

    /// <summary>
    /// Positions the text over or along the first extension line.
    /// </summary>
    OverFirstExtLine = 3,

    /// <summary>
    /// Positions the text over or along the second extension line.
    /// </summary>
    OverSecondExtLine = 4
};

/// Controls the placement of dimension text.
/// </summary>
enum DimensionTextVerticalAlignment {
    /// <summary>
    /// Centers the dimension text between the two parts of the dimension line.
    /// </summary>
    Centered = 0,

    /// <summary>
    /// Places the dimension text above the dimension line except when the
    /// dimension line is not horizontal and text inside the extension lines is
    /// forced horizontal
    /// (<see cref="DimensionStyle.TextInsideHorizontal"/> = true). The distance
    /// from the dimension line to the baseline of the lowest line of text is
    /// the current <see cref="DimensionStyle.DimensionLineGap" /> value.
    /// </summary>
    Above = 1,

    /// <summary>
    /// Places the dimension text on the side of the dimension line farthest
    /// away from the first defining point.
    /// </summary>
    Outside = 2,

    /// <summary>
    /// Places the dimension text to conform to a Japanese Industrial Standards
    /// (JIS) representation.
    /// </summary>
    JIS = 3,

    /// <summary>
    /// Places the dimension text under the dimension line.
    /// </summary>
    Below = 4
};

/// Controls the arc length symbol position in an arc length dimension.
public
enum ArcLengthSymbolPosition : short {
    /// <summary>
    /// Before the dimension text (default).
    /// </summary>
    BeforeDimensionText,
    /// <summary>
    /// Above the dimension text.
    /// </summary>
    AboveDimensionText,
    /// <summary>
    /// Don't display the arc length symbol.
    /// </summary>
    None,
};

/// <summary>
/// Represents the fraction format when the linear unit format is set to
/// architectural or fractional.
/// </summary>
enum FractionFormat : short {
    /// <summary>
    /// Horizontal stacking.
    /// </summary>
    Horizontal,
    /// <summary>
    /// Diagonal stacking.
    /// </summary>
    Diagonal,
    /// <summary>
    /// Not stacked.
    /// </summary>
    None,
};

/// <summary>
/// How dimension text and arrows are arranged when space is not sufficient to
/// place both within the extension lines.
/// </summary>
enum TextArrowFitType : unsigned char {
    /// <summary>
    /// Places both text and arrows outside extension lines
    /// </summary>
    Both = 0,
    /// <summary>
    /// Moves arrows first, then text
    /// </summary>
    ArrowsFirst = 1,
    /// <summary>
    /// Moves text first, then arrows
    /// </summary>
    TextFirst = 2,
    /// <summary>
    /// Moves either text or arrows, whichever fits best
    /// </summary>
    BestFit = 3
};

/// <summary>
/// Represents the text direction (left-to-right or right-to-left).
/// </summary>
enum TextDirection : unsigned char
	{
		/// <summary>Display text left-to-right.</summary>
		LeftToRight = 0,
		/// <summary>Display text right-to-left.</summary>
		RightToLeft = 1,
	}

	/// <summary>
	/// Text movement rules.
	/// </summary>
	enum TextMovement : short
	{
		/// <summary>
		/// Moves the dimension line with dimension text.
		/// </summary>
		MoveLineWithText,
		/// <summary>
		/// Adds a leader when dimension text is moved.
		/// </summary>
		AddLeaderWhenTextMoved,
		/// <summary>
		/// Allows text to be moved freely without a leader.
		/// </summary>
		FreeTextPosition,
	}

	/// <summary>
	/// Tolerance alignment.
	/// </summary>
	enum ToleranceAlignment : unsigned char
	{
		/// <summary>
		/// Aligns the tolerance text with the bottom of the main dimension text.
		/// </summary>
		Bottom = 0,

		/// <summary>
		/// Aligns the tolerance text with the middle of the main dimension text.
		/// </summary>
		Middle = 1,

		/// <summary>
		/// Aligns the tolerance text with the top of the main dimension text.
		/// </summary>
		Top = 2
	};

/// <summary>
/// Represents supression of zeros in displaying decimal numbers.
/// </summary>
enum ZeroHandling : unsigned char {
    /// <summary>
    /// Suppress zero feet and exactly zero inches.
    /// </summary>
    SuppressZeroFeetAndInches = 0,
    /// <summary>
    /// Show zero feet and exactly zero inches.
    /// </summary>
    ShowZeroFeetAndInches = 1,
    /// <summary>
    /// Show zero feet and suppress zero inches.
    /// </summary>
    ShowZeroFeetSuppressZeroInches = 2,
    /// <summary>
    /// Suppress zero feet and show zero inches.
    /// </summary>
    SuppressZeroFeetShowZeroInches = 3,
    /// <summary>
    /// Suppress leading zeroes in decimal numbers.
    /// </summary>
    SuppressDecimalLeadingZeroes = 4,
    /// <summary>
    /// Suppress trailing zeroes in decimal numbers.
    /// </summary>
    SuppressDecimalTrailingZeroes = 8,
    /// <summary>
    /// Suppress both leading and trailing zeroes in decimal numbers
    /// </summary>
    SuppressDecimalLeadingAndTrailingZeroes = 12,
};

class DimensionStyle : TableEntity {};

} // namespace Tables
} // namespace dwg